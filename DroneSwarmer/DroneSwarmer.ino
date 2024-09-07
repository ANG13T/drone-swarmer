/*
 *
 *   ______   ______  _____  __   _ _______      _______ _  _  _ _______  ______ _______ _______  ______
 *   |     \ |_____/ |     | | \  | |______      |______ |  |  | |_____| |_____/ |  |  | |______ |_____/
 *   |_____/ |    \_ |_____| |  \_| |______      ______| |__|__| |     | |    \_ |  |  | |______ |    \_
 *
 *
 * This code base is a derivative work based on the RemoteIDSpoofer project.
 * The majority of the code, architecture, and core functionality have been derived from the original RemoteIDSpoofer repository.
 *
 * Original RemoteIDSpoofer Project: https://github.com/jjshoots/RemoteIDSpoofer
 * Copyright (c) 2020-2022, Steve Jack.
 *
 * Drone Swarmer (a variant of the RemoteIDSpoofer project) includes the following modifications:
 * - No frontend for direct flashing of a prototype
 * - Removed redundant code due to project constraints of soley using WEMOS D1 Mini (ESP8266)
 * - Additional hardware and configuration for enhanced spoofing
 * - Customization such as custom case enclosures to snapfit onto the DJI Mini 2 
 * 
 * Author of Drone Swarmer: Angelina Tsuboi (angelinatsuboi.com) aka G4LXY
 * Copyright (c) 2024, Angelina Tsuboi
 * 
 *  HARDWARE:
 *  GPS Module: GY-GPS6MV2 NEO6M
 *  MICROCONTROLLER: ESP8266 WEMOS D1 Mini
 *
 *  INSTRUCTIONS:
 *  1. Connect the GPS VIN to 5V
 *  2. Connect the GPS GND pin to GND
 *  3. Connect the GPS TX (transmit) pin to Digital 1
 *  4. Connect the GPS RX (receive) pin to Digital 2
 *
 */


#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include "spoofer.h"

const int TXPin = 5; // D1
const int RXPin = 4; // D2

SoftwareSerial ss(TXPin, RXPin);  // TX, RX
Adafruit_GPS GPS(&ss);

int num_spoofers = 16;
Spoofer spoofers[16];

double latitude;
double longitude;

bool startProgram = false;

void setup() {
  Serial.begin(115200);
  GPS.begin(9600);
  configureGPS();
  startProgram = false;
}

void configureGPS() {
  Serial.println("Configuring GPS Module...");
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
}

float convertToDecimalDegrees(String coordinate) {
    // Extract the direction (N/S for latitude, E/W for longitude)
    char direction = coordinate[coordinate.length() - 1];

    // Remove the direction character (N/S/E/W)
    coordinate = coordinate.substring(0, coordinate.length() - 1);

    // Locate the decimal point in the string
    int decimalIndex = coordinate.indexOf('.');

    // Degrees are everything before the last two digits before the decimal point
    int deg_length = (decimalIndex > 4) ? 3 : 2;  // Longitude has 3 digits, latitude 2
    float degrees = coordinate.substring(0, deg_length).toFloat();

    // Minutes are everything after the degrees
    float minutes = coordinate.substring(deg_length).toFloat();

    // Convert to decimal degrees
    float decimalDegrees = degrees + (minutes / 60.0);

    // Adjust for the hemisphere (S or W need to be negative)
    if (direction == 'S' || direction == 'W') {
        decimalDegrees = -decimalDegrees;
    }

    return decimalDegrees;
}


uint32_t timer = millis();

void loop() {
  char c = GPS.read();

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))   
      return;  
  }

  // approximately every 2 seconds or so, print out the current stats
  if ((millis() - timer > 2000) && (startProgram == false)) {
    timer = millis(); // reset the timer
    if (GPS.fix) {
      String combinedLat = String(GPS.latitude, 6) + String(GPS.lat);
      latitude = convertToDecimalDegrees(combinedLat);
      String combinedLong = String(GPS.longitude, 6) + String(GPS.lon);
      longitude = convertToDecimalDegrees(combinedLong);

      for (int i = 0; i < num_spoofers; i++) {
        spoofers[i].init();
        spoofers[i].updateLocation(latitude, longitude);
      }
      Serial.println("\nStarting spoofing drones...");
      Serial.println("LATITUDE: " + String(latitude));
      Serial.println("LONGITUDE: " + String(longitude) + " \n");
      startProgram = true;
    }
  }

  // Update all spoofers
  if (startProgram) {
    // Serial.println("Updating...");
    for (int i = 0; i < num_spoofers; i++) {
      spoofers[i].update();
      delay(200 / num_spoofers);
    }
  }
}
