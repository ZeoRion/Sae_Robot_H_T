/**
 ******************************************************************************
 * @file	nb_dac_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion du bus de 8 LED (8 sorties numériques) sur
 * 			la NBoard.
 * 			Cette bibliothèque permet de :
 *			+ écrire la valeur d'un bus de 8 sorties numériques.
 *
 *			/!\ Cette bibliothèque n'est compatible qu'avec la NBoard.
 *
 * @todo	03/10/2024 : est-ce que d'autres cartes utilisées à l'IUT ont un
 * 			bus de LED ? si oui, à compléter pour la compatibilité avec ces
 * 			autres cartes.
 *
 ******************************************************************************
 */

#include "nboard.h"

uint8_t tab_bus_pinnames[8] = { NC, NC, NC, NC, NC, NC, NC, NC };

/**
 * @brief	Configure les 8 GPIO d'un bus en sorties numériques.
 * @param	uint8_t la pin 7 à configurer en sortie numérique
 * @param	...
 * @param	uint8_t la pin 0 à configurer en sortie numérique
 * @retval
 */
void NB_8LED_output(uint8_t pin7, uint8_t pin6, uint8_t pin5, uint8_t pin4,
		uint8_t pin3, uint8_t pin2, uint8_t pin1, uint8_t pin0)
{
	tab_bus_pinnames[0] = pin0;
	GPIO_output(pin0);
	tab_bus_pinnames[1] = pin1;
	GPIO_output(pin1);
	tab_bus_pinnames[2] = pin2;
	GPIO_output(pin2);
	tab_bus_pinnames[3] = pin3;
	GPIO_output(pin3);
	tab_bus_pinnames[4] = pin4;
	GPIO_output(pin4);
	tab_bus_pinnames[5] = pin5;
	GPIO_output(pin5);
	tab_bus_pinnames[6] = pin6;
	GPIO_output(pin6);
	tab_bus_pinnames[7] = pin7;
	GPIO_output(pin7);
}

/**
 * @brief	Ecrit la valeur d'un bus de 8 sorties numériques.
 * @param	uint8_t la valeur à écrire (base 10 ou base 16)
 * @retval
 */
void NB_8LED_write(uint8_t value)
{
	uint8_t i = 0;
	for (i = 0; i < 8; i++)
	{
		if (tab_bus_pinnames[i] != NC)
		{
			/* écriture individuelle de chaque sortie numérique du bus */
			GPIO_write(tab_bus_pinnames[i], value & (1 << i));
		}
		else
		{
			/* L'écriture d'une valeur sur un bus qui n'a pas été correctement
			 * configuré (toutes les pins du bus en sortie numérique) est une
			 * erreur à gérer. */
			IHM_LCD_clear();
			IHM_LCD_printf("   no output     for led bus !!!");
			while (1);
		}
	}
}
