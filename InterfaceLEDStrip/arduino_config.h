#ifndef ARDUINO_CONFIG_H
#define ARDUINO_CONFIG_H

#define NUMPIXELS       240
#define PATTERN_DEPTH   4

#include <array>

typedef std::array< std::array<char, PATTERN_DEPTH>, NUMPIXELS> pattern_t;


#endif // ARDUINO_CONFIG_H

