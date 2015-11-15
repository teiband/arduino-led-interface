#include "MultiPlusData.h"
#include <string>
#include <iomanip>

using namespace KogniMobil;
using namespace std;

MultiplusData::
MultiplusData (	class RTDBConn& DBC,
		const char* name,
		const int& otype) 
            : MultiplusData_T(DBC, name, otype) {
	data = subobj_p;

}

MultiplusData::
~MultiplusData(void) {

}

const string MultiplusData::getLEDStateString(bool onState, bool blinkState) const{
    string state;
    if (blinkState)
        state = "Blink";
    else if (onState)
        state = "On";
    else
        state = "Off";
    return state;
}

std::string MultiplusData::
dump(void) const {

    std::ostringstream ostr;

    // std::setfill(' ');

    ostr << "* LED Status" << endl;
    ostr << "Mains: ";
    ostr << getLEDStateString(data->On.mains, data->Blink.mains) << endl;
    ostr << "Absorption: ";
    ostr << getLEDStateString(data->On.absorption, data->Blink.absorption) << endl;
    ostr << "Bulk: ";
    ostr << getLEDStateString(data->On.bulk, data->Blink.bulk) << endl;
    ostr << "Float: ";
    ostr << getLEDStateString(data->On.Float, data->Blink.Float) << endl;
    ostr << "Inverter: ";
    ostr << getLEDStateString(data->On.inverter, data->Blink.inverter) << endl;
    ostr << "Overload: ";
    ostr << getLEDStateString(data->On.overload, data->Blink.overload) << endl;
    ostr << "Low Battery: ";
    ostr << getLEDStateString(data->On.lowbattery, data->Blink.lowbattery) << endl;
    ostr << "Temperature: ";
    ostr << getLEDStateString(data->On.temperature, data->Blink.temperature) << endl << endl;

    ostr << "* DC InfoFrame" << endl;
    ostr << "DC voltage [V]: " << (data->if0_DC_Voltage / 100.0) << endl;
    ostr << "DC current used by inverter [A]: " << (data->if0_DC_Current_Inv / 100.0) << endl;
    ostr << "DC current provided by charger [A]: " << (data->if0_DC_Current_Chg / 100.0) << endl;
    ostr << "DC inverter frequency [Hz]: " << (10000000 / (float)data->if0_Inv_Periode) << endl << endl;

    ostr << "* AC-L1 InfoFrame" << endl;
    ostr << "Phase L1 bf factor: "              << +data->if1_L1_bf_factor << endl;
    ostr << "Phase L1 inverter factor: "        << +data->if1_L1_inverter_factor << endl;
    ostr << "Phase L1 phase info: "             << +data->if1_L1_phase_info << endl;
    ostr << "Phase L1 mains voltage [V]: "      << (data->if1_L1_mains_voltage / 100.0) << endl;
    ostr << "Phase L1 mains current [A]: "      << ((data->if1_L1_mains_current * data->if1_L1_bf_factor) / 100.0) << endl;
    ostr << "Phase L1 inverter voltage [V]: "   << (data->if1_L1_inverter_voltage / 100.0) << endl;
    ostr << "Phase L1 inverter current [A]: "   << ((data->if1_L1_inverter_current * data->if1_L1_inverter_factor) / 100.0) << endl;
    ostr << "Phase L1 mains frequency [Hz]: "   << (10000000 / (float)data->if1_L1_mains_periode) << endl << endl;

    /*
    ostr << "* Master MultiLED Frame" << endl;
    int ac0=(data->mplf_ac_input_conf & 0x01) ? 1 : 0;
    int ac1=(data->mplf_ac_input_conf & 0x02) ? 1 : 0;
    ostr << "Master last active input AC0: " << ac0 << endl;
    ostr << "Master last active input AC1: " << ac1 << endl;
    ostr << "Master minimum input current limit [A]: "  << (data->mplf_min_inp_cur_lmt / 100.0) << endl;
    ostr << "Master maximum input current limit [A]: "  << (data->mplf_max_inp_cur_lmt / 100.0) << endl;
    ostr << "Master actual input current limit [A]: "   << (data->mplf_actual_inp_cur_lmt / 100.0) << endl << endl;
    */


    ostr << endl;

    // do not touch :-)
    ostr << std::endl << MultiplusData_T::dump() << std::endl;
	return ostr.str();
}

