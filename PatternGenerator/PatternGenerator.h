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

// TODO define this file!
// #include <PatternGeneratorData.h>

// get common arduino constants from xml file
// uint32_t pattern[NUMPIXELS][3];

class PatternGenerator
{
private:

    // Member pointer for RTDB subobject
    KogniMobil::subobj_patternGenerator_t *pattern;

public:

    PatternGenerator();

    void setRawPattern(uint32_t* pattern);
    void setFillPattern(uint32_t color, unsigned int spacing = 0);

    void setFillArea(uint32_t color, unsigned int start, unsigned int end, unsigned int spacing = 0);
    
    void shiftPattern(unsigned int digits = 1);

    virtual ~PatternGenerator();

};

#endif /* MULTIPLUS_H_ */
