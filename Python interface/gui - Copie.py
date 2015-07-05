# -*- coding: ISO-8859-1 -*-
import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import tkinter as tk


class Gui(tk.Tk):
    
    def __init__(self):
        tk.Tk.__init__(self)
        self.wm_title("Battery Monitor")
        self.f = Figure(figsize=(5,4), dpi=100)
        self.p = self.f.add_subplot(111)
        self.canvas = FigureCanvasTkAgg(self.f, master=self)
        self.canvas.show()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        self.button = tk.Button(master=self, text='Quit', command=self._quit)
        self.button.pack(side=tk.BOTTOM)
        self.first = True

    def addData(self, t, v):
        if (self.first):
            self.first = False
        else:
            self.p.plot([self.old_t, t], [self.old_v, v], 'k')
            self.canvas.draw()
        self.old_t, self.old_v = t, v

    def _quit(self):
        self.quit()     # stops mainloop
        self.destroy()  # this is necessary on Windows to prevent
                        # Fatal Python Error: PyEval_RestoreThread: NULL tstate


# code de test

##import time
##
##btGui = Gui()
##time.sleep(1)
##btGui.addData(0,0)
##btGui.addData(1,1)
##time.sleep(1)
##btGui.addData(2,1)
##time.sleep(1)
##btGui.addData(3,0)
##btGui.mainloop()




