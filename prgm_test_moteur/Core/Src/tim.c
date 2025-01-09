/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "tim.h"
/* USER CODE BEGIN 0 */

#include "pinnames.h"

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
#if defined(STM32F303x8) /* cas de la NBoard */
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim15;
TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;
#endif

/* TIM2 init function */
void MX_TIM2_Init(void)
{

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 64 - 1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 4294967295;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* /!\ Rajout par rapport au code auto-généré */
	HAL_TIM_Base_Start(&htim2); /* démarrage du TIM2 */

	/* USER CODE END TIM2_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{

	if (tim_baseHandle->Instance == TIM2)
	{
		/* USER CODE BEGIN TIM2_MspInit 0 */

		/* USER CODE END TIM2_MspInit 0 */
		/* TIM2 clock enable */
		__HAL_RCC_TIM2_CLK_ENABLE();
		/* USER CODE BEGIN TIM2_MspInit 1 */

		/* USER CODE END TIM2_MspInit 1 */
	}
#if defined(STM32F303x8) /* cas de la NBoard */
	else if (tim_baseHandle->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspInit 0 */

		/* USER CODE END TIM3_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();
		/* USER CODE BEGIN TIM3_MspInit 1 */

		/* USER CODE END TIM3_MspInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM15)
	{
		/* USER CODE BEGIN TIM15_MspInit 0 */

		/* USER CODE END TIM15_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_TIM15_CLK_ENABLE();
		/* USER CODE BEGIN TIM15_MspInit 1 */

		/* USER CODE END TIM15_MspInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM16)
	{
		/* USER CODE BEGIN TIM16_MspInit 0 */

		/* USER CODE END TIM16_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_TIM16_CLK_ENABLE();
		/* USER CODE BEGIN TIM16_MspInit 1 */

		/* USER CODE END TIM16_MspInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM17)
	{
		/* USER CODE BEGIN TIM17_MspInit 0 */

		/* USER CODE END TIM17_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_TIM17_CLK_ENABLE();
		/* USER CODE BEGIN TIM17_MspInit 1 */

		/* USER CODE END TIM17_MspInit 1 */
	}
#endif
}

/* /!\ Modification par rapport au code auto-généré (dont modification du
 * prototype = des paramètres de la fonction) */
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim, uint8_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (htim->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspPostInit 0 */

		/* USER CODE END TIM3_MspPostInit 0 */
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM3 GPIO Configuration
		 PA4     ------> TIM3_CH2
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_4;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM3_MspPostInit 1 */

		/* USER CODE END TIM3_MspPostInit 1 */
	}
	else if (htim->Instance == TIM15)
	{
		/* USER CODE BEGIN TIM15_MspPostInit 0 */

		/* USER CODE END TIM15_MspPostInit 0 */

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM15 GPIO Configuration
		 PA1     ------> TIM15_CH1N
		 PA3     ------> TIM15_CH2
		 */

		if (pin == PA_1)
		{
			GPIO_InitStruct.Pin = GPIO_PIN_1;
		}
		else if (pin == PA_3)
		{
			GPIO_InitStruct.Pin = GPIO_PIN_3;
		}
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF9_TIM15;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM15_MspPostInit 1 */

		/* USER CODE END TIM15_MspPostInit 1 */
	}
	else if (htim->Instance == TIM16)
	{
		/* USER CODE BEGIN TIM16_MspPostInit 0 */

		/* USER CODE END TIM16_MspPostInit 0 */
		if (pin == PA_6)
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
			/**TIM16 GPIO Configuration
			 PA6     ------> TIM16_CH1
			 */
			GPIO_InitStruct.Pin = GPIO_PIN_6;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			GPIO_InitStruct.Alternate = GPIO_AF1_TIM16;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		else if (pin == PB_4)
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
			/**TIM16 GPIO Configuration
			 PA6     ------> TIM16_CH1
			 */
			GPIO_InitStruct.Pin = GPIO_PIN_4;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			GPIO_InitStruct.Alternate = GPIO_AF1_TIM16;
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		/* USER CODE BEGIN TIM16_MspPostInit 1 */

		/* USER CODE END TIM16_MspPostInit 1 */
	}
	else if (htim->Instance == TIM17)
	{
		/* USER CODE BEGIN TIM17_MspPostInit 0 */

		/* USER CODE END TIM17_MspPostInit 0 */

		if (pin == PA_7)
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
			/**TIM17 GPIO Configuration
			 PB5     ------> TIM17_CH1
			 */
			GPIO_InitStruct.Pin = GPIO_PIN_7;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			GPIO_InitStruct.Alternate = GPIO_AF1_TIM17;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		else if (pin == PB_5)
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
			/**TIM16 GPIO Configuration
			 PA6     ------> TIM16_CH1
			 */
			GPIO_InitStruct.Pin = GPIO_PIN_5;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			GPIO_InitStruct.Alternate = GPIO_AF10_TIM17;
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		/* USER CODE BEGIN TIM17_MspPostInit 1 */

		/* USER CODE END TIM17_MspPostInit 1 */
	}

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle)
{

	if (tim_baseHandle->Instance == TIM2)
	{
		/* USER CODE BEGIN TIM2_MspDeInit 0 */

		/* USER CODE END TIM2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM2_CLK_DISABLE();
		/* USER CODE BEGIN TIM2_MspDeInit 1 */

		/* USER CODE END TIM2_MspDeInit 1 */
	}
#if defined(STM32F303x8) /* cas de la NBoard */
	else if (tim_baseHandle->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspDeInit 0 */

		/* USER CODE END TIM3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM3_CLK_DISABLE();
		/* USER CODE BEGIN TIM3_MspDeInit 1 */

		/* USER CODE END TIM3_MspDeInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM15)
	{
		/* USER CODE BEGIN TIM15_MspDeInit 0 */

		/* USER CODE END TIM15_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM15_CLK_DISABLE();
		/* USER CODE BEGIN TIM15_MspDeInit 1 */

		/* USER CODE END TIM15_MspDeInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM16)
	{
		/* USER CODE BEGIN TIM16_MspDeInit 0 */

		/* USER CODE END TIM16_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM16_CLK_DISABLE();
		/* USER CODE BEGIN TIM16_MspDeInit 1 */

		/* USER CODE END TIM16_MspDeInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM17)
	{
		/* USER CODE BEGIN TIM17_MspDeInit 0 */

		/* USER CODE END TIM17_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM17_CLK_DISABLE();
		/* USER CODE BEGIN TIM17_MspDeInit 1 */

		/* USER CODE END TIM17_MspDeInit 1 */
	}
#endif
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
