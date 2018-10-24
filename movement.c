/*
 * movement.c
 *
 *  Created on: Jan 26, 2018
 *      Author: saldanha
 */

#include "movement.h"
#include "open_interface.h"
#include "drop_sensor.h"

// looks to see which side of robot was bumped (returns 1 for left and 2 for right and 0 for nothing)
int find_object(oi_t *sensor)
{
    int sensorLeft = sensor->bumpLeft;
    int sensorRight = sensor->bumpRight;

    if (sensorLeft) // if left sensor is bumped, stop robot and save bool into bumpL
    {
        oi_update(sensor);
        oi_setWheels(0, 0);
        bumpL = sensorLeft; // not sure if needed
        return 1;
    }

    if (sensorRight) // if right sensor is bumped, stop robot and save bool into bumpR
    {
        oi_update(sensor);
        oi_setWheels(0, 0);
        bumpR = sensorRight; // not sure if needed
        return 2;
    }

    return 0;
}

// moves iRobot forward certain amount of centimeters
int move_forward(oi_t *sensor, int centimeters)
{
    oi_update(sensor);
    int sum = 0, boundary = 0, cliff = 0;
    int bound[4];
    boundary = sense_boundary(sensor, bound);
    cliff = drop(sensor);
    if (!boundary && !cliff)
    {
        oi_setWheels(76, 75);
    }

    while (sum < centimeters * 10 && !boundary && !cliff)
    {
        oi_update(sensor);
        int bound[4];
        boundary = sense_boundary(sensor, bound);
        cliff = drop(sensor);
        if (boundary || cliff)
        {
            break;
        }
        int sensorLeft = sensor->bumpLeft;
        int sensorRight = sensor->bumpRight;

        if (sensorLeft) // if left sensor is bumped, stop robot and save bool into bumpL
        {
            oi_update(sensor);
            sum += sensor->distance;
            oi_setWheels(0, 0);
            bumpL = sensorLeft;
            return sum;
        }

        if (sensorRight) // if right sensor is bumped, stop robot and save bool into bumpR
        {
            oi_update(sensor);
            sum += sensor->distance;
            oi_setWheels(0, 0);
            bumpR = sensorRight;
            return sum;
        }
        sum += sensor->distance;

    }
    oi_setWheels(0, 0);

    return sum;
}

int move_backward(oi_t *sensor, int centimeters)
{
    int bound[4];
    sense_boundary(sensor, bound);
    int sum = 0;
    oi_setWheels(-75, -75);
    while (sum > centimeters * 10 * -1)
    { // when sum reaches negative distance value, stop robot
        oi_update(sensor);
        sum += sensor->distance;
    }
    oi_setWheels(0, 0);
    return sum;
}

int turn_clockwise(oi_t *sensor, int degrees)
{
    int sum = 0;
    oi_setWheels(-100, 100);
    while (sum > degrees * -1)
    { // when sum reaches negative angle value, the robot stops turning
        oi_update(sensor);
        sum += sensor->angle;
    }
    oi_setWheels(0, 0);
    return sum;
}

int turn_counterclockwise(oi_t *sensor, int degrees)
{
    int sum = 0;
    oi_setWheels(100, -100);
    while (sum < degrees)
    { // when sum reaches positive angle value, the robot stops turning
        oi_update(sensor);
        sum += sensor->angle;
    }
    oi_setWheels(0, 0);
    return sum;
}

