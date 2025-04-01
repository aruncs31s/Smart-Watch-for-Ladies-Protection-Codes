/*
 * This file contains the configuration for the project
 */
#define DEBUG 1
#define BAUD_RATE 115200
#define GPS_BAUD_RATE 9600
#define GPS_UPDATE_INTERVAL 1000

#define SECOND 1000
#define HALD_SECOND 500

// Wifi Credentials
#define SSID "pi_wifi"
#define PASSWORD "12345678"
//
// NOTE: This is the correct one
#define GPS_TX D6 // This should connect to the TX pin of the GPS module
#define GPS_RX D7 // This should connect to the RX pin of the GPS module

// GSM_TX should be connected to the RX pin of the GSM module
// GSM_RX should be connected to the TX pin of the GSM module
#define GSM_TX D3
#define GSM_RX D4

#define SOS_BUTTON D5 // Push button
#define HELP_BUTTON D8 // From the AI thinker module


typedef struct {
  bool _gps_status;
  double _lat;  // latitude
  double _long; // longitude
} Location;

typedef struct {
  const char *police;
  const char *parent;
} Numbers;
