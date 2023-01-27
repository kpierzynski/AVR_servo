#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "servo.h"

int main(void)
{
	uart_init();
	servo_init();

	sei();
	uart_puts("start\r\n");

	servo_us(CHANNEL_A, 1500);
	servo_us(CHANNEL_B, 1000);

	while (1)
	{
	}
	return 0;
}
