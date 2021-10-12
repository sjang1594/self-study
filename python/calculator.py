## Libraries
from tkinter import *
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTk, FigureCanvasTkAgg

## API request
import urllib.request

import numpy as np
import math

class Calculator:
    def __init__(self, main):
        ## Setting the title
        main.title("Simple Calculator")
        ## Setting the window size (if not specified, default size)
        main.geometry()

        self.entry_val = Entry(main, width=40, justify=RIGHT)
        self.entry_val.grid(row=0, column=0, columnspan=3)
        self.entry_val.focus_set()

        ## UI settups 
        Button(main, text="=", width=20, command=lambda:self.get_result()).grid(row=5, column=2, columnspan=2)
        Button(main, text="AC", width=10, command=lambda:self.clear_all()).grid(row=4, column=0)
        Button(main, text="<", width=10, command=lambda:self.get_last_log()).grid(row=0, column=3)
        Button(main, text="+", width=10, command=lambda:self.input_value('+')).grid(row=1, column=3)
        Button(main, text="-", width=10, command=lambda:self.input_value('-')).grid(row=2, column=3)
        Button(main, text="*", width=10, command=lambda:self.input_value('*')).grid(row=3, column=3)
        Button(main, text="/", width=10, command=lambda:self.input_value('/')).grid(row=4, column=3)
        Button(main, text=".", width=10, command=lambda:self.input_value('.')).grid(row=4, column=2)
        Button(main, text="(", width=10, command=lambda:self.input_value('(')).grid(row=5, column=0)
        Button(main, text=")", width=10, command=lambda:self.input_value(')')).grid(row=5, column=1)
        Button(main, text="7", width=10, command=lambda:self.input_value(7)).grid(row=1, column=0)
        Button(main, text="8", width=10, command=lambda:self.input_value(8)).grid(row=1, column=1)
        Button(main, text="9", width=10, command=lambda:self.input_value(9)).grid(row=1, column=2)
        Button(main, text="4", width=10, command=lambda:self.input_value(4)).grid(row=2, column=0)
        Button(main, text="5", width=10, command=lambda:self.input_value(5)).grid(row=2, column=1)
        Button(main, text="6", width=10, command=lambda:self.input_value(6)).grid(row=2, column=2)
        Button(main, text="1", width=10, command=lambda:self.input_value(1)).grid(row=3, column=0)
        Button(main, text="2", width=10, command=lambda:self.input_value(2)).grid(row=3, column=1)
        Button(main, text="3", width=10, command=lambda:self.input_value(3)).grid(row=3, column=2)
        Button(main, text="0", width=10, command=lambda:self.input_value(0)).grid(row=4, column=1)
        
        f = open("calc_log.txt", "w")
        f.close()

    def input_value(self, val):
        self.entry_val.insert("end", val)
    
    def clear_all(self):
        self.entry_val.delete(0, "end")
    
    def get_result(self):
        try:
            # return_val = eval(self.entry_val.get())
            api_url = "http://api.mathjs.org/v4/?expr="
            expr = self.entry_val.get().replace("+", "%2B")
            url = api_url + expr
            url_data = urllib.request.urlopen(url)

            return_val = url_data.read().decode('utf-8')

            f = open("calc_log.txt", "w")
            f.write(self.entry_val.get())
        except SyntaxError or NameError:
            self.entry_val.delete(0, "end")
            self.entry_val.insert(0, return_val)
        else:
            self.entry_val.delete(0, "end")
            self.entry_val.insert(0, return_val)

    def get_last_log(self):
        f = open("calc_log.txt", "r")
        read_val = f.read()
        self.entry_val.delete(0, "end")
        self.entry_val.insert(0, read_val)

# Inheritence 
class Scientific_Calculator(Calculator):
    def __init__(self, main):
        super().__init__(main)
        Button(main, text="sqrt", width=10, command=lambda:self.get_sqrt()).grid(row=5, column=0)
        Button(main, text="**", width=10, command=lambda:self.get_pow()).grid(row=5, column=1)

    def get_sqrt(self):
        try:
            return_val = eval(self.entry_val.get())
        except SyntaxError or NameError:
            self.entry_val.delete(0, "end")
            self.entry_val.insert(0, "Input Error, Press AC Button")
        else:
            calc_val = math.sqrt(return_val)
            self.entry_val.delete(0, "end")
            self.entry_val.insert(0, calc_val)
    
    def get_pow(self):
        try:
            return_val = eval(self.entry_val.get())
        except SyntaxError or NameError:
            self.entry_val.delete(0, "end")
            self.entry_val.insert(0, "Input Error, Press AC Button")
        else:
            calc_val = math.pow(return_val, 2)
            self.entry_val.delete(0, "end")
            self.entry_val.insert(0, calc_val)
    
class GraphCalculator(Scientific_Calculator):
    x = []
    y = []
    # 3 inch x 3 inch, dot per inch(dpis)
    fig = Figure(figsize=(3,3), dpi=100)
    ax = fig.add_subplot(111)
    canvas = None

    def get_sqrt(self):
        super().get_sqrt()
        for t in np.linspace(0, 100, 100):
            self.x.append(t)
            self.y.append(math.sqrt(t))
        
        self.ax.plot(self.x, self.y)
        self.canvas = FigureCanvasTkAgg(self.fig, main)
        self.canvas.get_tk_widget().grid(row=6, column=0, columnspan=4)
    
    def get_pow(self):
        super().get_pow()
        for t in np.linspace(0, 100, 100):
            self.x.append(t)
            self.y.append(math.pow(t,2))
        
        self.ax.plot(self.x, self.y)
        self.canvas = FigureCanvasTkAgg(self.fig, main)
        self.canvas.get_tk_widget().grid(row=6, column=0, columnspan=4)

    
## Main
if __name__ == "__main__":
    main = Tk()
    calc = GraphCalculator(main)
    main.mainloop()