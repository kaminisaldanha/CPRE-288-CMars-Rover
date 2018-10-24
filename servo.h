/*
 * servo.h
 *
 *  Created on: Mar 27, 2018
 *      Author: saldanha
 */

#ifndef SERVO_H_
#define SERVO_H_


void servo_init();
void counter_init(float degrees, int dir);
float get_Degrees();
int get_match_value();


#endif /* SERVO_H_ */
