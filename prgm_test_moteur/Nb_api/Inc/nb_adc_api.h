/**
 ******************************************************************************
 * @file	nb_adc_api.h
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion de l'ADC (convertisseur analogique /
 * 			numérique) sur la NBoard.
 *
 * @todo	03/10/2024 : à compléter pour la compatibilité avec d'autres cartes
 *			que la NBoard.
 *
 ******************************************************************************
 */

#ifndef INC_NB_ADC_API_H_
#define INC_NB_ADC_API_H_

/******************* PROTOTYPES DE FONCTIONS *********************************/

/* Fonction configuration mux analogique *************************************/
void NB_ADC_MUX_select(uint8_t value);
/* Fonction initialisation entrée analogique *********************************/
void NB_ADC_input(uint8_t pin);
/* Fonction lecture entrée analogique ****************************************/
uint16_t NB_ADC_read(uint8_t pin);

#endif /* INC_NB_ADC_API_H_ */
