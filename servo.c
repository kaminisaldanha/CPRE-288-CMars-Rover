/*
 * servo.c
 *
 *  Created on: Mar 27, 2018
 *      Author: saldanha
 */

#include "servo.h"
#include "Timer.h"
#include <inc/tm4c123gh6pm.h>
#include "button.h"

volatile enum
{
    LOW, HIGH, DONE
} state;
volatile unsigned rising_time;
volatile unsigned falling_time;
unsigned int pwm_period;
int match_value;
float refDegrees;

void counter_init(float degrees, int dir)
{
    //***counter initialization***

    // start value in clock cycles
    pwm_period = 320000; // 20 ms period in timer ticks (16Mhz*.020)
    if (dir == -1)
    { // change direction of degrees based on orient
        degrees = degrees * -1.0;
    }
    refDegrees += degrees;
    match_value += (((35700.0 - 7500.0) / 180.0) * degrees);
    if (refDegrees < 0)
    { // make sure servo doesn't go past 0
        match_value = 7500;
        refDegrees = 0;
    }
    if (refDegrees > 180)
    { // make sure servo doesn't go past 180
        match_value = 35700;
        refDegrees = 180;
    }

    TIMER1_TBMATCHR_R = (320000 - match_value) & 0xFFFF; // counter after 1 high pulse width (period - high pulse)
    TIMER1_TBPMR_R = (320000 - match_value) >> 16; // save same value into this one too for prescaler

}

void servo_init()
{

    //***GPIO Initializations***

    // initialize clock for port B
    SYSCTL_RCGCGPIO_R |= 0x02;

    // initialize direction for PB5 to output
    GPIO_PORTB_DIR_R |= 0x20;

    // configure alternate function for PB5
    GPIO_PORTB_AFSEL_R |= 0x20;

    // initialize digital enable for PB5
    GPIO_PORTB_DEN_R |= 0x20;

    // initialize peripheral control
    GPIO_PORTB_PCTL_R |= 0x00700000;

    // ***initialize timers***

    // enable system clock
    SYSCTL_RCGCTIMER_R |= 0x02;

    //  disable timer B
    TIMER1_CTL_R &= 0b011111111;

    // initialize GPTMCFG, configures whether a 16 bit or 32 bit timer is used
    TIMER1_CFG_R |= 0x00000004;

    // initialize GPTMTBMR, controls timer mode
    TIMER1_TBMR_R |= 0x0000000A;

    match_value = 7500; // initialize match value for 0 degree position

    refDegrees = 0; // initialize displayed degrees to 0

    TIMER1_TBILR_R = 320000 & 0xFFFF; // lower 16 bits of the pwm period
    TIMER1_TBPR_R = 320000 >> 16; // shift it 16 to get the next 8 bits

    TIMER1_TBMATCHR_R = (320000 - 7500) & 0xFFFF; // counter after 1 high pulse width (period - high pulse)
    TIMER1_TBPMR_R = (320000 - 7500) >> 16; // save same value into this one too for prescaler


    //  enable timer B
    TIMER1_CTL_R |= 0b100000000;

}

float get_Degrees()
{ // return degrees
    return refDegrees;
}

int get_match_value()
{ // return running counter value
    return match_value;
}

