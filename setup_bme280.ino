void setupBme280() {
  message(SETUP_BME280);
  
  if (!bme.begin(BME280_ADDRESS)) {
    message(BME280_FAILED);
    setupFailed = true;
    return;
  }
}

void printBme280(byte line) {
  printHumidity(line);
  printPressure(line);
  printTemperature(line);
}

void printHumidity(byte line) {
  float humi = bme.readHumidity();

  char buffer[LCD_WIDTH];
  
  dtostrf(humi, LCD_WIDTH - 1, 1, buffer);

  buffer[LCD_WIDTH - 1] = '%';
 
  lcd.setCursor(0, line-1);
  lcd.print(buffer);
}

void printPressure(byte line) {
  float press = bme.readPressure() / 100.0F;
  
  byte segmentLength = LCD_WIDTH / 2 - 1;
  char buffer[segmentLength];
  
  dtostrf(press, segmentLength, 1, buffer);
  
  lcd.setCursor(10, line);
  lcd.print(buffer);
  lcd.setCursor(19, line);
  lcd.write(CLOCK);
}

void printTemperature(byte line) {
  float temp = bme.readTemperature();

  lcd.setCursor(0, line);
  lcd.print(temp);
  lcd.write(DOT);
  lcd.print("C");
}
