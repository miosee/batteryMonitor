# -*- coding: ISO-8859-1 -*-
import numpy
from matplotlib import pyplot
from batteryMonitor import BatMon

batMon = BatMon()
batMon.setPort('COM12')
if (not(batMon.connect())):
    print('Impossible de se connecter au dispositif')
elif (not(batMon.getId())):
    print('Connecté au port, mais le dispositif ne répond pas')
else:
    print("Connecté au dispositif")
    tmp = batMon.getData()
    while (tmp[1] != 2):
        tmp = batMon.getData()
        print(tmp)
    print("Batterie détectée, la décharge commence")
    # crée le dictionnaire pour stocker les données
    data = {}
    count = 0
    data[count] = tmp
    voltage = [tmp[0]]
    while (tmp[1] != 1):
        tmp = batMon.getData()
        data[count] = tmp
        voltage.append(tmp[0])
        count = count+1
        print(tmp)

    time = numpy.linspace(0,count,count+1)
    pyplot.plot(time, voltage)
    pyplot.show()
    
