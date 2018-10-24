/*
 * ping.c
 *
 *  Created on: Mar 21, 2018
 *      Author: saldanha
 */

#include "ping.h"
#include "Timer.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

volatile enum
{
    LOW, HIGH, DONE
} state;
volatile unsigned rising_time;
volatile unsigned falling_time;
unsigned long time_diff;
volatile unsigned long current_time = 0;
volatile unsigned long last_time;
int overflow;
int dist;

void TIMER3B_HANDLER(void)
{
    last_time = current_time;
    if (state == LOW)
    {
        rising_time = TIMER3_TBR_R;
        current_time = rising_time;
        state = HIGH;
    }
    else if (state == HIGH)
    {
        falling_time = TIMER3_TBR_R;
        state = DONE;
    }
    TIMER3_ICR_R = 0x0400; //clear flag
}

void ping_init()
{

    // ***initialize GPIO***

    // initialize clock for port B
    SYSCTL_RCGCGPIO_R |= 0x02;

    // initialize direction for PB3 to output
    GPIO_PORTB_DIR_R |= 0x08;

    // configure alternate function for PB3
    GPIO_PORTB_AFSEL_R |= 0x08;

    // initialize digital enable for PB3
    GPIO_PORTB_DEN_R |= 0x08;

    // initialize peripheral control
    GPIO_PORTB_PCTL_R |= 0x00007000;

    // ***initialize timers***

    // enable system clock
    SYSCTL_RCGCTIMER_R |= 0x08;

    //  disable timer B
    TIMER3_CTL_R &= 0b01111111;

    // initialize GPTMCTL, timer features
    TIMER3_CTL_R |= 0xC00;

    // initialize GPTMCFG, configures whether a 32 or 64 bit timer is used
    TIMER3_CFG_R |= 0x00000004;

    // initialize GPTMTBMR, controls timer mode
    TIMER3_TBMR_R |= 0x00000007;
    TIMER3_TBMR_R |= 0b10000;

    // set timer prescaler(extended timer) and load initvalue to max
    TIMER3_TBPR_R = 0xFF;

    // 24-bit timeout value
    TIMER3_TBILR_R = 0xFFFF;

    /**** initialize interrupts for timer****/
    TIMER3_ICR_R = (TIMER_ICR_TBTOCINT | TIMER_ICR_CBECINT); //clears TIMER3 time-out interrupt flags
    TIMER3_IMR_R |= TIMER_IMR_CBEIM; //enable TIMER3(A&B) time-out interrupts
    NVIC_EN1_R = 0x00000010; //enable the interrupt register on the NVIC

    IntRegister(INT_TIMER3B, TIMER3B_HANDLER);
    IntMasterEnable(); // enable global interrupts

}

void send_pulse()
{
    TIMER3_CTL_R &= 0b1111111011111111;
    GPIO_PORTB_AFSEL_R &= 0b11110111;

    GPIO_PORTB_DIR_R |= 0x08; // set PB3 as output
    GPIO_PORTB_DATA_R |= 0x08; // set PB3 to high
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= 0xF7; // set PB3 to low
    GPIO_PORTB_DIR_R &= 0xF7; // set PB3 as input
    GPIO_PORTB_AFSEL_R |= 0x08;

    TIMER3_CTL_R |= 0x00000100; //enable timer 3B

    state = LOW;

    while (state != DONE)
    {

    }
}

unsigned int ping_read()
{
    send_pulse();
    timer_waitMillis(20);
    dist = calcDist();
    return dist;
}

unsigned long calcDist()
{
    time_diff = falling_time - rising_time;
    return ((time_diff/16000000.0) * (34000.0)) / 2.0;
}

int get_pulseWidth() {
    return time_diff;
}

int get_pulseWidth_millis() {
    return (time_diff / 16000000) * 1000;
}

int overflowCalc() {
    overflow += (current_time < last_time);
    time_diff = ((unsigned long)overflow<<24) + current_time - last_time;;
    return overflow;
}
