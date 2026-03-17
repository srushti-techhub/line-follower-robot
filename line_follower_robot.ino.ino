// --- Pin Definitions ---
#define ENA 5
#define ENB 6
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 12
#define IR_LEFT A0
#define IR_RIGHT A1

// --- Settings ---
const int speedForward = 100;
const int speedTurn    = 90;  

void forward(int speed) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speed); analogWrite(ENB, speed);
}

void back(int speed) {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed); analogWrite(ENB, speed);
}

void pivotLeft(int speed) {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speed); analogWrite(ENB, speed);
}

void pivotRight(int speed) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed); analogWrite(ENB, speed);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}

void setup() {
  // Motor Pins
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  
  // IR Sensor Pins
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Short delay before the robot starts moving
  delay(500);
}

void loop() {
  // --- LINE FOLLOWING (Straddle Logic) ---
  int L = digitalRead(IR_LEFT);
  int R = digitalRead(IR_RIGHT);

  if (L == LOW && R == LOW) {
    // Both sensors off the line -> Move Forward
    forward(speedForward);
  } 
  else if (L == HIGH && R == LOW) {
    // Left sensor hits the line -> Correct Left
    pivotLeft(speedTurn);
  } 
  else if (L == LOW && R == HIGH) {
    // Right sensor hits the line -> Correct Right
    pivotRight(speedTurn);
  } 
  else {
    // Both sensors hit the line (L == HIGH && R == HIGH)
    // Depending on your track, you may want to stop here instead.
    forward(speedForward);
  }
}
