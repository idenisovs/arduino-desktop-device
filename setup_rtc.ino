void setupRtc() {
  message(SETUP_RTC);

  if (!rtc.begin()) {
    message(RTC_FAILED);
    setupFailed = true;
    return;
  }

  if (!rtc.isrunning() || FORCE_RTC_ADJUST) {
    message(RTC_LOST_POWER);
    message(RTC_TIME_ADJUST);
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    message(DONE);
    delay(3000);
    lcd.clear();
  }
}

void printDateTime(byte line) {
  printDateTime(line, rtc.now());
}

void printDateTime(byte line, DateTime datetime) {
  char output[LCD_WIDTH];

  sprintf(output, "%02u.%02u.%u. %02u:%02u:%02u", datetime.day(), datetime.month(), datetime.year(), datetime.hour(), datetime.minute(), datetime.second());

  lcd.setCursor(0, line - 1);
  lcd.print(output);
}
