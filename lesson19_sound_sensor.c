#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>

#define PCF 120

int main (void) {
    wiringPiSetup();
    pcf8591Setup(PCF, 0x48);
    while(1) {
	int value;
        value = analogRead(PCF);
	if (value < 100) {
	    printf("Sound  %d\n", value);
	    delay(100);
	}
    }
    return 0;
}
