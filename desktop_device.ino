#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

#include "messages.h"
#include "lcd_symbols.h"

#define LCD_WIDTH 20
#define LCD_HEIGHT 4
#define FORCE_RTC_ADJUST false
#define BTN_PIN 2

#ifdef BME280_ADDRESS
    #undef BME280_ADDRESS
#endif

#define BME280_ADDRESS 0x76

LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);
RTC_DS1307 rtc;
Adafruit_BME280 bme;

bool setupFailed = false;

byte storedSecond = 0;

unsigned int d = 0;
byte h = 0;
byte m = 0;
byte s = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  setupLcd();
  setupRtc();
  setupButtonHandler();
  setupBme280();

  if (setupFailed) {
    abort();
  }
  
  delay(1000);
  
  lcd.clear();
}

void loop() {
  updateCounters();
  
  printDateTime(1);
  printTimer(2);
  printBme280(3);
  
  delay(1000);
}
