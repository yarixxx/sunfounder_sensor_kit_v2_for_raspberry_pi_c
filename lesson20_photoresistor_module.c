#include "t_extension.h"
#include <wiringPi.h>
#include <stdio.h>

#define LIGHT_STATUS_PIN B17

int main(void) {
    printf("Lesson 20. Photoresistor Module.\n");
    wiringPiSetup();	
    pinMode(LIGHT_STATUS_PIN, INPUT);
    int light_status = LOW;
    while(1){
        int new_light_status = digitalRead(LIGHT_STATUS_PIN);
	if (new_light_status != light_status) {
	    light_status = new_light_status;
            if (light_status == 0) {
	        printf("Light is on.\n");
	    } else {
	        printf("Light is off.\n");
	    }
	}
        // This delay prevents fake events.
	delay(400);	
    }
    return 0;
}

