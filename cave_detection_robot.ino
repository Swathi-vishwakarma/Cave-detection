// BombDetectionRobot.ino

#include <LiquidCrystal_I2C.h>

// Pin Definitions
#define METAL_SENSOR_PIN A0
#define BUZZER_PIN 8
#define LEFT_MOTOR_IN1 2
#define LEFT_MOTOR_IN2 3
#define RIGHT_MOTOR_IN3 4
#define RIGHT_MOTOR_IN4 5

// LCD Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Bomb Detector");

  // Pin Modes
  pinMode(METAL_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_IN3, OUTPUT);
  pinMode(RIGHT_MOTOR_IN4, OUTPUT);

  delay(2000);
  lcd.clear();
}

void loop() {
  int metalValue = analogRead(METAL_SENSOR_PIN);
  Serial.print("Metal Value: ");
  Serial.println(metalValue);

  lcd.setCursor(0, 0);
  lcd.print("Scanning...");

  if (metalValue > 500) { // Threshold for detection
    lcd.setCursor(0, 1);
    lcd.print("Bomb Detected!  ");
    digitalWrite(BUZZER_PIN, HIGH);
    stopMotors();
  } else {
    lcd.setCursor(0, 1);
    lcd.print("All Clear     ");
    digitalWrite(BUZZER_PIN, LOW);
    moveForward();
  }

  delay(500);
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN3, HIGH);
  digitalWrite(RIGHT_MOTOR_IN4, LOW);
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_IN4, LOW);
}
