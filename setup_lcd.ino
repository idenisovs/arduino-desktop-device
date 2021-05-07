void setupLcd() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(DOT, dot);
  lcd.createChar(CLOCK, clock);
  message(SETUP_LCD);
}
