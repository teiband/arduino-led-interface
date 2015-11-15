/*
 * main.cpp
 *
 *  Created on: 21 Apr 2015
 *      Author: Thomas Eiband
 *
 *      thomas.eiband@tum.de
 */

/*! \mainpage Interfacing a Victron Multiplus-Inverter over the serial port
 *
 * \section Intro
 *
 * This documentation was created with Doxygen. See the full project documentation (Practical Course Report) for further details.
 *
 * The project was part of a practical course in cooperative and distributed systems.
 * The modules are included in the wearhap workspace. Further, a connection to the Kogmo-RTDB is required.
 * <p>The LED status, the DC info and the AC info of the Victron-Multiplus can be accessed graphically with the ARCADE inspector from the Kogmo-RTDB.
 * To see the status, execute the following files in "/wearhap", where "/dev/multiplus" is the name of the serial device:</p>
 * 1. source setup.sh<br>
 * 2. rtdb-start<br>
 * 3. multiplus --device /dev/multiplus<br>
 * 4. IceServerViewer & GuiViewer<br>
 *
 * </p>
 *
 * \section Contact
 *
 * Technische Universität München<br>
 * Lehrstuhl für Informationstechnische Regelung<br>
 * Univ.-Prof. Dr.-Ing. Sandra Hirche
 *
 * Supervisors:<br>
 * Dipl.-Ing Martin Lawitzky, ml@tum.de<br>
 * Dipl.-Ing Sebastian Erhart, erhart@tum.de<br>
 *
 *
 * <p>Author:      Thomas Eiband<br>
 * Email:       thomas.eiband@tum.de</p>
 *
 */

#include "Multiplus.h"
#include <getopt.h>
#include <iostream>
#include <MultiPlusData.h>

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
    int o;
    int optionindex;
    std::string device_name = "/dev/multiplus";
    bool verbose_mode = false;

    while ((o = getopt_long(argc, argv, "d:v", long_options, &optionindex)) != -1) {
        switch(o) {
            case 'd':
                device_name = optarg;
                break;
	    case 'v':
		verbose_mode = true;
		break;
            case '?':
                std::cerr << "Usage: " << argv[0] << " [--device /dev/multiplus]" << std::endl;
                exit(1);
                break;
            default:
                abort();
        }

    }


    char *device_name_c = new char[device_name.size() + 1];
    std::copy(device_name.begin(), device_name.end(), device_name_c);
    device_name_c[device_name.size()] = '\0';

    cout << "Establishing database connection ..." << endl;
    RTDBConn DBC("MultiPlus", 5.0);
    if (verbose_mode)
    cout << "Database connection established!" << endl << endl;

    // Create rtdb database object with name MultiPlusData
    MultiplusData rtdb_obj(DBC, "MultiPlusData");

    // create Multiplus object with serial connection to device and pointer to database subobject
    cout << "Create Multiplus object and establish serial connection ..." << endl;
    Multiplus mp((device_name_c), rtdb_obj.subobj_p);
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
