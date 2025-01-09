/**
 ******************************************************************************
 * @file	ihm_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * 			sur la base de la bibliothèque développée par Jacques-Olivier KLEIN
 * 			et Bruno LARNAUDIE pour la XBoard
 * @brief	Bibliothèque de gestion de l'IHM de la NBoard (passant par le bus
 * 			CAN).
 * 			Cette bibliothèque permet de :
 * 			+ écrire sur le LCD de l'IHM ;
 * 			+ commander les 10 LED du bargraph de l'IHM ;
 * 			+ lire la valeur du JOG de l'IHM ;
 * 			+ lire la valeur du codeur de l'IHM.
 *
 * @todo	03/10/2024 : à généraliser pour la compatibilité avec le cas d'une
 * 			carte IHM distante (non intégrée à la carte comme c'est le cas sur
 * 			la NBoard)
 *
 ******************************************************************************
 */

#include <stdarg.h>  // pour va_list dans IHM_LCD_printf
#include <stdio.h>   // pour vsprintf dans IHM_LCD_printf

#include "nboard.h"

#include "ident_ihm.h"

uint8_t curseur = 0;
char tab_ecran[65];

static uint8_t tab_data_tx[8];


/**
 * @brief	Positionne le curseur sur le LCD de l'IHM.
 * @param	uint8_t l'indice de la ligne (0 à 1)
 * @param	uint8_t l'indice de la colonne (0 à 15)
 * @retval
 */
void IHM_LCD_locate(uint8_t lig, uint8_t col)
{
	curseur = (lig * 16 + col) % 32;
}

/**
 * @brief	Ecrit une chaîne de caractères sur le LCD de l'IHM. Cette fonction
 * 			a les mêmes effets que la fonction printf de stdio.
 * @param	const char* le pointeur sur la chaîne de caractères à écrire
 * @retval
 */
void IHM_LCD_printf(const char *format, ...)
{
	unsigned char i, j;

	va_list arg;
	va_start(arg, format);
	curseur = curseur + vsprintf(tab_ecran + curseur % 64, format, arg);
	if (curseur > 31)
	{
		for (i = 32; i < curseur; i++)
		{
			tab_ecran[i % 32] = tab_ecran[i];
		}
		curseur = curseur % 32;
	}
	else
	{
		for (i = 0; i < 32; i++)
		{
			if (tab_ecran[i] == 0)
				tab_ecran[i] = 20;
		}
	}
	va_end(arg);
	tab_ecran[32] = '\0';
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 8; i++)
		{
			tab_data_tx[i] = tab_ecran[i + j * 8];
		}
		CAN_send_data_frame(LCD_CHAR0 + j, 8, tab_data_tx);
	}
}

/**
 * @brief	Efface le LCD de l'IHM.
 * @param
 * @retval
 */
void IHM_LCD_clear(void)
{
	uint8_t i;

	curseur = 0;
	for (i = 0; i < 32; i++)
	{
		tab_ecran[i] = 32;
	}
	CAN_send_data_frame(LCD_CLEAR, 0, 0);
}

/**
 * @brief	Commande les 10 LED du bargraph de l'IHM.
 * @param	uint16_t l'ordre d'allumage, exprimé sur les 10 bits de droite.
 * 			Le bit k doit valoir 1 pour allumer la LED k, 0 pour l'éteindre.
 * 			Exemples : 1<<9 allume la LED 9, 0x00F allume les 4 LED de droite
 * 			(sur 10), numérotées 0 à 3.
 * @retval
 */
void IHM_BAR_write(uint16_t valeur)
{
	tab_data_tx[0] = valeur >> 8;
	tab_data_tx[1] = (uint8_t) valeur;
	CAN_send_data_frame(BAR_WRITE, 2, tab_data_tx);
}

/**
 * @brief	Indique la position (parmi les 8 possibles) et l'enfoncement du
 * 			JOG de l'IHM.
 * 			Utiliser les constantes symboliques de ihm_api.h pour interpréter
 * 			la valeur renvoyée.
 * @param
 * @retval	uint8_t la position (RIGHT, LEFT, UP, DOWN + 4 combinaisons) et
 * 			l'enfoncement (PUSH) du JOG, exprimés sur 5 bits utiles.
 */
uint8_t IHM_JOG_read(void)
{
	CAN_send_remote_frame(JOG_REQ);
	while (mise_a_jour_JOG == 0)
	{
		CAN_decode_IHM();
	}
	mise_a_jour_JOG = 0;
	return JOG_valeur;
}

/**
 * @brief	Indique la rotation effectuée par le codeur incrémental de l'IHM
 * 			depuis son initialisation (= initialisation de l'IHM), exprimée en
 * 			douzièmes de tour (+ dans le sens horaire, - dans le sens
 * 			anti-horaire).
 * @param
 * @retval	int8_t la rotation du codeur incrémental en douzièmes de tour.
 * 			Exemples : +2 si le codeur a tourné de 2 crans vers la droite, -3
 * 			si le codeur a tourné de 3 crans vers la gauche.
 */
int8_t IHM_COD_read(void)
{
	CAN_send_remote_frame(COD_REQ);
	while (mise_a_jour_COD == 0)
	{
		CAN_decode_IHM();
	}
	mise_a_jour_COD = 0;
	return COD_valeur;
}
