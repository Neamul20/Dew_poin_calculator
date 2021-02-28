//============================================================================
// Name        : Phidgetsemifinal.cpp
// Author      : Neamul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Sensors.h"
#include <unistd.h>
//#include <conio.h>
//#include <condition_variable>
using namespace std;


int main() {
PhidgetNet_enableServerDiscovery(PHIDGETSERVER_DEVICEREMOTE);// Newly added line for connecting the server for SBC



        Sensors obj;

        obj.setPressure(1);
        obj.setHUmidity(0);
        obj.settemperature(0);
       // obj.setsensors (1,0,0);

        //char c;
        //cout<<"press esc to exit! "<<std::endl;
int n=0;
        while (n<20){

        cout<<"Pressure is " <<obj.pressure_value<<" kPh" <<endl;
        cout<<"Relative Humidity is " <<obj. humidity_value<<" %" <<endl;
        cout<<"Temperature value " <<obj. temperature_values<<"   0" <<endl;
        cout<<" "<<endl;
        n+=1;


        obj.dewPoint();
        cout<<" "<<endl;
       // usleep(50000);







}
        cout<<"I am here"<<endl;

        getchar();
        obj.closeSenseros();
return 0;
}



