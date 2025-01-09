#include "nboard.h"

/******************* CONSTANTES SYMBOLIQUES **********************************/

#define BP0 GPIO_read(PA_9)
#define BP1 GPIO_read(PA_10)
#define BP2 GPIO_read(PB_0)
#define BP3 GPIO_read(PB_7)

#define LED1 PA_7

/******************* PROTOTYPES DE FONCTIONS *********************************/

/******************* PROGRAMME PRINCIPAL *************************************/

int main(void)
{
	// Initialisation de variables locales
	float speed = 0.25;

	// Initialisation de la carte
	NB_init();

	IHM_LCD_clear();
	IHM_LCD_locate(0, 0);

	while (1)
	{


		if (BP0 == 0)
		{
			speed = 0.0;
		}
		else if (BP2 == 0)
		{
			speed = 1.0;
		}
		else if (BP1 == 0)
		{
			speed = speed - 0.1;
			if (speed <= 0.1 )
			{
				speed = 0.1;
			}
		}
		else if (BP3 == 0)
		{
			speed = speed + 0.1;
			if (speed >= 0.9 )
			{
				speed = 0.9;
			}
		}

		PWM_write(LED1, speed);
		TIM_wait_ms(100);
		PWM_write(LED1, 0);

		IHM_LCD_clear();
		IHM_LCD_printf("speed=%4.2f", speed);
		TIM_wait_ms(10);
	}
}
