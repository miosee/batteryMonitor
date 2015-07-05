/*!
 * @file uart.h
 * @author Kevin De Cuyper
 * @brief Header file pour la configuration des UART
 */

#ifndef UART_H
#define	UART_H


typedef enum {
	UART_8N1_NO_HANDSHAKE	= 0x00,
	UART_8E1_NO_HANDSHAKE	= 0x02,
	UART_8O1_NO_HANDSHAKE	= 0x04,
	UART_9N1_NO_HANDSHAKE	= 0x06,
	UART_8N2_NO_HANDSHAKE	= 0x01,
	UART_8E2_NO_HANDSHAKE	= 0x03,
	UART_8O2_NO_HANDSHAKE	= 0x05,
	UART_9N2_NO_HANDSHAKE	= 0x07,
	UART_8N1_HARD_HANDSHAKE	= 0x200,
	UART_8E1_HARD_HANDSHAKE = 0x202,
	UART_8O1_HARD_HANDSHAKE = 0x204,
	UART_9N1_HARD_HANDSHAKE = 0x206,
	UART_8N2_HARD_HANDSHAKE = 0x201,
	UART_8E2_HARD_HANDSHAKE = 0x203,
	UART_8O2_HARD_HANDSHAKE = 0x205,
	UART_9N2_HARD_HANDSHAKE = 0x207
} uartModeType;


/**
 * Configure l'UART avec le baudrate et le mode de fonctionnement voulu
 * @param baudrate : baudrate désiré, en Hz
 * @param uartMode : mode de fonctionnement désiré (cf. uartModeType)
 */
void uart1Config(float baudrate, uartModeType uartMode);
void uart2Config(float baudrate, uartModeType uartMode);

/**
 * Envoie un octet sur le port série. /!\ fonction bloquante
 * @param data: octet à envoyer
 */
void uart1SendChar(char data);
void uart2SendChar(char data);

/**
 * Lit un octet sur le port série. /!\ Fonction bloquante
 * @return : octet reçu
 */
char uart1GetChar(void);
char uart2GetChar(void);


void uart1SendFloat(float data);
void uart2SendFloat(float data);


void uart1SendString(char* data, int length);
void uart2SendString(char* data, int length);


/**
 * indique si il y a un octet à lire dans le buffer de réception
 * @return : 1 si il y a un octet à lire, 0 sinon
 */
#define uart1RxDataAvailable()  U1STAbits.URXDA
#define uart2RxDataAvailable()  U2STAbits.URXDA

/**
 * indique si le buffer d'émission est prêt à recevoir un nouvel octet à émettre
 * @return : 1 si le buffer est disponible, 0 sinon
 */
#define uart1TxReady()  (!U1STAbits.UTXBF)
#define uart2TxReady()  (!U2STAbits.UTXBF)

/**
 * Active/désactive l'ISR d'émission/réception de l'uart
 */
#define uart1TxIsrEnable()      IEC0bits.U1TXIE = 1
#define uart2TxIsrEnable()      IEC1bits.U2TXIE = 1

#define uart1TxIsrDisable()     IEC0bits.U1TXIE = 0
#define uart2TxIsrDisable()     IEC1bits.U2TXIE = 0

#define uart1RxIsrEnable()      IEC0bits.U1RXIE = 1
#define uart2RxIsrEnable()      IEC1bits.U2RXIE = 1

#define uart1RxIsrDisable()     IEC0bits.U1RXIE = 0
#define uart2RxIsrDisable()     IEC1bits.U2RXIE = 0


/*
 * Template pour les ISR des UART
 *
 * void __attribute__((interrupt, auto_psv)) _U1TXInterrupt(void) {
 *     IFS0bits.U1TXIF = 0;
 * }
 *
 * void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void) {
 *     IFS0bits.U1RXIF = 0;
 * }
 *
 *  void __attribute__((interrupt, auto_psv)) _U2TXInterrupt(void) {
 *     IFS1bits.U2TXIF = 0;
 * }
 *
 * void __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void) {
 *     IFS1bits.U2RXIF = 0;
 * }
 */

#endif	/* UART_H */

