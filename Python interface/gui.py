# -*- coding: ISO-8859-1 -*-
import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import tkinter as tk
from tkinter import StringVar


class Gui(tk.Tk):
    
    def __init__(self, verrou):
        tk.Tk.__init__(self)
        self.wm_title("Battery Monitor")
        # frame contenant les infos et boutons
        self.leftFrame = tk.Frame(master=self)
        self.leftFrame.pack(side=tk.LEFT,anchor=tk.N)
        # Affichage de l'état du dispositif
        self.stateStr = StringVar()
        self.stateStr.set("initialisation")
        self.stateLbl = tk.Label(master=self.leftFrame, textvariable=self.stateStr, relief=tk.RIDGE, width=15)
        self.stateLbl.pack(padx=5,pady=5)
        #affichage de la tension batterie
        self.voltageStr = StringVar()
        self.voltageStr.set("0V")
        self.voltageLbl = tk.Label(master=self.leftFrame, textvariable=self.voltageStr, relief=tk.RIDGE, width=15)
        self.voltageLbl.pack()
        self.button = tk.Button(master=self.leftFrame, text='Quit', command=self._quit)
        self.button.pack(pady=5)
        # création du graphique
        self.f = Figure(figsize=(6,6), dpi=100)
        self.p = self.f.add_subplot(111)
        #self.p.set_title("Décharge de la batterie")
        self.p.set_xlabel("t (min)")
        self.p.set_ylabel("Tension de la batterie (V)")
        self.canvas = FigureCanvasTkAgg(self.f, master=self)
        self.canvas.show()
        self.canvas.get_tk_widget().pack(side=tk.RIGHT, fill=tk.BOTH, expand=1)
        self.first = True
        self.ended = False
        self.verrou = verrou

    def addData(self, t, v):
        if (self.first):
            self.first = False
        else:
            self.p.plot([self.old_t, t], [self.old_v, v], 'k')
            self.canvas.draw()
        self.old_t, self.old_v = t, v

    def changeState(self, newState):
        self.stateStr.set(newState)

    def changeVoltage(self, newValue):
        self.voltageStr.set("%fV" % newValue)

    def _quit(self):
        self.verrou.acquire(True)
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
##btGui.destroy()



