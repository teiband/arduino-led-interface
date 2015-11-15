#ifndef __MULTIPLUSDATA_H__
#define __MULTIPLUSDATA_H__

#ifdef __cplusplus
	#include <kogmo_rtdb.hxx>
	namespace KogniMobil {
	extern "C" {
#endif

#include <kogmo_rtdb.h>

/** Subobject of RTDB object, which contains all Victron-Multiplus stats.
*/
typedef struct {
    // LED status
    /** struct, which contains on/off states of LED
    */
	struct stOn {
        	bool mains, absorption, bulk, Float, inverter, overload, lowbattery, temperature;
	} On;
    /** struct, which contains blink states of LED
    */
	struct stBlink {
		bool mains, absorption, bulk, Float, inverter, overload, lowbattery, temperature;
	} Blink;
	char bOn;
	char bBlink;

    //if0=InfoFrame0 (DC Frame)
    u_int8_t if0_phase_info;
    u_int16_t if0_DC_Voltage;
    u_int32_t if0_DC_Current_Inv;
    u_int32_t if0_DC_Current_Chg;
    u_int32_t if0_Inv_Periode;
    //if1=InfoFrame1
    u_int8_t if1_L1_bf_factor;
    u_int8_t if1_L1_inverter_factor;
    u_int8_t if1_L1_phase_info;
    u_int16_t if1_L1_mains_voltage;
    int16_t if1_L1_mains_current;
    u_int16_t if1_L1_inverter_voltage;
    int16_t if1_L1_inverter_current;
    u_int32_t if1_L1_mains_periode;
    //if2=InfoFrame2
    u_int8_t if2_L2_bf_factor;
    u_int8_t if2_L2_inverter_factor;
    u_int8_t if2_L2_phase_info;
    u_int16_t if2_L2_mains_voltage;
    int16_t if2_L2_mains_current;
    u_int16_t if2_L2_inverter_voltage;
    int16_t if2_L2_inverter_current;
    u_int32_t if2_L2_mains_periode;
    //if3=InfoFrame3
    u_int8_t if3_L3_bf_factor;
    u_int8_t if3_L3_inverter_factor;
    u_int8_t if3_L3_phase_info;
    u_int16_t if3_L3_mains_voltage;
    int16_t if3_L3_mains_current;
    u_int16_t if3_L3_inverter_voltage;
    int16_t if3_L3_inverter_current;
    u_int32_t if3_L3_mains_periode;
    //if4=InfoFrame4
    u_int8_t if4_L4_bf_factor;
    u_int8_t if4_L4_inverter_factor;
    u_int8_t if4_L4_phase_info;
    u_int16_t if4_L4_mains_voltage;
    int16_t if4_L4_mains_current;
    u_int16_t if4_L4_inverter_voltage;
    int16_t if4_L4_inverter_current;
    u_int32_t if4_L4_mains_periode;
    //mplf=MultiPlusLED frame
    u_int8_t mplf_ac_input_conf;
    u_int16_t mplf_min_inp_cur_lmt;
    u_int16_t mplf_max_inp_cur_lmt;
    u_int16_t mplf_actual_inp_cur_lmt;

} subobj_multiplus_t;

/** RTDB object, which contains the subobject and additional information for the database
*/
typedef struct {
    kogmo_rtdb_subobj_base_t base;
    subobj_multiplus_t multiplus_data;
} obj_multiplus_t;

#ifdef __cplusplus
}; /* extern "C" */

    /**
 * @brief MultiplusData_T is the parent class of MultiplusData
 */
typedef RTDBObj_T < subobj_multiplus_t, TYPEID_MULTIPLUS_DATA, RTDBObj > MultiplusData_T;

/** Data class to handle the RTDB object and writing to the RTDB
 */
class MultiplusData : public MultiplusData_T {
    private:
    /**
         * @brief Convert the data of On- and Blink-state to a string
         * @param onState
         * @param blinkState
         * @return constant string of LED state (On/ Blink)
         */
        const string getLEDStateString(const bool onState, const bool blinkState) const;
	protected:
		subobj_multiplus_t *data;
	public:
        MultiplusData (class RTDBConn& DBC, const char* name = "", const int& otype = TYPEID_MULTIPLUS_DATA);

        ~MultiplusData();

        /**
         * @brief Dump function, which converts the RTDB object's data to a legible string.
         * @return string, which is displayed in the ARCADE inspector (GUI of the RTDB)
         */
		std::string dump(void) 		const;
		
};

inline std::ostream& operator<< (std::ostream& out, const MultiplusData& O) {
        return out << O.dump() << std::endl;
}

};     // namespace KogniMobil
#endif //__cplusplus

#endif //__LASERDATA_H__

