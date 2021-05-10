#define LCD_ADDRESS 0x27
#define LCD_WIDTH 20
#define LCD_HEIGHT 4
#define FORCE_RTC_ADJUST false
#define BTN_PIN 2
#define SDCARD_SS_PIN 10
#define WRITE_INTERVAL_SEC 10

#ifdef BME280_ADDRESS
    #undef BME280_ADDRESS
#endif

#define BME280_ADDRESS 0x76
