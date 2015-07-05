# -*- coding: ISO-8859-1 -*-
from gui import Gui
from batteryMonitor import BatMon
import time, pickle
from threading import Thread, Lock


class BatMonTh(Thread):
    
    def __init__(self):
        Thread.__init__(self)
        self.count = 0
        self.voltage = 0
        self.state = "idle"
        self.batNb = int(input("Entrez le numéro de la batterie :"))
        self.fileName = ""
        self.com = BatMon()
        self.com.setPort('COM12')
        self.verrou = Lock()
        self.gui = Gui(self.verrou)
        self.start()
        self.gui.mainloop()

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
                        time.sleep(0.5)
                else:
                    time.sleep(0.5)
            else:
                data = self.com.getData()
                self.voltage = data[0]
                self.state = data[1]
                self.count += 1
                if ((self.state == "discharging") and (self.count%3==0)):
                    if (self.verrou.acquire(False)):
                        self.gui.addData(self.count, self.voltage)
                        self.verrrou.release()
                    else:
                        appRunning = False
                    pickle.dump(self.count, self.file)
                    pickle.dump(self.voltage, self.file)
            if (self.verrou.acquire(False)):
                self.gui.changeVoltage(self.voltage)
                self.gui.changeState(self.state)
                self.verrou.release()
            else:
                appRunning = False
        try:
            self.file.close()
        except:
            self.fileName = ''

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
            

appTh = BatMonTh()
appTh.join()

