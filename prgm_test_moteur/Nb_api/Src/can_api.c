/**
 ******************************************************************************
 * @file	can_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion du CAN de la NBoard.
 * 			Cette bibliothèque permet de :
 * 			+ envoyer des trames CAN (envoi à l'IHM) ;
 * 			+ recevoir des trames CAN (envoyées par l'IHM).
 *
 * 			/!\ Cette bibliothèque n'est compatible qu'avec la NBoard
 * 			(traitement "en dur" des trames CAN reçues envoyées par l'IHM).
 *
 * @todo	03/10/2024 : à généraliser et compléter pour la compatibilité avec
 * 			d'autres cartes
 *
 ******************************************************************************
 */

#include "nboard.h"

#include "ident_ihm.h"

T_CAN_trame_tx trame_tx;
uint8_t FIFO_ecriture = 0;
T_CAN_trame_rx trames_rx[SIZE_FIFO];

uint8_t JOG_valeur;
int8_t COD_valeur;
uint8_t mise_a_jour_JOG = 0, mise_a_jour_COD = 0;

/**
 * @brief	Routine d'interruption associée à la réception d'une trame CAN.
 *			/!\ Fonction définie dans la HAL ST et surchargée (redéclarée) ici.
 * @param	CAN_HandleTypeDef* l'adresse du périphérique CAN sur lequel la
 * 			trame a été reçue.
 * @retval
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan_rx)
{
	if (HAL_CAN_GetRxMessage(hcan_rx, CAN_RX_FIFO0,
			&trames_rx[FIFO_ecriture].header, trames_rx[FIFO_ecriture].data)
			!= HAL_OK)
	{
		Error_Handler();
	}
	FIFO_ecriture = (FIFO_ecriture + 1) % SIZE_FIFO;
}

/**
 * @brief	Configure les filtres de réception sur le CAN.
 * 			/!\ Il faut faire cette configuration pour chaque périphérique CAN
 * 			si plusieurs sont utilisés.
 * @param
 * @retval
 */
void CAN_config_filters(void)
{
	CAN_FilterTypeDef filtres_rx;
	filtres_rx.FilterBank = 0;
	filtres_rx.FilterMode = CAN_FILTERMODE_IDMASK;
	filtres_rx.FilterScale = CAN_FILTERSCALE_32BIT;
	/* Toutes les trames CAN sont acceptées. */
	filtres_rx.FilterIdHigh = 0x0000;
	filtres_rx.FilterIdLow = 0x0000;
	filtres_rx.FilterMaskIdHigh = 0x0000;
	filtres_rx.FilterMaskIdLow = 0x0000;
	filtres_rx.FilterFIFOAssignment = CAN_RX_FIFO0;
	filtres_rx.FilterActivation = ENABLE;
	filtres_rx.SlaveStartFilterBank = 14;
	if (HAL_CAN_ConfigFilter(&hcan, &filtres_rx) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief	Envoie une trame de données sur le bus CAN.
 * @param	uint16_t l'ID de la trame CAN
 * @param	uint8_t le nombre d'octets de données dans la trame CAN
 * @param	uint8_t* l'adresse du tableau de données à envoyer
 * @retval
 */
void CAN_send_data_frame(uint16_t ident, uint8_t size, uint8_t *tab_data)
{
	trame_tx.header.IDE = CAN_ID_STD;
	trame_tx.header.StdId = ident;
	trame_tx.header.RTR = CAN_RTR_DATA;
	trame_tx.header.DLC = size;
	while (HAL_CAN_AddTxMessage(&hcan, &trame_tx.header, tab_data,
			&trame_tx.mailbox) != HAL_OK);
}

/**
 * @brief	Envoie une trame de requête sur le bus CAN.
 * @param	uint16_t l'ID de la trame CAN
 * @retval
 */
void CAN_send_remote_frame(uint16_t ident)
{
	trame_tx.header.IDE = CAN_ID_STD;
	trame_tx.header.StdId = ident;
	trame_tx.header.RTR = CAN_RTR_REMOTE;
	while (HAL_CAN_AddTxMessage(&hcan, &trame_tx.header, 0, &trame_tx.mailbox)
			!= HAL_OK);
}

/**
 * @brief	Décode (traite) les trames reçues sur le bus CAN et stockées dans
 * 			la FIFO de réception.
 * @param
 * @retval
 */
void CAN_decode_IHM(void)
{
	static uint8_t FIFO_lecture = 0, FIFO_max_occupation = 0;
	static int8_t FIFO_occupation = 0;

	uint16_t id = 0;

	FIFO_occupation = FIFO_ecriture - FIFO_lecture;
	if (FIFO_occupation < 0)
	{
		/* le lecteur est plus grand que l'écrivain */
		FIFO_occupation = FIFO_occupation + SIZE_FIFO;
	}
	if (FIFO_max_occupation < FIFO_occupation)
	{
		/* calcul de l'occupation maximale de la FIFO */
		FIFO_max_occupation = FIFO_occupation;
	}
	if (FIFO_occupation > SIZE_FIFO)
	{
		/* les trames sont écrites (reçues) plus vite qu'elles ne sont lues
		 * (traitées)
		 */
		FIFO_occupation = 0;
	}
	if (FIFO_occupation != 0)
	{
		/* il y a au moins une trame à traiter */
		id = trames_rx[FIFO_lecture].header.StdId;
		if (id > 0x700) /* plage d'identifiants CAN de l'IHM */
		{
			switch (id)
			{
				case JOG_DATA:
					JOG_valeur = trames_rx[FIFO_lecture].data[0];
					mise_a_jour_JOG = 1;
					break;
				case COD_DATA:
					COD_valeur = trames_rx[FIFO_lecture].data[0];
					mise_a_jour_COD = 1;
					break;
				default:
					break;
			}
		}
		FIFO_lecture = (FIFO_lecture + 1) % SIZE_FIFO;
	}
}
