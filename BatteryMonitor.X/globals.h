/* 
 * File:   globals.h
 * Author: Kevin
 *
 * Created on 26 juin 2015, 12:29
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#define SAMPLE_PERIOD   1000            // période d'échantillonnage, en ms
#define ACK_TIMEOUT     100             // Time-out ppour l'acquittement des messages
#define FULL_LEVEL      7.0             // Tension minimale d'une bbatterie considérée comme chargée
#define LOW_LEVEL       6.5             // Tension à laquelle la charge se termine
#define NO_BAT_LEVEL    1.0             // Tension en dessous de laquelle on considère qu'aucune batterie n'est connectée

#define LED0            _LATB2
#define LED1            _LATB15

#endif	/* GLOBALS_H */

