#include <QTRSensors.h>

// PINs connected to the motor 1
const int m11Pin = 7;
const int m12Pin = 6;
const int m1Enable = 11;
// speed of motor 1
int m1Speed = 0;

// PINs connected to the motor 1
const int m21Pin = 5;
const int m22Pin = 4;
const int m2Enable = 10;
// speed of motor 2
int m2Speed = 0;

// maximum values for speed of the motors
const int baseSpeed = 100;
const int minSpeed = 0;
const int maxSpeed = 255;

const int sensorSize = 6;
// array where the sensor's values will be stored
const int sensors[sensorSize] = {0, 0, 0, 0, 0, 0};

const float Kp = 4;
const float Ki = 0.0001;
const float Kd = 1;

int P = 0;
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
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorSize);

  for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();
  }

  Serial.begin(9600);
}

void loop() {
  readError(error);

  float motorSpeed = PID(error, lastError);

  m1Speed = baseSpeed;
  m2Speed = baseSpeed;

  if (error < 0) {
    m1Speed += motorSpeed;
  } else {
    m2Speed -= motorSpeed;
  } 

  m1Speed = constrain(m1Speed, minSpeed, maxSpeed);
  m2Speed = constrain(m2Speed, minSpeed, maxSpeed);

  updateLastError(error, lastError);
}

void readError(int &error) {
  // read the sensor's values and save the in the array
  // and map the computed error to a speed for the motors
  error = map(qtr.readLineBlack(sensors), 0, 5000, -50, 50);
}

void updateLastError(int error, int &lastError) {
  // change the last error to be equal
  // to the current error
  lastError = error;
}

float PID(int error, int &lastError) {
  // update proportional
  P = error;
  // update integral
  I = I + error;
  // update derivative
  D = error - lastError;

  // calculate the PID speed 
  return Kp * P + Ki * I + Kd * D; 
}

void setMotorSpeed(int motor1Speed, int motor2Speed) {
  // one of the two motors is running backwards,
  // so reverse the motor's speed
  motor2Speed = -motor2Speed;

  if (motor1Speed == 0) {
    digitalWrite(m11Pin, LOW);
    digitalWrite(m12Pin, LOW);
    analogWrite(m1Enable, motor1Speed);
  } else {
    if (motor1Speed > 0) {
      digitalWrite(m11Pin, HIGH);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    }
    if (motor1Speed < 0) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, HIGH);
      analogWrite(m1Enable, -motor1Speed);
    }
  }
  if (motor2Speed == 0) {
    digitalWrite(m21Pin, LOW);
    digitalWrite(m22Pin, LOW);
    analogWrite(m2Enable, motor2Speed);
  } else {
    if (motor2Speed > 0) {
      digitalWrite(m21Pin, HIGH);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    }
    if (motor2Speed < 0) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, HIGH);
      analogWrite(m2Enable, -motor2Speed);
    }
  }
}