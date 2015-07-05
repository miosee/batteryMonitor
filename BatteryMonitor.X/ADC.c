#include <xc.h>
#include "clock.h"
#include "adc.h"

#define F_ADC_MAX   13000000    // 1/75ns nominalement, on prend une marge

void adcConfig(adcBitNbMode bitNb, adcTriggerModeType triggerMode, int channel) {
	//! ADC1 is disabled to be configured
	AD1CON1bits.ADON = 0;
	//! ADC1 will be used in 10bit mode
	AD1CON1bits.AD12B = bitNb;
	AD1CON3bits.ADCS = FCY/F_ADC_MAX + 1;
	//! AN0 is the positive input of  the CH0 S/H amplifier
	AD1CHS0bits.CH0SA = channel;
	//! Automatic sampling is enabled
	AD1CON1bits.ASAM = 1;
	//! Automatic sampling on TIMER3
	AD1CON1bits.SSRC = triggerMode;
	// Interrupt flag is reset
	_AD1IF = 0;
	// Interrupt is disabled
	_AD1IE = 0;
	//! ADC1 is enabled
	AD1CON1bits.ADON = 1;
}


int adcManualConversion(void) {
    if (AD1CON1bits.SSRC != ADC_MANUAL) {
        while(1);   // cette fonction ne peut être appelée que si l'ADC est en manuel
    }
    AD1CON1bits.SAMP = 0;
    while(!AD1CON1bits.DONE);
    return(ADC1BUF0);
}


int adcRead(void) {
	return(ADC1BUF0);
}