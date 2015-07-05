import pickle

batNb = 1
fileNb = 0
success = False
while(not(success)):
    try:
        fileName = "Bat%02i-%03i.BDi" % (batNb, fileNb)
        myFile = open(fileName,'rb')
        fileNb += 1
    except:
        success = True
print(fileName)

myFile = open(fileName,'wb')
for count in range(10):
    data = count*2
    pickle.dump(count,myFile)
    pickle.dump(data,myFile)
myFile.close()
##
##myFile = open("Bat01-000.BDi",'rb')
##for count in range(11):
##    try:
##        print("%f, %f" % (pickle.load(myFile), pickle.load(myFile)))
##    except:
##        print("fichier vide")
##myFile.close()
