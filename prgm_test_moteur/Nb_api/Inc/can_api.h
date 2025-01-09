/**
 ******************************************************************************
 * @file	can_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion du CAN de la NBoard.
 *
 * 			/!\ Cette bibliothèque n'est compatible qu'avec la NBoard
 * 			(traitement "en dur" des trames CAN reçues envoyées par l'IHM).
 *
 * @todo	03/10/2024 : à généraliser et compléter pour la compatibilité avec
 * 			d'autres cartes
 *
 ******************************************************************************
 */

#ifndef INC_CAN_API_H_
#define INC_CAN_API_H_

/******************* BIBLIOTHEQUES *******************************************/

#include "can.h"

/******************* CONSTANTES SYMBOLIQUES **********************************/

/* Constante symbolique FIFO réception CAN ***********************************/
#define SIZE_FIFO 32

/******************* TYPES STRUCTURES ****************************************/

/**
 * @brief	Définition de la structure CAN_trame_tx pour l'envoi de trames CAN
 */
typedef struct
{
	CAN_TxHeaderTypeDef header; /* Spécifie l'en-tête de la trame CAN à envoyer
	 (ID, IDE, RTR, DLC) */
	uint8_t data[8]; /* Spécifie les données (0 à 8 octets) de la
	 trame CAN à envoyer */
	uint32_t mailbox; /* Spécifie l'adresse de la mailbox utilisée
	 pour l'envoi de la trame CAN */
} T_CAN_trame_tx;

/**
 * @brief	Définition de la structure CAN_trame_rx pour la réception de trames
 *			CAN
 */
typedef struct
{
	CAN_RxHeaderTypeDef header; /* Spécifie l'en-tête de la trame CAN reçue
	 (ID, IDE, RTR, DLC) */
	uint8_t data[8];  /* Spécifie les données de la trame CAN reçue */
} T_CAN_trame_rx;

/******************* PROTOTYPES DE FONCTIONS *********************************/

/* Fonction initialisation filtres CAN ***************************************/
void CAN_config_filters(void);
/* Fonctions envoi trame CAN *************************************************/
void CAN_send_data_frame(uint16_t ident, uint8_t size, uint8_t *tab_data);
void CAN_send_remote_frame(uint16_t ident);
/* Fonction réception trame CAN **********************************************/
void CAN_decode_IHM(void);

#endif /* INC_CAN_API_H_ */
