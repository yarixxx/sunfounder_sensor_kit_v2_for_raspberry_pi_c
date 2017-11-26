#include "t_extension.h"
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>

#define TRIG B17
#define ECHO B18

double raw_ultrasonic_measure(int trig, int echo) {
  digitalWrite(trig, LOW);
  delay(1);

  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);

  while(!(digitalRead(echo) == 1));
  int time1 = micros();

  while(!(digitalRead(echo) == 0));
  int time2 = micros();
  return (double)(time2 - time1) / 100;
}

double ultrasonic_measure(int trig, int echo) {
  double value1 = raw_ultrasonic_measure(trig, echo);
  delay(1);
  double value2 = raw_ultrasonic_measure(trig, echo);
  delay(1);
  double value3 = raw_ultrasonic_measure(trig, echo);
  delay(1);
  double value4 = raw_ultrasonic_measure(trig, echo);
  delay(1);
  double value5 = raw_ultrasonic_measure(trig, echo);
  return (value1 + value2 + value3 + value4 + value5) / 5;
} 

int main(void) {
  wiringPiSetup();
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

  while(1){
    double value = raw_ultrasonic_measure(TRIG, ECHO);
    printf("%0.1f cm\n", value);
    delay(1000);
  }

  return 0;
}
