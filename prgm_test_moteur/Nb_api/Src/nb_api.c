/**
 ******************************************************************************
 * @file	nb_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque d'initialisation de la NBoard.
 * 			Cette bibliothèque permet de :
 *			+ initialiser la NBoard selon votre application (en TP SN, en SAE
 *			robot, ...).
 *
 ******************************************************************************
 */

#include "nboard.h"

/**
 * @brief	Initialise la NBoard.
 * @param
 * @retval
 */
void NB_init(void)
{
	/******************* NE PAS TOUCHER **************************************/

	/* Initialisations toujours valables (fait appel aux fonctions auto-
	 * générées) */
	HAL_Init();
	SystemClock_Config();

	MX_GPIO_Init();
	MX_ADC1_Init();
	MX_CAN_Init();
	MX_DAC1_Init();
	MX_TIM2_Init();

	/*************************************************************************/

	/******************* A REMPLIR : ENTREES NUMERIQUES **********************/

	GPIO_input(PA_9, PULL_UP); // BP0
	GPIO_input(PA_10, PULL_UP);//BP1
	GPIO_input(PB_0, PULL_UP);//BP2
	GPIO_input(PB_7, PULL_UP);//BP3

	/*************************************************************************/

	/******************* A REMPLIR : SORTIES NUMERIQUES **********************/

	GPIO_output(PB_3); // LED0

	/*************************************************************************/

	/******************* A REMPLIR : BUS SORTIES NUMERIQUES ******************/



	/*************************************************************************/

	/******************* A REMPLIR : ENTREES DE SELECTION DU MUX *************/



	/*************************************************************************/

	/******************* A REMPLIR : ENTREES ANALOGIQUES *********************/



	/*************************************************************************/

	/******************* A REMPLIR : SORTIES ANALOGIQUES *********************/



	/*************************************************************************/

	/******************* A REMPLIR : PWM *************************************/

	PWM_output(PB_5,1); //sortie PWM

	/*************************************************************************/
}
