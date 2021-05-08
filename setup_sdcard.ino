void setupSdcard() {
  message(SDCARD_SETUP);
  
  if (!SD.begin(SDCARD_SS_PIN)) {
    message(SDCARD_FAILED);
  }
}

void writeTimerState() {  
  DateTime now = rtc.now();

  char datetime[LCD_WIDTH + 2];

  snprintf(datetime, sizeof(datetime), "%02u.%02u.%u. %02u:%02u:%02u", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());
  
  File timerFile = SD.open("timer.csv", FILE_WRITE);

  timerFile.print(datetime);
  timerFile.print(";");
  timerFile.println(timerRecord);
  timerFile.close();

  timerRecordFlag = false;
}
