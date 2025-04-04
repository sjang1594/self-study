import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.fft import fft, fftshift
from enum import Enum
import os
from dataclasses import dataclass

"""
Radar Parameter Settings
maximum range: 
range resolution
maximum velocity
carrier frequency
speed of light

bandwidth = c / (2 * range_resolution)
chirp duration = (some_scale_factor0) * range_resolution / c
slope = bandwidth / chirp_duration
maximum IF frequency = (slope * 2 * maximum range) / c
current If frequency = (slope * 2 * target_distance) / c
Number of chirps
Number of adc sampling points
end time
speed resolution = (c / carrier_frequency) / (2 * number of chirps * (chirp_duration + endtime))
sampling rate = number of adc sampling points / chirp duration

Resources
https://github.com/moodoki/radical_sdk
https://github.com/ibaiGorordo/AWR1642-Read-Data-Python-MMWAVE-SDK-2/blob/master/MATLAB%20code/readData_AWR1642.m
https://raw.githubusercontent.com/moodoki/radical_sdk/master/samples/indoor_human_rcs.cfg
https://medium.com/@itberrios6/introduction-to-radar-part-2-8a332066917e
https://www.radartutorial.eu/02.basics/Frequency%20Modulated%20Continuous%20Wave%20Radar.en.html
https://github.com/PreSenseRadar/OpenRadar/blob/master/mmwave/dsp/doppler_processing.py
chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/https://www.ti.com/lit/an/swra553a/swra553a.pdf?ts=1714172430750
"""

@dataclass
class RadarROSConfig:
    number_of_chirps: int
    number_of_samples_per_chirp: int
    number_of_antenna: int
    sampling_frequency = 2e6
    lower_frequency = 5.7e10
    bandwidth = 7e9

@dataclass
class RadarAnsysConfig:
    number_of_chirps: int
    number_of_samples_per_chirp: int
    number_of_antenna: int
    chirp_duration = 2e-6
    bandwidth = 200e6
    center_frequency = 76.5e9

class DataFormat(Enum):
    ANSYS = 1
    ROS = 2

def parse_single_radar_data(file_path, dataFormat:DataFormat=DataFormat.ROS):
    try:
        if(dataFormat == DataFormat.ROS):
            data_df = pd.read_csv(file_path)
            frame_number = 189

            # one frame data
            frame_data = data_df['.data'].iloc[frame_number]
            if len(frame_data) == 0:
                raise Exception("No data found in the file")

            parsed_from_data = np.fromstring(frame_data.strip('()'), sep=',')
            radarParam = RadarROSConfig(4, 150, 1)
            return parsed_from_data, radarParam
        else:
            # read first line from the text
            with open(file_path, 'r') as f:
                # Better to keep this in dict
                config_data = f.readline().split(" ")
                num_rx = int(config_data[1]) # for the receiver
                num_chirps = int(config_data[2])
                num_samples_per_chirp = int(config_data[3])
                center_cpi = int(config_data[4])
                data = [float(line.strip()) for line in f]
                if len(data) < num_chirps * num_samples_per_chirp:
                    raise Exception("Data is not enough for the given chirps and samples")
                radarParam = RadarAnsysConfig(num_chirps, num_samples_per_chirp, num_rx)
            return np.array(data[:num_chirps*num_samples_per_chirp]), radarParam
    except Exception as e:
        print(e)
        return np.array([]), None

def freq_to_range(f, slope):
    """Convert frequency to range"""
    c = 299792458
    return f * c/( 2 * slope )

def process_range(data, num_samples_per_chirp, sampling_frequency, bandwidth):
    chirp_duration = num_samples_per_chirp / sampling_frequency
    """data => chirp0 samples"""
    chirp_fft  = fft(data, n=num_samples_per_chirp)
    # frequencies = np.arange(0, num_samples_per_chirp//2) * sampling_frequency/num_samples_per_chirp
    frequencies = np.fft.fftfreq(num_samples_per_chirp, d=1/sampling_frequency)
    frequencies = frequencies[:num_samples_per_chirp // 2]
    chirp_fft = chirp_fft[:num_samples_per_chirp // 2]
    slope = bandwidth / chirp_duration
    ranges = freq_to_range(frequencies, slope)
    plt.figure(figsize=(15, 5))
    plt.plot(ranges, 10 * np.log10(np.abs(chirp_fft)))
    plt.plot(ranges, 10 * np.log10(np.abs(chirp_fft)), "k+")
    plt.xlabel("Range $r$ [m]")
    plt.title("Derveid Range (FFT of chirp0)")
    plt.show()
    print(freq_to_range(frequencies, slope)[np.argmax(2.0/num_samples_per_chirp*np.abs(chirp_fft))])
    return ranges

def construct_range_doppler_map(adc_data, radarParam, dataFormat:DataFormat):
    c = 299792458
    if (dataFormat == DataFormat.ANSYS):
        number_of_chirps = radarParam.number_of_chirps
        num_adc_sample = radarParam.number_of_samples_per_chirp
        number_of_antenna = radarParam.number_of_antenna
        chirp_duration = radarParam.chirp_duration
        bandwidth = radarParam.bandwidth
        center_frequency = radarParam.center_frequency
    else:
        number_of_chirps = radarParam.number_of_chirps
        num_adc_sample = radarParam.number_of_samples_per_chirp
        number_of_antenna = radarParam.number_of_antenna
        sampling_frequency = radarParam.sampling_frequency
        lower_frequency = radarParam.lower_frequency
        bandwidth = radarParam.bandwidth
        center_frequency = lower_frequency + (bandwidth * 0.5)
         # assuming that the chirp duration is the same as the sample time
        chirp_duration = num_adc_sample / sampling_frequency

    # Reshape the (chipr number, receive_antenna number, number of samples)
    adc_data = adc_data.reshape(number_of_chirps, number_of_antenna, num_adc_sample)
    range_cube = np.fft.fft(adc_data, axis=2).transpose(2, 1, 0)
    range_doppler = np.fft.fftshift(np.fft.fft(range_cube, axis=2), axes=2)
    range_doppler_psd = 10*np.log10( np.abs(range_doppler)**2 ).sum(axis=1).T # power septral density

    _, ax = plt.subplots(1, 1, figsize=(20, 5))
    ax.imshow(range_doppler_psd)
    ax.set_title("Range Doppler Power Spectrum")
    ax.set_xlabel("Range Bins")
    ax.set_ylabel("Doppler Bins")
    plt.show()

    _, ax = plt.subplots(1, 2, figsize=(15, 5))
    ax[0].plot(range_doppler_psd.T); # plot range hits from each Doppler Bin
    ax[0].set_title("Range bins for each Doppler")
    ax[1].set_xlabel("Range Bins")
    ax[1].set_ylabel("Relative Magnitude")
    ax[1].plot(range_doppler_psd.sum(axis=0)); # Sum Range hits across Doppler Bins
    ax[1].set_title("Range bins summed across Doppler")
    ax[1].set_xlabel("Range Bins")
    ax[1].set_ylabel("Relative Magnitude")
    plt.show()

    # Coompute range resolution in meters
    print("------------------")
    print("# of Chirps : ", adc_data.shape[0])
    wavelength = c / (center_frequency)
    range_resolution = c / (2 * (bandwidth)) # meters
    max_range = c * num_adc_sample / (4.0 * bandwidth)
    doppler_resolution = wavelength / (2 * chirp_duration * number_of_chirps)
    max_doppler = number_of_chirps * doppler_resolution / 2
    max_velocity = wavelength / (4.0 * num_adc_sample / sampling_frequency)

    print("------------------")
    print("BandWidth", bandwidth)
    print("Range Resolution", range_resolution)
    print("Max Range", max_range)
    print("Doppler Resolution", doppler_resolution)
    print("Max Doppler", max_doppler)
    print("Max Velocity", max_velocity)

    ranges = np.arange(0, max_range + range_resolution, range_resolution)
    dopplers = np.arange(-max_doppler, max_doppler + doppler_resolution, doppler_resolution)

    observed_range_index = np.argmax(range_doppler_psd.sum(axis=0))  # Index of max range bin
    # observed_range = ranges[observed_range_index]
    # print("Observed Range", observed_range)

    observed_velocities_indicies = np.argmax(range_doppler_psd, axis=0)  # Index of max Doppler per range bin
    observed_velocities = dopplers[observed_velocities_indicies]
    for i in observed_velocities:
        print("Max Velocities", i)

    range_ticks = np.arange(0, len(ranges), len(ranges)//8)
    range_tick_labels = ranges[::len(ranges)//8].round(3)
    doppler_ticks = np.arange(0, len(dopplers), len(dopplers)//2)
    doppler_tick_labels = dopplers[::len(dopplers)//2][::-1].round(3)

    fig, ax = plt.subplots(1, 1, figsize=(25, 2))
    ax.imshow(range_doppler_psd)
    fig.suptitle("Range Doppler Power Spectrum")
    ax.set_xlabel("Range (meters)")
    ax.set_ylabel("Doppler Velocity (m/sec)")

    # apply Range and Doppler labels
    ax.set_xticks(range_ticks, range_tick_labels)
    ax.set_yticks(doppler_ticks, doppler_tick_labels)
    plt.show()

if __name__ == '__main__':
    # relative path for the data
    # file_path = './RadarDataROS/movingObstacle_NormalX1.csv' (ROS)
    dataFormat = DataFormat.ROS
    if (dataFormat == DataFormat.ANSYS):
        file_path = './RadarDataAnsys/radar_000000050_Mode000_adcsamples.txt' # (Ansys)
        data, radarParam = parse_single_radar_data(file_path, DataFormat.ANSYS)
    else:
        file_path = './RadarDataROS/scenario_5.csv' # (ROS)
        data, radarParam = parse_single_radar_data(file_path, DataFormat.ROS)
        process_range(data, radarParam.number_of_samples_per_chirp, radarParam.sampling_frequency, 
                      radarParam.bandwidth)
    construct_range_doppler_map(data, radarParam, dataFormat)