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

    static const char HEADER = 0x01;
    static const char MOUSE_TAG = 'M';
    static const int TOTAL_BYTES = 32 ; // Gesamtgröße der Nachricht
    static const int TOTAL_DATA = 30;   // Gesamtgröße der Nutzdaten
    static const char TOTAL_PACKETS = 2;
    static const int NUMPIXELS = 20;  // usually 240, No of LEDs on Adafruit Dotstar strip

    static const int INPUT_BUFFER_SIZE = 64;

    char *color_buf[NUMPIXELS*3];
    char *extra_buf[TOTAL_DATA];

    int calcChecksum(char *frame, unsigned char frameLength) const;
public:
    arduino(char *deviceName);

    virtual ~arduino();
    void write();
    void createColorTriple(char red, char green, char blue, char *color_buf);
    void createColorTriple(uint32_t color, char *color_buf);
    void fillColor(char *colorTriple);
    void read(char *input_buf, unsigned int size);
    uint32_t dimLight(uint32_t color, float factor);
    void dimLight(char *color_buf, float factor);
    void setBattVoltage(float voltage);
};



#endif // ARDUINO_H
