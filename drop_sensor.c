/*
 * drop_sensor.c
 *
 *  Created on: Apr 17, 2018
 *      Author: saldanha
 */

#include "open_interface.h"
#include "drop_sensor.h"
#include "uart.h"

int drop(oi_t *sensor) // 1 -> drop on left, 2 -> drop on right, 0 -> no drop
{
    //char print[10];
    oi_update(sensor);

    int dropFrontLeft = sensor->cliffFrontLeft;
    //  sprintf(print, "DropLeftFront: %d\n", dropFrontLeft);
    //  uart_sendStr(print);
    int dropFrontRight = sensor->cliffFrontRight;
    // sprintf(print, "DropRightFront: %d\n", dropFrontRight);
    //uart_sendStr(print);
    int dropLeft = sensor->cliffLeft;
   //sprintf(print, "DropLeft: %d\n", dropLeft);
   // uart_sendStr(print);
    int dropRight = sensor->cliffRight;
    //sprintf(print, "DropRight: %d\n", dropRight);
   // uart_sendStr(print);

    if (dropFrontLeft) // if left front cliff sensor is 1, stop robot and update sensor
    {
        oi_setWheels(0, 0);
       // uart_sendStr("Cliff Front left\n");
        dropL = dropLeft; // saves boolean value if left sensor sensed drop
        return 1;
    }

    if (dropFrontRight) // if right front cliff sensor is 1, stop robot and update sensor
    {
        oi_setWheels(0, 0);
       // uart_sendStr("Cliff Front right\n");
        dropR = dropRight; // saves boolean value if right sensor sensed drop
        return 1;
    }

    if (dropLeft) // if left cliff sensor is 1, stop robot and update sensor
    {
        oi_setWheels(0, 0);
       // uart_sendStr("Cliff left\n");
        dropL = dropLeft; // saves boolean value if left sensor sensed drop
        return 1;
    }

    if (dropRight) // if right cliff sensor is 1, stop robot and update sensor
    {
        oi_setWheels(0, 0);
       // uart_sendStr("Cliff right\n");
        dropR = dropRight; // saves boolean value if right sensor sensed drop
        return 1;
    }

    return 0;
}

int sense_boundary(oi_t *sensor, int bound[])
{
    //char right[10];
    //char left[10];
    oi_update(sensor);
    int rightfrontB = sensor->cliffFrontRightSignal;
    // sprintf(right, "RightFront: %d\n", rightfrontB);
    // uart_sendStr(right);
    int leftfrontB = sensor->cliffFrontLeftSignal;
    // sprintf(left, "LeftFront: %d\n", leftfrontB);
    // uart_sendStr(left);
    int rightB = sensor->cliffRightSignal;
    // sprintf(right, "Right: %d\n", rightB);
    // uart_sendStr(right);
    int leftB = sensor->cliffLeftSignal;
    // sprintf(left, "Left: %d\n", leftB);
    // uart_sendStr(left);
    int boundary = 0;

  /*  if (rightB > 2800 && leftB > 2800)
    {
        oi_setWheels(0, 0);
      //  uart_sendStr("Boundary straight\n");
        boundary = 1;
    } */

    // init boundary values to all 0
    int i = 0;
    for (i = 0; i < 4; i++) {
        bound[i] = 0;
    }


    if (leftfrontB > 2800)
    {
        oi_setWheels(0, 0);
      //  uart_sendStr("Boundary Front Left\n");
        boundary = 1;
        bound[0] = 1;
    }

    if (rightfrontB > 2800)
    {
        oi_setWheels(0, 0);
      //  uart_sendStr("Boundary Front Right\n");
        boundary = 1;
        bound[1] = 1;
    }

    if (leftB > 2800)
    {
        oi_setWheels(0, 0);
      //  uart_sendStr("Boundary Left\n");
        boundary = 1;
        bound[2] = 1;
    }

    if (rightB > 2800)
    {
        oi_setWheels(0, 0);
      //  uart_sendStr("Boundary Right\n");
        boundary = 1;
        bound[3] = 1;
    }

    return boundary;
}

