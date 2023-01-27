#ifndef __SERVO_H_
#define __SERVO_H_

#include <avr/io.h>
#include <avr/interrupt.h>

// ================= CONFIG
// How many channels to use? Valid options are 1 or 2.
#define USE_CHANNELS 2

#define PRESCALER 8UL
#define F_PWM 50UL

#define CHANNEL_A_PIN PD3
#define CHANNEL_A_PORT PORTD
#define CHANNEL_A_DDR DDRD

#define CHANNEL_B_PIN PD5
#define CHANNEL_B_PORT PORTD
#define CHANNEL_B_DDR DDRD

// PWM frequency can vary, change this to calibrate
#define F_CALLIBRATION 60

// ================= END CONFIG

#define MULTIPLAYER (F_CPU / 1000000UL) / PRESCALER
#define FREQUENCY_OCR F_CPU / PRESCALER / F_PWM - 1

#define CHANNEL_A 0
#define CHANNEL_A_REG OCR1A

#define CHANNEL_A_OUT CHANNEL_A_DDR |= (1 << CHANNEL_A_PIN)
#define CHANNEL_A_LOW CHANNEL_A_PORT &= ~(1 << CHANNEL_A_PIN)
#define CHANNEL_A_HIGH CHANNEL_A_PORT |= (1 << CHANNEL_A_PIN)

#define CHANNEL_B 1
#define CHANNEL_B_REG OCR1B

#define CHANNEL_B_OUT CHANNEL_B_DDR |= (1 << CHANNEL_B_PIN)
#define CHANNEL_B_LOW CHANNEL_B_PORT &= ~(1 << CHANNEL_B_PIN)
#define CHANNEL_B_HIGH CHANNEL_B_PORT |= (1 << CHANNEL_B_PIN)

void servo_init();

#if USE_CHANNELS == 2
void servo_us(uint8_t channel, uint16_t us);
#elif USE_CHANNELS == 1
void servo_us(uint16_t us);
#endif

#endif