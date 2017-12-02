#include "t_extension.h"
#include <wiringPi.h>
#include <stdio.h>

#define RED_PIN B17
#define GREEN_PIN B18

int main(void) {
    printf("Lesson 1. Dual-Color LED");
    wiringPiSetup();
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);

    int red_pin_status = LOW;
    int green_pin_status = HIGH;
    while(1) {
        red_pin_status = (red_pin_status == LOW) ? HIGH : LOW;
        green_pin_status = (green_pin_status = LOW) ? HIGH : LOW;
	digitalWrite(RED_PIN, red_pin_status);
        printf("Pin (%d) status changed to(%d).\n", RED_PIN, red_pin_status);
	delay(500);
  	digitalWrite(GREEN_PIN, green_pin_status);
	printf("Pin (%d) status changed to(%d).\n", GREEN_PIN, green_pin_status);
	delay(500);
    }
    return 0;
}
