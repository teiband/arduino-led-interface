/*
 * PatternGenerator.cpp
 *
 *  Created on: 29 Oct 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

#include "PatternGenerator.h"

using namespace std;


PatternGenerator::PatternGenerator(KogniMobil::subobj_multiplus_t *rtdb_obj) : (rtdb_obj)
{
  // TODO read constants from xml file?
}

void PatternGenerator::setRawPattern(pattern_t pattern)
{
    this->pattern = pattern;
}
void PatternGenerator::setFillPattern(unsigned int spacing /* = 0 */)
{
    for (int i=0; i < NUMPIXELS; i++) {
        pattern[i][0] = color[0];
        pattern[i][1] = color[1];
        pattern[i][2] = color[2];
        pattern[i][3] = color[3];
    // TODO add spacing functionality
    }
}

void PatternGenerator::setColor(char red, char green, char blue, unsigned char prio)
{
    // color order is defined in arduino constant DOTSTAR_RGB
    color[0] = blue;
    color[1] = green;
    color[2] = red;
    color[3] = prio;
}

void PatternGenerator::setColor(char color, unsigned char prio)
{
    switch (color) {
        case 'r':
        case 'R':
            setColor(0x10, 0x00, 0x00, prio);
            break;
        case 'g':
        case 'G':
            setColor(0x00, 0x10, 0x00, prio);
            break;
        case 'b':
        case 'B':
            setColor(0x00, 0x00, 0x10, prio);
            break;
        case 'w':
        case 'W':
            setColor(0x10, 0x10, 0x10, prio);
            break;
    }
}

void PatternGenerator::setColor(uint32_t color_value, unsigned char prio)
{
    // TODO check color order, compare with color generation part to shift in right way
    uint32_t bit_mask = 0x000011;
    color[0] = (char)(color_value & bit_mask);
    color[1] = (char)((color_value >> 8) & bit_mask);
    color[2] = (char)((color_value >> 16) & bit_mask);
    color[3] = prio;
}

void PatternGenerator::debugPattern(int flag) const
{
    cout << "debug pattern:" << endl;

    for (int i=0; i < NUMPIXELS; i++) {
        if (flag) {
            cout << (int)pattern[i][0] << ", " << pattern[i][1] << ", " << pattern[i][2] << ", " << pattern[i][3] << endl;
        }
        else {
            cout << pattern[i][0] > 0 ? 'X' : '0';
            cout << pattern[i][1] > 0 ? 'X' : '0';
            cout << pattern[i][2] > 0 ? 'X' : '0';
            cout << pattern[i][3] > 0 ? 'X' : '0';
        }

    }
    cout << endl;
}


// pass factor 0 ... 1 to dim light color array
void PatternGenerator::dimLight(char* buf, float factor) {
    for (int i=0; i < NUMPIXELS; i++) {
        for (int j=0; j < 3; j++) {
            pattern[i][j] = (char)(buf[i] * factor);
        }
    }
}

void PatternGenerator::setFillArea(unsigned int start, unsigned int end, unsigned int spacing /* = 0 */)
{
    checkRange(start);
    checkRange(end);

    for (int i=start; i < end; i += spacing) {
        copy2pattern(i);
    }
}

void PatternGenerator::copy2pattern(int i)
{
    for (int j=0; j < 4; j++)
        pattern[i][j] = color[j];
}

void PatternGenerator::setBrightness(float brightness)
{
    for (int i=0; i < 3; i++)
        color[i] *= brightness;
}

void PatternGenerator::setPixel(unsigned int pixel)
{
    checkRange(pixel);
    copy2pattern(pixel);
}

void PatternGenerator::checkRange(int i)
{
    // TODO also throw name of calling function with __func__
    if (i < 0 || i >= NUMPIXELS) {
        cerr << "Pixel index out of range. Range is from 0 to " << NUMPIXELS << endl;
        exit(EXIT_FAILURE);
    }
}

void PatternGenerator::setFadingArea(unsigned int start, int range , bool single_sided /* = false */)
{
    checkRange(start);
    checkRange(start+range);
    checkRange(start-range);

    // set start pixel color
    setPixel(start);
  
    if (single_sided = false) {
    range = abs(range);
    // create color transition:
    for (int i = range; i > 0; i--) {
        setBrightness(i / range);
        setPixel(start++ );
        setPixel(start--);
    }
    }
    else {
    // create color transition:
    for (int i = abs(range); i > 0; i--) {
        setBrightness(i / range);
        if (range > 0)
        setPixel(start++);
        else
        setPixel(start--);
    }
  }

}

void PatternGenerator::shiftPattern(int digits /* = 1 */)
{
    checkRange(digits);


  if (abs(digits) >= NUMPIXELS) {
    cerr << "shift value too big: digits = " << digits << ", maximum is NUMPIXELS = " << NUMPIXELS << endl;
    exit(EXIT_FAILURE);
  }
  
  if (digits > 0) {
    for (int i=0; i < (NUMPIXELS); i++) {
      // check if index after shifting is bigger than NUMPIXELS, then beginn from 0 again
      pattern[i] = pattern[((i + digits) >= NUMPIXELS ? (NUMPIXELS - 1 - i) : (i + digits))];
    }
  }
  if (digits < 0) {
    for (int i=0; i < (NUMPIXELS); i++) {
      // check if index after shifting is bigger than NUMPIXELS, then beginn from 0 again
      pattern[i] = pattern[((i + digits) < 0 ? (NUMPIXELS - i) : (i + digits))];
    }
  }
  
}

void PatternGenerator::clear()
{
    setColor(0,0,0,0);
    for (int i=0; i < NUMPIXELS; i++) {
        setPixel(i);
    }
}

PatternGenerator::~PatternGenerator()
{
  
}


