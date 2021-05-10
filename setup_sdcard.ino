void setupSdcard() {
  message(SDCARD_SETUP);
  
  if (!SD.begin(SDCARD_SS_PIN)) {
    message(SDCARD_FAILED);
    setupFailed = true;
  }
}

void backupTimer() { 
  byte * buffer = (byte *)&t1;

  byte mode = SD.exists("t1.bin") ? O_WRITE : FILE_WRITE;

  File timerFile = SD.open("t1.bin", mode);
  
  timerFile.seek(0);
  timerFile.write(buffer, sizeof(Timer));
  timerFile.close();
}

void loadTimer() {  
  if (!SD.exists("t1.bin")) {
    return;
  }
  
  byte * buffer;

  File timerFile = SD.open("t1.bin", FILE_READ);
  timerFile.read(&buffer, sizeof(Timer));
  timerFile.close();

  Timer * timerPtr = (Timer *)&buffer;

  t1.dd = timerPtr->dd;
  t1.hh = timerPtr->hh;
  t1.mm = timerPtr->mm;
  t1.ss = timerPtr->ss;
}

void writeTimerState() {   
  DateTime now = rtc.now();

  char datetime[LCD_WIDTH+1];

  snprintf(datetime, sizeof(datetime), "%02u.%02u.%u. %02u:%02u:%02u", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());

  char timer[LCD_WIDTH+1];

  snprintf(timer, sizeof(timer), "%u:%02u:%02u:%02u ", t1.dd, t1.hh, t1.mm, t1.ss);
  
  File timerFile = SD.open("timer.csv", FILE_WRITE);

  timerFile.print(datetime);
  timerFile.print(";");
  timerFile.println(timer);
  timerFile.close();
}

void resetTimer() {
  t1.dd = 0;
  t1.hh = 0;
  t1.mm = 0;
  t1.ss = 0;
}
