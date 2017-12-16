#include "t_extension.h"
#include <wiringPi.h>
#include <stdio.h>

#define DHTPIN B25

void initializeDht() {
    pinMode(DHTPIN, OUTPUT);
    digitalWrite(DHTPIN, LOW);
    delay(18);
    digitalWrite(DHTPIN, HIGH);
    delayMicroseconds(40); 
    pinMode(DHTPIN, INPUT);
}

int read_dht11_dat() {
    int dht11_dat[5];
    dht11_dat[0] = dht11_dat[2] = dht11_dat[4] = 0;
    int laststate = HIGH;
	int counter = 0;
    int j = 0;
    int i;
	for (i=0; i< 85; i++) {
		counter = 0;
		while (digitalRead(DHTPIN) == laststate) {
			counter++;
			delayMicroseconds(1);
			if (counter == 255) break;
		}
		laststate = digitalRead(DHTPIN);

		if ((i >= 4) && (i%2 == 0)) {
			dht11_dat[j/8] <<= 1;
			// dht11_dat[j/8] = 0;
			if (counter > 16) {
				dht11_dat[j/8] |= 1;
            }
			j++;
		}
	}

    int sum = dht11_dat[0] + dht11_dat[2];
    if (sum == dht11_dat[4]) {        
        return dht11_dat[0];
    }
    return 1;
}

int main (void) {
    wiringPiSetup();
    printf("Start!\n");
    while (1) {
      initializeDht();
	  int humidity = read_dht11_dat();
      printf("Humidity: %d\n");
	  delay(1000);
    }
    return 0;
}
