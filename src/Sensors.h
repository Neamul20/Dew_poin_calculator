/**
 * \filename Sensors.h (/Phidgetsemifinal/src/Sensors.h,/home/neamul/eclipse-workspace/Phidgetsemifinal/src/Sensors.h)
 * \ingroup Phidgetsemifinal
 * \brief
 *
 * \date:   Created on: Feb 17, 2021
 * \author: neamul
 * \version: 0.0
 *
 * \remarks 
 *
 * \todo TODO
 */
#ifndef SENSORS_H_
#define SENSORS_H_
#include <phidget22.h>
#include <iostream>
using namespace std;

class Sensors {
public:
	static double humidity_value;
	static double temperature_values;
	static double pressure_value;
	Sensors();
	virtual ~Sensors();


	/*// waiting for sensor:
	PhidgetReturnCode ret;
	PhidgetReturnCode errorCode;
	const char * errorString;
	char errorDetail[100];
	size_t errorDetailLen = 100;
	*/

////// Event handeler Pressure
	//double dewPoint (double humidity_value,double temperature_values , double pressure_value );
	void dewPoint ( );
	static void CCONV onPressureChange(PhidgetPressureSensorHandle ch, void * ctx, double pressure);
	static void CCONV onHumidityChange(PhidgetHumiditySensorHandle ch, void * ctx, double humidity);
	static void CCONV onTemperatureChange(PhidgetTemperatureSensorHandle ch, void * ctx, double temperature);
	static void CCONV  onError (PhidgetHandle ch, void * ctx, Phidget_ErrorEventCode code, const char * description);

	static void CCONV onAttach_Hum_Temp (PhidgetHandle ch, void * ctx);
	static void CCONV onDetach_Hum_Temp(PhidgetHandle ch, void * ctx);

	static void CCONV onAttach_Pressure (PhidgetHandle ch, void * ctx);
	static void CCONV onDetach_Pressure(PhidgetHandle ch, void * ctx);

	static void setPressure(int HubPort);
	static void setHUmidity(int Hubport);
	static void settemperature(int Hubport);
	static void closeSenseros();


};

#endif /* SENSORS_H_ */
