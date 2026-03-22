#include <Adafruit_NeoPixel.h>

#define LED_PIN 7
#define LED_COUNT 18
#define PIEZO_PIN A0

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int threshold = 50;
unsigned long lastHitTime = 0;
unsigned long holdTime = 150; // milliseconds (adjust this!)

void setup() {
  strip.begin();
  strip.setBrightness(50);
  strip.show();
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(PIEZO_PIN);
  Serial.println(sensorValue);

  // Detect hit
  if (sensorValue > threshold) {
    lastHitTime = millis();
  }

  // Keep LEDs on for a short time after hit
  if (millis() - lastHitTime < holdTime) {
    showPink();
  } else {
    strip.clear();
    strip.show();
  }

  delay(5);
}

void showPink() {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(255, 20, 147));
  }
  strip.show();
}