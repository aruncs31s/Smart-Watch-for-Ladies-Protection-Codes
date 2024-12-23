#define BAUD_RATE 9600
#define MIC_PIN A0
#define GPS_BAUD_RATE 9600

#if defined(ARDUINO)
#define GSM_TX 3
#define GSM_RX 2
#elif defined(ESP8266)
#define GSM_TX D5
#define GSM_RX D6
#endif
