typedef enum adcByteNb {
    ADC_10BIT = 0,
    ADC_12BIT = 1
} adcBitNbMode;

typedef enum {
    ADC_MANUAL = 0,
    ADC_TIMER3 = 2
} adcTriggerModeType;


void adcConfig(adcBitNbMode bitNb, adcTriggerModeType triggerMode, int channel);
int adcManualConversion(void);
int adcRead(void);
