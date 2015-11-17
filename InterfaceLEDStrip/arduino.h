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

#include <stdint.h>
#include "RS232.h"




class arduino {
private:
    RS232 COM;

    void debugHEX(char* color_buf, unsigned int length) const;


    static const int TOTAL_BYTES = 32 ;         // Size of a frame
    static const int TOTAL_DATA = 30;           // Size of payload of a frame
    static const int NUMPIXELS = 240;           // usually 240, No of LEDs on Adafruit Dotstar strip
    static const char LEDS_PER_PACKAGE = 10;    // do not change, hence payload is 3*10 = 30 bytes
    static const char TOTAL_LED_PACKETS = NUMPIXELS / LEDS_PER_PACKAGE;

    static const int INPUT_BUFFER_SIZE = 64;

    char color_buf[NUMPIXELS*3];
    char voltage_buf[TOTAL_DATA];

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
};



#endif // ARDUINO_H
