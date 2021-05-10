#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define FORMATL "%-" STR(LCD_WIDTH) "s"
#define FORMATR "%" STR(LCD_WIDTH) "s"

const char * SETUP_RTC = "setup rtc";
const char * RTC_FAILED = "rtc failed";
const char * RTC_LOST_POWER = "rtc lost power";
const char * RTC_TIME_ADJUST = "rtc time adjust";

const char * SETUP_LCD = "setup lcd";
const char * SETUP_BTN = "setup btn1 handler";

const char * SETUP_BME280 = "setup bme280";
const char * BME280_FAILED = "bme280 failed";

const char * SDCARD_SETUP = "setup sdcard";
const char * SDCARD_FAILED = "sdcard failed";

const char * DONE = "done";
const char * OK = "ok";
