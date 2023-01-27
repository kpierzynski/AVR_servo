#include "servo.h"

void servo_init()
{
	CHANNEL_A_OUT;
	CHANNEL_A_LOW;

#if USE_CHANNELS == 2
	CHANNEL_B_OUT;
	CHANNEL_B_LOW;
#endif

	// Set Timer1 in Fast PWM mode (14)
	TCCR1A |= (1 << WGM11); // | (1 << WGM10);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);

	// Prescaler
	TCCR1B |= (1 << CS11); // Set to 8

	// Set frequency
	ICR1 = FREQUENCY_OCR + F_CALLIBRATION;

	OCR1A = 0;

	TIMSK1 |= (1 << OCIE1A) | (1 << ICIE1);

#if USE_CHANNELS == 2
	TIMSK1 |= (1 << OCIE1B);
	OCR1B = 0;
#endif
}

#if USE_CHANNELS == 2
void servo_us(uint8_t channel, uint16_t us)
{
	switch (channel)
	{
	case CHANNEL_A:
		CHANNEL_A_REG = us * MULTIPLAYER;
		break;

	case CHANNEL_B:
		CHANNEL_B_REG = us * MULTIPLAYER;
		break;

	default:
		break;
	}
}
#elif USE_CHANNELS == 1
void servo_us(uint16_t us)
{
	CHANNEL_A_REG = us * MULTIPLAYER;
}
#endif

ISR(TIMER1_COMPA_vect)
{
	CHANNEL_A_LOW;
}

#if USE_CHANNELS == 2
ISR(TIMER1_COMPB_vect)
{
	CHANNEL_B_LOW;
}
#endif

ISR(TIMER1_CAPT_vect)
{
	CHANNEL_A_HIGH;
	CHANNEL_B_HIGH;
}