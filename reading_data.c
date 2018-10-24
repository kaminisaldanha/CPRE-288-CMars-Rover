/*
 * reading_data.c
 *
 *  Created on: Apr 21, 2018
 *      Author: saldanha
 */

#define M_PI 3.14159265358979323846
#include "stdio.h"
#include "stdlib.h"
#include "lcd.h"
#include "Timer.h"
#include "servo.h"
#include "button.h"
#include "ping.h"
#include "ADC.h"
#include "uart.h"
#include <inc/tm4c123gh6pm.h>
#include "drop_sensor.h"
#include "open_interface.h"
#include "movement.h"
#include "Math.h"

// local variables
char print[100];
float sonarDist[180];
int irDist[180];
int curDeg = 0; // the current degrees we are at
int minIndex = 0; // looks for the index of the smallest object
int curRad = 0;
int found = 0; // to look for an object found it is used to look for anomalies in the IR sensor data
int check = 0; // used to get out if statement which checks for anomalies in the IR sensor data
int tracking = 0; // whether an object is detected or not

struct obstacle // struct for objects on field
{
    int radial;
    float dist;
    double size;
    int location;
};

struct obstacle arr_obst[10]; // array to store multiple objects
int i = 0;

/* returns linear distance based on radial size and distance on both edges */
float calcLinearDistance(float distance, int radial)
{
    return sqrt(
            2 * (distance * distance)
                    - (2 * distance * distance) * cos(radial * (M_PI / 180.0)));
}

/* returns index of smallest object */
int findSmallestObj()
{
    int k = 0;
    int j = 0;
    int minSize = arr_obst[j].size; // initialize minimum object size to first object
    for (j = 1; j < i; j++)
    {
        if (arr_obst[j].size < minSize) // find and set smallest object
        {
            minSize = arr_obst[j].size;
            k = j; // new variable for index of smallest object
        }
    }

    return k;
}

void print_data()
{
    curDeg = 0;
    i = 0;
    while (curDeg <= 180)
    {
        // read sensor data into variables

        //   curDeg = get_Degrees(); // store current degree value that servo is on

        // print data to putty
        // sprintf(praint, "%-7.2f    %-16d    %-19d\n", curDeg, irDist, sonarDist);
        // uart_sendStr(print);

        if ((irDist[curDeg] > 10 && irDist[curDeg] < 80)
                && (abs(irDist[curDeg] - sonarDist[curDeg]) < 15)) // check if object is within operational range
        {
            found++;

            if (found > 2 && !check)
            {
                curRad += 2;
                check = 1;
                arr_obst[i].dist = sonarDist[curDeg]; // set initial distance value to IR distance
            }
            if (check == 1)
            {
                curRad++; // increment object radial size
                tracking = 1;

            }
        }

        if ((tracking) && (irDist[curDeg] < 10 || irDist[curDeg] > 80)
                && (abs(irDist[curDeg] - sonarDist[curDeg]) > 15)) // check if sensor is no longer reading current object
        {
            tracking = 0;
            arr_obst[i].radial = curRad; // set object radial value
            arr_obst[i].size = calcLinearDistance(arr_obst[i].dist,
                                                  arr_obst[i].radial); // calculate linear distance
            arr_obst[i].location = (curDeg) - (curRad / 2); // set object central location
            curRad = 0;
            found = 0;
            check = 0;
            i++; // increment arr_obst for new object

        }
        curDeg++;
    }
    /*
     if (curDeg >= 180)
     {
     minIndex = findSmallestObj();
     counter_init(180 - arr_obst[minIndex].location, -1); // move servo opposite direction to central location of smallest object
     lcd_printf("Index:%d\nDistance: %.2f\nWidth: %.2lf\nDegrees: %d", i,
     arr_obst[minIndex].dist, // print attributes of smallest object
     arr_obst[minIndex].size, arr_obst[minIndex].radial);

     }

     */
    sprintf(print, "%d\n", i);
    uart_sendStr(print);
    int l = 0;
    for (l = 0; l < i; l++)
    {
        sprintf(print, "%.2f %.2lf %d\n ",
                arr_obst[l].dist, // print attributes of smallest object
                arr_obst[l].size, arr_obst[l].location);
        uart_sendStr(print);
    }
}

void read_data()
{
// print headings for data on putty

   // sprintf(print, "Degrees    IR Distance (cm)    Sonar Distance (cm)\n");
   // uart_sendStr(print);

    int j = 0;
    for (j = 0; j < 180; j++)
    {
        sonarDist[j] = ping_read(); // read ping sensor
        irDist[j] = ADC_distance(ADC_read(0xA)); // read IR sensor
        counter_init(1, 1); // increment servo by 1 degree
        // print data to putty
       // sprintf(print, "%-7d    %-16d    %-19.0f\n", j, irDist[j],
        //        sonarDist[j]);
      //  uart_sendStr(print);
    }
    counter_init(180, -1);

}

