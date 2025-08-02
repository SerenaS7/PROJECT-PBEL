#include <LiquidCrystal.h>

// LCD setup: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin assignments
const int tempPin = A2;       // Temperature pot
const int humidityPin = A1;   // Humidity pot
const int mq135Pin = A0;      // Air quality pot
const int ledPin = 8;         // LED pin

void setup() {
  pinMode(ledPin, OUTPUT);    
  lcd.begin(16, 2);           
  lcd.print("Hi");
  delay(2000);
  Serial.begin(9600);         
}

void loop() {
  // Read values from pots
  int tempRaw = analogRead(tempPin);        // 0–1023
  int humidityRaw = analogRead(humidityPin);
  int airQuality = analogRead(mq135Pin);

  // Map to human-readable values
  int temp = map(tempRaw, 0, 1023, 20, 40);         // 20–40°C
  int humidity = map(humidityRaw, 0, 1023, 30, 90); // 30–90%

  // Print to Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Air: ");
  Serial.println(airQuality);

  // Show on LCD
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C H:");
  lcd.print(humidity);
  lcd.print("%  "); // Padding to clear old digits

  lcd.setCursor(0, 1);
  lcd.print("Air:");
  lcd.print(airQuality);
  lcd.print("     "); // Extra spaces to clear old digits

  // LED based on air quality
  if (airQuality > 300) {
    digitalWrite(ledPin, HIGH); // Poor air
  } else {
    digitalWrite(ledPin, LOW);  // Good air
  }

  delay(2000);  // 2-second delay
}


