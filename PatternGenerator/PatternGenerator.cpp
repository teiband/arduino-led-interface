/*
 * PatternGenerator.cpp
 *
 *  Created on: 29 Oct 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

#include "PatternGenerator.h"


PatternGenerator::PatternGenerator(KogniMobil::subobj_multiplus_t *rtdb_obj) : (rtdb_obj)
{
  // read constants from xml file
}

void PatternGenerator::setRawPattern(uint32_t* pattern)
{
  memcpy (rtdb_obj.pattern, pattern, NUMPIXELS * 3);
}
void PatternGenerator::setFillPattern(uint32_t color, unsigned int spacing /* = 0 */)
{
  for (int i=0; i < (NUMPIXELS); i++) {
    memcpy (pattern + i, colorTriple, 1);
    // TODO add spacing functionality
  }
}

void PatternGenerator::setFillArea(uint32_t color, unsigned int start, unsigned int end, unsigned int spacing /* = 0 */)
{
  for (int i=0; i < (NUMPIXELS); i++) {
    memcpy (pattern + i, color, 1);
  }
}

void PatternGenerator::setBrightness(uint32_t color, float brightness)
{
  // see arduino.cpp
  // brightness from 0 to 1
}

void PatternGenerator::setPixel(uint32_t color, unsigned int pixel)
{
  pattern[pixel] = color;
}

void PatternGenerator::setFadingArea(uint32_t color, unsigned int start, int range , boolean single_sided /* = false */)
{
  // set start pixel color
  setPixel(color, start);
  
  if (single_sided = false) {
    range = abs(range)
    // create color transition:
    for (int i = range; i > 0; i--) {
      color = setBrightness(color, i / range);
      setPixel(color, start++ );
      setPixel(color, start--);
    }
  }
  else {
    // create color transition:
    for (int i = abs(range); i > 0; i--) {
      color = setBrightness(color, i / range);
      if (range > 0)
        setPixel(color, start++);
      else
        setPixel(color, start--)
    }
  }
  
}

void PatternGenerator::shiftPattern(int digits /* = 1 */)
{
  if (abs(digits) >= NUMPIXELS) {
    cerr << "shift value too big: digits = " << digits << endl
    cerr << "Maximum is NUMPIXELS = " << NUMPIXELS << endl;
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

void PatternGenerator::debugLEDs(int flag /* = 0 */) {
  // TODO finish debug function
  switch(i) {
    case 0: // print color
      for (int i=0; i < NUMPIXELS; i++) {
        cout << pattern[i]
        cout << (i%10 == 0 ? endl : " ")
      }
      
    case 1: // print pattern
      for (int i=0; i < NUMPIXELS; i++) {
        cout << pattern[i]
        cout << (i%10 == 0 ? endl : " ")
      }
    
  }
  
}

void PatternGenerator::clear()
{
  memset(pattern, 0, sizeof(pattern)); // for automatically-allocated arrays
}

PatternGenerator::~PatternGenerator()
{
  
}
