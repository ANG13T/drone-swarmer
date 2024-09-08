<p align="center">
  <img width="800" src="https://github.com/ANG13T/drone-swarmer/blob/main/assets/banner.png" alt="DroneSwarmer image" />
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
    - [✈️ Features](#features-️)
    - [⚡ Demo Gallery](#demo-gallery-️)
    - [⚙️ Build](#build-it-yourself-️)
    - [🚀 Code Base](#detecting-for-spoofing-)
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

### Disclaimer

## Features ✈️
- 📡  Spoofing "ghost" drones using Wi-Fi beacon broadcasts
- 🔨  ESP8266 and NEO6M GPS module prototype
- ⚙️  Code variant of [Remote ID Spoofer](https://github.com/jjshoots/RemoteIDSpoofer)


## Demo Gallery ⚡️

<table>
  <tr>
    <td valign="top"><img src="https://github.com/ANG13T/fly-catcher/blob/main/assets/display_1.png?raw=true" alt="Gallery Image" height="180" width="250"> <h4 align="center">Picture of the completed build</h4></td>
    <td valign="top"><img src="https://github.com/ANG13T/fly-catcher/blob/main/assets/display_2.png?raw=true" alt="Gallery Image" height="180" width="250"> <h4 align="center">Device shown with the SportCruiser</h4></td>
    <td valign="top"><img src="https://github.com/ANG13T/fly-catcher/blob/main/assets/display_3.png?raw=true" alt="Gallery Image" height="180" width="250"> <h4 align="center">Display shown on the TFT Screen</h4></td>
  </tr>
</table>

## Watch it in Action 🎥
Watch DroneSwarmer in action on the NullByte YouTube channel



## Build ⚙️

###  Materials List
- NEO6M GPS Module

<img src="https://github.com/ANG13T/fly-catcher/blob/main/assets/materials.png?raw=true" alt="Folium Map" width="400" />


### Running the Radar Code

Clone the Repository on the Pi
```
git clone https://github.com/ANG13T/fly-catcher.git
```

Run the Program
```
python3 fly-catcher/device-rpi/piawareradar.py longitude latitude
```
Replace longitude and latitude with your [geo-coordinates](https://www.gps-coordinates.net/)

## Detecting for Spoofing 🔎

### Download the Jupyter Notebook
```
git clone https://github.com/ANG13T/fly-catcher.git
cd notebook
jupyter notebook
```
Install [Jupyter Notebook](https://jupyter.org/install) if you do not have it


## Research Article 🔬
To get a more in-depth and technical overview of Fly Catcher, you can refer to this [research article](google.com)

## Future Improvements 🚀
- Enhanced UI features on the radar screen
- Deep learning techniques such as RNNs and LSTM networks
- Incorporating reinforcement learning techniques
- Differentiate spoofing attacks (ie. GPS spoofing, aircraft masquerading, etc)

## Contributing ✨
Drone Swarmer is open to any contributions. Please fork the repository and make a pull request with the features or fixes you want to implement.

## Special Thanks & Credits 🏆
The Drone Swarmer leveraged on previous ADS-B works and references included below

- [Pi Aware Radar by Martin O'Hanlon](http://www.stuffaboutcode.com/2015/11/raspberry-pi-piaware-aircraft-radar.html)
- [Reference dump1090 README](https://github.com/SDRplay/dump1090/blob/master/README-json.md)
- [Data Samples from ADSB Exchange](https://www.adsbexchange.com/data-samples/)
- [IEEE Research on ADS-B Signals](https://ieeexplore.ieee.org/document/9377975)


## Support 💜
If you enjoyed Drone Swarmer, please consider becoming a sponsor in order to fund my future projects.

To check out my other works, visit my [GitHub profile](github.com/ANG13T).