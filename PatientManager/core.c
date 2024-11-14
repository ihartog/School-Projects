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

#include "core.h"
#include "clinic.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// inputInt 

int inputInt(void) {

    int value;
    char newLine;

    scanf("%d%c", &value, &newLine);
    while (newLine != '\n') {
        clearInputBuffer();
        printf("Error! Input a whole number: ");
        scanf("%d%c", &value, &newLine);
    }

    return value;

}

// inputIntPositive

int inputIntPositive(void) {

    int value;
    char newLine;

    scanf("%d%c", &value, &newLine);
    while (newLine != '\n' || value <= 0) {
        if (newLine != '\n') {
            clearInputBuffer();
        }
        printf("ERROR! Value must be > 0: ");
        scanf("%d%c", &value, &newLine);
    }

    return value;
}

// inputIntRange

int inputIntRange(int lowerBound, int upperBound) {

    int value;

    //use inputInt for first int checks
    value = inputInt();

    while (value < lowerBound || value > upperBound) {
        printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        value = inputInt();
    }
    return value;
}

// inputCharOption

char inputCharOption(const char* charList) {

    char value;
    char newLine;

    while (1) {
        scanf("%c%c", &value, &newLine);
        while (newLine != '\n') {
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", charList);
            scanf("%c%c", &value, &newLine);
        }

        if (strchr(charList, value) != '\0')
        {
            return value;
        }

        printf("ERROR: Character must be one of [%s]: ", charList);
    }

    return '\0';

}

// inputCString

void inputCString(char* cString, int minChar, int maxChar) {

    int stringLength;
    char c;

    while (1) {
        stringLength = 0;
        scanf("%c", &c);

        while (stringLength < maxChar && c != '\n')
        {
            cString[stringLength] = c;
            scanf("%c", &c);
            ++stringLength;
        }
        cString[stringLength] = '\0';

        if (c != '\n')
        {
            if (minChar == maxChar)
            {
                printf("ERROR: String length must be exactly %d chars: ", minChar);
            }
            else
            {
                printf("ERROR: String length must be no more than %d chars: ", maxChar);
            }
            clearInputBuffer();
        }
        else if (stringLength >= minChar && stringLength <= maxChar)
        {
            return;
        }

        else if (minChar == maxChar)
        {
            printf("ERROR: String length must be exactly %d chars: ", minChar);
        }
        else
        {
            printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
        }
    }

}

// displayFormattedPhone

void displayFormattedPhone(const char* phoneNum) {
    int valid, i;

    valid = 1;
    if (phoneNum == NULL)
    {
        valid = 0;
    }
    else if (strlen(phoneNum) != 10)
    {
        valid = 0;
    }
    else
    {
        for (i = 0; i < 10 && valid; i++)
        {
            if (phoneNum[i] < '0' || phoneNum[i] > '9')
            {
                valid = 0;
            }
        }
    }

    if (valid)
    {
        printf("(%.3s)%.3s-%.4s", phoneNum, phoneNum + 3, phoneNum + 6);
        return;
    }
    else
    {
        printf("(___)___-____");
        return;
    }
}

// input date
struct Date inputDate(void) {
    struct Date temp;
    int months[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int upperDay;
    
    printf("Year        : ");
    scanf("%d", &temp.year);
    printf("Month (1-12): ");
    temp.month = inputIntRange(1, 12);
    upperDay = months[temp.month];
    if (temp.month == 2)
    {
        if (temp.year % 400 == 0) //one way for it to be a leap year
        {
            ++upperDay;
        }
        else if (temp.year % 4 == 0 && temp.year % 100 != 0)
        {
            ++upperDay;
        }
    }
    printf("Day (1-%d)  : ", upperDay);
    temp.day = inputIntRange(1, upperDay);

    return temp;
}

// input time
struct Time inputTime(void) {
    struct Time temp;
      
    printf("Hour (0-23)  : ");
    temp.hour = inputIntRange(0, 23);

    printf("Minute (0-59): ");
    temp.min = inputIntRange(0, 59);

    return temp;
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
// 

int isTimeSlotAvailable(const struct Time tm, const struct Date dt, const struct Appointment ap[], int maxAppointments) 
{
    int i;

    for (i = 0; i < maxAppointments; ++i)
    {
        if (ap[i].date.year != dt.year)
        {
            continue;
        }
        if (ap[i].date.month != dt.month)
        {
            continue;
        }
        if (ap[i].date.day != dt.day)
        {
            continue;
        }
        if (ap[i].time.hour != tm.hour)
        {
            continue;
        }
        if (ap[i].time.min != tm.min)
        {
            continue;
        }
        return 0;
    }
    return 1;
}

int isLessThan(const struct Appointment left, const struct Appointment right) {

    if (left.date.year < right.date.year)
    {
        return 1;
    }
    else if (left.date.year > right.date.year)
    {
        return 0;
    }
    else if (left.date.month < right.date.month)
    {
        return 1;
    }
    else if (left.date.month > right.date.month)
    {
        return 0;
    }
    else if (left.date.day < right.date.day)
    {
        return 1;
    }
    else if (left.date.day > right.date.day)
    {
        return 0;
    }
    else if (left.time.hour < right.time.hour)
    {
        return 1;
    }
    else if (left.time.hour > right.time.hour)
    {
        return 0;
    }
    else if (left.time.min < right.time.min)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
// 
//Sorting funciton
void selectSort(struct Appointment data[], int max)
{
    int i, j, minIdx;
    struct Appointment temp;

    for (i = 0; i < max; i++)
    {
        minIdx = i;

        for (j = i + 1; j < max; j++)
        {
            if (isLessThan(data[j],data[minIdx]))
            {
                minIdx = j;
            }
        }

        if (minIdx != i)
        {
            temp = data[i];
            data[i] = data[minIdx];
            data[minIdx] = temp;
        }
    }
}
