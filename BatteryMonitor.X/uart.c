#include <xc.h>
#include "clock.h"		// pour la d�finition de FCY
#include "uart.h"


#define ABS(x) ((x)<0 ? -(x) : (x))

void uart1Config(float baudrate, uartModeType uartMode) {
	float tmp;

	if ((baudrate > 152) && (baudrate < 10E6)) {
		U1MODEbits.UARTEN = 0;				// d�sactive le p�riph�rique avant de le configurer
		U1MODE = uartMode;					// sp�cifie le mode de fonctionnement
		tmp = FCY/(16*baudrate) - 1;			// on calcule la valeur exacte � placer dans le compteur pour obtenir le baudrate d�sir�
		U1MODEbits.BRGH = 0;				// on d�cide de toujours fonctionner en high speed (cela nous limite � 152 baud minimum)
		U1BRG = (unsigned int)tmp;			// on assigne la valeur calcul�e pour le baudrate, ce qui la tronque � l'entier inf�rieur
		if (tmp-U1BRG > 0.5) {				// on v�rifie si il n'aurait pas mieux valu arrondir � l'entier sup�rieur
			U1BRG++;							// si oui, on le fait
		}
		tmp = FCY/(16*(float)(U1BRG + 1));
		if (ABS(tmp-baudrate) > baudrate/50) {
			U1MODEbits.BRGH = 1;				// on d�cide de toujours fonctionner en high speed (cela nous limite � 152 baud minimum)
			tmp = FCY/(4*baudrate) - 1;
			U1BRG = (unsigned int)tmp;			// on assigne la valeur calcul�e pour le baudrate, ce qui la tronque � l'entier inf�rieur
			if (tmp-U1BRG > 0.5) {				// on v�rifie si il n'aurait pas mieux valu arrondir � l'entier sup�rieur
				U1BRG++;							// si oui, on le fait
			}
		}
		U1MODEbits.UARTEN = 1;				// on active l'UART
		U1STAbits.UTXEN = 1;				// on active l'�mission (Attention, cela active aussi U1TXIF)
	}
}


void uart2Config(float baudrate, uartModeType uartMode) {
	float tmp;

	if ((baudrate > 152) && (baudrate < 10E6)) {
		U2MODEbits.UARTEN = 0;				// d�sactive le p�riph�rique avant de le configurer
		U2MODE = uartMode;					// sp�cifie le mode de fonctionnement
		tmp = FCY/(16*baudrate) - 1;			// on calcule la valeur exacte � placer dans le compteur pour obtenir le baudrate d�sir�
		U2MODEbits.BRGH = 0;				// on d�cide de toujours fonctionner en high speed (cela nous limite � 152 baud minimum)
		U2BRG = (unsigned int)tmp;			// on assigne la valeur calcul�e pour le baudrate, ce qui la tronque � l'entier inf�rieur
		if (tmp-U2BRG > 0.5) {				// on v�rifie si il n'aurait pas mieux valu arrondir � l'entier sup�rieur
			U2BRG++;							// si oui, on le fait
		}
		tmp = FCY/(16*(float)(U2BRG + 1));
		if (ABS(tmp-baudrate) > baudrate/50) {
			U2MODEbits.BRGH = 1;				// on d�cide de toujours fonctionner en high speed (cela nous limite � 152 baud minimum)
			tmp = FCY/(4*baudrate) - 1;
			U2BRG = (unsigned int)tmp;			// on assigne la valeur calcul�e pour le baudrate, ce qui la tronque � l'entier inf�rieur
			if (tmp-U2BRG > 0.5) {				// on v�rifie si il n'aurait pas mieux valu arrondir � l'entier sup�rieur
				U2BRG++;							// si oui, on le fait
			}
		}
		U2MODEbits.UARTEN = 1;				// on active l'UART
		U2STAbits.UTXEN = 1;				// on active l'�mission (Attention, cela active aussi U2TXIF)
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
