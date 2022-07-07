#include <stm32f4xx.h>
#include "delay.h"
#include "uart2.h"

void print(char *str);

int main(void)
{
	uart2_init_transmitter();
	uart2_init_receiver();
	int count = 0;
	while (1)
	{
		//uart2_transmit(uart2_receive());
		printf("Hello Nitin %d\r\n",count);
		count++;
	}
}

void print(char *str)
{
	while (*str != '\0')
	{
		uart2_transmit(*str);
		str++;
	}
}

