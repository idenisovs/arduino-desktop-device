void setupSdcard() {
  message(SDCARD_SETUP);
  
  if (!SD.begin(SDCARD_SS_PIN)) {
    message(SDCARD_FAILED);
    setupFailed = true;
  }
}
