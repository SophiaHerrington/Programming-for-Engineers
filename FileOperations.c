/***********************************************************************/
//Programme Banner: FileOperations.c
// Created by Khemraj Emrith on 25/11/2019.
//Description: This file contains the description/definitions of all file
//                                          operations used by the system
// version 1.0 - functions to read files and Display sensor data added
// version 2.0 - function to implement variance added
/***********************************************************************/

#include "FileOperations.h"

/************************************/
// Function CaculateVariance
// Author   K. Emrith
// Date     15/12/2020
// Input    Array of float of size ArrSize
// Output   Variance of array values
// Version  1.0

/***********************************/
float CalculateVariance(float Data[], int ArrSize){
    float var, mean, sum=0.0f, sdiff=0.0f;
    int i, j;

    //Compute average of elements
    for (i=0; i<ArrSize; i++){
        sum += Data[i];
    }
    mean = (float) sum/ (float) ArrSize;

    //compute sum of squared differences with mean
    for (j = 0; j < ArrSize; j++) {
        sdiff += ((Data[j] - mean) * (Data[j] - mean));
    }

    return ( (float)sdiff / (float)ArrSize);
}


/********************************************************************/
//Function DisplaySensorData
//Author:K.Emrith
//Date: 25/11/2019
//Version : 1.0
/********************************************************************/

void DisplaySensorData() {
int k, t=0;

while (t<24) {
    //print
    printf("\n");
    printf("\t time=%s", TimeDat[t]); //myDat[t].time);
    printf("\t iTemp=%f", TempArr[t][1]);
    printf("\t Hum=%f", HumiArr[t]);
    printf("\t eTemp=%f", TempArr[t][0]);
    for (k = 0; k < 6; k++)
        printf(" Mot:%f\t", MotionArr[t][k]);

    t++;
    }
}


/********************************************************************/
//Function ReadDataFile
//Author:K.Emrith
//Date: 25/11/2019
//Version : 1.0
//Description: Function allows sensor data to be read from different location
/********************************************************************/

void ReadDataFile(char *location) {
    int t=0, k;
    char src[100]={};

    strcat( strcat(src, MYPATH), location);
    //open file for reading
    ptr = fopen(src,"r");

    if(ptr == NULL)
    {
        printf("Error!\n");
        exit(1);
    }
    else
        printf("Success!\n");

    while ((!feof(ptr)) && (t<24)) {
        //read time
        fscanf(ptr, "%s", TimeDat[t]);
        //read temperatures
        fscanf(ptr, "%f%f", &TempArr[t][0], &TempArr[t][1]);
        //read humidity
        fscanf(ptr, "%f",  &HumiArr[t]);
        //read motion data
        for ( k=0; k<6; k++)
            fscanf(ptr,"%f",  &MotionArr[t][k]);

        t++;

    }
    fclose(ptr);
}
