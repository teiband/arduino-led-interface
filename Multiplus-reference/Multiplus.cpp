/*
 * Multiplus.cpp
 *
 *  Created on: 21 Apr 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

#include "Multiplus.h"
#include <string>

#include <iostream>
#include <iomanip>

using namespace std;

const char Multiplus::REQUEST01[] = {0x02, 0xff, 0x4c, 0xb3 };          // LED Status
const char Multiplus::REQUEST02[] = {0x03, 0xff, 0x46, 0x00 , 0xb8 };   // InfoFrame0 (DC)
const char Multiplus::REQUEST03[] = {0x03, 0xff, 0x46, 0x01 , 0xb7 };   // InfoFrame1 (AC L1)
const char Multiplus::REQUEST04[] = {0x03, 0xff, 0x46, 0x02 , 0xb6 };   // InfoFrame2 (AC L2)
const char Multiplus::REQUEST05[] = {0x03, 0xff, 0x46, 0x03 , 0xb5 };   // InfoFrame3 (AC L3)
const char Multiplus::REQUEST06[] = {0x03, 0xff, 0x46, 0x04 , 0xb4 };   // InfoFrame4 (AC L4)
const char Multiplus::REQUEST07[] = {0x03, 0xff, 0x46, 0x05 , 0xb3 };   // InfoFrame5 (MasterMultiLED frame) required?


Multiplus::Multiplus(char *deviceName, KogniMobil::subobj_multiplus_t *rtdb_obj) : COM(deviceName), Status(rtdb_obj)
{

}

void Multiplus::debugHEX(char *buf) const
{
    printf("DEBUG-HEX: %i,%i,%c,", buf[0], buf[1], buf[2]);

    if (buf[0] > 2) {
        for (int i=3; i < (buf[0]+1); i++) {
            printf("0x%x,", (unsigned char)buf[i]);
        }
    }
    else
        cout << "no_data,";

    // print checksum
    printf("CS:%i;", buf[buf[0]+2]);
    cout << endl;
}

void Multiplus::update()
{
    // comment in/out functions to request required data.
    parseLEDStatus();
    parseInfoframe_0();
    parseInfoframe_1();
    // parseMasterMultiLEDframe();
}

int Multiplus::calcChecksum(char* frame, unsigned char frameLength) const
{
    // calculate checksum
    int checksum = 0;
    for(int i=0; i < frameLength; i++) {
        checksum += frame[i];
    }
    return (checksum %=256); // Modulo operation to limit checksum to char size
}

int Multiplus::parseLEDStatus()
{
    int size = sizeof(REQUEST01);
    char buf[BUFFERSIZE_MK2];
    char checksum;

    cout << "Request LED Status" << endl;

    COM.rs232_write(REQUEST01, size);
    COM.rs232_read(buf, BUFFERSIZE_MK2, RS232_TIMEOUT_MK2);

    // removeVersionFrame(buf);

    if((u_int8_t)buf[1]==0xff && (u_int8_t)buf[2]== 'L' && (checksum = calcChecksum(buf, buf[0]+2))==0)
    {
        u_int8_t led_on= (u_int8_t)buf[3];
        u_int8_t led_blink= (u_int8_t)buf[4];

        Status->On.mains =       (led_on & 0x01) ? 1 : 0;
        Status->On.absorption =  (led_on & 0x02) ? 1 : 0;
        Status->On.bulk =        (led_on & 0x04) ? 1 : 0;
        Status->On.Float =       (led_on & 0x08) ? 1 : 0;
        Status->On.inverter =    (led_on & 0x10) ? 1 : 0;
        Status->On.overload =    (led_on & 0x20) ? 1 : 0;
        Status->On.lowbattery =  (led_on & 0x40) ? 1 : 0;
        Status->On.temperature=  (led_on & 0x80) ? 1 : 0;

        Status->Blink.mains =       (led_blink & 0x01) ? 1 : 0;
        Status->Blink.absorption =  (led_blink & 0x02) ? 1 : 0;
        Status->Blink.bulk =        (led_blink & 0x04) ? 1 : 0;
        Status->Blink.Float =       (led_blink & 0x08) ? 1 : 0;
        Status->Blink.inverter =    (led_blink & 0x10) ? 1 : 0;
        Status->Blink.overload =    (led_blink & 0x20) ? 1 : 0;
        Status->Blink.lowbattery =  (led_blink & 0x40) ? 1 : 0;
        Status->Blink.temperature=  (led_blink & 0x80) ? 1 : 0;

        cout << "LED Status parsed" << endl;
    }
    else if(checksum != 0)
    {
        cerr << "Error: LED frame checksum: " << +checksum << endl;
        return 1;
    }
    else
    {
        cerr << "Error: LED frame could not be parsed" << endl;
        return 1;
    }
    return 0;
}

//Parse DC InfoFrame 0
int Multiplus::parseInfoframe_0()
{
    int size = sizeof(REQUEST02);
    char buf[BUFFERSIZE_MK2];
    char checksum;

    cout << "Request InfoFrame 0 (DC)" << endl;

    COM.rs232_write(REQUEST02, size);
    COM.rs232_read(buf, BUFFERSIZE_MK2, RS232_TIMEOUT_MK2);

    // removeVersionFrame(buf);

    if((u_int8_t)buf[1]== ' ' && (checksum = calcChecksum(buf, buf[0]+2))==0)
    {
        Status->if0_phase_info = (u_int8_t)buf[6];
        Status->if0_DC_Voltage = (u_int8_t)buf[7] | (u_int8_t)buf[8] << 8;
        Status->if0_DC_Current_Inv = (u_int32_t)((u_int8_t)buf[9] | (u_int8_t)buf[10] << 8 | (u_int8_t)buf[11] << 16);
        Status->if0_DC_Current_Chg = (u_int32_t)((u_int8_t)buf[12] | (u_int8_t)buf[13] << 8 | (u_int8_t)buf[14] << 16);
        Status->if0_Inv_Periode = (u_int8_t)buf[15];
        Status->if0_Inv_Periode |= 0x100;
        Status->if0_Inv_Periode <<= 9;

        cout << "DC InfoFrame 0 parsed" << endl;
    }
    else if(checksum != 0)
    {
        cerr << "Error: DC InfoFrame 0 checksum: " << +checksum << endl;
        return 1;
    }
    else
    {
        cerr << "Error: DC InfoFrame 0 could not be parsed" << endl;
        return 1;
    }

  return 0;

}

//Parse AC InfoFrame 1
int Multiplus::parseInfoframe_1()
{
    int size = sizeof(REQUEST03);
    char buf[BUFFERSIZE_MK2];
    char checksum;

    cout << "Request InfoFrame 1 (AC-L1)" << endl;

    COM.rs232_write(REQUEST03, size);
    COM.rs232_read(buf, BUFFERSIZE_MK2, RS232_TIMEOUT_MK2);

    // removeVersionFrame(buf);

    if((u_int8_t)buf[1]== ' ' && (checksum = calcChecksum(buf, buf[0]+2))==0)
    {
        Status->if1_L1_bf_factor = (u_int8_t)buf[2];
        Status->if1_L1_inverter_factor = (u_int8_t)buf[3];
        Status->if1_L1_phase_info = (u_int8_t)buf[6];
        Status->if1_L1_mains_voltage = (u_int8_t)buf[7] | (u_int8_t)buf[8] << 8;
        Status->if1_L1_mains_current = ((u_int8_t)buf[9] | (u_int8_t)buf[10] << 8) * Status->if1_L1_bf_factor;
        Status->if1_L1_inverter_voltage = (u_int8_t)buf[11] | (u_int8_t)buf[12] << 8;
        Status->if1_L1_inverter_current = ((u_int8_t)buf[13] | (u_int8_t)buf[14] << 8) * Status->if1_L1_inverter_factor;
        Status->if1_L1_mains_periode = (u_int8_t)buf[15];
        Status->if1_L1_mains_periode <<= 10;

        cout << "AC-L1 InfoFrame 1 parsed" << endl;
    }
    else if(checksum != 0)
    {
        cerr << "Error: AC-L1 InfoFrame1 checksum: " << +checksum << endl;
        return 1;
    }
    else
    {
        cerr << "Error: AC-L1 InfoFrame 1 could not be parsed: " << endl;
        return 1;
    }

    return 0;

}

int Multiplus::parseMasterMultiLEDframe()
{
    int size = sizeof(REQUEST07);
    char buf[BUFFERSIZE_MK2];
    char checksum;

    cout << "Request MasterMultiLED frame" << endl;

    COM.rs232_write(REQUEST07, size);
    COM.rs232_read(buf, BUFFERSIZE_MK2, RS232_TIMEOUT_MK2);

    // removeVersionFrame(buf);

    if((u_int8_t)buf[2]== 'V' && (checksum = calcChecksum(buf, buf[0]+2))==0)
    {
        Status->mplf_ac_input_conf=(u_int8_t)buf[6];
        Status->mplf_min_inp_cur_lmt=(u_int8_t)buf[7] | (u_int8_t)buf[8] << 8;;
        Status->mplf_max_inp_cur_lmt=(u_int8_t)buf[9] | (u_int8_t)buf[10] << 8;;
        Status->mplf_actual_inp_cur_lmt=(u_int8_t)buf[11] | (u_int8_t)buf[12] << 8;;

        cout << "MasterMultiLEDFrame parsed" << endl;
    }
    else if(checksum != 0)
    {
        cerr << "Error: MasterMultiPlusLEDFrame checksum: " << +checksum << endl;
        return 1;
    }
    else
    {
        cerr << "Error: MasterMultiLEDFrame could not be parsed" << endl;
        return 1;
    }
    return 0;
}

/*
void Multiplus::removeVersionFrame(char *buf)
{
    cout << "DEBUG before removeVersionFrame" << endl;
    debugHEX(buf);
    if((u_int8_t)buf[1]==0xff && buf[2]=='V')
    {
        char length=0;
        char temp[BUFFERSIZE_MK2];

        // shift buffer to remove MK2 version frame, which occurs once a second
        length =  (u_int8_t)buf[0]+2;

        cout << "length of version frame: " << +length << endl;

        memcpy(temp, buf, length);
        memcpy(buf, temp+length, length);
    }
    cout << "DEBUG after removeVersionFrame" << endl;
    debugHEX(buf);

}
*/

/*
void Multiplus::getLEDStatus()
{
    char command = 'L'; // command for requesting LED status
    char *data = NULL;
    unsigned char size = 0;

    processCommand(command, data, size);

    char reply[BUFFERSIZE_MK2];
    // write data into reply buffer
    receiveReply(reply);

    if((u_int8_t)reply[1]==0xff && (u_int8_t)reply[1]== 'L' && calcChecksum(reply, reply[0]+2) == 0)
    {
        u_int8_t led_on= (u_int8_t)reply[3];
        u_int8_t led_blink= (u_int8_t)reply[4];

        Status->On.mains =          (led_on & 0x01) ? 1 : 0;
        Status->On.absorption =     (led_on & 0x02) ? 1 : 0;
        Status->On.bulk =           (led_on & 0x04) ? 1 : 0;
        Status->On.Float =          (led_on & 0x08) ? 1 : 0;
        Status->On.inverter =       (led_on & 0x10) ? 1 : 0;
        Status->On.overload =       (led_on & 0x20) ? 1 : 0;
        Status->On.lowbattery =     (led_on & 0x40) ? 1 : 0;
        Status->On.temperature=     (led_on & 0x80) ? 1 : 0;

        Status->Blink.mains =       (led_blink & 0x01) ? 1 : 0;
        Status->Blink.absorption =  (led_blink & 0x02) ? 1 : 0;
        Status->Blink.bulk =        (led_blink & 0x04) ? 1 : 0;
        Status->Blink.Float =       (led_blink & 0x08) ? 1 : 0;
        Status->Blink.inverter =    (led_blink & 0x10) ? 1 : 0;
        Status->Blink.overload =    (led_blink & 0x20) ? 1 : 0;
        Status->Blink.lowbattery =  (led_blink & 0x40) ? 1 : 0;
        Status->Blink.temperature=  (led_blink & 0x80) ? 1 : 0;

        Status->bOn = led_on;
        Status->bBlink = led_on;

    }
    else
    {
        cerr << "Multiplus: Checksum LEDFrame: Error" << endl;
        // return 1;
    }

    // return 0;
}
*/

/*
void Multiplus::processCommand(char command, char* data, unsigned char size) const
{
    // Length, 0xFF, Command, Data_0... Data_n, Checksum
    // Length: Length of frame, excluding length and checksum
    char length = size + 2;			// + 0xFF + command
    char frameLength = length + 2;	// + length + checksum
    char frame[frameLength];
    frame[0] = length;
    frame[1] = 0xFF;
    frame[2] = command;

    memcpy((frame + 3), data, size);

    int checksum = 0;
    checksum = - calcChecksum(frame, frameLength-1);

    // negate checksum and add to last field, so that frame equals 0
    frame[frameLength-1] = (char)checksum;

    // check for checksum again for full frame
    if(calcChecksum(frame, frameLength) == 0)
        cout << "Checksum calculation for processed command successfull!" << endl;
    else
        cerr << "Multiplus: Checksum calculation for processed command failed!" << endl;

    debugHEX(frame);

    // write to serial port
    COM.rs232_write(frame, frameLength);
}

int Multiplus::receiveReply(char* buf) const
{
    int bytes_read = 0;

    // sleep(RS232_TIMEOUT_MK2);

    bytes_read=COM.rs232_read(buf, BUFFERSIZE_MK2, RS232_TIMEOUT_MK2);

    debugHEX(buf);

    return bytes_read;
}
*/

Multiplus::~Multiplus()
{

}
