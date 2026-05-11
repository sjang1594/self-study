import torch
import numpy as np

def collocation_points(*args, sampling=None):
    grids = torch.meshgrid(*args, indexing='ij')
    coordinates = torch.stack(grids, dim=len(args)).reshape(-1, len(args))

    if sampling:
        coordinates_t0 = coordinates[coordinates[:, 0] == coordinates[0, 0]]
        # coordinates_te = coordinates[coordinates[:, 0] == coordinates[-1,0]]

        coordinates_sub = coordinates[
            ((coordinates[:, 0] != coordinates[0, 0]) & (coordinates[:, 0] != coordinates[-1, 0]))]

        coordinates = coordinates_t0  # torch.vstack([coordinates_t0,coordinates_te])

        ninstances = int(len(coordinates_sub) / sampling[1])
        # print(len(coordinates_te),len(coordinates_t0),ninstances*sampling[1])
        for i in range(sampling[1]):
            idx = np.random.randint(low=0, high=ninstances, size=int(sampling[0] * ninstances))
            coordinates = torch.vstack([coordinates, coordinates_sub[i * ninstances:(i + 1) * ninstances][idx]])

    return coordinates

def relative_l2_error(u, w):
    zl2 = np.sqrt(np.sum((u - w) ** 2, axis=1))
    ul2 = np.sqrt(np.sum(u ** 2, axis=1))
    return zl2 / ul2


class TensorData(torch.utils.data.Dataset):
    def __init__(self, cdata):
        self.cdata = cdata
        self.len = len(cdata)

    def __getitem__(self, index):
        return self.cdata[index]

    def __len__(self):
        return self.len


def dataloader(cdata, batch_size=10000):
    return torch.utils.data.DataLoader(TensorData(cdata), batch_size=batch_size, shuffle=True)


def fwd_gradients(obj, x):
    dummy = torch.ones_like(obj)
    derivative = torch.autograd.grad(obj, x, dummy, create_graph=True)[0]
    return derivative


def population_growth(u, t):
    u_t = fwd_gradients(u, t)
    e = u_t - 0.005 * (100 * u - u ** 2)
    return e


def harmonic_oscillator(u, t):
    u_t = fwd_gradients(u, t)
    u_tt = fwd_gradients(u_t, t)
    e = u_tt + 2 * u_t + 101 * u
    return e


def burgers_equation(u, tx):
    u_tx = fwd_gradients(u, tx)
    u_t = u_tx[:, 0:1]
    u_x = u_tx[:, 1:2]
    u_xx = fwd_gradients(u_x, tx)[:, 1:2]
    e = u_t + u * u_x - (0.01 / torch.pi) * u_xx
    return e


def ac_equation(u, tx):
    u_tx = fwd_gradients(u, tx)
    u_t = u_tx[:, 0:1]
    u_x = u_tx[:, 1:2]
    u_xx = fwd_gradients(u_x, tx)[:, 1:2]
    e = u_t - 0.0001 * u_xx + 5 * u ** 3 - 5 * u
    return e


def heat_equation(u, txy):
    u_txy = fwd_gradients(u, txy)
    u_t = u_txy[:, 0:1]
    u_x = u_txy[:, 1:2]
    u_y = u_txy[:, 2:3]
    u_xx = fwd_gradients(u_x, txy)[:, 1:2]
    u_yy = fwd_gradients(u_y, txy)[:, 2:3]
    e = u_t - 0.001 * (u_xx + u_yy)
    return e

# test code
if (__name__ == '__main__'):
    nt = 10
    nx = 16
    t = torch.linspace(0, 1, nt)
    x = torch.linspace(-1, 1, nx)

    cdata = collocation_points(t, x)
    print(cdata.shape)

    sampling = (0.5, 10)  # (sample_rate, number of subdomains)
    cdata = collocation_points(t, x, sampling=sampling)
    print(cdata.shape)