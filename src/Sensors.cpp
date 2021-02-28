/*
 * Sensors.cpp
 *
 *  Created on: Feb 2, 2021
 *      Author: neamul
 */

#include "Sensors.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
# include <cmath>

using namespace std;
double Sensors::pressure_value=0.0;
double Sensors::humidity_value =0.0;
double Sensors::temperature_values=0.0;

PhidgetReturnCode ret;
PhidgetReturnCode errorCode;
const char * errorString;
char errorDetail[100];
size_t errorDetailLen = 100;
PhidgetHumiditySensorHandle humiditySensor0;
PhidgetPressureSensorHandle pressureSensor0;
PhidgetTemperatureSensorHandle temperatureSensor0;

Sensors::Sensors() {


}
//Declare any event handlers here. These will be called every time the associated event occurs.


//////////////////////////////////////Pressure Event handlar//////////////////////
void Sensors:: CCONV onPressureChange(PhidgetPressureSensorHandle ch, void * ctx, double pressure){
	pressure_value=pressure;
	;
}
//////////////////////////////////////Humidity Eventhandlar//////////////////////
void Sensors::CCONV onHumidityChange(PhidgetHumiditySensorHandle ch, void * ctx, double humidity){
	humidity_value=humidity;


};
//////////////////////////////////////Pressure Eventhandlar//////////////////////
void Sensors:: CCONV onTemperatureChange(PhidgetTemperatureSensorHandle ch, void * ctx, double temperature){
	temperature_values=temperature;


};
//////////////////////////////////////////Attach Deteach///////////////////////////////////////////
void Sensors::CCONV onAttach_Hum_Temp(PhidgetHandle ch, void * ctx){
	printf("Humidity and temperature sensore Attached!\n");

}
void Sensors::CCONV onDetach_Hum_Temp (PhidgetHandle ch, void * ctx) {
	printf("Humidity and temperature sensore Detach!\n");
	exit(EXIT_SUCCESS);
}



void Sensors::CCONV onAttach_Pressure (PhidgetHandle ch, void * ctx){
	printf("Pressure sensore Attached!\n");

}

void Sensors::CCONV onDetach_Pressure(PhidgetHandle ch, void * ctx){

	printf("Pressure sensore Detach!\n");
	exit(EXIT_SUCCESS);
}




///////////////////////////////////Error event////////////////////////////////
void Sensors::CCONV  onError (PhidgetHandle ch, void * ctx, Phidget_ErrorEventCode code, const char * description){
	printf("Description: %s\n", description);
		printf("----------\n");
}

/////////////////////////Dew point Calculation//////////////////////////////////////////
//double Sensors::dewPoint (double humidity_value,double temperature_values , double pressure_value ){
void Sensors::dewPoint (){
	 //float a,b,c,d=6.1121;18.678;257.14;234.5;
	        float a=6.1121;
	        float b=18.687;
	        float c=257.14;
	        float d=234.5;
	        double f=1.0016+(3.15*pow(10,-6)*pressure_value)-(0.074/pressure_value);

	        double gamma= log((humidity_value/100)* exp( (b-(temperature_values/d))*(temperature_values/(c+temperature_values)))*f);
		double numerator=c*gamma;
		double denominator=b-gamma;
		double dew_Point= numerator/denominator;


		//return dewPoint;

			cout<<"dew Point is: "  <<  dew_Point <<endl;





};

void Sensors::closeSenseros(){

	cout<< "Seneors are closing"<<endl;



				// Pressure

				ret=Phidget_close((PhidgetHandle)pressureSensor0);
				if (ret != EPHIDGET_OK) {
									Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
									printf("Error (%d): %s", errorCode, errorString);
									exit(1);
								}
				PhidgetPressureSensor_delete(&pressureSensor0);

				//Humidity

				ret=Phidget_close((PhidgetHandle)humiditySensor0);
				if (ret != EPHIDGET_OK) {
						Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
						printf("Error (%d): %s", errorCode, errorString);
						exit(1);
					}

				PhidgetHumiditySensor_delete(&humiditySensor0);


				//Temp

				ret=Phidget_close((PhidgetHandle)temperatureSensor0);
				if (ret != EPHIDGET_OK) {
									Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
									printf("Error (%d): %s", errorCode, errorString);
									exit(1);
								}
				PhidgetTemperatureSensor_delete(&temperatureSensor0);

				cout<< "Seneors are closed"<<endl;


};

void Sensors::setPressure(int HubPort){
	//Declare your Phidget channels and other variables


		//Create your Phidget channels
		PhidgetPressureSensor_create (&pressureSensor0);

		//Set addressing parameters to specify which channel to open (if any)
		ret=Phidget_setHubPort((PhidgetHandle)pressureSensor0, HubPort);
		if (ret != EPHIDGET_OK) {
							Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
							printf("Error (%d): %s", errorCode, errorString);
							exit(1);
						}



		Phidget_setDeviceSerialNumber((PhidgetHandle)pressureSensor0, 592207);


		//Assign any event handlers you need before calling open so that no events are missed.
		PhidgetPressureSensor_setOnPressureChangeHandler(pressureSensor0, onPressureChange, NULL);

		Phidget_setOnAttachHandler((PhidgetHandle)pressureSensor0, onAttach_Pressure, NULL);// Attach
		Phidget_setOnDetachHandler((PhidgetHandle)pressureSensor0, onAttach_Pressure, NULL);//Detach
		Phidget_setOnErrorHandler((PhidgetHandle)pressureSensor0, onError, NULL);// error event

		//Open your Phidgets and wait for attachment
		ret=Phidget_openWaitForAttachment((PhidgetHandle)pressureSensor0, 5000);
		if (ret != EPHIDGET_OK) {
							Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
							printf("Error (%d): %s", errorCode, errorString);
							exit(1);
						}





}
void Sensors:: setHUmidity(int Hubport){
	//Declare your Phidget channels and other variables


	//Create your Phidget channels
	PhidgetHumiditySensor_create(&humiditySensor0);


	//Set addressing parameters to specify which channel to open (if any)
	ret=Phidget_setHubPort((PhidgetHandle)humiditySensor0, Hubport);

	if (ret != EPHIDGET_OK) {
			Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
			printf("Error (%d): %s", errorCode, errorString);
			exit(1);
		}

	Phidget_setDeviceSerialNumber((PhidgetHandle)humiditySensor0, 592207);

	//Assign any event handlers you need before calling open so that no events are missed.
	PhidgetHumiditySensor_setOnHumidityChangeHandler(humiditySensor0, onHumidityChange,NULL);
	Phidget_setOnAttachHandler((PhidgetHandle)humiditySensor0, onAttach_Hum_Temp, NULL);// Attach
	Phidget_setOnDetachHandler((PhidgetHandle)humiditySensor0, onDetach_Hum_Temp, NULL);//Detach
	Phidget_setOnErrorHandler((PhidgetHandle)humiditySensor0, onError, NULL);// error event

	//Open your Phidgets and wait for attachmentdewPoint();
	ret=Phidget_openWaitForAttachment((PhidgetHandle)humiditySensor0, 5000);

	if (ret != EPHIDGET_OK) {
		Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
		printf("Error (%d): %s", errorCode, errorString);
		exit(1);
	}



};
void Sensors::settemperature(int Hubport){
	//Declare your Phidget channels and other variables

	//Create your Phidget channels
	PhidgetTemperatureSensor_create(&temperatureSensor0);

	ret=Phidget_setHubPort((PhidgetHandle)temperatureSensor0, Hubport);

	if (ret != EPHIDGET_OK) {
			Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
			printf("Error (%d): %s", errorCode, errorString);
			exit(1);
	}





	Phidget_setDeviceSerialNumber((PhidgetHandle)temperatureSensor0, 592207);
	PhidgetTemperatureSensor_setOnTemperatureChangeHandler(temperatureSensor0, onTemperatureChange, NULL);

	Phidget_setOnAttachHandler((PhidgetHandle)temperatureSensor0, onAttach_Hum_Temp, NULL);// Attach
	Phidget_setOnDetachHandler((PhidgetHandle)temperatureSensor0, onDetach_Hum_Temp, NULL);//Detach
	Phidget_setOnErrorHandler((PhidgetHandle)temperatureSensor0, onError, NULL);// error event

	ret=Phidget_openWaitForAttachment((PhidgetHandle)temperatureSensor0, 5000);

	if (ret != EPHIDGET_OK) {
			Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
			printf("Error (%d): %s", errorCode, errorString);
			exit(1);
		}

}

Sensors::~Sensors() {
	// TODO Auto-generated destructor stub
}

