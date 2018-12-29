
#include <Servo.h>

Servo servo;  // create servo object to control a servo

enum BridgeState {
  BRIDGE_DOWN,
  BRIDGE_UP
};

// defines pins numbers
const int trigPinFront = 6;
const int echoPinFront = 5;

const int trigPinBack = 9;
const int echoPinBack = 10;

const int redLED = 4;
const int greenLED = 2;

const int detectionThreshold = 13;

const int timeUp = 490;
const int timeDown = 430;
const int timeWait = 3000;

// defines variables
long duration;
int distance;

int frontDistance;
int backDistance;

int servoVal;
int state = BRIDGE_DOWN;

void setup() {
  pinMode(trigPinFront, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinFront, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinBack, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinBack, INPUT); // Sets the echoPin as an Input

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  servo.attach(7);
  servo.write(90);
  digitalWrite(redLED, HIGH);
  Serial.begin(9600); // Starts the serial communication
}


void loop() {
  frontDistance = measureFrontDistance();
  backDistance = measureBackDistance();
  servo.write(90);

  if (frontDistance <= detectionThreshold && state == BRIDGE_DOWN) {
    Serial.println("Moving up");
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    state = BRIDGE_UP;
    servo.write(180);
    delay(timeUp);
    servo.write(90);
    delay(timeWait);
  }

  else if (backDistance <= detectionThreshold && state == BRIDGE_UP) {
    Serial.println("Moving down");
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    state = BRIDGE_DOWN;
    servo.write(0);
    delay(timeDown);
    servo.write(90);
    delay(timeWait);
  }
    // Prints the distance on the Serial Monitor
    Serial.print("Front Distance: ");
    Serial.print(frontDistance);
    Serial.print("\t Back Distance: ");
    Serial.println(backDistance);
}

int measureFrontDistance() {
  //     Clears the trigPin
  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinFront, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}

int measureBackDistance() {
  //     Clears the trigPin
  digitalWrite(trigPinBack, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinBack, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinBack, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinBack, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}

