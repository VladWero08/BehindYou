#include <QTRSensors.h>

// PINs connected to the motor 1
const int m11PIN = 7;
const int m12PIN = 6;
const int m1Enable = 11;
// speed of motor 1
int m1Speed = 0;

// PINs connected to the motor 1
const int m21PIN = 5;
const int m22PIN = 4;
const int m2Enable = 12;
// speed of motor 2
int m2Speed = 0;

// maximum values for speed of the motors
const int baseSpeed = 100;
const int maxSpeed = 255;
const int minSpeed = -255;

const int sensorSize = 6;
// array where the sensor's values will be stored
const int sensors[sensorSize] = {0, 0, 0, 0, 0};

const float Kp = 1;
const float Ki = 0;
const float Kd = 0;

int P = 1;
int I = 0;
int D = 0;

int error = 0;
int lastError = 0;

QTRSensors qtr;

void setup() {
  // set up for motor's PINs
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const int uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorSize);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void PID() {}

void setMotorSpeed() {}