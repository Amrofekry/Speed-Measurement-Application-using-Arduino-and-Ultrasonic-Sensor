#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define SOUND_SPEED_CM_PER_US 0.03445 // Speed of sound in cm/µs

float distance1, distance2, speed;
const float DELAY_TIME_SEC = 1.0; // delay time in seconds

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  calculateSpeed();
  printSpeedOnLCD();
  
  if (speed == 0) {
    lcd.setCursor(11, 1);
    lcd.print("Move!");
  }
}

float calculateDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH); // Duration in µs
  float distance = (duration * SOUND_SPEED_CM_PER_US) / 2.0; // Calculating distance in cm
  
  Serial.print("Distance in cm = ");
  Serial.println(distance);

  return distance;
}

void calculateSpeed() {
  distance1 = calculateDistance();
  delay(DELAY_TIME_SEC * 1000); // Delay in milliseconds
  distance2 = calculateDistance();
  
  if (abs(distance2 - distance1) <= 0.2) {
    speed = 0;
  } else {
    speed = abs(distance2 - distance1) / DELAY_TIME_SEC;
  }
  
  Serial.print("Speed (cm/s) = ");
  Serial.println(speed);
}

void printSpeedOnLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Speed (cm/s) =");
  lcd.setCursor(0, 1);
  lcd.print(speed);
}

