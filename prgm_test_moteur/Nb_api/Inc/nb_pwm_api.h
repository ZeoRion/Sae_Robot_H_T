/**
 ******************************************************************************
 * @file	nb_pwm_api.h
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion des PWM sur la NBoard.
 * 			Cette bibliothèque permet de :
 *			+ configurer les PWM pour certaines pins de la NBoard  (sorties PWM
 *			pour SAE robot, sortie BNC et LED si compatibles).
 *
 *			/!\ Cette bibliothèque n'est compatible qu'avec la NBoard.
 *
 * @todo	12/11/2024 : à compléter pour la compatibilité avec d'autres cartes
 *			que la NBoard.
 *
 ******************************************************************************
 */

#ifndef INC_NB_PWM_API_H_
#define INC_NB_PWM_API_H_

/******************* TYPES STRUCTURES ****************************************/

/**
 * @brief	Définition de la structure PWM_TIM pour gérer une sortie PWM
 * 			(paramètres du TIM utilisé)
 */
typedef struct
{
	uint32_t TIM_prescaler; /*!< Spécifie le prédiviseur du TIM utilisé pour
	 générer la PWM. */
	uint32_t TIM_period; /*!< Spécifie la période de comptage du TIM utilisé
	 pour générer la PWM. */
	float frequency; /*!< Spécifie la fréquence réelle (en hertz) de la PWM. */
} T_PWM_TIM;

/******************* PROTOTYPES DE FONCTIONS *********************************/

/* Fonction initialisation PWM ***********************************************/
float PWM_output(uint8_t pin, float frequency_in_hz);
/* Fonction configuration rapport cyclique PWM *******************************/
void PWM_write(uint8_t pin, float duty_cycle);

#endif /* INC_NB_PWM_API_H_ */
