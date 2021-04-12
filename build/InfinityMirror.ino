/*
  Infinity Mirror Program

  Description:  This program changes the colours of an LED strip whenever the capacitive touch sensor
                registers above a certain threshold.

  Setup:        Please see the accompanying fritzing diagram and readme file for information about the setup.

  modified 10 Apr 2021
  by Vincent Derzaph
  created 21 Feb 2021
  by Vincent Derzaph

  Credits:      Adafruit for providing the Adafruit NeoPixel library and example files which can be downloaded here:
                https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation
                This program uses some of the code and comments from this library's example files.

                Phillip Burgess for providing the Adafruit NeoPixel Uberguide which outlines how to setup
                and use the NeoPixels:
                https://learn.adafruit.com/adafruit-neopixel-uberguide

                Paul Badger for his article on capacitive touch sensors and for originally creating the
                Capacitive Sensing Library that is used in this program:
                https://playground.arduino.cc/Main/CapacitiveSensor/

                Paul Stoffregen for maintaining the Capacitive Sensing Library mentioned above.
*/

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

// Libraries
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>
#ifdef __AVR__
#include <avr/power.h>                                      // Required for 16 MHz Adafruit Trinket.
#endif


// Pins
#define LED_PIN    6                                        // Which pin on the Arduino is connected to the NeoPixels?
CapacitiveSensor   cs_9_A0 = CapacitiveSensor(9, A0);       // Capacitive Touch Sensor Output/Send Pin (9) and Input Pin (A0).

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 41

// Constants
const int PRIMARY_DELAY_TIME = 250;                         // The minimum time that must pass until the user can change the state of the LED
                                                            //    strip again.
const int SECONDARY_DELAY_TIME = 50;                        // A small delay used throughout the program to reduce the load on the Arduino and
                                                            //    ensure that the capacitive touch sensor doesn't constantly send pulses through
                                                            //    the send pin.
const long CAP_SENSOR_THRESHOLD = 25;                       // The threshold at which the capacitive touch sensor will trigger a change in
                                                            //    the LEDs. This value may need to be calibrated.

// Global Variables
long lastCapSensorValue = 0;                                // The capacitive touch sensor value obtained from the last read.
long curCapSensorValue = 0;                                 // The current capacitive touch sensor value.
bool InterruptFlag = false;                                 // A flag that will allow the user to change the state of the LEDs during loops
                                                            //    (i.e. during the rainbow() function).
int choice = 0;                                             // Used in a switch statement to keep track of the current colour pattern.


// Declare our NeoPixel strip object:
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// ========================================================================
// Setup
// ========================================================================
// Runs once when the Arduino is powered on
void setup() {

  // Begin serial communication
  Serial.begin(9600);                                       // Used for debugging and calibrating the capacitive touch sensor.

  strip.begin();                                            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();                                             // Turn OFF all pixels ASAP
  strip.setBrightness(255);                                 // Set BRIGHTNESS (min = 0; max = 255)
}

// ========================================================================
// Main Program Loop
// ========================================================================
void loop() {

  CycleChoice();                                            // Wait for the user to activate the capacitive touch sensor and change
                                                            // the state of the LED strip.

  // DEBUG - Format and output the capacitive touch sensor's values to the serial monitor.
//    if (lastCapSensorValue < 10)
//    {
//      Serial.print("LastCap:  ");
//    }
//    else
//    {
//      Serial.print("LastCap: ");
//    }
//    Serial.print(lastCapSensorValue);
//    Serial.print("  CurCap: ");
//    Serial.println(curCapSensorValue);


  delay(SECONDARY_DELAY_TIME);                              // A small delay to reduce the load on the Arduino and prevent the capacitive touch sensor
                                                            //    from reading new values constantly.
}

// ========================================================================
// StoreAndStoreAndReadCapacitiveTouchSensorValues
// ========================================================================
// This function stores the last sensor value and reads the current value
void StoreAndReadCapacitiveTouchSensorValues()
{
  lastCapSensorValue = curCapSensorValue;                   // Store the last capacitive touch sensor value.
  curCapSensorValue =  cs_9_A0.capacitiveSensor(30);        // Read the current capacitive touch sensor value - 30 is the default number of samples.
}

// ========================================================================
// CycleChoice
// ========================================================================
// This function checks if the capacitive touch sensor was activated. If so, it will change the state of the LED strip.
void CycleChoice()
{
  // If the capacitive touch sensor was activated during a colour pattern loop then skip storing and reading a sensor value and change the
  //    state of the LED strip.
  if (InterruptFlag == false)
  {
    StoreAndReadCapacitiveTouchSensorValues();
  }

  // If the capacitive touch sensor is activated above the set threshold then change the state of the LED strip. Also, change the state if the
  //     sensor was activated during a colour pattern loop.
  if ((curCapSensorValue >= CAP_SENSOR_THRESHOLD && lastCapSensorValue < CAP_SENSOR_THRESHOLD) || InterruptFlag)
  {
    InterruptFlag = false;                                  // Turn the interrupt flag off now that it has served its purpose.
    choice++;

    // If the current choice value is higher than the number of available lighting patterns then reset it.
    if (choice >= 8)
    {
      choice = 0;
    }

    // Cycle through the colour patterns each time the user activates the sensor.
    switch (choice)
    {
      case 0:
        colorWipe(strip.Color(0,   0,   0), 0);             // Off
        break;
      case 1:
        colorWipe(strip.Color(255,   0,   0), 0);           // Red
        break;
      case 2:
        colorWipe(strip.Color(0,   255,   0), 0);           // Green
        break;
      case 3:
        colorWipe(strip.Color(0,   0,   255), 0);           // Blue
        break;
      case 4:
        rainbow(1);
        break;
      case 5:
        theaterChaseRainbow(50);
        break;
      case 6:
        rainbowWheel(10);
        break;
      case 7:
        rainbowCycleWheel(10);
        break;
      default:
        colorWipe(strip.Color(0,   0,   0), 0);             // Off
        break;
    }

    delay(PRIMARY_DELAY_TIME);                              // Pause for a short time to ensure that the colour patterns don't change too quickly.
  }
}

// ========================================================================
// CheckSensorWhileRunning
// ========================================================================
// This function will check whether or not the capacitive touch sensor has been activated during
// a colour pattern loop such as rainbow().
void CheckSensorWhileRunning()
{
  StoreAndReadCapacitiveTouchSensorValues();                // Store the old sensor value and retrieve a new one.

  // DEBUG - Useful during calibration of the CAP_SENSOR_THRESHOLD. Use this to output the sensor values during colour pattern loops.
      // Format the output and output the sensor values
//      if (lastCapSensorValue < 10)
//      {
//        Serial.print("LastCap:  ");
//      }
//      else
//      {
//        Serial.print("LastCap: ");
//      }
//      Serial.print(lastCapSensorValue);
//      Serial.print("  CurCap: ");
//      Serial.println(curCapSensorValue);

  // If the sensor value is above the threshold then turn on the interrupt flag which will allow a faster transition to the next colour pattern.
  if (curCapSensorValue >= CAP_SENSOR_THRESHOLD && lastCapSensorValue < CAP_SENSOR_THRESHOLD)
  {
    InterruptFlag = true;
  }
}

// ========================================================================
// SensorWatch
// ========================================================================
// This function will ensure that the colour patterns don't change too quickly during the colour pattern loops (such as rainbow()).
//    This means that the function will not check if the capacitive touch sensor was activated until PRIMARY_DELAY_TIME milliseconds have passed.
//    When PRIMARY_DELAY_TIME has passed then this function will ensure that the sensor is checked only once every SECONDARY_DELAY_TIME milliseconds.
void SensorWatch (unsigned long functionStartTime, unsigned long& timeCheck, unsigned long& lastCheck)
{
  timeCheck = millis() - functionStartTime;                  // Determine how many seconds have passed since the start of the colour pattern loop.

  // If the colour pattern changed more than PRIMARY_DELAY_TIME milliseconds ago and the time since the last sensor check is greater than SECONDARY_DELAY_TIME
  //    then the user may change the colour pattern again.
  if (timeCheck > PRIMARY_DELAY_TIME && (timeCheck - lastCheck > SECONDARY_DELAY_TIME))
  {
    lastCheck = timeCheck;                                  // Store the last time the sensor was checked.
    CheckSensorWhileRunning();                              // Check if the sensor has been activated.
  }
}

// ========================================================================
// Lighting Effects
// ========================================================================


// ========================================================================
// colorWipe
// ========================================================================
// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {

  for (int i = 0; i < strip.numPixels(); i++) {             // For each pixel in strip...

    strip.setPixelColor(i, color);                          //  Set pixel's color (in RAM).
    strip.show();                                           //  Update strip to match.
    delay(wait);                                            //  Pause for a moment.
  }
}

// ========================================================================
// rainbow
// ========================================================================
// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {

  // Local variables
  unsigned long functionStartTime = millis();               // Record when this colour pattern began running.
  unsigned long timeCheck = functionStartTime;              // Set the initial timeCheck to when this colour pattern began running.
  unsigned long lastCheck = functionStartTime;              // Set the initial lastCheck to when this colour pattern began running.
  long firstPixelHue = 0;



  // Loop through the rainbow effect repeatedly until the interupt flag is triggered by the activation of the capacitive touch sensor.
  while (!InterruptFlag) {

    for (int i = 0; i < strip.numPixels(); i++) {           // For each pixel in strip...

      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));

    }

    strip.show();                                           // Update strip with new contents.

    // Check if the capacitive touch sensor has been activated during the rainbow effect loop. If so, interrupt the effect
    //    and change to the next effect.
    SensorWatch(functionStartTime, timeCheck, lastCheck);

    // If the capacitive touch sensor has been activated then exit this while loop.
    if (InterruptFlag)
    {
      break;
    }

    firstPixelHue += 256;                                   // Iterate through the hues.
    delay(wait);                                            // Pause for a moment.
  }
}

// ========================================================================
// theatherChaseRainbow
// ========================================================================
// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {

  // Local variables
  int firstPixelHue = 0;                                    // First pixel starts at red (hue 0).
  unsigned long functionStartTime = millis();               // Record when this colour pattern began running.
  unsigned long timeCheck = functionStartTime;              // Set the initial timeCheck to when this colour pattern began running.
  unsigned long lastCheck = functionStartTime;              // Set the initial lastCheck to when this colour pattern began running.

  // Loop through the rainbow effect repeatedly until the interupt flag is triggered by the activation of the capacitive touch sensor.
  while (!InterruptFlag) {
    for (int b = 0; b < 3; b++) {                           //  'b' counts from 0 to 2...

      strip.clear();                                        //   Set all pixels in RAM to 0 (off)

      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue));// hue -> RGB
        strip.setPixelColor(c, color);                      // Set pixel 'c' to value 'color'
      }

      strip.show();                                         // Update strip with new contents.

      // Check if the capacitive touch sensor has been activated during the rainbow effect loop. If so, interrupt the effect
      //    and change to the next effect.
      SensorWatch(functionStartTime, timeCheck, lastCheck);

      // If the capacitive touch sensor has been activated then exit this for loop.
      if (InterruptFlag)
      {
        break;
      }

      delay(wait);                                          // Pause for a moment.
      firstPixelHue += 65536 / 90;                          // One cycle of color wheel over 90 frames.
    }

    // If the capacitive touch sensor has been activated then exit this while loop.
    if (InterruptFlag)
    {
      break;
    }
  }
}

// ========================================================================
// rainbowWheel
// ========================================================================
void rainbowWheel(uint8_t wait) {

  // Local variables
  uint16_t i, j = 0;
  unsigned long functionStartTime = millis();               // Record when this colour pattern began running.
  unsigned long timeCheck = functionStartTime;              // Set the initial timeCheck to when this colour pattern began running.
  unsigned long lastCheck = functionStartTime;              // Set the initial lastCheck to when this colour pattern began running.

  // Loop through the rainbow effect repeatedly until the interupt flag is triggered by the activation of the capacitive touch sensor.
  while (!InterruptFlag) {

    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }

    strip.show();                                           // Update strip with new contents.

    // Check if the capacitive touch sensor has been activated during the rainbow effect loop. If so, interrupt the effect
    //    and change to the next effect.
    SensorWatch(functionStartTime, timeCheck, lastCheck);

    // If the capacitive touch sensor has been activated then exit this while loop.
    if (InterruptFlag)
    {
      break;
    }
    j++;
    delay(wait);                                            // Pause for a moment.
  }
}

// ========================================================================
// RainbowCycleWheel
// ========================================================================
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycleWheel(uint8_t wait) {

  // Local variables
  uint16_t i, j = 0;
  unsigned long functionStartTime = millis();               // Record when this colour pattern began running.
  unsigned long timeCheck = functionStartTime;              // Set the initial timeCheck to when this colour pattern began running.
  unsigned long lastCheck = functionStartTime;              // Set the initial lastCheck to when this colour pattern began running.

  // Loop through the rainbow effect repeatedly until the interupt flag is triggered by the activation of the capacitive touch sensor.
  while (!InterruptFlag) {

    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }

    strip.show();                                           // Update strip with new contents.

    // Check if the capacitive touch sensor has been activated during the rainbow effect loop. If so, interrupt the effect
    //    and change to the next effect.
    SensorWatch(functionStartTime, timeCheck, lastCheck);

    // If the capacitive touch sensor has been activated then exit this while loop.
    if (InterruptFlag)
    {
      break;
    }
    j++;
    delay(wait);                                            // Pause for a moment.
  }
}

// ========================================================================
// Wheel
// ========================================================================
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
