/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Ian Hartog
Email      : ihartog@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    int flag = 0;

    for (i = 0; i < max; i++) //check if there are any patient records
    {
        if (patient[i].patientNumber != -1)
        {
            flag = 1;
        }
    }

    if (flag == 0) //if no records are found
    {
        printf("*** No records found ***\n");
    }
    else //if records are found display them
    {
        if (fmt == FMT_TABLE)
        {
            displayPatientTableHeader();
        }

        for (i = 0; i < max; i++)
        {
            if (patient[i].patientNumber != -1)
                displayPatientData(&patient[i], fmt);
        }
    }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do
    {
        //menu display
        puts("Search Options");
        puts("==========================");
        puts("1) By patient number");
        puts("2) By phone number");
        puts("..........................");
        puts("0) Previous menu");
        puts("..........................");
        printf("Selection: ");
        //use inputIntRange to ensure a value between 0 and 2 inclusive is selected
        selection = inputIntRange(0, 2);
        printf("\n");
        if (selection == 1) //if 1 is selected call search by patient number
        {
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (selection == 2) //if 2 is selected call search by phone number
        {
            searchPatientByPhoneNumber(patient, max);
            suspend();
        }


    } while (selection != 0);
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max) {
    int i, flag = 0;
    int emptyIndex;

    for (i = 0; i < max && flag == 0; i++)
    {
        if (patient[i].patientNumber == -1) //check if there are any empty patient record slots
        {
            flag = 1;
            emptyIndex = i;
        }
    }

    if (flag == 0) //if no empty slots available
    {
        printf("ERROR: Patient listing is FULL!\n");
    }
    else
    {
        patient[emptyIndex].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[emptyIndex]);
        puts("*** New patient record added ***");
    }
    printf("\n");
}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max) {
    int matchingIndex, numInput;

    printf("Enter the patient number: ");
    numInput = inputInt();

    matchingIndex = findPatientIndexByPatientNum(numInput, patient, max);
    printf("\n");

    if (matchingIndex == -1)
    {
        puts("ERROR: Patient record not found!\n");
    }
    else
    {
        menuPatientEdit(&patient[matchingIndex]);
    }
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max) {
    int matchingIndex, numInput;
    char charInput;

    printf("Enter the patient number: ");
    numInput = inputInt();
    
    matchingIndex = findPatientIndexByPatientNum(numInput, patient, max);
    printf("\n");
    if (matchingIndex == -1)
    {
        puts("ERROR: Patient record not found!\n");
    }
    else
    {
        displayPatientData(&patient[matchingIndex], FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        charInput = inputCharOption("yn");
        if (charInput == 'y')
        {
            patient[matchingIndex].patientNumber = -1;
            puts("Patient record has been removed!\n");
        }
        else
        {
            puts("Operation aborted.");
        }
    }    
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData* cd) {
    int i, index;

    selectSort(cd->appointments, cd->maxAppointments);
    displayScheduleTableHeader(NULL, 1);

    for (i = 0; i < cd->maxAppointments; ++i)
    {
        if (cd->appointments[i].patientNumber != -1) 
        {
            index = findPatientIndexByPatientNum(cd->appointments[i].patientNumber, cd->patients, cd->maxPatient);
            if (index != -1)
            {
                displayScheduleData(&(cd->patients[index]), &(cd->appointments[i]), 1);
            }
        }                
    }
    printf("\n");
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* cd) {
    int i, index;
    struct Date date;

    date = inputDate();

    printf("\n");

    selectSort(cd->appointments, cd->maxAppointments);

    displayScheduleTableHeader(&date, 0);

    for (i = 0; i < cd->maxAppointments; ++i)
    {
        if (cd->appointments[i].patientNumber != -1)
        {
            if (date.year == cd->appointments[i].date.year && date.month == cd->appointments[i].date.month && date.day == cd->appointments[i].date.day)
            {
                index = findPatientIndexByPatientNum(cd->appointments[i].patientNumber, cd->patients, cd->maxPatient);
                if (index != -1)
                {
                    displayScheduleData(&(cd->patients[index]), &(cd->appointments[i]), 0);
                }
            }
        }

    }
    printf("\n");
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment ap[], int maxAppointments, const struct Patient pt[], int maxPatients) {
    int i, validInterval, validTime;
    int emptyIndex = -1, patientNum, indexNum;
    struct Date tempDate;
    struct Time tempTime;

    for (i = 0; (i < maxAppointments) && (emptyIndex == -1); ++i)
    {
        if (ap[i].patientNumber == -1)
        {
            emptyIndex = i;
        }
    }

    printf("Patient Number: ");
    scanf("%d", &patientNum);
    indexNum = findPatientIndexByPatientNum(patientNum, pt, maxPatients);
    if (indexNum == -1)
    {
        puts("ERROR: Patient record not found!");
        return;
    }
    do {
        validTime = 1; //assume for now time inputted is valid
        tempDate = inputDate();
        do {
            validInterval = 1; // assume for now interval is valid
            tempTime = inputTime();

            if (tempTime.hour < START_TIME || tempTime.hour > END_TIME)
            {
                validInterval = 0;
            }
            else if (tempTime.hour == END_TIME && tempTime.min > 0)
            {
                validInterval = 0;
            }
            else if (tempTime.min % APPOINTMENT_INTERVAL != 0)
            {
                validInterval = 0;
            }

            if (!validInterval)
            {
                printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", START_TIME, END_TIME, APPOINTMENT_INTERVAL);
                            }           

        } while (!validInterval);

        if (!isTimeSlotAvailable(tempTime, tempDate, 
            ap, maxAppointments))
        {
            puts("\nERROR: Appointment timeslot is not available!\n");
            validTime = 0;
        }
        
    } while (!validTime);
    
    ap[emptyIndex].date = tempDate;
    ap[emptyIndex].time = tempTime;
    ap[emptyIndex].patientNumber = patientNum;

    puts("\n*** Appointment scheduled! ***\n");
}



// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment ap[], int maxAppointments, const struct Patient pt[], int maxPatients) {
    int patientNum, patientIndex, i;
    struct Date tempDate;
    char input;

    printf("Patient Number: ");
    scanf("%d", &patientNum);
    patientIndex = findPatientIndexByPatientNum(patientNum, pt, maxPatients);
    if (patientIndex == -1)
    {
        puts("ERROR: Patient record not found!\n");
        clearInputBuffer();

        return;
    }

    tempDate = inputDate();    

    for (i = 0; i < maxAppointments; ++i) 
    {
        if (ap[i].patientNumber != patientNum)
        {
            continue;
        }
        if (ap[i].date.year != tempDate.year)
        {
            continue;
        }
        if (ap[i].date.month != tempDate.month)
        {
            continue;
        }
        if (ap[i].date.day != tempDate.day)
        {
            continue;
        }
        printf("\nName  : %s\n", pt[patientIndex].name);
        printf("Number: %05d\n", patientNum);
        printf("Phone : (%.3s)%.3s-%.4s (%s)\n", pt[patientIndex].phone.number, pt[patientIndex].phone.number + 3, pt[patientIndex].phone.number + 6, pt[patientIndex].phone.description);
        printf("Are you sure you want to remove this appointment (y,n): ");
        input = inputCharOption("yn");
        if (input == 'y')
        {
            ap[i].patientNumber = -1;
            puts("\nAppointment record has been removed!\n");
        }
        else
        {
            puts("\nAppointment record was not removed.");
        }
        return;
    }      
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int patientNum, indexNum;

    printf("Search by patient number: ");
    patientNum = inputInt();

    indexNum = findPatientIndexByPatientNum(patientNum, patient, max);
    printf("\n");
    if (indexNum == -1)
    {
        puts("*** No records found ***");
    }
    else
    {
        displayPatientData(&patient[indexNum], FMT_FORM); //not finding correct patientNumber
    }
    printf("\n");
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    int i, flag = 0;
    char patientPhoneNum[PHONE_LEN + 1];


    printf("Search by phone number: ");
    inputCString(patientPhoneNum, PHONE_LEN, PHONE_LEN);
    printf("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(patientPhoneNum, patient[i].phone.number) == 0)
        {
            flag = 1;
            displayPatientData(&patient[i], FMT_TABLE);
        }
    }

    if (flag == 0)
    {
        puts("\n*** No records found ***");
    }
    printf("\n");
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max) {
    int i;
    int greatest = 0;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > greatest)
        {
            greatest = patient[i].patientNumber;
        }
    }
    return greatest + 1;
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {
    int i;

    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            return i;
        }

    }

    return -1;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient) {


    puts("Patient Data Input");
    puts("------------------");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    printf("\n");
    inputPhoneData(&(patient->phone));
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone) {
    int choice;
    char buffer[21];

    puts("Phone Information");
    puts("-----------------");
    puts("How will the patient like to be contacted?");
    puts("1. Cell");
    puts("2. Home");
    puts("3. Work");
    puts("4. TBD");
    printf("Selection: ");
    choice = inputIntRange(1, 4);
    printf("\n");
    if (choice >= 1 && choice <= 3)
    {
        switch (choice)
        {
        case 1:
            strcpy(phone->description, "CELL");
            break;

        case 2:
            strcpy(phone->description, "HOME");
            break;

        case 3:
            strcpy(phone->description, "WORK");
            break;
        }
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        do {
            inputCString(buffer, 1, 20);
            if (strlen(buffer) != PHONE_LEN)
            {
                printf("Invalid 10-digit number! ");
                printf("Number: ");
            }
        } while (strlen(buffer) != PHONE_LEN);
        strcpy(phone->number, buffer);
        printf("\n");
    }
    else
    {
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "          ");
    }
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* fp = NULL;
    int patientCount = 0;
    char garb;
    int i;

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (patientCount < max && fscanf(fp, "%d", &patients[patientCount].patientNumber) == 1) //read lines in file until max number is reached or no patient number is scanned (EOF)
        {
            fscanf(fp, "%c", &garb); //read bar
            fscanf(fp, "%15[^|]", patients[patientCount].name);
            fscanf(fp, "%c", &garb); //read bar
            fscanf(fp, "%4[^|]", patients[patientCount].phone.description);
            fscanf(fp, "%c", &garb); //read bar
            fscanf(fp, "%10[^\n]", patients[patientCount].phone.number);
            fscanf(fp, "%c", &garb); //read new line

            patientCount++; //counter for number of lines/patients                     
        }
        fclose(fp);
        fp = NULL;

        //Remainder of entries in patients array will be set to available
        //by setting patient number to -1
        for (i = patientCount; i < max; ++i)
        {
            patients[i].patientNumber = -1;
        }
    }
    else
    {
        printf("Error opening file\n");
    }
    return patientCount;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* fp = NULL;
    int appointsCount = 0;
    int i;

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (appointsCount < max && fscanf(fp, "%d%*c", &appoints[appointsCount].patientNumber) == 1) //read lines in file until max number is reached or no patient number is scanned (EOF)
        {
            fscanf(fp, "%d%*c", &appoints[appointsCount].date.year);
            fscanf(fp, "%d%*c", &appoints[appointsCount].date.month);
            fscanf(fp, "%d%*c", &appoints[appointsCount].date.day);
            fscanf(fp, "%d%*c", &appoints[appointsCount].time.hour);
            fscanf(fp, "%d%*c", &appoints[appointsCount].time.min);            
            
            appointsCount++; //counter for number of lines/patients                     
        }
        fclose(fp);
        fp = NULL;

        //Remainder of entries in appointments array will be set to available
        //by setting patient number to -1
        for (i = appointsCount; i < max; ++i)
        {
            appoints[i].patientNumber = -1;
            appoints[i].date.year = 9999;
            appoints[i].date.month = 12;
            appoints[i].date.day = 31;
            appoints[i].time.hour = 23;
            appoints[i].time.min = 59;
        }
    }
    else
    {
        printf("Error opening file\n");
    }
    return appointsCount;
}
