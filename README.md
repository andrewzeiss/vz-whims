# WHIMS Development Directory

Repo for development on St. Louis University CHROME lab WHIMS Project. Work completed by Andrew Zeiss from May to July 2024.

## Table of Contents

1. whims_sketch  
Arduino Code

2. WhimsWearable  
Garmin Wearable application code

3. WhimsServer  
Python application for manual Arduino communication 

### whims_sketch  

The whims_sketch is code run on Arduino to establish the Arduino as a peripheral device to the central Bluetooth wearable. This is achieved by declaring service and characteristic UUID's, then setting the Arduino broadcast name and awaiting connection. Once connected, the Arduino awaits for the central device to write any non-zero value to the specified characteristic, then conducts one SingleCycle before rewriting the characteristic back to 0 and awaiting further communication.  
Note that an arduino with Bluetooth low energy capabilities is required to run the program.

### WhimsWearable

The WhimsWearable is an application designed for Garmin wearable devices. I found the [this video](https://www.youtube.com/watch?v=_sHBqQKpIZg&ab_channel=VolodymyrBudnyi) useful for the download and installation of Garmin SDK. Garmin applications are written in MonkeyC, an object oriented language I found to be similar to Java. The Project directory and structure closely resembles that of Android Studio. A tutorial and many examples of Garmin applications can be found [here](https://starttorun.info/connect-iq-apps-with-source-code/).

The garmin SDK specifics can be found [here](https://developer.garmin.com/connect-iq/api-docs/index.html), although be warned the documentation is extremely lengthy and can be difficult to navigate. Some useful links are as follows-  
[Access Current Stress Level](https://developer.garmin.com/connect-iq/api-docs/Toybox/ActivityMonitor/Info.html#stressScore-var)  
[Bluetooth methods](https://developer.garmin.com/connect-iq/api-docs/Toybox/BluetoothLowEnergy.html)

Currently, the application is setup for minimum sdk level 4.0, and is configured only for a Garmin Venu Sq2. A demonstration of adding more compatible devices can be found in the previous video link.  

### WhimsServer

WhimsServer is a python program that utilizes Bleak and TKinter to automatically connect to the Arduino and provide the user an option to manually trigger the single cycle haptic response. The code is object oriented and lacks comments, but is otherwise complete. Before running, ensure the whims_sketch is ran on the Arduino. The program connects to the Aruino automatically based on the name, and if multiple BLE capable Arduinos are present it may require more precise naming or a different method of connecting to the correct Arduino (device UUID, Service UUID, etc).
