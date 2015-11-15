/*
 * arduino.cpp
 *
 *  Created on: 21 Oct 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

#include "arduino.h"
#include <string>

#include <iostream>
#include <iomanip>
#include <math.h>

#include <stdio.h> // for printf support, only for DEBUG

using namespace std;

arduino::arduino(char* deviceName)  : COM(deviceName)
{
    buf = new char[TOTAL_BYTES];
}

void arduino::write()
{
    char output_buf[TOTAL_BYTES];
    char input_buf[INPUT_BUFFER_SIZE];
    char expected_package = 0;

    // bool ready = false;

    while (expected_package < (TOTAL_PACKETS-1)) {
        // set packet_counter

        read(input_buf, INPUT_BUFFER_SIZE);

        cout << "input: ";
        debugHEX(input_buf, 2);
        cout << "input2: " << input_buf[0] << (int)input_buf[1] << endl;

        // check for received arduino header:
        if (input_buf[0] == 'N')
            cerr << "arduino::write(): Arduino(HW) expects new transmission: packet 0x00" << endl;
        else if (input_buf[0] == 'W')
            cerr << "ERROR: arduino::write(): Arduino(HW) received wrong package" << endl;

        if (input_buf[0] != 'R' && input_buf[0] != 'W' && input_buf[0] != 'N')
            cerr << "ERROR: arduino::write(): Received wrong header from Arduino(HW)" << endl;


        // check if received packet_counter is valid
        if (input_buf[1] >= TOTAL_PACKETS || input_buf[1] < 0) {
            cerr << "ERROR arduino: write(): received package_counter outside of index range" << endl;
            expected_package = 0;
        }
        else {
            expected_package = input_buf[1];
        }

        output_buf[0] = expected_package;

        // cout << "Expected Package: " << (int)expected_package << endl;

        // copy from color buf to output_buf
        memcpy (output_buf + 1, buf + (expected_package * TOTAL_DATA), TOTAL_DATA);

        // TODO: implement checksum here

        output_buf[TOTAL_BYTES - 1] = (char)calcChecksum(output_buf, TOTAL_BYTES - 1);
        // cout << "checksum: " << (int)output_buf[TOTAL_BYTES] << endl;

        cout << "output: ";
        debugHEX(output_buf, TOTAL_BYTES);

        COM.rs232_write(output_buf, TOTAL_BYTES);

        cout << "output2: ";
        debugHEX(output_buf, TOTAL_BYTES);
    }

    cout << "------------------------------------------------------------" << endl;
    cout << "All packets transfered to Arduino!" << endl << endl;


}


void arduino::read(char* input_buf, unsigned int size)
{
    COM.rs232_read(input_buf, 2, 1);
}

void arduino::createColorTriple(char red, char green, char blue, char* buf)
{
    //            BLUE  RED   GREEN
    buf[0] = red;
    buf[1] = green;
    buf[2] = blue;
}

void arduino::createColorTriple(uint32_t color, char* buf)
{
    buf[0] = (color >> 16) & 0x00110000;
    buf[1] = (color >> 8) & 0x00001100;
    buf[2] = color & 0x00000011;
}

void arduino::fillColor(char* colorTriple)
{
    for (int i=0; i < (NUMPIXELS * 3); i++) {
        memcpy (buf + (3*i), colorTriple, 3);
    }
    // cout << hex << (int)buf[0] << (int)buf[1] << (int)buf[2] << endl;
}

void arduino::debugHEX(char *buf, unsigned int length) const
{
    printf("DEBUG-HEX: ");

    for (int i=0; i < length; i++) {
        printf("0x%X,", (unsigned char)buf[i]);
    }

    cout << endl;
}


// pass factor 0 ... 1 to dim light color array
void arduino::dimLight(char* buf, float factor) {
    for (int i=0; i < NUMPIXELS*3; i++) {
        buf[i] = (char)floor(buf[i] * factor);
    }
}

// pass factor 0 ... 1 to dim single light color
uint32_t arduino::dimLight(uint32_t color, float factor) {
    char r, g, b;

    r = color;
    g = color << 8;
    b = color << 16;

    r = (char)floor(r * factor);
    g = (char)floor(g * factor);
    b = (char)floor(b * factor);

    return color;
}

int arduino::calcChecksum(char* frame, unsigned char frameLength) const
{
    // calculate checksum without header (i = 1 because of implementation in Arduino(HW))
    int checksum = 0;
    for(int i=1; i < frameLength; i++) {
        checksum += frame[i];
    }
    return - (checksum %=256); // Modulo operation to limit checksum to char size
}

arduino::~arduino()
{
    delete[] buf;
}
