#include <DHT.h>

// --- Sensor setup ---
#define DHTPIN 3          // Pin for DHT11 sensor
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define PIR_PIN 2         // Motion/vibration detection
#define BUZZER_PIN 8
#define LED_PIN 9
#define SPRAY_PIN 10      // Relay to control sprayer motor

void setup() {
  Serial.begin(9600);
  
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SPRAY_PIN, OUTPUT);

  dht.begin();

  // Initialize all actuators off
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(SPRAY_PIN, LOW);

  Serial.println("Smart Eye System Initialized...");
}

void loop() {
  int motion = digitalRead(PIR_PIN);
  float temp = dht.readTemperature();

  // Display readings
  Serial.print("Motion: ");
  Serial.print(motion);
  Serial.print(" | Temp: ");
  Serial.println(temp);

  // Trigger alert if motion detected or temp too high
  if (motion == HIGH || temp > 35.0) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(SPRAY_PIN, HIGH); // Activate spray

    Serial.println("Intruder Detected! Action taken!");
    delay(3000);  // Spray and alert for 3 seconds
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(SPRAY_PIN, LOW);
  }

  delay(1000); // Wait 1 second before next reading
}
