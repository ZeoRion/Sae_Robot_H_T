/**
 ******************************************************************************
 * @file	nboard.h
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de définition globale pour la NBoard.
 *
 ******************************************************************************
 */

#ifndef INC_NBOARD_H_
#define INC_NBOARD_H_

/******************* BIBLIOTHEQUES *******************************************/

/* Bibliothèques ST (code auto-généré) ***************************************/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dac.h"
#include "gpio.h"
#include "tim.h"

/* Bibliothèques IUT communes (indépendantes de la carte) ********************/
#include "adc_dac_api.h"
#include "clock_api.h"
#include "gpio_api.h"
#include "pinnames.h"
#include "tim_api.h"

/* Bibliothèques IUT spécifiques NBoard **************************************/
#include "can_api.h"
#include "ihm_api.h"
#include "nb_api.h"
#include "nb_adc_api.h"
#include "nb_bus_api.h"
#include "nb_dac_api.h"
#include "nb_pwm_api.h"

/* Vos bibliothèques *********************************************************/
// à compléter si besoin

#endif /* INC_NBOARD_H_ */
