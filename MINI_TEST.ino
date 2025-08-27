#include <Wire.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include "img.h" // Pozadi
#include "cudl.h" // Cudl
#include "Adafruit_SHT4x.h"

#define DC    17  
#define RST   16  
#define BUSY  4 
#define POWER 2

// BATERIE ---------------------------------------------------------------
const int batteryPins[] = {12, 13, 14, 15, 26, 27}; // GPIO piny pro 6 baterií
const int batteryCount = 6;
const float R1 = 96500.0; // dělič napětí rezistory
const float R2 = 27500.0;
const int numSamples = 20;         // počet měření pro průměr
const float minVoltage = 3.3;      // napětí 0%
const float maxVoltage = 4.2;      // napětí 100%
int batteryPercentages[batteryCount]; // pole pro procenta baterií

// SHT4x senzor
Adafruit_SHT4x sht4 = Adafruit_SHT4x();

double shtTemperature = 0;
double shtHumidity = 0;

// Inicializace displeje 2.13" černobílý (SSD1680 driver)
GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(GxEPD2_213_B74(SS, DC, RST, BUSY));

void setup() {
  Serial.begin(115200);
  Serial.println();

  Wire.begin(21, 22); // SDA = GPIO21, SCL = GPIO22

  if (!sht4.begin()) {
    Serial.println("SHT4x sensor not found. Check wiring.");
    while (1) delay(1);
  }
  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  sht4.setHeater(SHT4X_NO_HEATER);

  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, HIGH);
  Serial.println("Display power ON");
  delay(1000);
  display.init(115200, true, 2, false);
  if (display.pages() > 1) {
    Serial.print("pages = ");
    Serial.print(display.pages());
    Serial.print(", page height = ");
    Serial.println(display.pageHeight());
    delay(1000);
  }
  render(); // výchozí zobrazení
  display.display(true);
  delay(100);
  digitalWrite(POWER, LOW);
  display.powerOff();
  Serial.println("setup done");
}

float readBatteryVoltage(int pin) {
  float sumVoltage = 0.0;
  for (int i = 0; i < numSamples; i++) {
    int rawValue = analogRead(pin);
    float voltageAtPin = (rawValue / 4095.0) * 3.3;
    float batteryVoltage = voltageAtPin * ((R1 + R2) / R2);
    sumVoltage += batteryVoltage;
    delay(2);
  }
  return sumVoltage / numSamples;
}

int voltageToPercent(float voltage) {
  if (voltage >= maxVoltage) return 100;
  else if (voltage <= minVoltage) return 0;
  else return (int)(((voltage - minVoltage) / (maxVoltage - minVoltage)) * 100);
}

void loop() {
  digitalWrite(POWER, HIGH);
  display.init(115200, true, 2, false);

  // Čtení baterií
  for (int i = 0; i < batteryCount; i++) {
    float voltage = readBatteryVoltage(batteryPins[i]);
    batteryPercentages[i] = voltageToPercent(voltage);
    Serial.print("Baterie ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(voltage, 2);
    Serial.print(" V / Stav nabití: ");
    Serial.print(batteryPercentages[i]);
    Serial.println(" %");
  }

  // Čtení teploty a vlhkosti ze senzoru SHT4x
  sensors_event_t humidity, temp;
  sht4.getEvent(&humidity, &temp);
  shtTemperature = temp.temperature;
  shtHumidity = humidity.relative_humidity;

  Serial.print("Teplota senzoru: "); Serial.print(shtTemperature); Serial.println(" C");
  Serial.print("Vlhkost senzoru: "); Serial.print(shtHumidity); Serial.println(" %");

  render();
  display.display(true);

  digitalWrite(POWER, LOW);
  display.powerOff();

  delay(5000);
}

void render() {
  display.setRotation(0);
  display.setFont(0); // Nejmenší defaultní font
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();
  do {
    display.drawBitmap(0, 0, epd_bitmap_UX_128_250, 128, 250, GxEPD_BLACK);

    // Lambda pro vykreslení baterie
    auto drawBattery = [&](int x, int y, int percent) {
      if (percent == 100) display.setCursor(x + 6, y + 70);
      else display.setCursor(x + 10, y + 70);
      display.print(percent);
      display.print("%");
      if (percent > 75) {
        display.drawBitmap(x, y + 7, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
        display.drawBitmap(x, y + 21, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
        display.drawBitmap(x, y + 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
        display.drawBitmap(x, y + 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
      } else if (percent > 50) {
        display.drawBitmap(x, y + 21, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
        display.drawBitmap(x, y + 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
        display.drawBitmap(x, y + 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
      } else if (percent > 25) {
        display.drawBitmap(x, y + 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
        display.drawBitmap(x, y + 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
      } else if (percent > 0) {
        display.drawBitmap(x, y + 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
      }
    };

    // Vykreslení baterií
    drawBattery(5, 0, batteryPercentages[0]);
    drawBattery(46, 0, batteryPercentages[1]);
    drawBattery(87, 0, batteryPercentages[2]);
    drawBattery(5, 78, batteryPercentages[3]);
    drawBattery(46, 78, batteryPercentages[4]);
    drawBattery(87, 78, batteryPercentages[5]);

    // Zobrazení teploty ze senzoru
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(20, 205);
    display.print(shtTemperature, 1);
    display.write(176);
    display.print(" C");

    // Zobrazení vlhkosti ze senzoru
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(35, 230);
    display.print(shtHumidity, 1);
    display.write(176);
    display.print(" %");

  } while (display.nextPage());
}
