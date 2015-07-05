# -*- coding: ISO-8859-1 -*-
from numpy import sin, pi
import time, threading

import matplotlib
matplotlib.use('TkAgg')

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
# implement the default mpl key bindings
#from matplotlib.backend_bases import key_press_handler

from matplotlib.figure import Figure

import tkinter as Tk



class DrawGraph(threading.Thread):
    
    def __init__(self):
        threading.Thread.__init__(self)
        self.count = 0
        self.voltage = [0]
        self.t = [self.count]

    def run(self):
        while (self.count < 21):
            self.count += 1
            self.voltage.append(sin(2*pi*self.count/20))
            self.t.append(self.count)
            a.plot(self.t[self.count-1:self.count+1],self.voltage[self.count-1:self.count+1], 'k')
            time.sleep(0.2)
            canvas.draw()
            

root = Tk.Tk()
root.wm_title("Embedding in TK")

f = Figure(figsize=(5,4), dpi=100)
a = f.add_subplot(111)


# a tk.DrawingArea
canvas = FigureCanvasTkAgg(f, master=root)
canvas.show()
canvas.get_tk_widget().pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)
drawDraphThread = DrawGraph()
drawDraphThread.start()

def _quit():
    root.quit()     # stops mainloop
    root.destroy()  # this is necessary on Windows to prevent
                    # Fatal Python Error: PyEval_RestoreThread: NULL tstate

button = Tk.Button(master=root, text='Quit', command=_quit)
button.pack(side=Tk.BOTTOM)



Tk.mainloop()




