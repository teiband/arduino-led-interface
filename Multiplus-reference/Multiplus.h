/*
 * Multiplus.h
 *
 *  Created on: 21 Apr 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

/** Interface between Victron-Multiplus and Kogmo-RTDB
 *
 */

#ifndef MULTIPLUS_H_
#define MULTIPLUS_H_

#include "RS232.h"
#include <MultiPlusData.h>

class Multiplus {
private:

    /// Buffersize of the used hardware for the serial connection
    static const unsigned int BUFFERSIZE_MK2 = 255;
    /// Time (milliseconds) of the MK2 hardware to answer a request. In the Multiplus documentation, a minimum timeout value of 0.5 secs is advised.
    static const unsigned int RS232_TIMEOUT_MK2 = 750;

    /// Frame to request the LED Status of the device
    static const char REQUEST01[];  // LED Status
    /// Frame to request the DC info frame of the device
    static const char REQUEST02[];  // InfoFrame0 (DC)
    /// Frame to request the AC (L1) info frame of the device
    static const char REQUEST03[];  // InfoFrame1 (AC L1)
    /// Frame to request the AC (L2) info frame of the device
    static const char REQUEST04[];  // InfoFrame2 (AC L2)
    /// Frame to request the AC (L3) info frame of the device
    static const char REQUEST05[];  // InfoFrame3 (AC L3)
    /// Frame to request the AC (L4) info frame of the device
    static const char REQUEST06[];  // InfoFrame4 (AC L4)
    /// Frame to request the MasterMultiLED frame of the device
    static const char REQUEST07[];  // InfoFrame5 (MasterMultiLED frame) required?

    /// Instantiates class for serial connection handling
    RS232 COM;
    /// Member pointer for RTDB subobject
    KogniMobil::subobj_multiplus_t *Status;


    // void processCommand(char command, char* data, unsigned char size) const;
    //int receiveReply(char* buf) const;

    /**
     * @brief calcChecksum
     * @param frame pointer to char buffer
     * @param frameLength frame length of the char buffer
     * @return the sum of all bytes of the frame after modulo operation (sum%255). This should be 0 for a received frame, otherwise an checksum error will occur.
     */
    int calcChecksum(char* frame, unsigned char frameLength) const;
    /**
     * @brief Debug function to display data frames as hex-values. The length information of the buffer is taken from the buffer itself
     * @param buf pointer to a char array, which includes the frame
     */
    void debugHEX(char* buf) const;
    /**
     * @brief Request and receive LED Status
     * @return 0 for success, 1 for checksum error
     */
    int parseLEDStatus();
    /**
     * @brief Request and receive Master MultiLED Status
     * @return 0 for success, 1 for checksum error
     */
    int parseMasterMultiLEDframe();
    /**
     * @brief Request and receive DC InfoFrame 0
     * @return 0 for success, 1 for checksum error
     */
    int parseInfoframe_0();
    /**
     * @brief Request and receive AC-L1 InfoFrame 1
     * @return 0 for success, 1 for checksum error
     */
    int parseInfoframe_1();

    // void removeVersionFrame(char* buf);

public:
    /**
     * Constructs an Multiplus object.
     * @param deviceName device name of serial port in linux
     * @param rtdb_obj      pointer to an RTDB subobject to pass the data
     */
    Multiplus(char *deviceName, KogniMobil::subobj_multiplus_t *rtdb_obj);

    // void getLEDStatus();

    /**
     * @brief update function calls all available data request functions
     */
    void update();
    /**
     * @brief Destructor of Multiplus class, no cleanup necessary.
     */
    ~Multiplus();
};



#endif /* MULTIPLUS_H_ */
