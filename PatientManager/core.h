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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

#include "clinic.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// inputInt
int inputInt(void);

// inputIntPositive
int inputIntPositive(void);

// inputIntRange
int inputIntRange(int lowerBound, int upperBound);

// inputCharOption
char inputCharOption(const char* charList);

// inputCString
void inputCString(char* cString, int minChar, int maxChar);

// displayFormattedPhone
void displayFormattedPhone(const char* phoneNum);

// input date
struct Date inputDate(void);

// input time
struct Time inputTime(void);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

int isTimeSlotAvailable(const struct Time tm, const struct Date dt, const struct Appointment ap[], int maxAppointments);

int isLessThan(const struct Appointment left, const struct Appointment right);

void selectSort(struct Appointment data[], int max);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
