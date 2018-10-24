/*
 * ping.h
 *
 *  Created on: Mar 21, 2018
 *      Author: saldanha
 */

#ifndef PING_H_
#define PING_H_

#include <inc/tm4c123gh6pm.h>

void TIMER3B_HANDLER(void);

void ping_init();

void send_pulse();

unsigned int ping_read();

unsigned long calcDist();

int get_pulseWidth();

int overflowCalc();

int get_pulseWidth_millis();



#endif /* PING_H_ */
