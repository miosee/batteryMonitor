#include <xc.h>
#include "clock.h"		// pour la définition de FCY
#include "uart.h"


#define ABS(x) ((x)<0 ? -(x) : (x))

void uart1Config(float baudrate, uartModeType uartMode) {
	float tmp;

	if ((baudrate > 152) && (baudrate < 10E6)) {
		U1MODEbits.UARTEN = 0;				// désactive le périphérique avant de le configurer
		U1MODE = uartMode;					// spécifie le mode de fonctionnement
		tmp = FCY/(16*baudrate) - 1;			// on calcule la valeur exacte à placer dans le compteur pour obtenir le baudrate désiré
		U1MODEbits.BRGH = 0;				// on décide de toujours fonctionner en high speed (cela nous limite à 152 baud minimum)
		U1BRG = (unsigned int)tmp;			// on assigne la valeur calculée pour le baudrate, ce qui la tronque à l'entier inférieur
		if (tmp-U1BRG > 0.5) {				// on vérifie si il n'aurait pas mieux valu arrondir à l'entier supérieur
			U1BRG++;							// si oui, on le fait
		}
		tmp = FCY/(16*(float)(U1BRG + 1));
		if (ABS(tmp-baudrate) > baudrate/50) {
			U1MODEbits.BRGH = 1;				// on décide de toujours fonctionner en high speed (cela nous limite à 152 baud minimum)
			tmp = FCY/(4*baudrate) - 1;
			U1BRG = (unsigned int)tmp;			// on assigne la valeur calculée pour le baudrate, ce qui la tronque à l'entier inférieur
			if (tmp-U1BRG > 0.5) {				// on vérifie si il n'aurait pas mieux valu arrondir à l'entier supérieur
				U1BRG++;							// si oui, on le fait
			}
		}
		U1MODEbits.UARTEN = 1;				// on active l'UART
		U1STAbits.UTXEN = 1;				// on active l'émission (Attention, cela active aussi U1TXIF)
	}
}


void uart2Config(float baudrate, uartModeType uartMode) {
	float tmp;

	if ((baudrate > 152) && (baudrate < 10E6)) {
		U2MODEbits.UARTEN = 0;				// désactive le périphérique avant de le configurer
		U2MODE = uartMode;					// spécifie le mode de fonctionnement
		tmp = FCY/(16*baudrate) - 1;			// on calcule la valeur exacte à placer dans le compteur pour obtenir le baudrate désiré
		U2MODEbits.BRGH = 0;				// on décide de toujours fonctionner en high speed (cela nous limite à 152 baud minimum)
		U2BRG = (unsigned int)tmp;			// on assigne la valeur calculée pour le baudrate, ce qui la tronque à l'entier inférieur
		if (tmp-U2BRG > 0.5) {				// on vérifie si il n'aurait pas mieux valu arrondir à l'entier supérieur
			U2BRG++;							// si oui, on le fait
		}
		tmp = FCY/(16*(float)(U2BRG + 1));
		if (ABS(tmp-baudrate) > baudrate/50) {
			U2MODEbits.BRGH = 1;				// on décide de toujours fonctionner en high speed (cela nous limite à 152 baud minimum)
			tmp = FCY/(4*baudrate) - 1;
			U2BRG = (unsigned int)tmp;			// on assigne la valeur calculée pour le baudrate, ce qui la tronque à l'entier inférieur
			if (tmp-U2BRG > 0.5) {				// on vérifie si il n'aurait pas mieux valu arrondir à l'entier supérieur
				U2BRG++;							// si oui, on le fait
			}
		}
		U2MODEbits.UARTEN = 1;				// on active l'UART
		U2STAbits.UTXEN = 1;				// on active l'émission (Attention, cela active aussi U2TXIF)
	}
}


void uart1SendChar(char data) {
	while(U1STAbits.UTXBF);
	U1TXREG = data;
}
void uart2SendChar(char data) {
	while(U2STAbits.UTXBF);
	U2TXREG = data;
}


char uart1GetChar(void) {
	while(U1STAbits.URXDA == 0);
	return U1RXREG;
}
char uart2GetChar(void) {
	while(U2STAbits.URXDA == 0);
	return U2RXREG;
}


void uart1SendFloat(float data) {
    int i;
    char* ptr;

    ptr = (char*)&data;
    for (i = 0; i < 4; i++) {
        uart1SendChar(*(ptr + i));
    }
}


void uart2SendFloat(float data) {
    int i;
    char* ptr;

    ptr = (char*)&data;
    for (i = 0; i < 4; i++) {
        uart2SendChar(*(ptr + i));
    }
}


void uart1SendString(char* data, int length) {
    int i;

    for(i=0; i<length; i++) {
        uart1SendChar(data[i]);
    }
}


void uart2SendString(char* data, int length) {
    int i;

    for (i=0; i<length; i++) {
        uart2SendChar(data[i]);
    }
}
