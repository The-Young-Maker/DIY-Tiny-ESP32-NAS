![](img/1.jpg) 

# TinyNAS

A ESP32 powered web server with NAS functionality

## Features

- Basic Web Server

- Directory View 

- Cookie based login system

- File Manager
  
  - File Upload / Download (with multiple-file zip download support)
  
  - File Open, Cut and Copy
  
  - Support UTF-8 filename (32 bit length only, filename length depends on variable bytes used per char)

- File Searching Tool
  
  - Much slower than Google Search (Is this even a feature?)

- System Information
  
  - SD storage info
  - WiFi info

- WebApps
  
  - Music Player
  - Photo Viewier
  - Video Player
  - Markdown Editor
  - Notepad (Modified version of ACE Editor)

## Usage

### Hosting

1. Format your micro SD card as FAT (Recommend using [SD Card Formatter](https://www.sdcard.org/downloads/formatter/))
2. Download and put everything under sd_card folder in this repo into your micro SD card
3. Edit the files under /cfg/ to setup WiFi credentials (wifi.txt), management passwords (admin.txt) and optionally mDNS domain name (mdns.txt)
4. Insert your SD card into the TinyNAS SD card slot
5. Power on your TinyNAS by inserting it into your computer USB port (for debug / flash mode) or phone charger with USB A port.
6. Access your TinyNAS using the device IP address (http://192.168.0.100/) or mDNS name (e.g. http://TinyNAS.local)

#### Using your domain with TinyNAS

mDNS are local only domain names. If you want your viewer to be able to access your website from the public internet via your domain or your home public ip address, you will need to purchase a domain name, setup your DNS and / or your NAT router's port forward rules. 

### Build from Source

The following libraries are required for building the TinyNAS backend code (firmware to be used in ESP8266) using Arduino IDE. You can find the source code for the backend bare metal web-server in the ```/web-server``` folder.

#### Board Settings

Here are the recommended settings for best performance.

- Board: Wemos D1 R2 & Mini
  
  * CPU clockspeed: 160Mhz
  
  * IwIP Varient: v2 Higher Bandwidth

## Screenshots

#### Basic Web Servers

The TinyNAS provide basic web server functions like a fresh install Apache

![image-20230814160226604](img/README/image-20230814160226604.png)

▲ Homepage template

![image-20230814160246137](img/README/image-20230814160246137.png)

▲ Web server for HTML files

![image-20230814160329296](img/README/image-20230814160329296.png)

▲ Directory listing

#### Admin / Management Functions

TinyNAS contains basic functions for single admin environment. All file operations can only be performed by the only admin user in this system.

![image-20230814160710900](img/README/image-20230814160710900.png)

▲ Login / User System (based on Cookie not Basic Auth)

![image-20230814160412119](img/README/image-20230814160412119.png)

▲File Manager (Support upload, (multi-zip) download, copy, cut, paste, rename and new folder / files)

![image-20230814160505939](img/README/image-20230814160505939.png)

▲ Basic Search Engine (for local files)

![image-20230814160534701](img/README/image-20230814160534701.png)

▲ System Statistics

#### Multimedia

There are also limited multimedia streaming functionality on the TinyNAS.

![image-20230814160904725](img/README/image-20230814160904725.png)

▲ Basic Music Player

![image-20230814161008552](img/README/image-20230814161008552.png)

▲ Video Player (really small webm / mp4 files only)

![image-20230814161040075](img/README/image-20230814161040075.png)

▲ Photo Viewer

#### Other Utilities

TinyNAS also got other text editing utilities. If you are using markdown as notes or you want to update your website remotely, you can use the markdown editor or the notepadA editor. 

![image-20230814161027242](img/README/image-20230814161027242.png)

▲ Markdown Editor (Powered by SimpleMDE project)

![image-20230814161104181](img/README/image-20230814161104181.png)

▲ NotepadA Code Editor (Powered by ace editor, support multi-tabs)

## Limitations

As you might have notice by now this system is hosted on a 1 USD MCU (ESP32), even if web server is written in bare metal, it still have the following limitations

- Filename length (hardcoded to 32 bits per filename, might be shorter for UTF-8 as it use variable byte structure, but technically this is not the system limit)

- File size limit (recommend) <= 5MB, any file size larger than 5MB that is not stream-able (e.g. mp4) is not meaningful. Stream-able files can be larger than this size (e.g. webm) with acceptable playback speed.

- Slow Upload / Download speed (2 - 4Mbps), Very slow concurrent R/W speed (200 - 210 Kbps)

- Single admin session (cookie), due to limit in runtime memory (i.e. If you try to login from 2nd browser, the first browser will automatically logged out)

## License
Hardware Design (PCB files): CC BY-NC-SA

Backend Code (Arduino): MIT License

Front-end Code (html files): AGPL

*(I strongly recommend anyone with ability to write a better UI than my system :D)*
