#include <xc.h>
#include "ADC.h"


#define SAMPLES_NB  5

void mesConfig(void) {
    adcConfig(ADC_10BIT, ADC_MANUAL, 0);
}


float mesGetVoltage(void) {
    static int idx = 0, filtOut = 0;
    static int measures[SAMPLES_NB] = {0, 0, 0, 0, 0};

    filtOut -= measures[idx];
    measures[idx] = adcManualConversion();
    filtOut += measures[idx];
    idx++;
    if (idx >= SAMPLES_NB) {
        idx = 0;
    }
    return (3.014*filtOut*(3.3 / 1024)/SAMPLES_NB); // diviseur résistif 20k/10k
}

