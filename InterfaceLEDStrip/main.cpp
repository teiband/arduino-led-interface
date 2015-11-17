#include <iostream>

// TODO: check this
#include <math.h>
//#define NUMPIXEL 240
#include <stdint.h>
#include "arduino.h"
#include <getopt.h>
#include <iostream>
#include <unistd.h> // for sleep()

using namespace std;


int main()
{
    const char *deviceName = "/dev/ttyACM0";
    arduino ard(deviceName);

    char color[3];

    while(1) {

        ard.setColor(rand()%20, rand()%20, rand()%20);
        // ard.setColor(0x00,0x00,0x01);
        // ard.setColor('r');
        ard.fillColor();

        ard.setBattVoltage(rand()%30);

        ard.write();
        sleep(1);

    }

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



