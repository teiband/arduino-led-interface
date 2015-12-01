/*
 * main.cpp
 *
 *  Created on: 22 Nov 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */


#include "main.h"
#include <iostream>

// TODO: check this
#include <math.h>
#include <stdint.h>
#include "arduino.h"
#include "arduino_config.h"                     // TODO change path to global (see multiplus)
#include <ArduinoData.h>    // TODO change path to global (see multiplus)
#include <getopt.h>
#include <iostream>
#include <unistd.h> // for sleep()
#include <thread>
#include <mutex>
using namespace std;

#include <kogmo_rtdb.hxx>
using namespace KogniMobil;

#define RTDB_WAIT_NEXT_TIMEOUT  1.0     // max wait for update of database object in s

/*
* 1. source setup.sh
* 2. rtdb-start
* 3. multiplus --device /dev/multiplus
* 4. IceServerViewer & GuiViewer
*/

// TODO dummy typedef, usually from ArduinoData.h
/*
typedef struct {
    std::array< std::array<char, PATTERN_DEPTH>, NUMPIXELS> pattern;
    bool emergency_state = false;
} subobj_arduino_t;
*/

void databaseThread(mutex &ard_mutex, arduino *ard, subobj_arduino_t *shared_data, ArduinoData *rtdb_obj, RTDBConn *DBC)
{
    cout << "done" << endl;
    subobj_arduino_t *data = rtdb_obj->subobj_p;

    while(1) {

        cout << "main:databaseThread: wating for RTDB read... ";
        rtdb_obj->RTDBReadWaitNext(DBC->getTimestamp(), RTDB_WAIT_NEXT_TIMEOUT);
        cout << "done" << endl << endl;

        // std::lock_guard<std::mutex> guard(ard_mutex);
        ard_mutex.lock();
        // ----------------------------------------------------
        // read or write to protected memory here
        ard->updatePattern(data->pattern, shared_data->pattern);    // update a pixel if its new priority is higher than the current one
        data->emergency_state = shared_data->emergency_state;       // write emergency state to rtdb object
        // emergency state can be reset from here
        // rtdb_subobj->emergency_state = ard->setEmergencyState();
        // ----------------------------------------------------
        ard_mutex.unlock();
    }
}

void arduinoThread(mutex &ard_mutex, arduino *ard, subobj_arduino_t *shared_data)
{
    cout << "done" << endl;
    while(1) {

        ard_mutex.lock();
        // ----------------------------------------------------
        // read or write to protected memory here
        ard->setPattern(shared_data->pattern);
        ard->decreasePrio(shared_data->pattern);
        shared_data->emergency_state = ard->getEmergencyState();
        // ----------------------------------------------------
        ard_mutex.unlock();

        ard->pattern2color_buf();
        ard->write();

        // sleep for 10ms
        usleep(1000*10);
    }
}

int main()
{

    const char *deviceName = "/dev/ttyACM0";
    arduino ard(deviceName);
    std::mutex ard_mutex;

    cout << "Establishing database connection ..." << endl;
    RTDBConn DBC("Arduino", 10.0);
    cout << "done" << endl << endl;

    // Create rtdb database object with name ArduinoData
    ArduinoData rtdb_obj(DBC, "ArduinoData");
    rtdb_obj.RTDBInsert();

    // Init shared data object for both threads
    subobj_arduino_t shared_data;

    // start two parallel threads
    cout << "Starting database thread... ";
    std::thread dT(databaseThread, std::ref(ard_mutex), &ard, &shared_data, &rtdb_obj, &DBC);
    cout << "Starting arduino thread ...";
    std::thread aT(arduinoThread, std::ref(ard_mutex), &ard, &shared_data);

    /*
    dT.join();
    aT.join();
    */
}



