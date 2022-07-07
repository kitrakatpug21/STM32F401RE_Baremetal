#include <stm32f4xx.h>
#include "delay.h"
#include "uart2.h"

void sudhakar_Callback();

#define GPIOAEN		(1U << 0)
#define PA5			(1U << 5)

int main(void)
{
	// 	1. DISABLE ALL THE PREVIOUS INTERRUPT ROUTINES
	__disable_irq();//double underscore disable
	// 	2. ENABLE CLOCK ACCESS FOR EXTI GPIO PIN (PC13)
	RCC->AHB1ENR |= (1U<<2);
	// 	3. MODE SETUP AS INPUT FOR THE PIN
	GPIOC-> MODER &= ~(1U<<0);
	GPIOC-> MODER &= ~(1U<<1);
	GPIOC-> MODER &= ~(1U<<2);
	GPIOC-> MODER &= ~(1U<<3);
	/*GPIOC-> MODER &= ~(1U<<26);
	GPIOC-> MODER &= ~(1U<<27);
	//  4. ENABLE CLOCK ACCESS FOR SYSCFG
	RCC -> APB2ENR |= (1U<<14);
	//	 5. SETUP THE INTERRUPT LINE -> EXTICR4
	SYSCFG -> EXTICR[3] |= (1U<<5);
	SYSCFG -> EXTICR[3] &= ~(1U<<4);
	SYSCFG -> EXTICR[3] &= ~(1U<<6);
	SYSCFG -> EXTICR[3] &= ~(1U<<7);
	//  6. SETUP THE MASKING IN (IMR)
	EXTI -> IMR |= (1U<<13);
	//  7. FALLING/RISING/BOTH EDGE TRIGGER
	EXTI -> FTSR |= (1U<<13);
	//  8. NVIC ENABLE
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	//  9. RESTART ALL THE PREVIOUS INTERRUPT ROUTINES
	 */
	Systick_Interrupt_Init();
	__enable_irq();//double underscore enable
	////////////////////////////////////////////////////////
	uart2_init_transmitter();
	RCC -> AHB1ENR |= GPIOAEN;
	GPIOA -> MODER |= (1U << 10);	// turn pin 5 as o/p
	GPIOA -> MODER &= ~(1U << 11);	// PA5
	GPIOA -> MODER |= (1U << 12);	// turn pin 6 as o/p
	GPIOA -> MODER &= ~(1U << 13);	// PA6
	GPIOA -> MODER |= (1U << 14);	// turn pin 7 as o/p
	GPIOA -> MODER &= ~(1U << 15);	// PA7

	while(1)
	{
		if ((!(GPIOC -> IDR & (1<<0))) && (GPIOC -> IDR & (1<<1)))
		{
			GPIOA -> ODR |= (1U<<6);
			GPIOA -> ODR &= ~(1U<<7);
		}
		else if ((GPIOC -> IDR & (1<<0)) && (!(GPIOC -> IDR & (1<<1))))
		{
			GPIOA -> ODR |= (1U<<7);
			GPIOA -> ODR &= ~(1U<<6);
		}
		else
		{
			GPIOA -> ODR &= ~(1U<<6);
			GPIOA -> ODR &= ~(1U<<7);
		}

	}
}

void sudhakar_Callback()
{
	printf("The button is pressed\r\n");
	GPIOA -> ODR ^= PA5;
}
void SysTick_Handler(void)
{
	sudhakar_Callback();
}
void EXTI15_10_IRQHandler(void)
{
	// here we will first check the Priority Flag
	// if any previous interrupts are pending or not
	if ((EXTI -> PR & (1U<<13)) != 0)
	{
		// clear the same flag bit
		EXTI -> PR |= (1U<<13);
		// do your action for callback
		sudhakar_Callback();
	}
}
