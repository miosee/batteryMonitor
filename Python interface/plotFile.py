# -*- coding: ISO-8859-1 -*-
import pickle
from matplotlib import pyplot as mpl


batNb = int(input("Entrez le numéro de la batterie : "))
fileNb = int(input("Entrez le numéro du fichier : "))
test = True
try:
    fileName = "Bat%02i-%03i.BDi" % (batNb, fileNb)
    myFile = open(fileName,'rb')
except:
    print("""Le fichier "%s" n'existe pas!""" % fileName)
    test = False

if test:
    t,v = [],[]
    E = 0
    eof = False
    while not(eof):
        try:
            t.append(pickle.load(myFile)/60)
            v.append(pickle.load(myFile))
            E += v[len(v)-1]/15/60
        except:
            eof = True
    myFile.close()
    print("Energie dissipée : %fAh" % E)
    mpl.plot(t,v)
    mpl.xlabel("t (min")
    mpl.ylabel("Vbat (V)")
    mpl.show()
