# -*- coding: ISO-8859-1 -*-
from gui import Gui
from batteryMonitor import BatMon
import time, threading, pickle


class BatMonTh(threading.Thread):
    
    def __init__(self, gui, com):
        threading.Thread.__init__(self)
        self.count = 0
        self.voltage = 0
        self.state = "idle"
        self.batNb = 1
        self.fileName = ""
        self.t = self.count
        self.com = com
        self.connected = False
        self.gui = gui

    def run(self):
        appRunning = True
        while (appRunning):
            self.voltage = 0
            if (self.state == "idle"):
                if (self.com.connect()):
                    if (self.com.getId()):
                        self.count = 0
                        self.state = "connected"
                        self.file = self.createFile()
            else:
                data = self.com.getData()
                self.voltage = data[0]
                self.state = data[1]
                self.count += 1
                if ((self.state == "discharging") and (self.count%3==0)):
                    self.gui.addData(self.count, self.voltage)
                    pickle.dump(self.count, self.file)
                    pickle.dump(self.voltage, self.file)
                elif (self.state == "discharged"):
                    if not(self.file.closed):
                        self.file.close()
            try:
                self.gui.changeVoltage(self.voltage)
                self.gui.changeState(self.state)
            except:
                appRunning = False

    def createFile(self):
        fileNb = 0
        success = False
        while(not(success)):
            try:
                self.fileName = "Bat%02i-%03i.BDi" % (self.batNb, fileNb)
                open(self.fileName,'rb')
                fileNb += 1
            except:
                success = True
        newFile = open(self.fileName, 'wb')
        return newFile    
            

btCom = BatMon()
btCom.setPort('COM12')

btGui = Gui()
appTh = BatMonTh(btGui, btCom)
appTh.start()
btGui.mainloop()
appTh.join()

