#include "t_extension.h"
#include <wiringPi.h>
#include <stdio.h>

#define DHTPIN B17

void initializeDht() {
    pinMode(DHTPIN, OUTPUT);
    digitalWrite(DHTPIN, LOW);
    delay(18);
    digitalWrite(DHTPIN, HIGH);
    delayMicroseconds(40); 
    pinMode(DHTPIN, INPUT);
}

void read_dht11_dat() {
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

		if (counter == 255) break;

		if ((i >= 4) && (i%2 == 0)) {
			dht11_dat[j/8] <<= 1;
			if (counter > 16)
				dht11_dat[j/8] |= 1;
			j++;
		}
	}

    int sum = dht11_dat[0] + dht11_dat[2];
    if (sum == dht11_dat[4]) {        
        printf("Humidity = %d\n", dht11_dat[0]);
        printf("Temperature C = %d\n", dht11_dat[2]);
    }
}

int main (void) {
    wiringPiSetup();
    printf("Start!\n");
    while (1) {
      initializeDht();
	  read_dht11_dat();
	  delay(1000);
    }
    return 0;
}
