/*
 * This file contains the configuration for the project
 */
#define DEBUG 1
#define BAUD_RATE 115200
#define SECOND 1000
#define HALD_SECOND 500

// Wifi Credentials
#define SSID "pi_wifi"
#define PASSWORD "12345678"
//
// NOTE: This is the correct one
#define GPS_TX D6 // This should connect to the TX pin of the GPS module
#define GPS_RX D5 // This should connect to the RX pin of the GPS module

// GSM_TX should be connected to the RX pin of the GSM module
// GSM_RX should be connected to the TX pin of the GSM module
#define GSM_TX D2
#define GSM_RX D3

typedef struct {
  bool _gps_status;
  double _lat;  // latitude
  double _long; // longitude
} Location;

typedef struct {
  const char *police;
  const char *parent;
} Numbers;
