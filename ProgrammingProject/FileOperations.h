#ifndef FILEPROCESSING_FILEOPERATIONS_H
#define FILEPROCESSING_FILEOPERATIONS_H

//header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

//defines
#define MYPATH  "C://ProgrammingProject//"
#define MotThresh 40  //Assuming that the range of motion is {0 .. 100}, Turn on Lights if Motion greater than 40
#define TempThresh 20 // Turn on Heater if internal temperature is less than 15
#define HumThresh 65  // Turn on Extractor if Humidity is greater than 65
#define HrsPerDay 24   // constant for number of hours per day


//global variables
FILE *ptr;
char *array1[24]; //Temporary Array to hold the values of the state of Temp sensors (ON or OFF)
char *array2[24]; //Temporary Array to hold the values of the state of Motion sensors
char *array3[24]; //Temporary Array to hold the values of the state of Humidity sensors
int state1[24]; //Temporary Array to hold the values of the state of Temp sensors in the form 1 (on) or 0 (Off)
int state2[24]; //Temporary Array to hold the values of the state of Motion sensors in the form 1 (on) or 0 (Off)
int state3[24]; //Temporary Array to hold the values of the state of Humidity sensors in the form 1 (on) or 0 (Off)
int BTempState[24]; //Array to hold the values of the state of Temp sensors in the Bedroom - in form 1 (on) or 0 (Off) - values of array are a copy of state1
int BMotState[24]; //Array to hold the values of the state of Motion sensors in the Bedroom - in form 1 (on) or 0 (Off) - values of array are a copy of state2
int BHumiState[24]; //Array to hold the values of the state of Humi sensors in the Bedroom - in form 1 (on) or 0 (Off) - values of array are a copy of state3
int LTempState[24]; //Array to hold the values of the state of Temp sensors in the Living Room - in form 1 (on) or 0 (Off) - values of array are a copy of state1
int LMotState[24]; //Array to hold the values of the state of Motion sensors in the Living Room - in form 1 (on) or 0 (Off) - values of array are a copy of state2
int LHumiState[24]; //Array to hold the values of the state of Humi sensors in the Living Room - in form 1 (on) or 0 (Off) - values of array are a copy of state3
int KTempState[24]; //Array to hold the values of the state of Temp sensors in the Kitchen - in form 1 (on) or 0 (Off) - values of array are a copy of state1
int KMotState[24]; //Array to hold the values of the state of Motion sensors in the Kitchen - in form 1 (on) or 0 (Off) - values of array are a copy of state2
int KHumiState[24]; //Array to hold the values of the state of Humi sensors in the Kitchen - in form 1 (on) or 0 (Off) - values of array are a copy of state3
int TotalE_Bedroom, TotalE_Livingroom, TotalE_Kitchen, Total_Energy; //Variables to hold total energy used in Bedroom, Living room, and kitchen - and total energy used (in KJ)
float Tempvar_bedroom, Tempvar_Kitchen, Tempvar_Livingroom; //variables to hold the calculated variance of temp data for Bedroom, Living room and Kitchen
float HumiAdd_Bedroom, HumiAdd_Kitchen, HumiAdd_Livingroom; //variables to hold the calculated total of Humi data for Bedroom, Living room and Kitchen
float HumiMean_Bedroom, HumiMean_Kitchen, HumiMean_Livingroom; //variables to hold the calculated mean of Humi data for Bedroom, Living room and Kitchen
float MotAdd_Bedroom, MotAdd_Kitchen, MotAdd_Livingroom; //variables to hold the calculated total of every hour for motion data for Bedroom, Living room and Kitchen
float MotAv_Bedroom[24], MotAv_Kitchen[24], MotAv_Livingroom[24]; //arrays to hold the calculated mean for each hour of motion data in Bedroom, Living room and Kitchen
float Motvar_Bedroom, Motvar_Kitchen, Motvar_Livingroom; //arrays to hold the calculated Variance for motion data in Bedroom, Living room and Kitchen


//Function Decleration
void ReadDataFile(char *location); //Function created by K.Emrith on 25/11/2019 that allows sensor data to be read from different location
float CalculateVariance(float Data[], int ArrSize);
void TotalEnergy();
void TempSensors(char *location); // function to go through each temp at time of day and see if temp is less than 15 - if it is turn it on
void MotionSensor(char *location); //function to go through range of motion at each hour of day and see if motion is greater than 40 - if it is turn it on
void HumiditySensor(char *location); //function go through each humidity value at time of day and Turn on Extractor if Humidity is greater than 65
void Bedroom(char *location); //function to create a text file to show the state of devices in bedroom every hour
void LivingRoom(char *location); //function to create a text file to show the state of devices in Living Room every hour
void Kitchen(char *location); //function to create a text file to show the state of devices in Kitchen every hour
void Menu(); //The Menu function displays a menu of options for the user to chose what they want to display
void Menu_restart(); //Function to ask the user if they want to choose another function
void StateOfAll(); //Function ask for input of time and will display state of all devices at that time
void StateOfLights(); //Function display state of all Lights for each hour
void StateOfHeating(); //Function display state of all Heating Devices for each hour
void StateOfVentilator(); //Function display state of all Ventilating Devices for each hour
void StateOfBedroom();  //Function ask for input of time and will display state of all devices in bedroom at that time
void StateOfLivingRoom(); //Function ask for input of time and will display state of all devices in Living Room at that time
void StateOfKitchen(); //Function ask for input of time and will display state of all devices in Kitchen at that time
void Faulty(); //function to see if any of the sensors are faulty
void FaultyTextFile(); //function that will open a text file and write the report of the sensors in it

#endif //FILEPROCESSING_FILEOPERATIONS_H
