# -*- coding: ISO-8859-1 -*-
from mySerial import MySerial

for a in range(12,13):
    port = 'COM%i' % a
    batMon = MySerial(port)
    if (not(batMon.connect())):
        print('%s : Echec de la connexion' % port)
    else:
        print('%s Connected...' % port)
        if batMon.sendString('Who'):
            #print('Starting the handshake')
            s = batMon.getString()
            print(s)
            if s == 'BatMon':
                print('BatMon detected at %s' % port)
            else:
                print('%s : Connecté, mais pas de réponse' % port)
        else:
            print("%s : Connecté, mais impossible d'écrire sur le port" % port)
        batMon.disconnect()



# bizarre : lors de 1er tests, il restait bloqué dans l'envoi du 'Who', pour COM4
# En ajoutant des strings de debug, cela s'est débloqué en ajoutant celle du 'starting the hadshake'
# mais elle n'apparait pas dans le shell, donc le problème est bien dans le sendString()
# en commentant cette string de debug, cela fonctionne tjs
# La veille, cela fonctionnait avec un sendInt()
