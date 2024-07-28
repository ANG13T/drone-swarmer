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
 * Copyright (c) 2024, Jun Jet.
 *
 * Drone Swarmer (a variant of the RemoteIDSpoofer project) includes the following modifications:
 * - No frontend for direct flashing of a prototype
 * - Removed redundant code due to project constraints of soley using WEMOS D1 Mini (ESP8266)
 * - Additional hardware and configuration for enhanced spoofing
 * - Updated code base to spoof drones with randomized IDs (this avoids the problem of duplicate drones when we add extra microcontrollers)
 * - Configured the SSID values of the beacon frames
 * 
 * Author of Drone Swarmer: Angelina Tsuboi (angelinatsuboi.com) aka G4LXY
 * Copyright (c) 2024, Angelina Tsuboi
 * 
 * 
 */

#include "spoofer.h"
#include <math.h>

int num_spoofers = 16;
Spoofer spoofers[16];

// TODO: INPUT YOUR GPS COORDINATES HERE
double latitude = 48.39462035187865;
double longitude = -114.33447620499432;

void setup() {
  Serial.begin(115200);
  
    for (int i = 0; i < num_spoofers; i++) {
      spoofers[i].init();
      spoofers[i].updateLocation(latitude, longitude);
    }
}

void loop() {
  for (int i = 0; i < num_spoofers; i++) {
    spoofers[i].update();
    delay(200 / num_spoofers);
  }
}
