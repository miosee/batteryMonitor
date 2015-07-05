/*!
 * @file clock.h
 * @author Kevin De Cuyper
 * @brief Header file pour la configuration de la PLL
 */

#ifndef CLOCK_H
#define	CLOCK_H

//! Définition de la fréquence d'horloge
#define FCY (40000000)

/**
 * @brief Configuration de la PLL interne � 40MHz 
 */
void pllConfig(void);

#endif	/* CLOCK_H */

