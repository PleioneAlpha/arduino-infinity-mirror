# Arduino Infinity Mirror [v1.0]
[![License](https://licensebuttons.net/l/by-sa/4.0/80x15.png)](https://creativecommons.org/licenses/by-sa/4.0/)

[pic1]: img/InfinityMirror-3.jpg "Infinity Mirror"
![alt-text][pic1]


## Table of Contents
* [Repository Contents](#repository-contents)
* [Requirements and Materials](#requirements-and-materials)
* [Installation](#installation)

## Repository Contents

* **/src** - Contains the code for the project.
* **/hardware** - Contains the fritzing file, breadboard outline, and schematic. Also contains the fusion 360 file for the 3D-printed case, and the associated stl files.
* **/build** - Contains the .ino file for use in the Arduino IDE.
* **/img** - Contains image files for this readme.
* **/LICENSE** - The license file.
* **/README.md** - The readme file.

## Requirements and Materials

Dependencies:
* Adafruit's NeoPixel Library https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation
* Paul Badger and Paul Stoffregen's Capacitive Sensing Library https://playground.arduino.cc/Main/CapacitiveSensor/

Materials:
* 1 x [Arduino Nano V3](https://store.arduino.cc/usa/arduino-nano)
* 1 x [USB Type A to Mini-B cable](https://www.amazon.ca/gp/product/B004W8EIMW/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1)
* 1 x [5VDC 4A Switching Power Supply](https://www.adafruit.com/product/1466)
* 1 x [Female DC Power adapter - 2.1mm Jack to Screw Terminal Block](https://www.adafruit.com/product/368)
* 1 x [Adafruit NeoPixel Digital RGB LED Strip - Black 60 LED - BLACK](https://www.adafruit.com/product/1461?length=1)
* 1 x [1000uF 25V Electrolytic Capacitor](https://bc-robotics.com/shop/1000uf25v-electrolytic-capacitor-2/)
* 1 x [Spool of 22AWG Stranded Wire - Red](https://bc-robotics.com/shop/22-awg-stranded-wire-red/)
* 1 x [Spool of 22AWG Stranded Wire - Black](https://bc-robotics.com/shop/22-awg-stranded-wire-black/)
* 1 x [9" Diameter Mirror](https://www.amazon.com/gp/product/B005IW5CE4/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
* 1 x 9" Diameter Two-Way Mirror (3.175mm thick) - Your local glass shop may be able to source and cut one of these.
* The following materials can be used instead of a glass two-way mirror:
  * Optional: 1 x [Acrylic (3.175mm thick)](https://www.amazon.com/dp/B004DYW31I/ref=pe_385040_30332190_pe_175190_21431760_M3T1_ST1_dp_2). Note: This must be cut into a 9" Diameter Disc.
  * Optional: 1 x [Gila Privacy Mirror Adhesive](https://www.amazon.com/dp/B000H5XTKG/ref=pe_385040_30332190_pe_175190_21431760_M3T1_ST1_dp_1) Note: This must be applied to the above acrylic. A guide which shows how to apply the film to the acrylic can be found [here](https://learn.adafruit.com/infinity-mirror-coaster/acrylic-setup).
* 1 x [Cryanoacrylate Super Glue](https://www.canadiantire.ca/en/pdp/lepage-all-plastics-super-glue-2-ml-0671451p.html#srp) __Warning: Use this in a well-ventilated area.__
* 1 x [1" x 18' Roll of Copper Tape](https://polymertape.com/products/copper-tape?variant=32412733734996)
* The following can be used instead of copper tape:
  * Aluminum Foil
* 1 x [100pF Capacitor](https://bc-robotics.com/shop/ceramic-capacitor-kit-250-pieces/)
* 1 x [470 Ohm Resistor](https://www.adafruit.com/product/2781)
* 4 x [100k Ohm Resistors](https://www.adafruit.com/product/2787)
* Optional but recommended:
  * To increase the sensitivity of the capacitive touch sensor, I recommend using one or more 1M ohm resistor(s) instead of the 100k Ohm Resistors: [1M Ohm Resistors](https://www.amazon.ca/Projects-100EP5141M00-Ohm-Resistors-Pack/dp/B0185FHALI/)
* 1 x [Adafruit Perma-Proto 1/2 Sized Breadboard](https://www.adafruit.com/product/1609)

Tools:
* 1 x Soldering Iron Kit
* 1 x Solder Wire
* 1 x Hot Glue Gun
* 1 x Wire Stripper
* 1 x Wire Cutter
* 1 x Small Philips Screwdriver

## Installation
