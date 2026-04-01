#include <Servo.h>

// -------------------- Flame Sensor Pins --------------------
#define FLAME_LEFT   A0
#define FLAME_CENTER A1
#define FLAME_RIGHT  A2

// -------------------- Motor Driver Pins --------------------
#define LEFT_MOTOR_FORWARD  5
#define LEFT_MOTOR_BACKWARD 6
#define RIGHT_MOTOR_FORWARD 9
#define RIGHT_MOTOR_BACKWARD 10

// -------------------- Relay & Servo --------------------
#define PUMP_RELAY 7
#define SERVO_PIN  3

Servo waterServo;

// Threshold value for flame detection
// (Lower value = stronger flame detected)
#define FIRE_THRESHOLD 900

// ----------------------------------------------------------

void setup() {
  Serial.begin(9600);

  // Motor pins setup
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);

  // Relay setup (LOW = ON, HIGH = OFF)
  pinMode(PUMP_RELAY, OUTPUT);
  digitalWrite(PUMP_RELAY, HIGH); // Pump OFF initially

  // Servo setup (start from center)
  waterServo.attach(SERVO_PIN);
  delay(200);
  waterServo.write(90); // center position
  waterServo.detach();

  // Flame sensors as input
  pinMode(FLAME_LEFT, INPUT);
  pinMode(FLAME_CENTER, INPUT);
  pinMode(FLAME_RIGHT, INPUT);

  Serial.println("Fire Fighting Robot Initialized");
}

// ----------------------------------------------------------

void loop() {

  // Read values from flame sensors
  int leftValue   = analogRead(FLAME_LEFT);
  int centerValue = analogRead(FLAME_CENTER);
  int rightValue  = analogRead(FLAME_RIGHT);

  // Print sensor values (for debugging)
  Serial.print("Left: "); Serial.print(leftValue);
  Serial.print(" | Center: "); Serial.print(centerValue);
  Serial.print(" | Right: "); Serial.println(rightValue);

  bool fireFound = false;

  // -------- Fire Detection Logic --------

  if (leftValue < FIRE_THRESHOLD) {
    Serial.println("Fire detected on LEFT");

    moveForwardLeft();
    delay(700);

    stopMotors();
    sprayWater();

    fireFound = true;
  }

  else if (centerValue < FIRE_THRESHOLD) {
    Serial.println("Fire detected in CENTER");

    moveForward();
    delay(700);

    stopMotors();
    sprayWater();

    fireFound = true;
  }

  else if (rightValue < FIRE_THRESHOLD) {
    Serial.println("Fire detected on RIGHT");

    moveForwardRight();
    delay(700);

    stopMotors();
    sprayWater();

    fireFound = true;
  }

  // If no fire detected
  if (!fireFound) {
    stopMotors();
    digitalWrite(PUMP_RELAY, HIGH); // ensure pump is OFF
    Serial.println("No Fire Detected");
  }

  delay(300);
}

// ----------------------------------------------------------
// MOTOR CONTROL FUNCTIONS
// ----------------------------------------------------------

void moveForward() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}

// Slight left turn
void moveForwardLeft() {
  analogWrite(LEFT_MOTOR_FORWARD, 100);   // slower
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);

  analogWrite(RIGHT_MOTOR_BACKWARD, 200); // faster
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
}

// Slight right turn
void moveForwardRight() {
  analogWrite(LEFT_MOTOR_FORWARD, 200);   // faster
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);

  analogWrite(RIGHT_MOTOR_BACKWARD, 100); // slower
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

// ----------------------------------------------------------
// WATER SPRAY FUNCTION
// ----------------------------------------------------------

void sprayWater() {
  Serial.println("Activating Water Pump...");

  // Turn ON pump
  digitalWrite(PUMP_RELAY, LOW);

  // Attach servo before use
  waterServo.attach(SERVO_PIN);
  delay(150);

  // Sweep left
  for (int pos = 90; pos >= 60; pos -= 5) {
    waterServo.write(pos);
    delay(60);
  }

  // Sweep right
  for (int pos = 60; pos <= 120; pos += 5) {
    waterServo.write(pos);
    delay(60);
  }

  // Back to center
  for (int pos = 120; pos >= 90; pos -= 5) {
    waterServo.write(pos);
    delay(60);
  }

  delay(700); // keep spraying for some time

  // Stop everything
  waterServo.detach();
  digitalWrite(PUMP_RELAY, HIGH);

  Serial.println("Water Spraying Done");
}