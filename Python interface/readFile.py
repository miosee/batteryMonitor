import pickle

batNb = 1
fileNb = 1
try:
    fileName = "Bat%02i-%03i.BDi" % (batNb, fileNb)
    myFile = open(fileName,'rb')
    eof = False
    while not(eof):
        try:
            print("%f, %f" % (pickle.load(myFile), pickle.load(myFile)))
        except:
            eof = True
    myFile.close()
except:
    print("Le fichier n'existe pas!")
