/*
 * PatternGenerator.h
 *
 *  Created on: 29 Oct 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

#ifndef MULTIPLUS_H_
#define MULTIPLUS_H_

#define NUMPIXELS 240

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../InterfaceLEDStrip/arduino_config.h"
#include <iostream>

// TODO define this file!
// #include <PatternGeneratorData.h>

// get common arduino constants from xml file
// uint32_t pattern[NUMPIXELS][3];

using namespace std;

class PatternGenerator
{
private:

    // Member pointer for RTDB subobject
    KogniMobil::subobj_arduino_t *rtdb_obj;
    array <char, 4> color;
    pattern_t pattern;


    void copy2pattern(int i);
    void checkRange(int i);
public:

    PatternGenerator();

    void setRawPattern(pattern_t pattern);
    void setFillPattern(unsigned int spacing = 0);

    void setFillArea(unsigned int start, unsigned int end, unsigned int spacing = 0);
    
    void shiftPattern(int digits = 1);

    virtual ~PatternGenerator();

    void setBrightness(float brightness);
    void setPixel(unsigned int pixel);
    void setFadingArea(unsigned int start, int range, bool single_sided);
    void clear();
    void setColor(char red, char green, char blue, unsigned char prio);
    void setColor(char color, unsigned char prio);
    void setColor(uint32_t color_value, unsigned char prio);
    void dimLight(char *buf, float factor);
    void debugPattern(int flag) const;
    void debugLEDs(int flag);
};

#endif /* MULTIPLUS_H_ */
