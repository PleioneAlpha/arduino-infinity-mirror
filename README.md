# Arduino Infinity Mirror [v1.0]
[![License](https://licensebuttons.net/l/by-sa/4.0/80x15.png)](https://creativecommons.org/licenses/by-sa/4.0/)

[pic1]: img/InfinityMirror-3.jpg "Infinity Mirror"
![alt-text][pic1]


## Table of Contents
* [Repository Contents](#repository-contents)
* [Requirements and Materials](#requirements-and-materials)
* [Building The Mirror](#building-the-mirror)
* [Installation](#installation)
* [Credits](#credits)

## Repository Contents

* **/hardware** - Contains the fritzing file, breadboard outline, and schematic. Also contains the fusion 360 file for the 3D-printed case, and the associated stl files. Note: The original fusion 360 file was created by [The Ruiz Brothers](https://learn.adafruit.com/infinity-mirror-coaster/3d-printing). I have modified their design and included an updated fusion 360 file and .stl files.
* **/build** - Contains the .ino file for use with the Arduino IDE.
* **/img** - Contains image files for this readme.
* **/LICENSE** - The license file.
* **/README.md** - This readme file.

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
* 1 x 9" Diameter Glass Two-Way Mirror (3.175mm thick) - Your local glass shop may be able to source and cut one of these.
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

## Building The Mirror

[pic2]: hardware/InfinityMirrorSketch_bb.jpg "Infinity Mirror Breadboard Sketch"
![alt-text][pic2]

[pic3]: hardware/InfinityMirrorSketch_schem.jpg "Infinity Mirror Schematic"
![alt-text][pic3]

[pic4]: img/InfinityMirrorBuild.jpg "Infinity Mirror Build"
![alt-text][pic4]

### 3D Printing The Case

Use the attached .stl files to 3D print the case. Note that the case is approximately 10 inches in diameter and will require a fairly large printing bed.

### Assembly and Soldering

1. Drill a hole in the case for the barrel jack adapter. A 9/32" drill bit should be large enough.
2. Use hot glue to attach the barrel jack adapter to the PCB Case.
3. Drill a hole in the case between where the Arduino Nano will sit and where the copper tape or aluminum foil will be installed. This is where the USB cable will be routed. In the picture above, I didn't follow this step and drilled on the far side of the copper tape. This made it difficult to touch the capacitive touch sensor. 
4. If you purchased an arduino nano with headers then remove the metal portions of the headers. If you purchased a nano without headers, proceed to the next step.
5. Use scissors or a large wire stripper to strip the Mini-B USB cable. Strip it near the USB Type A head. Remove the shielding and cut the green and white wires. Route the usb cable through the hole in the case, strip the red wire, and connect the red wire to the positive terminal of the barrel jack adapter. Strip and connect the black wire to the negative terminal of the barrel jack adapter.
6. Connect the 1000uF capacitor to the barrel jack adapter. The shorter leg is typically the cathode (- side). __Make sure you connect the positive and negative ends of the capacitor to the adapter properly. This capacitor won't tolerate reversed polarity. Failure to connect it properly may cause the capacitor to explode or become permanently damaged.__
7. Solder the various circuits and connections on the arduino nano, copper/aluminum foil, and adafruit perma-protoboard. See the above breadboard sketch and schematic images for further information. __Note: Don't connect the LED strip's wires to the protoboard or barrel jack adapter yet. Also, if you chose to use a 1M ohm resistor: Substitute the 1M ohm resistor in place of the four 100k ohm resistors.__
8. Use hot glue to secure the perma-protoboard and the USB cable to the PCB case.
9. There are two plastic arms protruding from the case. Push the nano into these arms until it clicks in place.
10. Secure the nano with hot glue. Optionally: Secure it with fasteners.
11. Remove the plastic backing on the copper tape and attach it to the case. If you chose to use aluminum foil: glue it to the case.
12. Place the two way mirror disc into the top 3D-printed ring. Clean the bottom side of the mirror if necessary as it won't be accessible later.
13. Cut the NeoPixel Strip to an appropriate length. There will be markings on the strip that show you where you can cut.
14. Use hot glue (if it is in a silicone sleeve use the Cryanoacrylate Super Glue __in a well-ventilated area - preferably outdoors. Avoid breathing in the fumes of the activator as they are toxic. Read the warning labels on the product and follow the necessary precautions.__) to secure the LED strip to the 3D-printed inner ring. See [The Ruiz Brothers' case assembly guide] (https://learn.adafruit.com/infinity-mirror-coaster/case-assembly) if you require more information on how to secure the LED strip to the inner ring.
15. Slide the inner ring into the top of the case and route the wires through the opening.
16. Slide the back mirror into the top of the case.
17. Route the LED strip's cables through the opening on the base of the case.
__Note: If your LED strip is not a WS2812 strip then you will need to lookup how to connect your strip properly.__
18. Solder the LED strip's white wire to the perma-protoboard as per the schematic/breadboard pictures above.
19. Solder the LED strip's black wire to the Arduino's ground pin.
20. Connect the LED strip's red wire to the + side of the barrel jack adapter.
21. Connect the LED strip's black wire to the - side of the barrel jack adapter.
22. Follow the [installation](#installation) steps and test the mirror to ensure that everything works before proceeding further.
23. Use the Cryanoacrylate Super Glue to secure the top of the infinity mirror case to the base. Make sure you do so __in a well-ventilated area - preferably outdoors. Avoid breathing in the fumes of the activator as they are toxic. Read the warning labels on the product and follow the necessary precautions.__
24. Connect the USB Mini-B connector to the Arduino Nano.
25. Plug the 5VDC 4A switching power supply into the wall and the barrel plug into the barrel jack adapter.

## Installation



## Credits

This project was based on two other projects:
* [The Ruiz Brothers' NeoPixel Infinity Mirror Coaster](https://learn.adafruit.com/infinity-mirror-coaster)
  * The original case was created and shared by them in the form of a fusion 360 file. I have modified this file to increase the size of the case and added/removed other properties. Many other ideas and procedures from their guide were used in this project.
* [Ben Finio's Arduino-controlled RGB LED Infinity Mirror](https://www.instructables.com/Arduino-controlled-RGB-LED-Infinity-Mirror/)
  * Ben's guide inspired me to make a larger infinity mirror than the above project's coaster. Some of the items mentioned and/or used in this project were mentioned in his guide (i.e. the regular 9" mirror, the 22AWG hookup wire, the acrylic sheets, and the mirrored window tint).

Acknowledgements and Thank Yous:
* Adafruit for providing the [NeoPixel library](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation) and example files.
* Phillip Burgess, Kattni Rembor, laday ada for providing the [Adafruit NeoPixel Uberguide](https://learn.adafruit.com/adafruit-neopixel-uberguide) which has been very informative and helpful during this project.
* Paul Badger and Paul Stoffregen for creating and maintaining the [Capacitive Sensing Library](https://playground.arduino.cc/Main/CapacitiveSensor/) that was used in this project.
