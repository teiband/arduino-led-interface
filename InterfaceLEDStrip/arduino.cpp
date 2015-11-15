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

arduino::arduino(const char *deviceName)  : COM(deviceName)
{
    //color_buf = new char[TOTAL_BYTES];
    //extra_buf = new char[TOTAL_BYTES];
    emergency_stop = false;

    for (int i=0; i < 3; i++)
        color_triple[i] = 0;

}

void arduino::setEmergencyState(bool state)
{
    emergency_stop = state;
}

bool arduino::getEmergencyState() const
{
    return emergency_stop;
}

/*
void arduino::readRTDB_pattern()
{
    for(int i=0; i < (NUMPIXELS*3); i++) {
        color = subobj.pattern[i];
        color_buf[i*3] = (color >> 16) & 0x00110000;
        color_buf[i*3+1] = (color >> 8) & 0x00001100;
        color_buf[i*3+2] = color & 0x00000011;
    }

}
*/

/*
void arduino::readRTDB_voltage()
{

}
*/

void arduino::write()
{
    char output_buf[TOTAL_BYTES];
    char input_buf[INPUT_BUFFER_SIZE];
    char expected_package = 0;

    bool emergency_flag = false;

    while ((expected_package < TOTAL_PACKETS) && (emergency_flag == false)) {

        read(input_buf, INPUT_BUFFER_SIZE);

        cout << "input: ";
        debugHEX(input_buf, 2);
        cout << "input2: " << input_buf[0] << (int)input_buf[1] << endl;

        // check for received arduino header:
        switch (input_buf[0]) {
            case 'E':
                cerr << "arduino::write(): Arduino(HW): EMERGENCY STOP occured" << endl;
                emergency_flag = true;
                setEmergencyState(true);
                break;
            case 'N':
                cerr << "arduino::write(): Arduino(HW) expects new transmission: packet 0x00" << endl;
                break;
            case 'W':
                cerr << "ERROR: arduino::write(): Arduino(HW) received wrong package" << endl;
                break;
            case 'R':
                cout << "arduino.write(): received right header" << endl;
                break;
            default:
                cerr << "ERROR: arduino::write(): Received wrong header from Arduino(HW)" << endl;
        }

        // check if received packet_counter is valid
        if (input_buf[1] > TOTAL_PACKETS || input_buf[1] < 0) {
            cerr << "ERROR arduino: write(): received package_counter outside of index range" << endl;
            expected_package = 0;
        }
        else {
            expected_package = input_buf[1];
        }

        output_buf[0] = expected_package;

        if (expected_package < TOTAL_PACKETS) {
            // copy from color_buf to output_buf
            memcpy (output_buf + 1, color_buf + (expected_package * TOTAL_DATA), TOTAL_DATA);
            cout << "arduino::write(): sending LED color information package no. " << (int)expected_package << endl;
        }
        else {
            // if last packet to send, then transmit extra package (voltage_information)
            memcpy (output_buf + 1, extra_buf, TOTAL_DATA);
            cout << "arduino::write(): sending voltage information package no." << (int)expected_package << endl;
        }

        output_buf[TOTAL_BYTES - 1] = (char)calcChecksum(output_buf, TOTAL_BYTES - 1);

        cout << "output: ";
        debugHEX(output_buf, TOTAL_BYTES);

        COM.rs232_write(output_buf, TOTAL_BYTES);
    }

    cout << "------------------------------------------------------------" << endl;
    cout << "All packets transfered to Arduino!" << endl << endl;

}


void arduino::read(char* input_buf, unsigned int size) const
{
    COM.rs232_read(input_buf, 2, 1);
}

void arduino::setColor(const char red, const char green, const char blue)
{
    // TODO check color order
    color_triple[0] = red;
    color_triple[1] = green;
    color_triple[2] = blue;
}

void arduino::createColorTriple(const char color)
{
    // TODO check color order
    switch (color) {
        case 'r':
        case 'R':
            setColor(0x10, 0x00, 0x00);
            fillColor();
            break;
        case 'g':
        case 'G':
            setColor(0x00, 0x10, 0x00);
            fillColor();
            break;
        case 'b':
        case 'B':
            setColor(0x00, 0x00, 0x10);
            fillColor();
            break;
        case 'w':
        case 'W':
            setColor(0x10, 0x10, 0x10);
            fillColor();
            break;
    }
}

void arduino::setColor(uint32_t color)
{
    // TODO check color order
    color_triple[0] = (color >> 16) & 0x00110000;
    color_triple[1] = (color >> 8) & 0x00001100;
    color_triple[2] = color & 0x00000011;
}

void arduino::fillColor()
{
    for (int i=0; i < (NUMPIXELS * 3); i++) {
        memcpy (color_buf + (3*i), color_triple, 3);
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

void arduino::setBattVoltage(float voltage)
{
    /*
    union float2chars {
        float voltage;
        char bytes[4];
    } f2c;
    */

    memcpy (extra_buf, &voltage, sizeof(float));  // sizeof(float) = 4byte
    cout << "DEBUG: float2char: " << endl;
}

/*
// pass factor 0 ... 1 to dim single light color
uint32_t arduino::dimLight(uint32_t color, float factor) {
    char r, g, b;

    r = color;
    g = color << 8;
    b = color << 16;

    r = (char)r * factor;
    g = (char)g * factor;
    b = (char)b * factor;

    return color;
}
*/

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
    // delete[] color_buf;
}
