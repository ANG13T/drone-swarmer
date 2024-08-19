# Drone Swarmer

### Troubleshooting

- 16 same set of drones

ONLY 16 drones for multiple microcontrollers

### Possible Work Arounds
- PCAP Analysis
- OpenDroneID App Analysis for Display of the Mobile Results
- DroneID Protocol Analysis

### Packet Analysis of OpenDroneID
- No.
- Time
- Source

Info:
- Transmitter Address
- Source Address
- BSSID

#### SSID Packet Header Frame Caveat
```
String Spoofer::getID() {
  randomSeed(ESP.getChipId() + millis());

  String characters = String("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
  String ID = "";
  for (int i = 0; i < 16; i++)
  {
    ID.concat(characters[(rand() % characters.length())]);
  }
  return ID;
}
```

### Packet Sequence Analysis

### Troubleshooting --- 

### Attempts - 7/28 @ 3:26 PM EST
Explaination: Did reversing of the OpenDroneId Receiver mobile application:
https://github.com/opendroneid/receiver-android/blob/master/Android/app/src/main/java/org/opendroneid/android/data/AircraftObject.java

By analysing the structure of the `AircraftObject` data type... I was able to conclude that there needs to be more seeding of the values for:

> MAC Address 

```
public AircraftObject(long macAddress) {
        this.macAddress = macAddress;
}

/ When two different BasicId messages have been received, use this function to force a periodic
    // swap between their uasId in the list view. It is assumed this is called once per second.
    // The change logic is slowed down to once per three seconds.
    public void updateShadowBasicId() {
        switch (idToShow) {
            case 0:
                id1Shadow.setValue(identification1.getValue());
                idToShow++;
                break;
            case 3:
                Identification id2 = identification2.getValue();
                if (id2 != null && id2.getIdType() != Identification.IdTypeEnum.None)
                    id2Shadow.setValue(identification2.getValue());
                idToShow++;
                break;
            case 6:
                idToShow = 0;
                break;
            default:
                idToShow++;
        }
    }

    @Override @NonNull
    public String toString() {
        return "AircraftObject{" +
                "macAddress=" + macAddress +
                ", identification1=" + identification1 +
                ", identification2=" + identification2 +
                '}';
    }
```

Also `Identification`

```
public byte[] getUasId() { return uasId; }
    public String getUasIdAsString() {
        if (uasId != null) {
            if (idType == IdTypeEnum.Serial_Number || idType == IdTypeEnum.CAA_Registration_ID) {
                for (int c : uasId) {
                    if ((c <= 31 || c >= 127) && c != 0) {
                        return "Invalid ID String";
                    }
                }
                return new String(uasId);
            } else if (idType == IdTypeEnum.UTM_Assigned_ID || idType == IdTypeEnum.Specific_Session_ID) {
                StringBuilder sb = new StringBuilder();
                sb.append("0x");
                for (byte b : uasId) {
                    sb.append(String.format("%02X", b));
                }
                return sb.toString();
            }
        }
        return "";
    }
    public void setUasId(byte[] uasId) {
        if (uasId.length <= Constants.MAX_ID_BYTE_SIZE)
            this.uasId = uasId;
    }
```


### Remediation of the Duplicate Drone Set Problem
https://github.com/opendroneid/receiver-android/blob/master/Android/app/src/main/java/org/opendroneid/android/data/AircraftObject.java


### Protocol Structure Interpretation ---

https://mavlink.io/en/services/opendroneid.html

```
For Drone ID data that is received from other UAs, the data of the message itself does not always identify exactly which UA the data originated from. E.g. for data received via Bluetooth Legacy Advertising (Bluetooth 4.x), many of the received messages will not contain the unique serial number/ID of the UA that broadcasted the data, due to the severe size limitation imposed by Legacy Advertising where only one 25 byte message can be broadcasted in one advertisement radio burst. The MAC address (possibly randomized) of the Bluetooth HW is the only way to associate these messages to the same UA. For Bluetooth 5.x and Wi-Fi, it is possible that the same can happen in certain specific situations (e.g. sending large amount of authentication data), although for the majority of normal usage this is unlikely, since the use of MESSAGE_PACKs is mandated. For data received via internet, the data packet will always contain the unique serial number/ID of the originating UA but no associated MAC address
```

`id_or_mac`

```
n order to allow e.g. a DAA component to sort and identify which UA each data message has originated from, the RID receiver components must add, to the MAVLink message, either the MAC address or the ID number associated with the UA that originated the data message
```

https://mavlink.io/en/messages/common.html#OPEN_DRONE_ID_BASIC_ID

`uas_id` type (uint8_t[20]) ~> UAS (Unmanned Aircraft System) ID following the format specified by id_type. Shall be filled with nulls in the unused portion of the field.


### OpenDroneID Message Pack

`OPEN_DRONE_ID_MESSAGE_PACK (12915)` [BINGO!]

https://mavlink.io/en/messages/common.html#OPEN_DRONE_ID_MESSAGE_PACK


### Exploit Explained....

### Possible future improvements
The current set of MAVLink drone ID messages do not provide any means for controlling some of the RID transmitter/receiver component details. The RID transmitter/receiver component must be hard-coded by the manufacturer to a certain configuration. Some discussion and proposal for this type of messages can be found here. It would be useful to control e.g. the following items:

Starting/stopping broadcast
Configure the broadcast method (BT4, BT5, Beacon, NaN)
Wi-Fi channel configuration for Beacon
Message update rates on the air
No regions currently require drone ID publication via the internet (Network Remote ID). However, it is possible that in the future this will change from being optional to mandatory for some use cases/regions as a part of the UTM/USpace efforts. Currently there are no suitable MAVLink messages defined to configure a Network Remote ID transceiver. Messages to specify the server(s) to connect to, credentials etc. would be needed.

Security of drone ID data is partly under definition. The Japan rule requires a signature of the drone ID data to be broadcasted in the AUTHENTICATION message. The details are in Japanese. No such requirement currently exists for the US and EU. It is possible that some use cases in the future might require more security related activities for drone ID data. Some additional protocol specification work is being drafted by the IETF in the DRIP working group.

During the PCAP scan analysis, the result would contain "groupings" of MAC Addresses such as
- 00:57:db:5e:20:fb
- 00:2d:cf:46:29:04
- 00:38:a8:4e:a6:14
- 00:57:db:5e:20:fb
- 00:7e:77:c6:2f:26
- 00:93:25:56:24:44

### Wireshark Queries

Investigating further into a single MAC Address grouping (`00:2d:cf:46:29:04`)

`opendroneid && wlan.sa == 00:2d:cf:46:29:04 && wlan.fc.type_subtype == 0x08`

Where `00:2d:cf:46:29:0` is the MAC Address of the drone

`0x08` filters for beacon frames (type = 0x00, subtype = 0x08)

I noticed DOZENS of different packets...

This is due to the lack of random seeding within the Drone Spoofer code...

To remedy this, I will need to add a random seed to MAC Address generation process

Inside `id_open.cpp`:

```cpp
#if ID_OD_WIFI

  // scrambled, not poached
  // Nodemcu doesn't like certain mac addresses
  // setting the first value to 0 seems to solve this
  WiFi_mac_addr[i] = 0;
  for (int i = 1; i < 6; i++) {
    // WiFi_mac_addr[i] = (uint8_t) (rand() % 100 + 100);
    WiFi_mac_addr[i] = (uint8_t) (rand() % 256);
  }
  
  memset(ssid,0,sizeof(ssid));

  strcpy(ssid,"UAS_ID_OPEN");

  beacon_interval = 10;
```

```
#if ID_OD_WIFI_BEACON && !USE_BEACON_FUNC

  init_beacon();

  // payload
  beacon_payload      = &beacon_frame[beacon_offset];
  beacon_offset      += 7;

  *beacon_payload++   = 0xdd;
  beacon_length       = beacon_payload++;

  *beacon_payload++   = 0xfa;
  *beacon_payload++   = 0x0b;
  *beacon_payload++   = 0xbc;

  *beacon_payload++   = 0x0d;
  beacon_counter      = beacon_payload++;

  beacon_max_packed   = BEACON_FRAME_SIZE - beacon_offset - 2;

  if (beacon_max_packed > (ODID_PACK_MAX_MESSAGES * ODID_MESSAGE_SIZE)) {

    beacon_max_packed = (ODID_PACK_MAX_MESSAGES * ODID_MESSAGE_SIZE);
  }
```

Investigating further into `id_open_beacon.cpp`:

```
for (i = 0; i < 6; ++i) {
    header->dest_addr[i] = 0xff;
    header->src_addr[i]  =  
    header->bssid[i]     = WiFi_mac_addr[i]; # <-- look into this [base station identifier]
 }
```

### Root Problem... MAC Address Collision


### Adjustment
Refer to: `ADJUSTMENT: 7/28 - 17:31 EDT` and `ADJUSTMENT: 7/28 - 17:38 EDT` inside `id_open.cpp`
DroneSwarmer_Revised_1_MAC_Collision.bin

Adding more seeding values...

```
 // ADJUSTMENT: 7/28 - 17:38 EDT
 unsigned int custom_seed() {
     unsigned int seed = (unsigned int)time(NULL);
     uint32_t chip_id = ESP.getChipId();
     seed ^= (unsigned int)(chip_id & 0xFFFF);  // Use lower 16 bits of the chip ID
     return seed;
 }
```


### OpenDroneID Protocol Analysis
https://mavlink.io/en/services/opendroneid.html

https://github.com/opendroneid/opendroneid-core-c

https://github.com/opendroneid/receiver-android

### MAC Address List ----
> 
> 
### LOGGING

`8/19` - Reverting back to OG binary to get the project back to working shape with limiting capacity of 16 drones
