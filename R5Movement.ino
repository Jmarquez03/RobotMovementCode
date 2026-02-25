const int pwmLB = 16;
const int pwmRB = 4;
const int pwmLF = 2;
const int pwmRF = 15;
//LB = BR
//RB = AR
//LF = AR
//RF = BR
const int aInOne = 5;
const int aInTwo = 17;
const int aInOneRB = 19;
const int aInTwoRB = 18;
const int ainLF = 14;
const int binLF = 17;
const int ainRF = 12;
const int binRF = 13;
const int TRIG_PIN_S = 23;
const int ECHO_PIN_S = 26;
const int TRIG_PIN_F = 32;
const int ECHO_PIN_F = 36;
void setup() {
  Serial.begin(9600);
  //PWM pins
  pinMode(pwmLB,OUTPUT);
  pinMode(pwmRB, OUTPUT);
  pinMode(pwmLF, OUTPUT);
  pinMode(pwmRF, OUTPUT);
  //Back left pins
  pinMode(aInOne, OUTPUT);
  pinMode(aInTwo, OUTPUT);
  //Front left pins
  pinMode(ainLF, OUTPUT);
  pinMode(binLF, OUTPUT);
  //Back right pins
  pinMode(aInOneRB, OUTPUT);
  pinMode(aInTwoRB, OUTPUT);
  //Front right pins
  pinMode(ainRF, OUTPUT);
  pinMode(binRF, OUTPUT);
  pinMode(TRIG_PIN_F, OUTPUT);
  pinMode(ECHO_PIN_F, INPUT);
  pinMode(TRIG_PIN_S, OUTPUT);
  pinMode(ECHO_PIN_S, INPUT);
}
//Make sure to use delay(500); or some type of delay after calling function. 
float ultrasonic_sensor(int TRIG_PIN, int ECHO_PIN){
    // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  float duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  float distance_cm = 0.017 * duration_us;
  Serial.print("Distance Measured: ");
  Serial.print(distance_cm);
  // print the value to Serial Monitor
  return distance_cm;
}
void moveForward(int pwm)
{
  digitalWrite(aInOne, HIGH);
  digitalWrite(aInTwo, LOW);
  analogWrite(pwmLB, pwm);
  digitalWrite(aInOneRB, HIGH);
  digitalWrite(aInTwoRB, LOW);
  analogWrite(pwmRB, pwm);
  digitalWrite(ainLF, HIGH);
  digitalWrite(binLF, LOW);
  analogWrite(pwmLF, pwm);
  digitalWrite(ainRF, HIGH);
  digitalWrite(binRF, LOW);
  analogWrite(pwmRF, pwm);
}
void moveBackward(int pwm){
  digitalWrite(aInOne, LOW);
  digitalWrite(aInTwo, HIGH);
  analogWrite(pwmLB, pwm);
  digitalWrite(aInOneRB, LOW);
  digitalWrite(aInTwoRB, HIGH);
  analogWrite(pwmRB, pwm);
  digitalWrite(ainLF, LOW);
  digitalWrite(binLF, HIGH);
  analogWrite(pwmLF, pwm);
  digitalWrite(ainRF, LOW);
  digitalWrite(binRF, HIGH);
  analogWrite(pwmRF, pwm);
}
void strafeRight(int pwm){
  //Front Left Move Forward
  digitalWrite(ainLF, HIGH);
  digitalWrite(binLF, LOW);
  analogWrite(pwmLF, pwm);
  //Back Left Move Backward
  digitalWrite(aInOne, LOW);
  digitalWrite(aInTwo, HIGH);
  analogWrite(pwmLB, pwm);
  //Front Right Move Backward
  digitalWrite(ainRF, LOW);
  digitalWrite(binRF, HIGH);
  analogWrite(pwmRF, pwm);
  //Back Right Move Forward
  digitalWrite(aInOneRB, HIGH);
  digitalWrite(aInTwoRB, LOW);
  analogWrite(pwmRB, pwm);
}

void strafeLeft(){
  //Front Left Move Backward
  
  //Back Left Move Forward
  //Front Right Move Forward
  //Back Right Move Backward
}

void rotateCenterCL(int pwm){
  //Front left move Forward
  digitalWrite(ainLF, HIGH);
  digitalWrite(binLF, LOW);
  analogWrite(pwmLF, pwm);
  //Front right move Backward
    digitalWrite(ainRF, LOW);
  digitalWrite(binRF, HIGH);
  analogWrite(pwmRF, pwm);
  //Back left move Forward
  digitalWrite(aInOne, HIGH);
  digitalWrite(aInTwo, LOW);
  analogWrite(pwmLB, pwm);
  //Back right move Backward
   digitalWrite(aInOneRB, HIGH);
  digitalWrite(aInTwoRB, LOW);
  analogWrite(pwmRB, pwm);
}

void rotateCenterCC()
{
  //Front left move Backward
  //Front right move Forward
  //Back left move Backward
  //Back right move Forward
}

void stopWheels()
{
  digitalWrite(ainRF, LOW);
  digitalWrite(binRF, LOW);
  digitalWrite(ainLF, LOW);
  digitalWrite(binLF, LOW);
  digitalWrite(aInOneRB, LOW);
  digitalWrite(aInTwoRB, LOW);
  digitalWrite(aInOne, LOW);
  digitalWrite(aInTwo, LOW);
  
}
void loop() {
  // 1. Move forward until the ultrasonic sensor on front reads 1 foot
  while(ultrasonic_sensor(TRIG_PIN_F, ECHO_PIN_F) > 45)
  {
    moveForward(150);
  }
  stopWheels();
  rotateCenterCL(200);
  delay(1500);
  stopWheels();
  while(ultrasonic_sensor(TRIG_PIN_F, ECHO_PIN_F) > 45)
  {
    moveFor`ward(150);
  }
  stopWheels();
  delay(10000);
}
