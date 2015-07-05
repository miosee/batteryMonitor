/*
 * Project: BatteryMonitor
 * File:   main.c
 * Author: M. Osée
 *
 * Creation:          16/06/2015
 */


#include <xc.h>
#include "clock.h"
#include "globals.h"
#include "timers.h"
#include "measure.h"
#include "communication.h"
//#include <stdio.h>



/////////////////////////////////////////////////
// FUNCTIONS PROTOTYPES
/////////////////////////////////////////////////
// configure la sortie digitale pour le controle de la charge
void loadConfig(void);
void loadEnable(void);
void loadDisable(void);


/////////////////////////////////////////////////
// MAIN FUNCTION
/////////////////////////////////////////////////

typedef enum {
    IDLE = 0,
    CONNECTED = 1,
    DISCHARGING = 2,
    DISCHARGED = 3
} stateType;


int main(void) {
    float voltage;
    stateType state = IDLE;

    //  Initialisations
    ///////////////////
    pllConfig();
    // Configuration de la LED
    _TRISB2 = 0;
    AD1PCFGLbits.PCFG4 = 1;
    LED0 = 0;
    _TRISB15 = 0;
    LED1 = 0;
    // configuration de la patte de commande de la charge
    loadConfig();
    loadDisable();
    comConfig();
    // Configuration de la mesure de tension
    mesConfig();
    timerConfig32(TIMER_2_3, SAMPLE_PERIOD);
    timerStart(TIMER_2_3);

    //  BOUCLE PRINCIPALE
    /////////////////////
    while (1) {
        while(!_T3IF);
        _T3IF = 0;
        voltage = mesGetVoltage();
        switch (state) {
            case IDLE:
                LED0 = 0;
                LED1 = 0;
                if (comIsConnected()) {
                    comSendId();
                    resetSampleCounter();
                    state = CONNECTED;
                }
                break;
            case CONNECTED:
                LED0 = 1;
                if (voltage > FULL_LEVEL) {
                    loadEnable();
                    state = DISCHARGING;
                }
                break;
            case DISCHARGING:
                LED1 = !LED1;
                if (voltage < LOW_LEVEL) {
                    loadDisable();
                    state = DISCHARGED;
                }
                break;
            case DISCHARGED:
                LED1 = 1;
                if (voltage < NO_BAT_LEVEL) {
                    state = CONNECTED;
                }
                break;
            default:
                break;
        }
        if (state!=IDLE) {
            if (!comSendMessage(state, voltage)) {
                loadDisable();
                state = IDLE;
            }
        }
    }
    return (0);
}


void loadConfig(void) {
    LATBbits.LATB12 = 0;
    TRISBbits.TRISB12 = 0;
}


void loadEnable(void) {
    LATBbits.LATB12 = 1;
}


void loadDisable(void) {
    LATBbits.LATB12 = 0;
}
