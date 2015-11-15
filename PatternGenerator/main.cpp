
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
    if (verbose_mode)
    cout << "Database connection established!" << endl << endl;

    // Create rtdb database object with name MultiPlusData
    ArduinoData rtdb_obj(DBC, "ArduinoData");

    // create object with serial connection to device and pointer to database subobject
    cout << "Create Arduino object and establish serial connection ..." << endl;
    PatternGenerator pg(rtdb_obj.subobj_p);
    cout << "Connected to Multiplus" << endl << endl;

    rtdb_obj.RTDBInsert();

    cout << "Start infinite loop and write periodically to database ..." << endl << endl;
    for(;;) {

        cout << "Multiplus.update() ..." << endl << endl;
        mp.update();
        cout << endl << "MultiplusData object updated!" << endl << endl;

        /*
        //dummy for database testing
        rtdb_obj.subobj_p->Blink.mains = false;
        rtdb_obj.subobj_p->On.mains = !rtdb_obj.subobj_p->On.mains;
        */

        cout << "Write to RTDB ..." << endl << endl;
        rtdb_obj.RTDBWrite();
        cout << "Write to RTDB successfull!" << endl << endl;
        sleep(1);

        // wait until cycle done
        DBC.CycleDone();
    }

    return 0;
}
