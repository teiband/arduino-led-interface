#include "ArduinoData.h"
#include <string>
#include <iomanip>

using namespace KogniMobil;
using namespace std;

ArduinoData::
ArduinoData (	class RTDBConn& DBC,
		const char* name,
		const int& otype) 
            : ArduinoData_T(DBC, name, otype) {
	data = subobj_p;

}

ArduinoData::
~ArduinoData(void) {

}

const string ArduinoData::getLEDStateString(bool onState, bool blinkState) const{
    string state;
    if (blinkState)
        state = "Blink";
    else if (onState)
        state = "On";
    else
        state = "Off";
    return state;
}

std::string ArduinoData::
dump(void) const {

    std::ostringstream ostr;

    ostr << "* LED Status" << endl;

    ostr << endl;

    // do not touch :-)
    ostr << std::endl << ArduinoData_T::dump() << std::endl;
	return ostr.str();
}

