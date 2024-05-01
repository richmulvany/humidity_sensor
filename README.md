# Humidity sensor made with DHT22 on an ESP32 which collects real-time data and sends mobile push notification when room humidity reaches threshold

### Components Required
![Components](https://i.imgur.com/Il0kmBM.jpg)

I used the following components in this build:
- ESP32 dev board
- DHT22 temperature and humidity sensor
- 10kOhm resistor
- Cabling

The DHT22 data line requires a pull-up resistor because the sensor uses an open-drain or open-collector output. This means that the sensor can pull the data line to ground but cannot drive it high itself. The resistor is needed to pull the line to a high state (VCC) when the sensor is not pulling it low. This helps avoid inconsistent data outputs.

### 3D Printing
![Printed Parts](https://i.imgur.com/pD0fAVj.jpg)

I designed parts for printing using AutoDesk Fusion; the STL files are provided in this repo [here.](https://github.com/richmulvany/deej/tree/master/stl)

I am new to 3D modelling and printing, and I admittedly didn't approach the design with any intentions of usability by anyone else, so keep in mind that it would be annoying to replicate. I also used a resin printer, where I would expect most people would be using a filament one. 

I superglued my parts together; I just happened to have superglue rather than screws, and it seems like resin prints work well with superglue. This does mean I will have to destroy the case to retrieve the components or make modifications, however. 

### Arduino Code

The Arduino [sketch](https://github.com/richmulvany/deej/tree/master/Arduino/mixer_sketch) I used for this project has been included in the repo. Setting up the wifi connection and the data upload to io.adafruit simply involves replacing the fields within the sketch. 

### Data Upload

I used Adafruit IO for uploading the data collection. They provide 30 days of data storage for up to 10 streams of data for in their free basic plan. My DHT22 is currently using 2 of those streams to stream the temperature and humidity data it is collecting. Adafruit IO also provides some data visualisation of the streams on their site, as well as the ability to have actions automated based on the real-time data. 

![Data Feeds](https://i.imgur.com/1gKBF6E.png)

![Data Visualisation](https://i.imgur.com/OAueMAA.png)

### Push Notifications

I had anticipated push notifications to be the most difficult step in the process of this project, but it turned out to be extremely simple to set up. I was looking to create a warning system whereby I recieved a push notification on my phone if my bedroom humidity gets to highm using the data feed being uploaded to Adafruit IO. It turns out that there are multiple options to do this easily; I used an app called IFTTT which lets you produce 'applets' to perform tasks such as this. 

|IFTTT has a simple, although rather rudementary and arguably overly minimilistic UI for setting up a trigger then action which can pull triggers from lots of sources including Adafruit IO.|![Applet Notification](https://i.imgur.com/BplXoob.png)|![Applet Creation](https://i.imgur.com/cqKTodE.png)|
|--|--|--|

### Schematic

![Schematic](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/04/dht_esp32_bb.png?w=714&quality=100&strip=all&ssl=1)

The above schematic details the connection between the DHT22 sensor and the ESP32 board. Note that the third pin is not utilised, and ground goes through the fourth pin. 

### Assembly

Here is how the schematic looks on a breadboard in the real:

![Assembled Components](https://i.imgur.com/axD5lwk.jpg) 


