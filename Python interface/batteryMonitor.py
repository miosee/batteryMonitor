# -*- coding: ISO-8859-1 -*-
from mySerial import MySerial

class BMdata(object):
    "données reçues du Battery Monitor"

    def __init__(self, index = 0):
        self.index = index
        self.state = 'IDLE'
        self.voltage = 0

    def getIndex(self):
        return self.index

    def setIndex(self, newIndex):
        self.index = newIndex

    def getState(self):
        return self.state
    
    def setState(self, newState):
        if (newState in ['IDLE', 'CONNECTED', 'DISCHARGING', 'DISCHARGED']):
            self.state = newState
        else:
            print("ERREUR : tentative d'assigner un état non reconnu (BMdata)")

    def getVoltage(self):
        return self.voltage

    def setVoltage(self, newVoltage):
        self.voltage = newVoltage



class BatMon(MySerial):

    def __init__(self, port='COM1'):
        "constructeur de la classe, initialise les champs"
        MySerial.__init__(self, port)
        self.serialPort.baudrate = 57600
        self.serialPort.timeout = 2
        self.dataCount = 0
        self.stateDef = {0:"idle", 1:"connected", 2:"discharging", 3:"discharged"}


    def getId(self):
        if self.sendString('Who'):
            if self.getString() == 'BatMon':
                return True
            else:
                return False
        else:
            return False   
        
    def getData(self):
        sof = self.serialPort.read(2)
        sof = sof.decode("ascii")
        data = 0
        state = "idle"
        if (sof != 'BM'):
            print('Erreur de lecture du péambule : %s' %sof)
        else:
            tmp = self.getInt()
            if (self.dataCount != tmp):
                print("Erreur de lecture de l'index : %i au lieu de %i" % (tmp, self.dataCount))
            else:
                self.dataCount = self.dataCount+1
                state = self.stateDef[self.getChar()]
                data = self.getFloat()
                self.sendString("OK")
                
        return (data, state)

    
