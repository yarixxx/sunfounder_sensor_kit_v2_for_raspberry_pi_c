#include "t_extension.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXTIMINGS 85

#define DHTPIN B25

int dht11_dat[5] = {0,0,0,0,0};

void read_dht11_dat() {
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;

	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

	pinMode(DHTPIN, OUTPUT);
	digitalWrite(DHTPIN, LOW);
	delay(18);
	digitalWrite(DHTPIN, HIGH);
	delayMicroseconds(40); 
	pinMode(DHTPIN, INPUT);

	for ( i=0; i< MAXTIMINGS; i++) {
		counter = 0;
		while (digitalRead(DHTPIN) == laststate) {
			counter++;
			delayMicroseconds(1);
			if (counter == 255) {
				break;
			}
		}
		laststate = digitalRead(DHTPIN);

		if (counter == 255) break;

		if ((i >= 4) && (i%2 == 0)) {
			dht11_dat[j/8] <<= 1;
			if (counter > 16)
				dht11_dat[j/8] |= 1;
			j++;
		}
	}

	if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)) ) {
            printf("Humidity = %d.%d %%\n", dht11_dat[0], dht11_dat[1]);
	    printf("Temperature C = %d.%d *C (%.1f *F)\n", dht11_dat[2], dht11_dat[3]);
	}
}

int main (void) {
    wiringPiSetup();
    printf("Start!\n");
    while (1) {
	read_dht11_dat();
	delay(1000);
    }
    return 0;
}
