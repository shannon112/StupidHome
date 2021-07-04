/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
uint16_t fanSwitchRawData[95] = {1322, 366,  1324, 362,  478, 1230,  1324, 366,  1326, 356,  480, 1226,  480, 1224,  480, 1226,  478, 1226,  480, 1224,  480, 1230,  1324, 6264,  1324, 368,  1324, 362,  478, 1230,  1326, 366,  1326, 358,  480, 1226,  478, 1224,  480, 1226,  478, 1226,  478, 1224,  480, 1230,  1324, 6266,  1326, 366,  1322, 364,  478, 1230,  1324, 368,  1324, 358,  478, 1226,  478, 1228,  454, 1250,  454, 1250,  454, 1252,  452, 1258,  1298, 7054,  1298, 396,  1298, 390,  452, 1256,  1298, 394,  1298, 386,  452, 1252,  452, 1250,  454, 1252,  452, 1252,  452, 1252,  452, 1256,  1298};  // SYMPHONY D81uint16_t rawData[95] = {1322, 366,  1324, 362,  478, 1230,  1324, 366,  1326, 356,  480, 1226,  480, 1224,  480, 1226,  478, 1226,  480, 1224,  480, 1230,  1324, 6264,  1324, 368,  1324, 362,  478, 1230,  1326, 366,  1326, 358,  480, 1226,  478, 1224,  480, 1226,  478, 1226,  478, 1224,  480, 1230,  1324, 6266,  1326, 366,  1322, 364,  478, 1230,  1324, 368,  1324, 358,  478, 1226,  478, 1228,  454, 1250,  454, 1250,  454, 1252,  452, 1258,  1298, 7054,  1298, 396,  1298, 390,  452, 1256,  1298, 394,  1298, 386,  452, 1252,  452, 1250,  454, 1252,  452, 1252,  452, 1252,  452, 1256,  1298};  // SYMPHONY D81
uint16_t fanAdjustRawData[95] = {1296, 394,  1296, 390,  452, 1256,  1298, 394,  1298, 386,  452, 1252,  452, 1252,  452, 1252,  452, 1252,  454, 1258,  1296, 390,  456, 7152,  1296, 392,  1298, 390,  452, 1256,  1300, 392,  1298, 386,  452, 1252,  452, 1252,  452, 1252,  452, 1252,  450, 1258,  1298, 390,  452, 7156,  1298, 392,  1298, 390,  452, 1254,  1300, 394,  1296, 386,  452, 1252,  452, 1250,  454, 1252,  452, 1252,  454, 1256,  1296, 390,  452, 7156,  1298, 394,  1296, 388,  452, 1254,  1300, 394,  1298, 384,  452, 1252,  452, 1250,  454, 1252,  450, 1254,  452, 1258,  1294, 392,  452};  // SYMPHONY D82
uint16_t tvSwitchRawData[71] = {9054, 4494,  550, 532,  576, 534,  574, 1666,  574, 536,  552, 532,  574, 534,  574, 532,  576, 532,  576, 1644,  574, 1668,  548, 560,  546, 1674,  574, 1642,  576, 1668,  546, 1674,  574, 1642,  574, 534,  574, 534,  576, 532,  576, 1644,  572, 534,  574, 534,  574, 534,  576, 532,  576, 1644,  572, 1668,  546, 1672,  574, 534,  574, 1642,  576, 1664,  550, 1670,  574, 1640,  576, 40726,  9052, 2222,  576};  // NEC 20DF10EF
uint16_t acSwitchOnRawData[227] = {3030, 1698,  478, 1070,  478, 1070,  478, 346,  480, 342,  480, 344,  480, 1070,  478, 344,  480, 362,  478, 1070,  478, 1070,  478, 344,  480, 1070,  476, 344,  480, 344,  480, 1070,  478, 1086,  478, 344,  480, 1070,  478, 1072,  476, 344,  480, 344,  480, 1070,  478, 344,  480, 362,  478, 1072,  476, 344,  480, 344,  480, 344,  480, 344,  480, 346,  478, 344,  480, 362,  476, 344,  480, 346,  478, 344,  480, 344,  480, 344,  480, 344,  480, 346,  480, 362,  476, 346,  480, 344,  480, 1070,  478, 344,  480, 344,  480, 1072,  476, 344,  480, 362,  476, 1070,  478, 1072,  476, 344,  480, 344,  480, 344,  478, 346,  480, 344,  478, 362,  478, 344,  480, 344,  480, 1070,  478, 346,  478, 344,  480, 344,  480, 344,  480, 362,  476, 344,  480, 344,  480, 344,  480, 1072,  476, 1068,  480, 1072,  476, 344,  478, 362,  478, 344,  478, 346,  478, 346,  480, 344,  478, 346,  480, 344,  480, 344,  478, 364,  476, 346,  478, 344,  480, 344,  480, 344,  478, 346,  480, 344,  480, 344,  478, 362,  478, 344,  478, 346,  478, 346,  480, 344,  478, 344,  480, 344,  480, 344,  480, 362,  478, 344,  480, 344,  478, 346,  478, 346,  478, 344,  478, 346,  480, 344,  480, 362,  476, 346,  480, 344,  480, 344,  480, 1072,  476, 1070,  478, 1072,  476, 1070,  478, 350,  478};  // TCL112AC
uint16_t acSwitchOffRawData[227] = {3028, 1698,  478, 1072,  476, 1072,  476, 346,  480, 342,  480, 344,  480, 1070,  478, 344,  480, 360,  478, 1070,  478, 1072,  478, 342,  480, 1070,  478, 344,  480, 344,  480, 1070,  478, 1086,  478, 344,  480, 1070,  478, 1072,  476, 344,  480, 344,  480, 1072,  476, 344,  480, 362,  478, 1072,  474, 344,  480, 342,  480, 344,  480, 344,  480, 344,  480, 344,  480, 360,  478, 344,  480, 344,  482, 344,  480, 344,  480, 344,  480, 344,  480, 344,  480, 362,  478, 344,  480, 344,  480, 344,  458, 370,  478, 344,  480, 1072,  476, 346,  478, 362,  478, 1070,  452, 1096,  478, 344,  456, 372,  476, 344,  456, 372,  452, 372,  452, 388,  452, 372,  476, 346,  460, 1092,  476, 344,  456, 372,  478, 344,  456, 370,  452, 388,  452, 372,  452, 370,  452, 372,  452, 1094,  454, 1096,  452, 1094,  454, 372,  452, 386,  454, 370,  454, 372,  452, 372,  452, 370,  454, 372,  452, 372,  452, 370,  454, 386,  454, 370,  454, 370,  452, 372,  452, 372,  452, 372,  452, 372,  452, 372,  452, 388,  452, 372,  452, 372,  454, 372,  452, 372,  452, 372,  454, 370,  452, 372,  452, 388,  452, 372,  452, 372,  452, 372,  452, 372,  452, 372,  452, 372,  450, 374,  452, 386,  452, 372,  452, 372,  450, 1098,  452, 372,  452, 1096,  452, 1096,  452, 1096,  450, 378,  452};  // TCL112AC

void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  if (Serial.available() > 0) 
  {
    String command = Serial.readString();
    Serial.println(command);
    if (command=="fanSwitch") irsend.sendRaw(fanSwitchRawData, 95, 38);  // Send a raw data capture at 38kHz.
    else if (command=="fanAdjust") irsend.sendRaw(fanAdjustRawData, 95, 38);
    else if (command=="tvSwitch") irsend.sendRaw(tvSwitchRawData, 71, 38);
    else if (command=="acSwitchOn") irsend.sendRaw(acSwitchOnRawData, 227, 38);
    else if (command=="acSwitchOff") irsend.sendRaw(acSwitchOffRawData, 227, 38);
    
  }
}
