/**
 ******************************************************************************
 * @file	nb_pwm_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion des PWM sur la NBoard.
 * 			Cette bibliothèque permet de :
 *			+ configurer les PWM pour certaines pins de la NBoard  (sorties PWM
 *			pour SAE robot, sortie BNC et LED si compatibles).
 *
 *			/!\ Cette bibliothèque n'est compatible qu'avec la NBoard.
 *
 * @todo	12/11/2024 : à généraliser et compléter pour la compatibilité avec
 * 			d'autres cartes
 *
 ******************************************************************************
 */
#include "nboard.h"

/* Fonction calcul paramètres TIM ********************************************/
T_PWM_TIM PWM_compute_TIM_params(uint32_t freq_TIM, float frequency_in_hz);
/* Fonctions initialisation TIM PWM ******************************************/
void MX_TIM3_Init(uint16_t TIM_prescaler, uint16_t TIM_period, uint8_t pin);
void MX_TIM15_Init(uint16_t TIM_prescaler, uint16_t TIM_period, uint8_t pin);
void MX_TIM16_Init(uint16_t TIM_prescaler, uint16_t TIM_period, uint8_t pin);
void MX_TIM17_Init(uint16_t TIM_prescaler, uint16_t TIM_period, uint8_t pin);

uint8_t status_tim_channel[20][7];

T_PWM_TIM tableau_tim[20];

/**
 * @brief	Configure une pin en sortie PWM.
 * @param	uint8_t la pin à configurer en sortie PWM
 * @param	float la fréquence de la PWM (en Hz)
 * @retval	float la fréquence réellement obtenue (en Hz). Elle peut être
 * 			différente de celle voulue par l'utilisateur
 */
float PWM_output(uint8_t pin, float frequency_in_hz)
{
	uint32_t freq_APB1 = 64000000; // 64 MHz	APB1	TIM3
	uint32_t freq_APB2 = 64000000; // 64 MHz	APB2	TIM15, 16, 17
	uint8_t numero_timer;

	switch (pin)
	{
		case PA_1: // TIM15 CH1N
			numero_timer = 15;
			tableau_tim[numero_timer] = PWM_compute_TIM_params(freq_APB2,
					frequency_in_hz);
			if (tableau_tim[numero_timer].frequency != 0)
			{
				MX_TIM15_Init(tableau_tim[numero_timer].TIM_prescaler,
						tableau_tim[numero_timer].TIM_period, pin);
				status_tim_channel[numero_timer][1] = 1;
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("TIM15 frequency  unattainable !");
				while (1);
			}
			break;

		case PA_3: // TIM15 CH2
			numero_timer = 15;
			tableau_tim[numero_timer] = PWM_compute_TIM_params(freq_APB2,
					frequency_in_hz);
			if (tableau_tim[numero_timer].frequency != 0)
			{
				MX_TIM15_Init(tableau_tim[numero_timer].TIM_prescaler,
						tableau_tim[numero_timer].TIM_period, pin);
				status_tim_channel[numero_timer][2] = 1;
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("TIM15 frequency  unattainable !");
				while (1);
			}
			break;

		case PA_4: // TIM3 CH1
			/* arrêt du DAC1 qui est relié à cette pin */
			hdac1.Instance = DAC1;
			HAL_DAC_Stop(&hdac1, DAC_CHANNEL_1);
			if (HAL_DAC_DeInit(&hdac1) != HAL_OK)
			{
				Error_Handler();
			}
			/* DAC arrêté... on peut utiliser la pin comme sortie PWM */
			numero_timer = 3;
			tableau_tim[numero_timer] = PWM_compute_TIM_params(freq_APB1,
					frequency_in_hz);
			if (tableau_tim[numero_timer].frequency != 0)
			{
				MX_TIM3_Init(tableau_tim[numero_timer].TIM_prescaler,
						tableau_tim[numero_timer].TIM_period, pin);
				status_tim_channel[numero_timer][2] = 1;
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("TIM3 frequency  unattainable !");
				while (1);
			}
			break;

		case PA_6: // TIM16 CH1
			numero_timer = 16;
			tableau_tim[numero_timer] = PWM_compute_TIM_params(freq_APB2,
					frequency_in_hz);
			if (tableau_tim[numero_timer].frequency != 0)
			{
				MX_TIM16_Init(tableau_tim[numero_timer].TIM_prescaler,
						tableau_tim[numero_timer].TIM_period, pin);
				status_tim_channel[numero_timer][1] = 1;
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("TIM16 frequency  unattainable !");
				while (1);
			}
			break;

		case PA_7: // TIM17 CH1
			numero_timer = 17;
			tableau_tim[numero_timer] = PWM_compute_TIM_params(freq_APB2,
					frequency_in_hz);
			if (tableau_tim[numero_timer].frequency != 0)
			{
				MX_TIM17_Init(tableau_tim[numero_timer].TIM_prescaler,
						tableau_tim[numero_timer].TIM_period, pin);
				status_tim_channel[numero_timer][1] = 1;
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("TIM17 frequency  unattainable !");
				while (1);
			}
			break;

		case PB_4: // TIM16 CH1
			numero_timer = 16;
			tableau_tim[numero_timer] = PWM_compute_TIM_params(freq_APB2,
					frequency_in_hz);
			if (tableau_tim[numero_timer].frequency != 0)
			{
				MX_TIM16_Init(tableau_tim[numero_timer].TIM_prescaler,
						tableau_tim[numero_timer].TIM_period, pin);
				status_tim_channel[numero_timer][1] = 1;
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("TIM16 frequency  unattainable !");
				while (1);
			}
			break;

		case PB_5: // TIM17 CH1
			numero_timer = 17;
			tableau_tim[numero_timer] = PWM_compute_TIM_params(freq_APB2,
					frequency_in_hz);
			if (tableau_tim[numero_timer].frequency != 0)
			{
				MX_TIM17_Init(tableau_tim[numero_timer].TIM_prescaler,
						tableau_tim[numero_timer].TIM_period, pin);
				status_tim_channel[numero_timer][1] = 1;
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("TIM17 frequency  unattainable !");
				while (1);
			}
			break;

		default:
			IHM_LCD_clear();
			IHM_LCD_printf("wrong PWM pin !!!!!!!!!!!!!!");
			while (1);
			break; // ne sert à rien mais bon on garde les bonnes habitudes
	}
	return tableau_tim[numero_timer].frequency;
}

/**
 * @brief	Configure le rapport cyclique de la PWM.
 * @param	uint8_t la sortie PWM à configurer
 * @param	float le rapport cyclique (entre 0 et 1)
 * @retval
 */
void PWM_write(uint8_t pin, float duty_cycle)
{
	if(duty_cycle < 0.0f)
	{
		duty_cycle = 0.0f;
		IHM_LCD_locate(0, 0);
		IHM_LCD_printf("PWM duty too low");
		IHM_LCD_locate(1, 0);
		IHM_LCD_printf("PWM duty too low");
	}
	else if(duty_cycle > 1.0f)
	{
		duty_cycle = 1.0f;
		IHM_LCD_locate(0, 0);
		IHM_LCD_printf("PWM duty too big");
		IHM_LCD_locate(1, 0);
		IHM_LCD_printf("PWM duty too big");
	}

	switch (pin)
	{
		case PA_1:
			if (status_tim_channel[15][1] == 1)
			{
				HAL_TIMEx_PWMN_Start(&htim15, TIM_CHANNEL_1); // channel N
				__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1,
						duty_cycle * tableau_tim[15].TIM_period);
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("PA_1 not in PWM output !");
				while (1);
			}
			break;

		case PA_3:
			if (status_tim_channel[15][2] == 1)
			{
				HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
				__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2,
						duty_cycle * tableau_tim[15].TIM_period);
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("PA_3 not in PWM output !");
				while (1);
			}
			break;

		case PA_4:
			if (status_tim_channel[3][2] == 1)
			{
				HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,
						duty_cycle * tableau_tim[3].TIM_period);
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("PA_4 not in PWM output !");
				while (1);
			}
			break;

		case PA_6:
			if (status_tim_channel[16][1] == 1)
			{
				HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
				__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1,
						duty_cycle * tableau_tim[16].TIM_period);
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("PA_6 not in PWM output !");
				while (1);
			}
			break;

		case PA_7:
			if (status_tim_channel[17][1] == 1)
			{
				HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
				__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1,
						duty_cycle * tableau_tim[17].TIM_period);
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("PA_7 not in PWM output !");
				while (1);
			}
			break;

		case PB_4:
			if (status_tim_channel[16][1] == 1)
			{
				HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
				__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1,
						duty_cycle * tableau_tim[16].TIM_period);
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("PB_4 not in PWM output !");
				while (1);
			}
			break;

		case PB_5:
			if (status_tim_channel[17][1] == 1)
			{
				HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
				__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1,
						duty_cycle * tableau_tim[17].TIM_period);
			}
			else
			{
				IHM_LCD_clear();
				IHM_LCD_printf("PB_5 not in PWM output !");
				while (1);
			}
			break;

		default:
			IHM_LCD_clear();
			IHM_LCD_printf("wrong PWM pin !!!!!!!!!!!!!!");
			while (1);
			break; // ne sert à rien mais bon on garde les bonnes habitudes
	}
}

/**
 * @brief	Calcule le prédiviseur et la période de comptage du TIM pour
 * 			configurer une pin en sortie PWM avec une fréquence voulue.
 * @param	uint32_t la fréquence d'horloge du TIM (en Hz)
 * @param	float la fréquence de la PWM (en Hz)
 * @retval	T_PWM_TIM une structure contenant les paramètres du TIM utilisé
 * 			(dont la fréquence réelle de la PWM)
 */
T_PWM_TIM PWM_compute_TIM_params(uint32_t freq_TIM, float freq_vise)
{
	float freq_finale, rapport;
	unsigned char sortie = 0;
	unsigned short TIM_period;
	unsigned short TIM_prescaler = 1;
	T_PWM_TIM output = { 0 };

	rapport = freq_TIM / (float)freq_vise;

	while (sortie == 0)
	{
		if (rapport > 0xFFFF)
		{
			if (rapport / 0xFFFF > 0xFFFF)
				sortie = 2;
			else
			{
				TIM_prescaler = rapport / 0xFFFF + 1;
				rapport = freq_TIM / (float)freq_vise / (float)TIM_prescaler;
			}
		}
		else
		{
			TIM_period = rapport;
			freq_finale = (float)freq_TIM / (float)TIM_period
					/ (float)TIM_prescaler;
			if ((freq_vise / freq_finale <= 1)
					|| (freq_vise / freq_finale > 0.98))
			{
				sortie = 1;
				output.TIM_prescaler = TIM_prescaler;
				output.TIM_period = TIM_period;
				output.frequency = freq_finale;
			}
			else
			{
				sortie = 2;
				output.TIM_period = 0;
				output.TIM_prescaler = 0;
				output.frequency = 0;
			}
		}
	}
	return output;
}

/* /!\ Code généré automatiquement par CubeIDE, isolé dans la bibliothèque
 * spécifique PWM, et modifié. */
/* TIM3 init function */
void MX_TIM3_Init(uint16_t TIM_prescaler, uint16_t TIM_period, uint8_t pin)
{

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = TIM_prescaler - 1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = TIM_period - 1;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

	/* /!\ Modification par rapport au code auto-généré = ajout du paramètre
	 * pin PWM */
	HAL_TIM_MspPostInit(&htim3, pin);

}

/* /!\ Code généré automatiquement par CubeIDE, isolé dans une bibliothèque
 * spécifique PWM, et modifié. */
/* TIM15 init function */
void MX_TIM15_Init(uint16_t TIM_prescaler, uint16_t TIM_period, uint8_t pin)
{
	/* USER CODE BEGIN TIM15_Init 0 */

	/* USER CODE END TIM15_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = { 0 };

	/* USER CODE BEGIN TIM15_Init 1 */

	/* USER CODE END TIM15_Init 1 */
	htim15.Instance = TIM15;
	htim15.Init.Prescaler = TIM_prescaler - 1;
	htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim15.Init.Period = TIM_period - 1;
	htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim15.Init.RepetitionCounter = 0;
	htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim15) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig)
			!= HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	/* /!\ Modification par rapport au code auto-généré = ajout du paramètre
	 * pin PWM */
	if (pin == PA_1)
	{
		if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_1)
				!= HAL_OK)
		{
			Error_Handler();
		}
	}
	else if (pin == PA_3)
	{
		if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_2)
				!= HAL_OK)
		{
			Error_Handler();
		}
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.BreakFilter = 0;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim15, &sBreakDeadTimeConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM15_Init 2 */

	/* USER CODE END TIM15_Init 2 */

	/* /!\ Modification par rapport au code auto-généré = ajout du paramètre
	 * pin PWM */
	HAL_TIM_MspPostInit(&htim15, pin);
}

/* /!\ Code généré automatiquement par CubeIDE, isolé dans la bibliothèque
 * spécifique PWM, et modifié. */
/* TIM16 init function */
void MX_TIM16_Init(uint16_t TIM_prescaler, uint16_t TIM_period, uint8_t pin)
{
	/* USER CODE BEGIN TIM16_Init 0 */

	/* USER CODE END TIM16_Init 0 */

	TIM_OC_InitTypeDef sConfigOC = { 0 };
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = { 0 };

	/* USER CODE BEGIN TIM16_Init 1 */

	/* USER CODE END TIM16_Init 1 */
	htim16.Instance = TIM16;
	htim16.Init.Prescaler = TIM_prescaler - 1;
	htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim16.Init.Period = TIM_period - 1;
	htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim16.Init.RepetitionCounter = 0;
	htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim16) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim16, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.BreakFilter = 0;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim16, &sBreakDeadTimeConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM16_Init 2 */

	/* USER CODE END TIM16_Init 2 */

	/* /!\ Modification par rapport au code auto-généré = ajout du paramètre
	 * pin PWM */
	HAL_TIM_MspPostInit(&htim16, pin);
}

/* /!\ Code généré automatiquement par CubeIDE, isolé dans la bibliothèque
 * spécifique PWM, et modifié. */
/* TIM17 init function */
void MX_TIM17_Init(uint16_t TIM_prescaler, uint16_t TIM_period, uint8_t pin)
{
	/* USER CODE BEGIN TIM17_Init 0 */

	/* USER CODE END TIM17_Init 0 */

	TIM_OC_InitTypeDef sConfigOC = { 0 };
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = { 0 };

	/* USER CODE BEGIN TIM17_Init 1 */

	/* USER CODE END TIM17_Init 1 */
	htim17.Instance = TIM17;
	htim17.Init.Prescaler = TIM_prescaler - 1;
	htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim17.Init.Period = TIM_period - 1;
	htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim17.Init.RepetitionCounter = 0;
	htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim17) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.BreakFilter = 0;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim17, &sBreakDeadTimeConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM17_Init 2 */

	/* USER CODE END TIM17_Init 2 */

	/* /!\ Modification par rapport au code auto-généré = ajout du paramètre
	 * pin PWM */
	HAL_TIM_MspPostInit(&htim17, pin);
}
