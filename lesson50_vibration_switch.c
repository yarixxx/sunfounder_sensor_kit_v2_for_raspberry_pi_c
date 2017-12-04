#include <wiringPi.h>
#include <stdio.h>
#include "t_extension.h"

#define VIBRATION_PIN	B17


int main(void) {
    wiringPiSetup();
    printf("Lesson: Vibration switch, knock the sensor!\n");
    pinMode(VIBRATION_PIN, INPUT);
    while (1) {
        if (digitalRead(VIBRATION_PIN) == LOW) {
	    printf("Knock-knock!\n");
            delay(1000);
	}
    }
    return 0;
}
