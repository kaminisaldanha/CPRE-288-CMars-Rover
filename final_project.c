/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

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
#include "reading_data.h"
#include "Math.h"
#include "song.h"

void flashLED()
{
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        oi_setLeds(0, 0, 255, 255);
        timer_waitMillis(500);
        oi_setLeds(0, 0, 255, 0);
        timer_waitMillis(500);
    }
}

void printSensors(oi_t *sensor)
{
    char print[500];
    int bound[4];
    sense_boundary(sensor, bound);
    sprintf(print,
            "\n\nBumpLeft: %d \nBumpRight: %d\nCliffLeft: %d\nCliffRight: %d\nCliffFrontLeft: %d\nCliffFrontRight: %d\nBoundaryLeft: %d\nBoundaryRight: %d\nBoundaryFrontLeft: %d\nBoundaryFrontRight: %d\n\n}",
            sensor->bumpLeft, sensor->bumpRight, sensor->cliffLeft,
            sensor->cliffRight, sensor->cliffFrontLeft,
            sensor->cliffFrontRight, bound[2], bound[3], bound[0], bound[1]);
    uart_sendStr(print);
}

int main(void)


{

    lcd_init();
    uart_init();
    button_init();
    servo_init();
    ping_init();
    ADC_init();

    // init

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    // driving

    char temp;
    int dist;
    int angle;
    char print[100];
    while (1)
    {
        oi_update(sensor_data);

        temp = uart_receive();

        if (temp == 'w')
        {
            dist = move_forward(sensor_data, 5);
            sprintf(print, "Dist Moved %d", dist);
            uart_sendStr(print);
        }

        else if (temp == 's')
        {
            dist = move_backward(sensor_data, 3*5);
            sprintf(print, "Dist Moved %d", dist);
            uart_sendStr(print);
        }

        else if (temp == 'a')
        {
            angle = turn_counterclockwise(sensor_data, 5);
            sprintf(print, "Angle Moved %d", angle);
            uart_sendStr(print);
        }

        else if(temp == 'b')
        {
            angle = turn_counterclockwise(sensor_data, 90);
            sprintf(print, "Angle Moved %d", angle);
            uart_sendStr(print);

        }

        else if (temp == 'd')
        {
            angle = turn_clockwise(sensor_data, 5);
            sprintf(print, "Angle Moved %d", angle);
            uart_sendStr(print);
        }

        else if(temp == 'c')
        {
            angle = turn_clockwise(sensor_data, 90);
            sprintf(print, "Angle Moved %d", angle);
            uart_sendStr(print);
        }

        else if (temp == 'f')
        {
            play_song(1);
        }

        else if (temp == 'r')
        {
            read_data();
            print_data();
        }
        printSensors(sensor_data);
    }

/*
     ADC_init();
     lcd_init();
     int sum = 0;
     int i = 0;
     int average;
     while (1) {
         for (i = 0; i < 1000; i++) { // takes an average of 1000 samples
              sum = sum + ADC_read(0xA);
         }
         timer_waitMillis(500); // waits to display print statement
         average = sum / 1000;
         lcd_printf("Voltage: %d\nDistance: %d cm", average, ADC_distance(average));
         sum = 0;
     }
*/
}
