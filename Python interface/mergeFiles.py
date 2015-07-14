import pickle

batNb = int(input("Entrez le numéro de la batterie : "))
fileNb1 = int(input("Entrez le numéro du 1er fichier source : "))
fileNb2 = int(input("Entrez le numéro du 2eme fichier source : "))
fileNb3 = int(input("Entrez le numéro du fichier ddestination : "))

test = True
fileNameSrc1 = "Bat%02i-%03i.BDi" % (batNb, fileNb1)
try:
    srcFile1 = open(fileNameSrc1,'rb')
except:
    print("""Le fichier "%s" n'existe pas!""" % fileNameSrc1)
    test = False

fileNameSrc2 = "Bat%02i-%03i.BDi" % (batNb, fileNb2)
try:
    srcFile2 = open(fileNameSrc2,'rb')
except:
    print("""Le fichier "%s" n'existe pas!""" % fileNameSrc2)
    test = False

fileNameDest = "Bat%02i-%03i.BDi" % (batNb, fileNb3)
try:
    destFile = open(fileNameDest,'wb')
except:
    print("""Le fichier "%s" n'existe pas!""" % fileNameDest)
    test = False

if test:
    eof = False
    while not(eof):
        try:
            count = pickle.load(srcFile1)
            pickle.dump(count, destFile)
            pickle.dump(pickle.load(srcFile1), destFile)
        except:
            eof = True
    srcFile1.close()
    eof = False
    while not(eof):
        try:
            dummyCount = pickle.load(srcFile2)
            count += 60
            pickle.dump(count, destFile)
            pickle.dump(pickle.load(srcFile2), destFile)
        except:
            eof = True
    srcFile2.close()
    destFile.close()
