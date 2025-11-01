#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set I2C address to 0x27 or 0x3F depending on your LCD module
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;
long duration;
float distance;

void setup() {
  Serial.begin(9600);
  
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on backlight
  lcd.setCursor(0,0);
  lcd.print("Ultrasonic Init");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(1500);
  lcd.clear();
}

void loop() {
  // Send 10us trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo pulse width
  duration = pulseIn(echoPin, HIGH, 30000); // timeout: 30 ms

  // Calculate distance in cm
  if (duration > 0) {
    distance = (duration * 0.0343) / 2;
  } else {
    distance = -1; // invalid reading
  }

  // Display results
  lcd.setCursor(0, 0);
  if (distance >= 0) {
    lcd.print("Distance: ");
    lcd.print(distance, 1);
    lcd.print("cm ");
    
    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.println(" cm");
  } else {
    lcd.print("Out of range   ");
    Serial.println("No echo detected (timeout)");
  }

  delay(500);
}
