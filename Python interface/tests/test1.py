import numpy
from matplotlib import pyplot
from mySerial import MySerial

batMon = MySerial('COM12')
if (not(batMon.connect())):
    print('Echec de la connexion')
else:
    sampleNb = 100                  # Nombre d'échantillons
    batMon.sendInt(sampleNb)
    #data = numpy.zeros((sampleNb,1), dtype='int16')
	data = numpy.zeros(sampleNb)
    for a in range(sampleNb):
        data[a] = batMon.getFloat()
    batMon.disconnect()

    endTime = sampleNb*0.1    #Durée de l'acquisition, en s
    time = numpy.linspace(0,endTime,sampleNb)
    pyplot.plot(time, data)
    pyplot.show()
