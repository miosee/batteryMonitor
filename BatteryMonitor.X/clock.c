/*!
 * @file clock.h
 * @author Kevin De Cuyper
 * @brief fonction de configuration de la PLL
 */

#include <xc.h>

// disables the JTAG to prevent conflicts with TRISA
_FICD(JTAGEN_OFF & ICS_PGD1);
_FWDT(FWDTEN_OFF) // on désactive le Watchdog
_FOSCSEL(FNOSC_FRC);
// enables clock switching and configure the primary oscillator for a 10MHz crystal
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FGS(GSS_OFF & //
	GCP_OFF & //
	GWRP_OFF); //

void pllConfig(void) {
	PLLFBD = 30; // M = 32
	CLKDIVbits.PLLPOST = 0; // N1 = 2
	CLKDIVbits.PLLPRE = 0; // N2 = 2
	// Initiate Clock Switch to Primary Oscillator with PLL
	__builtin_write_OSCCONH(3);
	__builtin_write_OSCCONL(1);
	// Wait for Clock switch to occur
	while (OSCCONbits.COSC != 0b011);
}
