/**
 ******************************************************************************
 * @file	gpio_api.h
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion des ADC (convertisseurs analogique /
 * 			numérique) et des DAC (convertisseurs numérique / analogique).
 *
 * @todo	12/11/2024 : à compléter pour la compatibilité avec d'autres cartes
 *			que la NBoard.
 *
 ******************************************************************************
 */

#ifndef INC_ADC_DAC_API_H_
#define INC_ADC_DAC_API_H_

/******************* PROTOTYPES DE FONCTIONS *********************************/

/* Fonctions initialisation entrée/sortie analogique *************************/
void ADC_input(uint8_t pin);
void DAC_output(uint8_t pin);

#endif /* INC_ADC_DAC_API_H_ */
