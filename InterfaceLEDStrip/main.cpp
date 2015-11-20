#include <iostream>

// TODO: check this
#include <math.h>
#include <stdint.h>
#include "arduino.h"
#include "arduino_config.h"                     // TODO change path to global (see multiplus)
// #include "../arch/rtdbobjects/ArduinoData.h"    // TODO change path to global (see multiplus)
#include <getopt.h>
#include <iostream>
#include <unistd.h> // for sleep()

#include <thread>
#include <mutex>

using namespace std;

// TODO dummy typedef, usually from ArduinoData.h
typedef struct {
    std::array< std::array<char, PATTERN_DEPTH>, NUMPIXELS> pattern;
    bool emergency_state = false;
} subobj_arduino_t;

void databaseThread(mutex &ard_mutex, arduino *ard, subobj_arduino_t *rtdb_subobj)
{
    bool emergency_state = false;

    while(1) {
        // read from database, readWaitNext;
        // implement timeout here, important when emergency stop occurs

        cout << "main:databaseThread: wating for read RTDB... ";
        rtdb_obj.RTDBReadWaitNext();
        cout << "successfull!" << endl << endl;

        // dummy color
        std::array<char, PATTERN_DEPTH> color;

        // std::lock_guard<std::mutex> guard(ard_mutex);
        ard_mutex.lock();
        // read or write to protected memory here
        std::fill(rtdb_subobj->pattern.begin(), rtdb_subobj->pattern.end(), color);   // dummy write

        // emergency state can be reset from here
        // rtdb_subobj->emergency_state = ard->setEmergencyState();
        ard_mutex.unlock();

        // write emergency_state to database

        // wait until cycle done
        // TODO implement in which thread?
        DBC.CycleDone();
    }
}

void arduinoThread(mutex &ard_mutex, arduino *ard, subobj_arduino_t *rtdb_subobj)
{
    while(1) {
        ard_mutex.lock();
        // read or write to protected memory here
        ard->setPattern(rtdb_subobj->pattern);
        ard->decreasePrio();
        rtdb_subobj->emergency_state = ard->getEmergencyState();
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

    // establish rtdb connection here

    subobj_arduino_t *rtdb_subobj;   // dummy object

    cout << "Establishing database connection ..." << endl;
    RTDBConn DBC("Arduino", 10.0);

    cout << "Database connection established!" << endl << endl;

    // Create rtdb database object with name ArduinoData
    ArduinoData rtdb_obj(DBC, "ArduinoData");

    // insert here or in pattern generator? no duplicates allowed!
    rtdb_obj.RTDBInsert();

    rtdb_obj.RTDBSearchWait("ArduinoData");


    // start two parallel threads
    std::thread dT(databaseThread, std::ref(ard_mutex), &ard, rtdb_subobj);
    std::thread aT(arduinoThread, std::ref(ard_mutex), &ard, rtdb_subobj);

    /*
    dT.join();
    aT.join();
    */

    // test without thread
    /*
    while(1) {

        ard.setColor(rand()%20, rand()%20, rand()%20);
        // ard.setColor(0x00,0x00,0x01);
        // ard.setColor('r');
        ard.fillColor();

        ard.setBattVoltage(rand()%30);

        ard.write();
        sleep(1);

    }
    */

    /*
    // Verbindung zur Datenbank aufbauen, unsere Zykluszeit is 33 ms
    RTDBConn DBC("a2_roadtracker_example_cxx", 0.033, "");

    // Auf Object fuer Fahrspur warten
    C3_Ints DemoObj(DBC);
    DemoObj.RTDBSearchWait("demo_object");

    while (1)
      {
        DemoObj.RTDBReadWaitNext();
        cout << DemoObj;
        cout << "Data: " << DemoObj.getInt(0) << " ..." << endl;
      }
    */



}



