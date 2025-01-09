/**
 ******************************************************************************
 * @file	tim_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion des TIM (timers).
 *
 * 			Cette bibliothèque permet de :
 * 			+ créer, démarrer, arrêter et lire un timer "chronomètre" pour
 * 			mesurer des temps précis (avec une précision supérieure ou égale à
 * 			la milliseconde) ;
 * 			+ déclencher une interruption périodique (fonction appelée de
 * 			manière répétée et à un rythme spécifié) ;
 * 			+ déclencher une interruption après un délai spécifié.
 *
 * 			/!\ Le TIM2 est utilisé par cette bibliothèque et ne peut donc pas
 * 			être utilisé pour d'autres fonctions (PWM, encodeur, ...).
 *
 ******************************************************************************
 */

#include "main.h"
#include "tim.h"
#include "tim_api.h"

uint32_t private_counter_start = 0, private_counter_end = 0;
uint8_t private_counter_is_running = 0;

T_TIM_ticker private_ticker = { 0, 0, NULL };
T_TIM_timeout private_timeout = { 0, 0, NULL };

/**
 * @brief	Attend un nombre de millisecondes (attente bloquante).
 * @param	uint32_t la durée de l'attente bloquante (en millisecondes)
 * @retval
 */
void TIM_wait_ms(uint32_t time_ms)
{
	HAL_Delay(time_ms);
}

/**
 * @brief	Attend un nombre de microsecondes (attente bloquante).
 * @param	uint32_t la durée de l'attente bloquante (en microsecondes)
 * @retval
 */
void TIM_wait_us(uint32_t time_us)
{
	uint32_t counter_start_before_waiting = __HAL_TIM_GET_COUNTER(&htim2);
	while ((__HAL_TIM_GET_COUNTER(&htim2) - counter_start_before_waiting)
			< time_us);
}

/**
 * @brief	Démarre le timer "chronomètre".
 * @param
 * @retval
 */
void TIM_start(void)
{
	if (!private_counter_is_running)
	{
		private_counter_start = __HAL_TIM_GET_COUNTER(&htim2)
				- (private_counter_end - private_counter_start);
		private_counter_end = 0;
		private_counter_is_running = 1;
	}
}

/**
 * @brief	Arrête le timer "chronomètre" (sans le réinitialiser).
 * @param
 * @retval
 */
void TIM_stop(void)
{
	if (private_counter_is_running)
	{
		private_counter_end = __HAL_TIM_GET_COUNTER(&htim2);
		private_counter_is_running = 0;
	}
}

/**
 * @brief	Réinitialise le timer "chronomètre". Si le timer était déjà lancé,
 * 			il va continuer à chronométrer.
 * @param
 * @retval
 */
void TIM_reset(void)
{
	private_counter_start = __HAL_TIM_GET_COUNTER(&htim2);
	if (private_counter_is_running)
	{
		private_counter_end = 0;
	}
	else
	{
		private_counter_end = __HAL_TIM_GET_COUNTER(&htim2);

	}
}
/**
 * @brief	Lit le temps écoulé depuis le lancement du timer en millisecondes.
 * @param
 * @retval	uint32_t le temps écoulé depuis le lancement (en millisecondes)
 */
uint32_t TIM_read_ms(void)
{
	return (TIM_read_us() / 1000);
}

/**
 * @brief	Lit le temps écoulé depuis le lancement du timer en microsecondes.
 * @param
 * @retval	uint32_t le temps écoulé depuis le lancement (en microsecondes)
 */
uint32_t TIM_read_us(void)
{
	if (private_counter_start <= private_counter_end)
	{
		return (private_counter_end - private_counter_start);
	}
	else
	{
		return (__HAL_TIM_GET_COUNTER(&htim2) - private_counter_start);
	}
}

/**
 * @brief	Configure une routine d'interruption déclenchée périodiquement
 *			(période en millisecondes).
 * @param	uint32_t la période (en millisecondes) de déclenchement de
 *			l'interruption
 * @param	void (*)(void) la routine d'interruption à effectuer
 * @retval
 */
void TIM_attach_isr_ms(uint32_t period_ms, void (*f)(void))
{
	private_ticker.previous_tick = HAL_GetTick();
	private_ticker.period_ms = period_ms;
	private_ticker.isr = f;
}

/**
 * @brief	déConfigure une routine d'interruption périodique.
 * @param
 * @retval
 */

void TIM_detach_isr_ms(void)
{
	private_ticker.previous_tick = 0;
	private_ticker.period_ms = 0;
	private_ticker.isr = NULL;
}

/**
 * @brief	Configure une routine d'interruption déclenchée après un délai
 *			écoulé (délai en millisecondes).
 * @param	uint32_t le délai (en millisecondes) après lequel déclencher
 *			l'interruption
 * @param	void (*)(void) la routine d'interruption à effectuer
 * @retval
 */
void TIM_timeout_ms(uint32_t delay_ms, void (*f)(void))
{
	private_timeout.start_tick = HAL_GetTick();
	private_timeout.delay_ms = delay_ms;
	private_timeout.isr = f;
}

/**
 * @brief	déConfigure une routine d'interruption "timeout" (déclenchée après
 * 			un délai écoulé).
 * @param
 * @retval
 */
void TIM_cancel_timeout_ms(void)
{
	private_timeout.start_tick = 0;
	private_timeout.delay_ms = 0;
	private_timeout.isr = NULL;
}
