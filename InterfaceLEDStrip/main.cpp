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

    ard.createColorTriple(0x06, 0x00, 0x00, color);
    ard.fillColor(color);

    while(1) {

        ard.createColorTriple(rand()%32, rand()%32, rand()%32, color);
        ard.fillColor(color);
        ard.write();
        sleep(2);

    }



}



