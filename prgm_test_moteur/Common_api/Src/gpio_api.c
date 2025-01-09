/**
 ******************************************************************************
 * @file	gpio_api.c
 * @author	Bruno LARNAUDIE, Pauline MICHEL
 * @brief	Bibliothèque de gestion des GPIO.
 *			Cette bibliothèque permet de :
 *			+ lire la valeur d'une entrée numérique ;
 *			+ écrire la valeur d'une sortie numérique ;
 *			+ déclencher une interruption quand une entrée numérique change de
 *			niveau (front montant ou descendant).
 *
 ******************************************************************************
 */

#include "main.h"

uint16_t flag_gpio_active_isr = 0;
void (*GPIO_isr[16])(void);

/**
 * @brief	Gère l'appel de la routine d'interruption associée à la pin sur
 *			laquelle s'est produit le changement de niveau.
 *			/!\ Fonction définie dans la HAL ST et surchargée (redéclarée) ici.
 * @param	uint16_t la pin sur laquelle s'est produit le changement de niveau
 * @retval
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint8_t i = 0;

	if (flag_gpio_active_isr & GPIO_Pin)
	{
		while (!(GPIO_Pin & 0x01))
		{
			GPIO_Pin >>= 1;
			i++;
		}
		GPIO_isr[i]();
	}
}

/**
 * @brief	Configure une GPIO en entrée.
 * @param	uint8_t la pin à configurer en entrée numérique
 * @param	uint8_t la résistance de tirage (PULL_NONE si pas de résistance
 * 			interne, PULL_UP, PULL_DOWN)
 * @retval
 */
void GPIO_input(uint8_t pin, uint8_t mode)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = mode;
	GPIO_InitStruct.Pin = 1 << (pin & 0x0F);
	HAL_GPIO_Init((GPIO_TypeDef*) (GPIOA_BASE + (pin >> 4) * 1024),
			&GPIO_InitStruct);
}

/**
 * @brief	Configure une GPIO en entrée d'interruption.
 * @param	uint8_t la pin à configurer en entrée
 * @param	uint8_t la résistance de tirage (PULL_NONE si pas de résistance
 * 			interne, PULL_UP, PULL_DOWN)
 * @param	uint32_t le déclenchement de l'interruption (front montant et/ou
 *			descendant)
 * @param	void (*)(void) la routine d'interruption à effectuer
 * @retval
 */
void GPIO_attach_isr(uint8_t pin, uint8_t mode, uint32_t trigger,
		void (*f)(void))
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = 1 << (pin & 0x0F);
	GPIO_InitStruct.Mode = trigger;
	GPIO_InitStruct.Pull = mode;
	HAL_GPIO_Init((GPIO_TypeDef*) (GPIOA_BASE + (pin >> 4) * 1024),
			&GPIO_InitStruct);

	flag_gpio_active_isr |= 1 << (pin & 0x0F);
	GPIO_isr[(pin & 0x0F)] = f;

	if (((pin & 0x0F) >= 0) && ((pin & 0x0F) <= 4))
	{
		HAL_NVIC_SetPriority(EXTI0_IRQn + (pin & 0x0F), 0, 0);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn + (pin & 0x0F));
	}
	else if (((pin & 0x0F) >= 5) && ((pin & 0x0F) <= 9))
	{
		HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	}
	else if (((pin & 0x0F) >= 10) && ((pin & 0x0F) <= 15))
	{
		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
}

/**
 * @brief	Configure une GPIO en sortie.
 * @param	uint8_t la pin à configurer en sortie numérique
 * @retval
 */
void GPIO_output(uint8_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = 1 << (pin & 0x0F);
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init((GPIO_TypeDef*) (GPIOA_BASE + (pin >> 4) * 1024),
			&GPIO_InitStruct);
}

/**
 * @brief	Lit la valeur d'une entrée numérique.
 * @param	uint8_t l'entrée à lire
 * @retval	uint8_t la valeur de l'entrée (0 ou 1)
 */
uint8_t GPIO_read(uint8_t pin)
{
	return HAL_GPIO_ReadPin((GPIO_TypeDef*) (GPIOA_BASE + (pin >> 4) * 1024),
			1 << (pin & 0x0F));
}

/**
 * @brief	Ecrit la valeur d'une sortie numérique.
 * @param	uint8_t la sortie à utiliser
 * @param	uint8_t la valeur à écrire (0 ou 1)
 * @retval
 */
void GPIO_write(uint8_t pin, uint8_t value)
{
	HAL_GPIO_WritePin((GPIO_TypeDef*) (GPIOA_BASE + (pin >> 4) * 1024),
			1 << (pin & 0x0F), value);
}

/**
 * @brief	Inverse la valeur d'une sortie numérique.
 * @param	uint8_t la sortie à inverser
 * @retval
 */
void GPIO_toggle(uint8_t pin)
{
	HAL_GPIO_TogglePin((GPIO_TypeDef*) (GPIOA_BASE + (pin >> 4) * 1024),
			1 << (pin & 0x0F));
}
