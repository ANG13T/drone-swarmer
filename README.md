<p align="center">
  <img width="800" src="https://github.com/ANG13T/drone-swarmer/blob/main/assets/banner.png" alt="Drone Swarmer image" />
</p>
<h1 align="center" style="font-size:50px !important;">Drone Swarmer</h1>
<p align="center">
  <i>Drone Swarmer is an ESP8266 device that spoofs "ghost" drones by exploiting an Open Drone ID vulnerability using Wi-Fi Beacon broadcasts</i>
   <br/><br/>
  <b><a href="#features-️">Learn More</a></b> | <b><a href="#build️">Build</a></b> | <b><a href="#detecting-for-spoofing-">Getting Started</a></b> | <b><a href="#">Video</a></b> | <b><a href="#">Research Paper</a></b> | <b><a href="#">Article</a></b>
  <br/><br/>
</p>

<details>
  <summary><b>Table of Contents</b></summary>
  <p>

- **Getting Started**
    - [📡️ Features](#features-️)
    - [⚡ Demo Gallery](#demo-gallery-️)
    - [⚙️ Build](#build-️)
    - [📟 Code Overview](#code-overview-)
- **Learning More**
    - [🎥 Watch it in Action](#watch-it-in-action-)
    - [📄 Read the Article](https://medium.com/@angelinatsuboi/detecting-hacker-aircraft-using-artificial-intelligence-ec249baa866b)
- **Community**
    - [✨ Contributing](#contributing-)
    - [🏆 Special Thanks & Credits](#special-thanks--credits-)
    - [💜 Support](#support-)
    - [📜 License](https://github.com/ANG13T/fly-catcher/blob/main/LICENSE)

  </p>
</details>

<br />

<details>
  <summary><b>Disclaimer ⚠️</b></summary>
  <p>
Drone Swarmer is a proof-of-concept device designed for research purposes only. The project demonstrates the potential vulnerabilities in the Open Drone ID protocol, specifically relating to drone identification systems. **The use of this device to spoof drones or interfere with legal and authorized drone operations is illegal in many jurisdictions.**

This project is intended strictly for **educational and research purposes** to highlight the need for improved security in drone communication systems. **Do not use Drone Swarmer in any manner that violates the law or regulations in your country.**
  </p>
</details>


## Features 📡
- 📡  Spoofing "ghost" drones using Wi-Fi beacon broadcasts
- 🔨  ESP8266 and NEO6M GPS module prototype
- ⚙️  Code variant of [Remote ID Spoofer](https://github.com/jjshoots/RemoteIDSpoofer)


## Demo Gallery ⚡️
<table>
  <tr>
    <td valign="top"><img src="https://github.com/ANG13T/drone-swarmer/blob/main/assets/asset_1.jpg" alt="Gallery Image" height="180" width="250"> <h4 align="center">Picture of the build</h4></td>
    <td valign="top"><img src="https://github.com/ANG13T/drone-swarmer/blob/main/assets/asset_2.jpg" alt="Gallery Image" height="180" width="250"> <h4 align="center">Device shown attached to DJI drone</h4></td>
    <td valign="top"><img src="https://github.com/ANG13T/drone-swarmer/blob/main/assets/asset_3.jpg" alt="Gallery Image" height="180" width="250"> <h4 align="center">Open Drone ID packet analysis with Wireshark</h4></td>
  </tr>
</table>

## Watch it in Action 🎥
Watch Drone Swarmer in action on the NullByte YouTube channel:


## Build ⚙️

###  Materials List
- NEO6M GPS Module
- ESP8266 WEMOS D1 Mini

<img src="https://github.com/ANG13T/drone-swarmer/blob/main/assets/asset_4.png" alt="Prototyping Build" width="400" />


### Code Overview 📟

1. Clone the Repository 
```
git clone https://github.com/ANG13T/drone-swarmer.git
```

2. Install the [Arduino IDE](https://www.arduino.cc/en/software)

3. Install the ESP8266 Board Manager
```
Tools -> Board -> Board Manager

Search for "ESP8266 Boards" and Install
```

4. Install Libraries for the Project 
```
Sketch -> Include Library -> Manage Libraries

Search for: "Adafruit GPS Library" and Install
```

5. Select "LOLIN(WEMOS) D1 Mini" Board under "Tools -> Board"

6. Click the "Upload" Button

## Research Article 🔬
To get a more in-depth and technical overview of Drone Swarmer, you can refer to this [research article](#)

## Future Improvements 🚀
- Find a way to include multiple microcontroller boards to spoof more than 16 drones (current capacity)
- Create a localhost web server to display the spoofed drones on a map
- Look into possible MAC Address collission issues within the code that may be causing the 16 drone capacity limit (refer to research article)

## Contributing ✨
Drone Swarmer is open to any contributions. Please fork the repository and make a pull request with the features or fixes you want to implement.

## Special Thanks & Credits 🏆
The Drone Swarmer leveraged on previous Open Drone ID projects, research, and references included below

- [Remote ID Spoofer](https://github.com/jjshoots/RemoteIDSpoofer)
- [Mavlink Overview of Open Drone ID](https://mavlink.io/en/services/opendroneid.html)
- [Open Drone ID Code](https://github.com/opendroneid/opendroneid-core-c)
- [Android Open Drone ID Receiver](https://github.com/opendroneid/receiver-android)
- [Open Drone ID Wireshark Dissector](https://github.com/opendroneid/wireshark-dissector)

## Support 💜
If you enjoyed Drone Swarmer, please consider becoming a sponsor in order to fund my future projects.

To check out my other works, visit my [GitHub profile](github.com/ANG13T).