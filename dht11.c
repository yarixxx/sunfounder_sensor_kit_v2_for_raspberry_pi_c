#include <stdio.h>


void initializeDht(int dhtPin) {
    pinMode(dhtPin, OUTPUT);
    digitalWrite(dhtPin, LOW);
    delay(18);
    digitalWrite(dhtPin, HIGH);
    delayMicroseconds(40); 
    pinMode(dhtPin, INPUT);
}

void read_dht11_dat(int dhtPin) {
    initializeDht(dhtPin);
    int dht11_dat[5];
    dht11_dat[0] = dht11_dat[2] = dht11_dat[4] = 0;
    int laststate = HIGH;
	int counter = 0;
    int j = 0;
    int i;
	for (i=0; i< 85; i++) {
		counter = 0;
		while (digitalRead(dhtPin) == laststate) {
			counter++;
			delayMicroseconds(1);
			if (counter == 255) break;
		}
		laststate = digitalRead(dhtPin);

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
	return {dht11_dat[0], dht11_dat[2]};        
    }
    return {}
}
