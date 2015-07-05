

myFile = open("Bat01-000.BDi",'w')

for count in range(10):
    data = count*2
    myFile.write("%f %f\n" % (count, data))
myFile.close()

myFile = open("Bat01-000.BDi",'r')
myStr = myFile.readline()
print(myStr)
tmp = myStr.split()
t,v = float(tmp[0]), float(tmp[1])
print(t)
print(v)
myFile.close()
