# FoxNet
A webserver designed for file hosting on an ESP32/SD card independent of the internet. When powered on the FoxNet will set itself up as an access point using the credentials found near the beginning of the code in the main.cpp file and connect to the microSD card to setup a fileserver with the basic FoxNet page structure.

## BOM
The hardware I used for this device
- USB-C ESP32 Devkit1 V1 
- MicroSD card reader board
- 6 wire Jumpers

## Construction
The pinout for the device
MicroSD card    ESP32
board pins      pins

3v3 <---------> 3v3
CS <----------> D5
MOSI <--------> D23
CLK <---------> D18
MISO <--------> D19
GND <---------> GROUND

*NOTE The CS pin is configured in the program but otherwise it uses the default SPI pins so you may need to look up what those are on your ESP32 if it is different

The included FoxNetRoot.zip folder contains a default webpage and folder structure for the file server to use. the contents can be placed directly in the root of the SD card for use or you can build your own.

## Mode Select
The 3 connection modes available for ESP32 boards are Wifi Client, Wifi Access Point and ESP-NOW. I have assigned each one a number in the table below and you can enable whichever combination you want by finding what the sum of the desired modes is and setting the networkConfiguration variable to that in main.cpp

Wifi Client -------- 1
Wifi Access Point -- 2
ESP-NOW ------------ 4 *This mode is not currently implemented

The default setting is 2 for Access Point mode but it could be changed to 3 for Client and Access Point modes combined or once ESP-Now is implemented 7 would enable all three

## Authentication and connecting
The SSID for the ESP32 and the password are currently hard coded into the program and you should change them before use.