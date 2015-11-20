#include <iostream>

// TODO: check this
#include <math.h>
#include <stdint.h>
#include "arduino.h"
#include <getopt.h>
#include <iostream>
#include <unistd.h> // for sleep()

#include <thread>
#include <mutex>

using namespace std;

std::mutex ard_mutex;

void databaseThread(arduino *ard)
{
    // generate pattern first
    // std::lock_guard<std::mutex> guard(ard_mutex);
    char pattern[240][4];

    ard_mutex.lock();
    ard->setPattern(pattern);
    ard_mutex.unlock();
}

void arduinoThread(arduino *ard)
{
    char pattern[240][4];
    ard_mutex.lock();
    ard->setPattern(pattern);
    ard_mutex.unlock();
}

int main()
{
    const char *deviceName = "/dev/ttyACM0";
    arduino ard(deviceName);

    std::thread dT(databaseThread, &ard);
    std::thread aT(arduinoThread, &ard);

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



