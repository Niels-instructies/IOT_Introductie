

// Include NewPing Library
#include "NewPing.h"

// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 2
#define ECHO_PIN 1

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400	

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//distance variable
int distance = 0;

// led
const int ledPin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Serial.println("Hello, ESP32-S2!");
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = sonar.ping_cm();
	if (distance > 0 && distance < 20) {
    // Send the message over the serial port
    Serial.println("Object detected");
    digitalWrite(ledPin, HIGH);
  } else if (distance >= 20) {
    // Send the message over the serial port
    Serial.println("Everything seems fine");
    digitalWrite(ledPin, LOW);
  }

	delay(1000);
}




