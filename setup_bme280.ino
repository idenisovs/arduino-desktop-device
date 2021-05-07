void setupBme280() {
  message(SETUP_BME280);
  
  if (!bme.begin(BME280_ADDRESS)) {
    message(BME280_FAILED);
    setupFailed = true;
    return;
  }
}

void printBme280(byte line) {
  float humi = bme.readHumidity();

  char buffer[LCD_WIDTH];
  
  dtostrf(humi, LCD_WIDTH - 1, 1, buffer);

  buffer[LCD_WIDTH - 1] = '%';
 
  lcd.setCursor(0, line-1);
  lcd.print(buffer);
  
  float temp = bme.readTemperature();

  lcd.setCursor(0, line);
  lcd.print(temp);
  lcd.write(DOT);
  lcd.print("C ");

  float press = bme.readPressure() / 100.0F;
  
  lcd.setCursor(13, line);
  lcd.print(press);
  lcd.write(CLOCK);
}
