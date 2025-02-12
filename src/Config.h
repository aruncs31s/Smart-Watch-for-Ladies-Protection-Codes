/*
 * In the circuit the D5 is connected to Tx of the Neo6m
 * and D6 is connected to Rx of the Neo6m
 * Which means that D5 is the Rx pin of the GPS Serial  and D6 is the Tx pin ie,
 * -> GPS_TX = D6 , GPS_RX = D5
 */

#define BAUD_RATE 115200
#define GSM_BAUD_RATE 9600
#define GPS_BAUD_RATE 9600
// TODO: Uncomment after editing
// #define ESP8266
// #if defined(ARDUINO)
// #define GSM_TX 3
// #define GSM_RX 2
// #elif defined(ESP8266)
#define GPS_TX D6 // This should connect to the TX pin of the GPS module
#define GPS_RX D5 // This should connect to the RX pin of the GPS module
// #endif

// GSM_TX should be connected to the RX pin of the GSM module
// GSM_RX should be connected to the TX pin of the GSM module
#define GSM_TX D2
#define GSM_RX D3
#define MSG_TERMINATOR 0x1A
#define SMALL_DELAY 500
#define ONE_SECOND 1000
// Where the push button is connected
// TODO: Add a decoubling/debouncing capacitor to the button
#define PUSH_BUTTON D5

// Microphone pin
#define MIC_PIN A0

typedef struct {
  bool _gps_status;
  double _lat;  // latitude
  double _long; // longitude
} Location;
typedef struct {
  const char *police;
  const char *parent;
} Numbers;
