/**
 ******************************************************************************
 * @file	nb_adc_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion de l'ADC (convertisseur analogique /
 * 			numérique) sur la NBoard.
 * 			Cette bibliothèque permet de :
 *			+ lire la valeur d'une entrée analogique.
 *
 * @todo	03/10/2024 : à compléter pour la compatibilité avec d'autres cartes
 *			que la NBoard.
 *
 ******************************************************************************
 */

#include "nboard.h"

/**
 * @brief	Sélectionne l'entrée du multiplexeur analogique qui sera reliée à
 * 			l'unique entrée analogique (PB_1) de la NBoard.
 * @param	uint8_t le numéro de la voie d'entrée du multiplexeur analogique à
 * 			utiliser (0 à 7)
 * @retval
 */
void NB_ADC_MUX_select(uint8_t value)
{
	/* Le multiplexeur analogique de la NBoard est un multiplexeur 8 vers 1. */

	/* vérification de la configuration des entrées de sélection du mux =
	 * doivent être en sorties */
	if ((((GPIOA->MODER) & (0x00030000)) == 0x00010000)
			&& (((GPIOF->MODER) & 0xF) == 0x5))
	{
		if (value < 8)
		{
			/* écriture des entrées de sélection du mux = sorties numériques vues
			 * de la NBoard */
			GPIO_write(PF_0, (value >> 2) & 0x01);
			GPIO_write(PF_1, (value >> 1) & 0x01);
			GPIO_write(PA_8, (value) & 0x01);
		}
		else
		{
			/* La sélection d'une voie du multiplexeur qui n'existe pas est une
			 * erreur à gérer. */
			IHM_LCD_clear();
			IHM_LCD_printf(" MUX selection   too high !!!!!");
			while (1);
		}
	}
	else
	{
		/* La mauvaise configuration des entrées de sélection du multiplexeur
		 * est une erreur à gérer. */
		IHM_LCD_clear();
		IHM_LCD_printf(" MUX address not in output !!!!!");
		while (1);
	}
}

/**
 * @brief	Configure une pin de la NBoard en entrée analogique.
 * @param	uint8_t la pin à configurer en entrée analogique
 * @retval
 */
void NB_ADC_input(uint8_t pin)
{
	/* Sur la NBoard, la seule entrée analogique disponible est sur PB_1. */
	if (pin == PB_1)
	{
		ADC_input(pin);
	}
	else
	{
		/* La sélection d'une pin qui n'est pas prévue pour être utilisée comme
		 * entrée analogique est une erreur à gérer. */
		IHM_LCD_clear();
		IHM_LCD_printf("wrong analog pin !!!!!!!!!!!!!!");
		while (1);
	}
}

/**
 * @brief	Lit la valeur d'une entrée analogique.
 * @param	uint8_t l'entrée à lire
 * @retval	uint16_t le résultat de la conversion de la tension (grandeur
 * 			analogique) en entrée
 */
uint16_t NB_ADC_read(uint8_t pin)
{
	/* Sur la NBoard, la seule entrée analogique disponible est sur PB_1. */
	if (pin == PB_1)
	{
		/* conversion de la tension sur la voie sélectionnée préalablement
		 * (dans ce cas dans l'initialisation, donc voie 12) de l'ADC1, avec
		 * attente bloquante de la fin de conversion (sans timeout) */
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		return HAL_ADC_GetValue(&hadc1);
	}
	else
	{
		/* La sélection d'une pin qui n'est pas prévue pour être utilisée comme
		 * entrée analogique est une erreur à gérer. */
		IHM_LCD_clear();
		IHM_LCD_printf("wrong analog pin !!!!!!!!!!!!!!");
		while (1);
	}
}
