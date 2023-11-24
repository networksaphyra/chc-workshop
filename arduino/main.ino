/* 
Code for Automatic Soap Dispenser
Cameron Heights Engineering
*/

#include <Servo.h>

// Initialize Variables
Servo micro_servo;

const int ULTRASONIC_TRIGGER = 9;
const int ULTRASONIC_ECHO = 8;
const int MICRO_SERVO_SIGNAL = 13;

// Distance for which to trigger servo in cm
const int DISTANCE_VALUE = 20;

// Time for which to keep soap on in ms
const int SOAP_DURATION = 1500;

// Creates an ultrasonic burst, returns duration of pulse (Upon sound wave coming back, "ECHO" will be set to HIGH for the duration of the sound wave)
float ultrasonic_burst() {
    digitalWrite(ULTRASONIC_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER, LOW);

    return pulseIn(ULTRASONIC_ECHO, HIGH);
}

void dispense_soap() {
    micro_servo.write(90);
    delay(SOAP_DURATION);
    micro_servo.write(0);
    delay(SOAP_DURATION);
}

void setup() {
    pinMode(ULTRASONIC_TRIGGER, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);
    micro_servo.attach(MICRO_SERVO_SIGNAL);

    Serial.begin(9600);
}

void loop() {
    float duration, distance;

    duration = ultrasonic_burst();
    // Calculate distance using d=vt, where v is the speed of sound for a millisecond
    distance = (duration * 0.0343) / 2; 
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < DISTANCE_VALUE) {
        dispense_soap();
    }
}
