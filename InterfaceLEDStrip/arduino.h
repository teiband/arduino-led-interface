/*
 * arduino.h
 *
 *  Created on: 21 Oct 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

#ifndef ARDUINO_H
#define ARDUINO_H

#include "arduino_config.h"
#include <stdint.h>
#include <array>
#include "RS232.h"

typedef std::array< std::array<char, PATTERN_DEPTH>, NUMPIXELS> pattern_t;

/* as in ArduinoData.h
typedef struct {
    std::array< std::array<char, PATTERN_DEPTH>, NUMPIXELS> pattern;
} subobj_arduino_t;
*/

class arduino {
private:
    RS232 COM;

    void debugHEX(char* color_buf, unsigned int length) const;


    static const int TOTAL_BYTES = 32 ;         // Size of a frame
    static const int TOTAL_DATA = 30;           // Size of payload of a frame
    // defined in arduino_config.h
    // static const int NUMPIXELS = 240;           // usually 240, No of LEDs on Adafruit Dotstar strip
    static const char LEDS_PER_PACKAGE = 10;    // do not change, hence payload is 3*10 = 30 bytes
    static const char TOTAL_LED_PACKETS = NUMPIXELS / LEDS_PER_PACKAGE;

    static const char TOTAL_RECEIVED_BYTES = 2;

    static const int INPUT_BUFFER_SIZE = 64;

    char color_buf[NUMPIXELS*3];
    char voltage_buf[TOTAL_DATA];

    // for thread implementation, 3 colors, 1 prio;
    pattern_t pattern;

    bool emergency_stop;

    int calcChecksum(char *frame, unsigned char frameLength) const;

    char color_triple[3];

    void processBattVoltage(float voltage);
public:
    arduino(const char *deviceName);

    virtual ~arduino();
    void write();
    void setColor(const char red, const char green, const char blue);
    void setColor(const char color);
    void setColor(uint32_t color);

    void fillColor();
    void fillColor(const char color);

    void read(char *input_buf, unsigned int size) const;
    // uint32_t dimLight(uint32_t color, float factor);
    void dimLight(char *color_buf, float factor);
    void setBattVoltage(float voltage);

    void setEmergencyState(bool state);
    bool getEmergencyState() const;

    void createColorTriple(const char color);

    void setPattern(pattern_t &pattern);

    void decreasePrio();
    void pattern2color_buf();
};



#endif // ARDUINO_H
