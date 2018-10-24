/*
 * movement.h
 *
 *  Created on: Jan 26, 2018
 *      Author: saldanha
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include "open_interface.h"

int bumpL, bumpR;

int move_forward(oi_t *sensor, int centimeters);

int turn_clockwise(oi_t *sensor, int degrees);

int turn_counterclockwise(oi_t *sensor, int degrees);

int move_backward(oi_t *sensor, int centimeters);

//looks to see
int find_object(oi_t *sensor);

#endif /* MOVEMENT_H_ */
