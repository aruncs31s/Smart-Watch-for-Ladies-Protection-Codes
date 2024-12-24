#define BAUD_RATE 9600
#define MIC_PIN A0
#define GPS_BAUD_RATE 9600
// TODO: Uncomment after editing
// #define ESP8266
// #if defined(ARDUINO)
// #define GSM_TX 3
// #define GSM_RX 2
// #elif defined(ESP8266)
#define GPS_TX D5 // This should connect to the TX pin of the GPS module
#define GPS_RX D6 // This should connect to the RX pin of the GPS module
// #endif

// Where the push button is connected
// TODO: Add a decoubling/debouncing capacitor to the button
#define PUSH_BUTTON D1

typedef struct {
  bool _gps_status;
  double _lat;  // latitude
  double _long; // longitude
} Location;
typedef struct {
  const char *police;
  const char *parent;
} Numbers;
