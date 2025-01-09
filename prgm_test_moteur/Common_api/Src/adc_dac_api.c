/**
 ******************************************************************************
 * @file	adc_dac_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion des ADC (convertisseurs analogique /
 * 			numérique) et des DAC (convertisseurs numérique / analogique).
 *			Cette bibliothèque permet de :
 *			+ configurer une pin en entrée analogique ;
 *			+ configurer une pin en sortie analogique.
 *
 * @todo	12/11/2024 : à compléter pour la compatibilité avec d'autres cartes
 *			que la NBoard.
 *
 ******************************************************************************
 */

#include "main.h"

/* Fonction initialisation entrée/sortie analogique **************************/
void GPIO_analog(uint8_t pin);

/**
 * @brief	Configure une pin en entrée analogique.
 * @param	uint8_t	la pin à configurer en entrée analogique
 * @retval
 */
void ADC_input(uint8_t pin)
{
	GPIO_analog(pin);
}

/**
 * @brief	Configure une pin en sortie analogique.
 * @param	uint8_t	la pin à configurer en sortie analogique
 * @retval
 */
void DAC_output(uint8_t pin)
{
	GPIO_analog(pin);
}

/**
 * @brief	Configure une pin en entrée/sortie analogique.
 * @param	uint8_t	la pin à configurer en entrée/sortie analogique
 * @retval
 */
void GPIO_analog(uint8_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = 1 << (pin & 0x0F);
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init((GPIO_TypeDef*) (GPIOA_BASE + (pin >> 4) * 1024),
			&GPIO_InitStruct);
}
