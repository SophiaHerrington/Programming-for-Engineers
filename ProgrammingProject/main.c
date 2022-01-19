#include "FileOperations.h"

struct Devices{ /*Struct to hold the values read from the Files*/
    float HumiArr[HrsPerDay];
    float TempArr[HrsPerDay][2];
    float MotionArr[HrsPerDay][6];
    char TimeDat[HrsPerDay][25];
};

struct Energy{/*Struct to hold the values for the hours of energy used for each location*/
    int Hours_lights[24];
    int Hours_Heat[24];
    int Hours_vent[24];
    int Hour_energy[24];
};
/*Definiton Of Struct types for Devices*/
struct Devices L1; /*L1 is to store the data of the file being read temperarily*/
struct Devices BedRoomDevices; /*BedRoomDecices is to store the data of the file BedRoom.txt*/
struct Devices LivingRoomDevices; /*LivingRoomDecices is to store the data of the file LivingRoom.txt*/
struct Devices KitchenDevices; /*KitchenDecices is to store the data of the file Kitchen.txt*/
struct Energy BedRoomEnergy; /*BedRoomEnergy is to store the data of the hours energy has been on for in the BedRoom*/
struct Energy LivingRoomEnergy; /*LivingRoomEnergy is to store the data of the hours energy has been on for in the Living Room*/
struct Energy KitchenEnergy; /*KitchenEnergy is to store the data of the hours energy has been on for in the Kitchen*/

int main() { /*Main function to call parts of code that always run and the Menu function*/
    Bedroom("BedroomData.txt");
    LivingRoom("LivingRoomData.txt");
    Kitchen("KitchenData.txt");
    /*The Functions Above are always called as they are the ones that read the data and create text files of the data once its been opened and read*/
    Faulty();
    TotalEnergy();
    /*The Functions Above are also always called as they are the ones analyse the energy consumation and if a sensor is fualty*/
    Menu(); /*calling the menu function*/
    return 0;
}

void Menu(){ /*The Menu function displays a menu of options for the user to chose what they want to display*/
    printf("Options:\n");
    printf("1: Display State of All Devices\n2: State of Lights\n3; State of Ventilators\n4: State of Heating\n5: State of devices in Bedroom\n6: State of devices in LivingRoom\n7: State of Devices in Kitchen\n");
    int input;
    printf("Please enter Decision\n");
    scanf("%d", &input); /*calls for the user to input an option from the ones printed above*/
    if (input == 1){
        StateOfAll(); /*If 1 is the inputted value it will call the function StateOfAll()*/
    }
    if (input == 2){
        StateOfLights(); /*If 2 is the inputted value it will call the function StateOfLights()*/
    }
    if (input == 3){
        StateOfVentilator(); /*If 3 is the inputted value it will call the function StateOfVentilator()*/
    }
    if (input == 4){
        StateOfHeating(); /*If 4 is the inputted value it will call the function StateOfHeating()*/
    }
    if (input == 5){
        StateOfBedroom(); /*If 5 is the inputted value it will call the function StateOfBedroom()*/
    }
    if (input == 6){
        StateOfLivingRoom(); /*If 6 is the inputted value it will call the function StateOfLivingRoom()*/
    }
    if (input == 7){
        StateOfKitchen(); /*If 7 is the inputted value it will call the function StateOfKitchen()*/
    }
    Menu_restart(); /*once the function chosen by the user is completed it will call the function Menu_Restart*/

}

void Menu_restart(){ /*Function to ask the user if they want to choose another function*/
    char YesOrNo;
    printf("Would you like to choose another option: Y/N\n");
    scanf(" %c", &YesOrNo); /*input of Y or N to see if the user wants to choose another Function*/
    if (YesOrNo == 'Y'){
        Menu(); /*If the user does want to call another option then it will call function Menu()*/
    }
    else{
        printf("goodbye"); /*If not a goodbye message will be displayed*/
    }
}

void ReadDataFile(char *location) { /*Function created by K.Emrith on 25/11/2019 that allows sensor data to be read from different location*/
    int t=0, k;                     /*Function has been edited to store data into structs*/
    char src[100]={};
    strcat( strcat(src, MYPATH), location);
    //open file for reading
    ptr = fopen(src,"r");
    if(ptr == NULL)
    {
        printf("Error!\n");
        exit(1); /*if file hasn't been read correctly error message will display*/
    }
    else
        printf("Success!\n"); /*if file has been read correctly success will display*/
    while ((!feof(ptr)) && (t<24)) { /*while loop to store the parts of the text file into structs*/
        //read time
        fscanf(ptr, "%s", L1.TimeDat[t]); /*stored data of the for time in L1.TimeDat*/
        //read temperatures
        fscanf(ptr, "%f%f", &L1.TempArr[t][0], &L1.TempArr[t][1]); /*stored data of the for Temp sensors in L1.TempArr*/
        //read humidity
        fscanf(ptr, "%f",  &L1.HumiArr[t]); /*stored data of the for humidity sensors in L1.HumiArr*/
        //read motion data
        for ( k=0; k<6; k++) /*another for loop as motion sensors have 6 values of data per hour*/
            fscanf(ptr,"%f",  &L1.MotionArr[t][k]); /*stored data of the for motion sensors in L1.MotionArr*/

        t++;
        /*L1 is used as a tempory storage for the data*/
    }
    fclose(ptr);
}

void TempSensors(char *location){ /* function to go through each temp at time of day and see if temp is less than 15 - if it is turn it on*/
    int t = 0;
    while (t<24) { /*loops through 24 times*/
        if (L1.TempArr[t][1] < TempThresh){ /*check if any of the values are under the temp threshold*/
            array1[t] = "ON"; /*If case is true set Array1 to on and state1 to 1*/
            state1[t] = 1;

        }
        else{
            array1[t] = "OFF"; /*If case is false set Array1 to off and state1 to 0*/
            state1[t] = 0;
        }
        t++;
        /*Both Array1 and State1 are temporary values to store the data temporarily*/
    }
}

void MotionSensor(char *location){ /*function to go through range of motion at each hour of day and see if motion is greater than 40 - if it is turn it on*/
    int k, t = 0;
    while (t<24) { /*loops through 24 times*/
        for (k = 0; k < 6; k++) /*loops through another 6 times as 6 values of motion recorded*/
           if (L1.MotionArr[t][k] > MotThresh){ /*check if any of the values are under the Motion threshold*/
               array2[t] = "ON"; /*If case is true set Array2 to on and state2 to 1*/
               state2[t] = 1;
           }
           else{
               array2[t] = "OFF"; /*If case is false set Array1 to off and state1 to 0*/
               state2[t] = 0;
            }

        t++;
        /*Both Array2 and State2 are temporary values to store the data temporarily*/
    }
}

void HumiditySensor(char *location){ /*function go through each humidity value at time of day and Turn on Extractor if Humidity is greater than 65*/
    int t = 0;
    while (t<24) { /*loops through 24 times*/
        if (L1.HumiArr[t] > HumThresh){ /*check if any of the values are under the humidity threshold*/
            array3[t] = "ON"; /*If case is true set Array3 to on and state3 to 1*/
            state3[t] = 1;
        }
        else{
            array3[t] = "OFF"; /*If case is false set Array3 to off and state3 to 0*/
            state3[t] = 0;
        }

        t++;
        /*Both Array3 and State3 are temporary values to store the data temporarily*/
    }
}

void Bedroom(char *location) { /*function to create a text file to show the state of devices in bedroom every hour*/
    ReadDataFile("BedroomData.txt"); /*calling for BedRoomData.txt to be read and data stored into L1*/
    memcpy(&BedRoomDevices, &L1, sizeof BedRoomDevices); /*copies the data of L1 into Bedroomdevices*/
    int i;
    /*opens a file called BedRoomDevices*/
    FILE *fpointer;
    fpointer = fopen("BedroomDevices.txt", "w");
    TempSensors("BedroomData.txt");
    MotionSensor("BedroomData.txt");
    HumiditySensor("BedroomData.txt");
    /*sends the data of Bedroom data to the variables TempSensors, MotionSensors and Humidity sensors to determine the state of the devices*/
    fprintf(fpointer, "TIME\t\t\tTEMP\tHUMID\tLIGHT\n");
    for (i = 0; i < 24; i++) {
    fprintf(fpointer, "%s\t\t%s\t%s\t%s\n", BedRoomDevices.TimeDat[i], array1[i], array3[i], array2[i]);
    }
    /*print the data into the files*/
    fclose(fpointer); /*closes the file*/
    for (i = 0; i < 24; i++){
        BTempState[i] = state1[i]; /*copies the data of State1 into BTempState*/
    }
    for (i = 0; i < 24; i++){
        BMotState[i] = state2[i]; /*copies the data of State2 into BMotState*/
    }
    for (i = 0; i < 24; i++) {
        BHumiState[i] = state3[i]; /*copies the data of State3 1 into BHumiState*/
    }

}

void LivingRoom(char *location){ /*function to create a text file to show the state of devices in Living Room every hour*/
    ReadDataFile("LivingRoomData.txt"); /*calling for LivingRoomData.txt to be read and data stored into L1*/
    memcpy(&LivingRoomDevices, &L1, sizeof LivingRoomDevices); /*copies the data of L1 into livingRoomDevices*/
    int i;
    /*opens a file called LivingRoomDevices*/
    FILE * fpointer;
    fpointer = fopen("LivingRoomDevices.txt", "w");
    TempSensors("LivingRoomData.txt");
    MotionSensor("LivingRoomData.txt");
    HumiditySensor("LivingRoomData.txt");
    /*sends the data of Living Room data to the variables TempSensors, MotionSensors and Humidity sensors to determine the state of the devices*/
    fprintf(fpointer, "TIME\t\t\tTEMP\tHUMID\tLIGHT\n");
    for (i = 0; i < 24; i++) {
        fprintf(fpointer, "%s\t\t%s\t%s\t%s\n", LivingRoomDevices.TimeDat[i], array1[i], array3[i], array2[i]);
    }
    /*print the data into the files*/
    fclose(fpointer); /*closes the file*/
    for (i = 0; i < 24; i++) {
        LTempState[i] = state1[i]; /*copies the data of State1 into LTempState*/
    }
    for (i = 0; i < 24; i++) {
        LMotState[i] = state2[i]; /*copies the data of State2 into LMotState*/
    }
    for (i = 0; i < 24; i++) {
        LHumiState[i] = state3[i]; /*copies the data of State3 1 into LHumiState*/
    }
}

void Kitchen(char *location){ /*function to create a text file to show the state of devices in Kitchen every hour*/
    ReadDataFile("KitchenData.txt"); /*calling for KitchenData.txt to be read and data stored into L1*/
    memcpy(&KitchenDevices, &L1, sizeof KitchenDevices); /*copies the data of L1 into KitchenDevices*/
    int i;
    /*opens a file called KitchenDevices*/
    FILE * fpointer;
    fpointer = fopen("KitchenDevices.txt", "w");
    TempSensors("KitchenData.txt");
    MotionSensor("KitchenData.txt");
    HumiditySensor("KitchenData.txt");
    /*sends the data of Kitchen data to the variables TempSensors, MotionSensors and Humidity sensors to determine the state of the devices*/
    fprintf(fpointer, "TIME\t\t\tTEMP\tHUMID\tLIGHT\n");
    for (i = 0; i < 24; i++) {
        fprintf(fpointer, "%s\t\t%s\t%s\t%s\n", KitchenDevices.TimeDat[i], array1[i], array3[i], array2[i]);
    }
    /*print the data into the files*/
    fclose(fpointer); /*closes the file*/
    for (i = 0; i < 24; i++) {
        KTempState[i] = state1[i]; /*copies the data of State1 into KTempState*/
    }
    for (i = 0; i < 24; i++) {
        KMotState[i] = state2[i]; /*copies the data of State2 into KMotState*/
    }
    for (i = 0; i < 24; i++) {
        KHumiState[i] = state3[i]; /*copies the data of State3 1 into KHumiState*/
    }
}

void StateOfAll(){/*Function ask for input of time and will display state of all devices at that time*/
    int value, input;
    printf("Please enter the hour you would like to see the state of devices, e.g. 1-23\n");
    scanf("%d", &input);
    value = input - 1;
    printf("The state of the devices in the Bedroom are\n");
    printf("Heating\t\tVentilator\tLights\n");
    printf("%d\t\t%d\t\t%d\n", BTempState[value], BHumiState[value], BMotState[value]);
    printf("The state of the devices in the Living Room are\n");
    printf("Heating\t\tVentilator\tLights\n");
    printf("%d\t\t%d\t\t%d\n", LTempState[value], LHumiState[value], LMotState[value]);
    printf("The state of the devices in the Kitchen are\n");
    printf("Heating\t\tVentilator\tLights\n");
    printf("%d\t\t%d\t\t%d\n", KTempState[value], KHumiState[value], KMotState[value]);
}
void StateOfLights(){ /*Function display state of all Lights for each hour*/
    int i;
    printf("The state of the Lights each hour are:\n");
    printf("Bedroom\t\tLiving Room\tKitchen\n");
    for (i=0; i<24; i++) {
        printf("%d\t\t%d\t\t%d\n",BMotState[i], LMotState[i], KMotState[i]);
    }
}
void StateOfHeating(){ /*Function display state of all Heating Devices for each hour*/
    int i;
    printf("The state of the Heating each hour is:\n");
    printf("Bedroom\t\tLiving Room\tKitchen\n");
    for (i=0; i<24; i++) {
        printf("%d\t\t%d\t\t%d\n", BTempState[i], LTempState[i], KTempState[i]);
    }
}
void StateOfVentilator(){ /*Function display state of all Ventilating Devices for each hour*/
    int i;
    printf("The state of the Ventilators for each hour is:\n");
    printf("Bedroom\t\tLiving Room\tKitchen\n");
    for (i=0; i<24; i++) {
        printf("%d\t\t%d\t\t%d\n", BHumiState[i], LHumiState[i], KHumiState[i]);
    }
}
void StateOfBedroom(){ /*Function ask for input of time and will display state of all devices in bedroom at that time*/
    int value, input;
    printf("Please enter the hour you would like to see the state of devices, e.g. 1-23\n");
    scanf("%d", &input);
    value = input - 1;
    printf("The state of the devices in the Bedroom are\n");
    printf("Heating\t\tVentilator\tLights\n");
    printf("%d\t\t%d\t\t%d\n", BTempState[value], BHumiState[value], BMotState[value]);

}
void StateOfLivingRoom(){ /*Function ask for input of time and will display state of all devices in Living Room at that time*/
    int value, input;
    printf("Please enter the hour you would like to see the state of devices, e.g. 1-23\n");
    scanf("%d", &input);
    value = input - 1;
    printf("The state of the devices in the Living Room are\n");
    printf("Heating\t\tVentilator\tLights\n");
    printf("%d\t\t%d\t\t%d\n", LTempState[value], LHumiState[value], LMotState[value]);
}
void StateOfKitchen(){ /*Function ask for input of time and will display state of all devices in Kitchen at that time*/
    int value, input;
    printf("Please enter the hour you would like to see the state of devices, e.g. 1-23\n");
    scanf("%d", &input);
    value = input - 1;
    printf("The state of the devices in the Kitchen are\n");
    printf("Heating\t\tVentilator\tLights\n");
    printf("%d\t\t%d\t\t%d\n", KTempState[value], KHumiState[value], KMotState[value]);
}

float CalculateVariance(float Data[], int ArrSize){ /*function to Caculate Variance by K. Emrith 15/12/2020*/
    float mean, sum=0.0f, sdiff=0.0f;
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

void Faulty(){ /*function to see if any of the sensors are faulty*/
    int i, k;
    /*finds the variance of the temp data for all 3 locations*/
    Tempvar_bedroom = CalculateVariance((float *) BedRoomDevices.TempArr, 24);
    /*Sets the value of Tempvar to the value returned from the data of temp from bedroom once put through calculate variance function*/
    Tempvar_Livingroom = CalculateVariance((float *) LivingRoomDevices.TempArr, 24);
    /*Sets the value of Tempvar to the value returned from the data of temp from Living Room once put through calculate variance function*/
    Tempvar_Kitchen = CalculateVariance((float *) BedRoomDevices.TempArr, 24);
    /*Sets the value of Tempvar to the value returned from the data of temp from Kitchen once put through calculate variance function*/

    /*finds the mean of the Humi data for all 3 locations*/
    for (i=0; i<24; i++){
        HumiAdd_Bedroom += BedRoomDevices.HumiArr[i]; /*finds the total for Humi data in BedRoom*/
    }
    HumiMean_Bedroom = HumiAdd_Bedroom / 24; /*finds the mean for Humi data in BedRoom*/
    for (i=0; i<24; i++){
        HumiAdd_Kitchen += KitchenDevices.HumiArr[i]; /*finds the total for Humi data in Kitchen*/
    }
    HumiMean_Kitchen = HumiAdd_Kitchen / 24; /*finds the mean for Humi data in Kitchen*/
    for (i=0; i<24; i++){
        HumiAdd_Livingroom += LivingRoomDevices.HumiArr[i]; /*finds the total for Humi data in LivingRoom*/
    }
    HumiMean_Livingroom = HumiAdd_Livingroom / 24; /*finds the mean for Humi data in LivingRoom*/

    /*finds the variance of the mean for motion data for all 3 locations*/
    for (i=0; i<24; i++){
        MotAdd_Bedroom = 0;
         for (k = 0; k < 6; k++){
             MotAdd_Bedroom += BedRoomDevices.MotionArr[i][k]; /*finds the total for motion data in BedRoom per hour*/
         }
         MotAv_Bedroom[i] = (MotAdd_Bedroom / 6); /*finds the average for motion data in BedRoom per hour*/
    }
    Motvar_Bedroom = CalculateVariance((float *)MotAv_Bedroom, 24);
    /*Sets the value of MotVar to the value returned from the average of motion from bedroom once put through calculate variance function*/
    for (i=0; i<24; i++){
        MotAdd_Kitchen = 0;
        for (k = 0; k < 6; k++){
            MotAdd_Kitchen += KitchenDevices.MotionArr[i][k];  /*finds the total for motion data in Kitchen per hour*/
        }
        MotAv_Kitchen[i] = (MotAdd_Kitchen / 6);  /*finds the average for motion data in Kitchen per hour*/
    }
    Motvar_Kitchen = CalculateVariance((float *)MotAv_Kitchen, 24);
    /*Sets the value of MotVar to the value returned from the average of motion from bedroom once put through calculate variance function*/
    for (i=0; i<24; i++){
        MotAdd_Livingroom = 0;
        for (k = 0; k < 6; k++){
            MotAdd_Livingroom += LivingRoomDevices.MotionArr[i][k]; /*finds the total for motion data in Living room per hour*/
        }
        MotAv_Livingroom[i] = (MotAdd_Livingroom / 6); /*finds the average for motion data in Living room per hour*/
    }
    Motvar_Livingroom = CalculateVariance((float *)MotAv_Livingroom, 24);
    /*Sets the value of MotVar to the value returned from the average of motion from bedroom once put through calculate variance function*/
    FaultyTextFile(); /*call function FualtyTextFile()*/
}
void FaultyTextFile(){ /*function that will open a text file and write the report of the sensors in it*/
    FILE * fpointer;
    fpointer = fopen("Faulty.txt", "w"); /*Opens a file called Faulty.txt*/
    /*conditions for temperature sensor report*/
    fprintf(fpointer, "Temperature sensor report:\n");
    if (Tempvar_bedroom < 3.0){
        fprintf(fpointer, "Temperature sensors in Bedroom are faulty\n");
    }
    else{
        fprintf(fpointer, "Temperature sensors in Bedroom are working correctly\n");
    }
    if (Tempvar_Kitchen < 3.0){
        fprintf(fpointer, "Temperature sensors in Kitchen are faulty\n");
    }
    else{
        fprintf(fpointer, "Temperature sensors in Kitchen are working correctly\n");
    }
    if (Tempvar_Livingroom < 3.0){
        fprintf(fpointer, "Temperature sensors in Living Room are faulty\n");
    }
    else{
        fprintf(fpointer, "Temperature sensors in LivingRoom are working correctly\n");
    }
    /*if the variance of any of the sensors are less than 3.0 the text file will display that there is a problem if not it will display that its working correct*/

    /*conditions for Humidity sensor report*/
    fprintf(fpointer, "Humidity sensor report:\n");
    if (HumiMean_Bedroom < 5.0){
        fprintf(fpointer, "Humidity sensors in Bedroom are faulty\n");
    }
    else{
        fprintf(fpointer, "Humidity sensors in Bedroom are working correctly\n");
    }
    if (HumiMean_Kitchen < 5.0){
        fprintf(fpointer, "Humidity sensors in Kitchen are faulty\n");
    }
    else{
        fprintf(fpointer, "Humidity sensors in Kitchen are working correctly\n");
    }
    if (HumiMean_Livingroom < 5.0){
        fprintf(fpointer, "Humidity sensors in Living Room are faulty\n");
    }
    else{
        fprintf(fpointer, "Humidity sensors in Living Room are working correctly\n");
    }
    /*if the mean of any of the sensors are less than 5.0 the text file will display that there is a problem if not it will display that its working correct*/

    /*conditions for Motion sensor report*/
    fprintf(fpointer, "Light sensor report:\n");
    if (Motvar_Bedroom < 2.0){
        fprintf(fpointer, "Light sensors in Bedroom are faulty\n");
    }
    else{
        fprintf(fpointer, "Light sensors in Bedroom are working correctly\n");
    }
    if (Motvar_Kitchen < 2.0){
        fprintf(fpointer, "Light sensors in Kitchen are faulty\n");
    }
    else{
        fprintf(fpointer, "Light sensors in Kitchen are working correctly\n");
    }
    if (Motvar_Livingroom < 2.0){
        fprintf(fpointer, "Light sensors in Living Room are faulty\n");
    }
    else{
        fprintf(fpointer, "Light sensors in Living Room are working correctly\n");
    }
    /*if the variance of the mean of any of the sensors are less than 2.0 the text file will display that there is a problem if not it will display that its working correct*/
    fclose(fpointer); /*close file*/
}

void TotalEnergy(){ /*function to calculate total energy and put it into a text file*/
    int i;
    /*total energy per hour for each device in bed room*/
    for (i = 0; i < 24; i++) {
        if (BTempState[i] == 1){
            BedRoomEnergy.Hours_Heat[i] = 300; /*if device is on energy = 300*/
        }
        if (BMotState[i] == 1){
            BedRoomEnergy.Hours_lights[i] = 100; /*if device is on energy = 100*/
        }
        if (BHumiState[i] == 1){
            BedRoomEnergy.Hours_vent[i] = 250; /*if device is on energy = 250*/
        }
        BedRoomEnergy.Hour_energy[i] = BedRoomEnergy.Hours_Heat[i] + BedRoomEnergy.Hours_lights[i] + BedRoomEnergy.Hours_vent[i]; /*total energy for devices per hour in bedroom*/
        TotalE_Bedroom += BedRoomEnergy.Hour_energy[i];  /*total energy used in bed room*/
    }
    /*total energy per hour for each device in Kitchen*/
    for (i = 0; i < 24; i++) {
        if (KTempState[i] == 1){
            KitchenEnergy.Hours_Heat[i] = 300; /*if device is on energy = 300*/
        }
        if (KMotState[i] == 1){
            KitchenEnergy.Hours_lights[i] = 100; /*if device is on energy = 100*/
        }
        if (KHumiState[i] == 1){
            KitchenEnergy.Hours_vent[i] = 250; /*if device is on energy = 250*/
        }
        KitchenEnergy.Hour_energy[i] = KitchenEnergy.Hours_Heat[i] + KitchenEnergy.Hours_lights[i] + KitchenEnergy.Hours_vent[i]; /*total energy for devices per hour in Kitchen*/
        TotalE_Kitchen += KitchenEnergy.Hour_energy[i]; /*total energy used in Kitchen*/
    }
    /*total energy per hour for each device in Living Room*/
    for (i = 0; i < 24; i++) {
        if (LTempState[i] == 1){
            LivingRoomEnergy.Hours_Heat[i] = 300; /*if device is on energy = 300*/
        }
        if (LMotState[i] == 1){
            LivingRoomEnergy.Hours_lights[i] = 100; /*if device is on energy = 100*/
        }
        if (LHumiState[i] == 1){
            LivingRoomEnergy.Hours_vent[i] = 250; /*if device is on energy = 250*/
        }
        LivingRoomEnergy.Hour_energy[i] = BedRoomEnergy.Hours_Heat[i] + BedRoomEnergy.Hours_lights[i] + BedRoomEnergy.Hours_vent[i]; /*total energy for devices per hour in Living Room*/
        TotalE_Livingroom += LivingRoomEnergy.Hour_energy[i]; /*total energy used in Living Room*/
    }
    Total_Energy = TotalE_Livingroom + TotalE_Kitchen + TotalE_Bedroom; /*total energy used in all locations*/
    FILE * fpointer;
    fpointer = fopen("Energy.txt", "w"); /*opening a file called Energy.txt*/
    /*Printing out table with Time, state of Heating, Ventilator, and lights and energy used per hour into a table for bedroom*/
    fprintf(fpointer, "Location: BedRoom\n");
    fprintf(fpointer, "TIME\t\tHeating\t\tVentilator\tLights\tEnergy Used\n");
    for (i = 0; i < 24; i++) {
        fprintf(fpointer, "%s\t%d\t\t%d\t\t%d\t%d\n", BedRoomDevices.TimeDat[i], BTempState[i], BHumiState[i], BMotState[i], BedRoomEnergy.Hour_energy[i]);
    }
    /*Printing out table with Time, state of Heating, Ventilator, and lights and energy used per hour into a table for Kitchen*/
    fprintf(fpointer, "\nLocation: Kitchen\n");
    fprintf(fpointer, "TIME\t\tHeating\t\tVentilator\tLights\tEnergy Used\n");
    for (i = 0; i < 24; i++) {
        fprintf(fpointer, "%s\t%d\t\t%d\t\t%d\t%d\n", KitchenDevices.TimeDat[i], KTempState[i], KHumiState[i], KMotState[i], KitchenEnergy.Hour_energy[i]);
    }
    /*Printing out table with Time, state of Heating, Ventilator, and lights and energy used per hour into a table for Living Room*/
    fprintf(fpointer, "\nLocation: Living Room\n");
    fprintf(fpointer, "TIME\t\tHeating\t\tVentilator\tLights\tEnergy Used\n");
    for (i = 0; i < 24; i++) {
        fprintf(fpointer, "%s\t%d\t\t%d\t\t%d\t%d\n", LivingRoomDevices.TimeDat[i], LTempState[i], LHumiState[i], LMotState[i], LivingRoomEnergy.Hour_energy[i]);
    }
    /*Printing out table for Energy used in the Bedroom, Kitchen and living room and the TotalEnergy*/
    fprintf(fpointer,"\nEnergy used in KJ:\n");
    fprintf(fpointer,"BedRoom\t\tKitchen\t\tLiving Room\tTotal\n");
    fprintf(fpointer,"%d\t\t%d\t\t%d\t\t%d\n", TotalE_Bedroom, TotalE_Kitchen, TotalE_Livingroom, Total_Energy);

    fclose(fpointer); /*close file*/
}
