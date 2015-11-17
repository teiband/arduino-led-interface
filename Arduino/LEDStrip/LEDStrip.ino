// for Adafruit DotStar:
// ############################################
#include <Adafruit_DotStar.h>
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

// Here's how to control the LEDs from any two pins:
#define DATAPIN       11
#define CLOCKPIN      13
// #############################################

// for Adafruit NeoPixel:
// #############################################
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NEOPIXEL_DATA_PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel voltage_strip = Adafruit_NeoPixel(60, NEOPIXEL_DATA_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// #############################################


#define TOTAL_BYTES       32  // Gesamtgröße der Nachricht
#define TOTAL_DATA        30   // Gesamtgröße der Nutzdaten
#define NUMPIXELS         240
#define LEDS_PER_PACKAGE  10
#define TOTAL_LED_PACKETS NUMPIXELS/LEDS_PER_PACKAGE

#define VOLTAGE_PACKAGE_CNT TOTAL_LED_PACKETS

#define VOLTAGE_NUMPIXELS 8

// 115200
#define BAUDRATE 115200

Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_RGB);
  // TODO: above change color set to right value DOTSTAR_RGB ...


/* Protokoll:
 *  0.  header
 *  1.  ...
 *  30. ... data
 *  31. checksum
 */

 // Colors: BLUE RED GREEN

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}

void setup()
{
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP

  voltage_strip.begin(); // Initialize pins for output
  voltage_strip.show();  // Turn all LEDs off ASAP
  
  
  Serial.begin(BAUDRATE);
}

char buf[TOTAL_BYTES];  // contains only data, not full package information

int calcChecksum(char* frame, unsigned char frameLength)
{
    int checksum = 0;
    for(int i=0; i < frameLength; i++) {
        checksum += frame[i];
    }
    return (checksum %=256); // Modulo operation to limit checksum to char size
}

void updateVoltageStrip(char* buf)
{
  for (int i=0; i < VOLTAGE_NUMPIXELS; i++) {
    voltage_strip.setPixelColor(i, buf[i*3], buf[i*3+1], buf[i*3+2]);
  }
  voltage_strip.show();
}

int freeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void updateStrip(int packet_counter, char* buf)
{
  for (int i=0; i < LEDS_PER_PACKAGE; i++) {
    // uint32_t color = (uint32_t)buf[i*3] | (uint32_t)buf[i*3+1] << 8 | (uint32_t)buf[i*3+2] << 16; 
    strip.setPixelColor(i + (packet_counter*LEDS_PER_PACKAGE), buf[i*3], buf[i*3+1], buf[i*3+2]);  
  } 
}

char packet_counter = 0;

void debugLED(int n)
{
  strip.setPixelColor(n, 0x0F0F00);
  strip.show();
}

void loop(){

  int checksum = 0;
  
  if ( Serial.available() >= TOTAL_BYTES)
  {
    char first_byte = Serial.read();
    
    if(first_byte == packet_counter)
    {
      /*
      // clear input buffer
      for (int i = 0; i < TOTAL_BYTES; i++)
        buf[i] = 0;
      */
      
      int n = Serial.readBytes(buf, TOTAL_BYTES - 1);
      
      // received a full package?
      if (n == (TOTAL_BYTES - 1))
      {    
        checksum = calcChecksum(buf, TOTAL_BYTES-1);
        if (checksum == 0) {
          if (packet_counter == VOLTAGE_PACKAGE_CNT) {
            updateVoltageStrip(buf);
          }
          else {
            updateStrip(packet_counter, buf);
          }
          // increase packet_counter after full package received and checksum is right!
          packet_counter++;
        }

        // received the last package?
        if (packet_counter == (TOTAL_LED_PACKETS+1)) {
          packet_counter = 0;
          strip.show();
        }

        // after receiving full package, answer to pc:
        serialFlush();  // empty serial input buffer (data is corrupted after this received package!)
        Serial.write('R');
        Serial.write(packet_counter); // send new package_counter to PC
      }
    }
    // received the wrong package:
    else {
      serialFlush();  // empty serial input buffer, if header is wrong
      Serial.write('W');
      Serial.write(packet_counter); // send actual package_counter to PC
      
    }
  }
  // not all bytes of a package received yet:
  else {
    // send arduino expects new transmission: package zero:
    if (packet_counter == 0 && !Serial.available()) {
      Serial.write('N');
      Serial.write(packet_counter);
      // Wait for transmission to come in
      delayMicroseconds(1000*10);
    }   
  } 
}
