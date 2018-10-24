/*
 * drop_sensor.h
 *
 *  Created on: Apr 17, 2018
 *      Author: saldanha
 */

#ifndef DROP_SENSOR_H_
#define DROP_SENSOR_H_

#include "open_interface.h"

int dropL, dropR, leftBoundary, rightBoundary;

//looks for hole in the maze by using cliffLeft, CliffRight from open interface
int drop(oi_t *sensor);

//looks for boundary in the maze by using the cliffLeftSignal, cliffRightSignal from open interface
int sense_boundary(oi_t *sensor, int bound[]);

#endif /* DROP_SENSOR_H_ */
