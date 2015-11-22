/*
 * main.cpp
 *
 *  Created on: 15 Nov 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

#include "PatternGenerator.h"
#include <getopt.h>
#include <iostream>
#include <ArduinoData.h>

using namespace std;

#include <kogmo_rtdb.hxx>
using namespace KogniMobil;

static struct option long_options[] = {
   {"device", required_argument, 0, 'd'},
   {"verbose", no_argument, 0, 'v'},
   {0,0,0,0}
};

int main(int argc, char *argv[])
{
    cout << "Establishing database connection ..." << endl;
    RTDBConn DBC("Arduino", 5.0);
    cout << "done" << endl << endl;

    ArduinoData rtdb_obj(DBC, "ArduinoData");

    PatternGenerator pg(rtdb_obj.subobj_p);

    cout << "Searching RTDB object \"ArduinoData\"... ";
    Road.RTDBSearchWait("a2_eigenfahrspur");
    cout << "done" << endl;

    cout << "Entering loop and generating some patterns" << endl;
    while (1) {

        // TODO implement funcionality
        pg.update();

        cout << "Write to RTDB ...";
        rtdb_obj.RTDBWrite();
        cout << "done" << endl;
        sleep(1);

        // wait until cycle done
        // (signal for ReadWaitNext() in Arduino main)
        DBC.CycleDone();
    }
    return 0;
}
