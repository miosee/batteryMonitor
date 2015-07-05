#include <xc.h>
#include "clock.h"
#include "globals.h"
#include "pps.h"
#include "uart.h"
#include <libpic30.h>


void comConfig(void) {
    // Configuration de l'UART
    ppsOutConfig(PPS_U1TX, 5);
    ppsInConfig(PPS_U1RX, 6);
    uart1Config(57600, UART_8N1_NO_HANDSHAKE);
}

unsigned int sampleCount = 0;

void resetSampleCounter(void) {
    sampleCount = 0;
}

int comSendMessage(int state, float data) {
    static char message[9] = {'B','M',0,0,'s','d','a','t','a'};//"BM00Sdata";
    char* ptr;
    int i;

    ptr = (char*)&sampleCount;
    for (i = 0; i < 2; i++) {
        message[2+i] = *(ptr+i);
    }
    sampleCount++;
    message[4] = (char)state;
    ptr = (char*)&data;
    for (i = 0; i < 4; i++) {
        message[5+i] = *(ptr+i);
    }
    uart1SendString(message, 9);
    
    __delay_ms(ACK_TIMEOUT);
    if (!uart1RxDataAvailable()) {
        return(0);
    } else if (uart1GetChar() != 'O') {
        return(0);
    } else if (!uart1RxDataAvailable()) {
        return(0);
    } else if (uart1GetChar() != 'K') {
        return(0);
    } else {
        return(1);
    }
}


char id[7] = "BatMon\n";
char expectedString[4] = "Who";

int comIsConnected(void) {
    char receivedChar = 0;
    static int i = 0;

    // on lit  ce qu'il y a dans le buffer tant qu'on n'a pas trouvé notre trame
    while (uart1RxDataAvailable() && (i < 3)) {
        receivedChar = uart1GetChar();
        if (receivedChar == expectedString[i]) {
            i++;
        } else if (receivedChar == expectedString[0]) {
            i = 1;
        } else {
            i = 0;
        }
    }
    if (i == 3) {
        i = 0;
        return (1);
    } else {
        return (0);
    }
}


void comSendId(void) {
    uart1SendString(id, 7);
}
