/* 
* Student: Abraham Alvarado
* Assignment: 3-1 Project One: Chada Tech Clocks
* Course: CS-210-T3624 Programming Languages 22EW3
* Professor: Bill Chan, M.S.
* Date: Monday January 17, 2022 - Sunday January 23, 2022
*/

#define _CRT_SECURE_NO_WARNINGS  // add above all include headers and enables the use of localtime() function
#include <iostream>
#include <iomanip>   // using setfill() & setw() manipulators
#include <string> 
#include <ctime>  // enables the use of time() function

using namespace std;

/* Functional Requirements
1. Clock12: Time should be displayed in 12-hour format where the clock does not exceed 12:59:59.
2. Clock24: Time should be displayed in 24-hour format where the clock does not exceed 23:59:59
3. Both clocks should display on the screen with the current time in the proper format.
4. Your solution should allow the user to exit the program as well as add one hour, minute, or
   second to both clocks from a user menu.
5. Once a selection is made from the user menu, the program should take action based on that
   choice. Both clocks must display on the screen simultaneously in the proper format next to each
   other. 
*/

void MenuDisplay() {
    // Center menu using text-alignment manipulators 
    // First Row
    cout << setw(23) << setfill(' ') << "" << setfill('*') << setw(26) << "" << endl;
    // Second Row
    cout << setw(23) << setfill(' ') << "" << "* 1 - Add One Hour" << setfill(' ') << setw(8) << "*" << endl;
    // Third Row
    cout << setw(23) << setfill(' ') << "" << "* 2 - Add One Minute" << setfill(' ') << setw(6) << "*" << endl;
    // Fourth Row
    cout << setw(23) << setfill(' ') << "" << "* 3 - Add One Second" << setfill(' ') << setw(6) << "*" << endl;
    // Fifth Row
    cout << setw(23) << setfill(' ') << "" << "* 4 - Exit Program" << setfill(' ') << setw(8) << "*" << endl;
    // Sixth Row
    cout << setw(23) << setfill(' ') << "" << setfill('*') << setw(26) << "" << endl;
}

void ClockDisplay(int Clock12_DisplayHrs, int Clock12_DisplayMin, int Clock12_DisplaySec, int Clock24_DisplayHrs, int Clock24_DisplayMin, int Clock24_DisplaySec, bool period) {
    
    // First Row
    cout << setw(8) << setfill(' ') << "" << setfill('*') << setw(26) << "" << setw(4) << setfill(' ') << "" << setfill('*') << setw(26) << "" << endl;
    // Second Row
    cout << setw(8) << setfill(' ') << "" << "*" << setw(6) << setfill(' ') << "" << "12-Hour Clock" << setw(5) << setfill(' ') << "" << "*";
    cout << setw(4) << setfill(' ') << "" << "*" << setw(6) << setfill(' ') << "" << "24-Hour Clock" << setw(5) << setfill(' ') << "" << "*" << endl;
    // Third Row
    cout << setw(8) << setfill(' ') << "" << "*" << setw(6) << setfill(' ') << "";
    cout << setw(2) << setfill(' ') << Clock12_DisplayHrs << ":";
    cout << setw(2) << setfill('0') << Clock12_DisplayMin << ":";
    cout << setw(2) << setfill('0') << Clock12_DisplaySec;
    cout << ((!period) ? " PM " : " AM ");
    cout << setw(6) << setfill(' ') << "" << "*";
   
    cout << setw(4) << setfill(' ') << "" << "*" << setw(8) << setfill(' ') << "";
    cout << setw(2) << setfill('0') << Clock24_DisplayHrs << ":";
    cout << setw(2) << setfill('0') << Clock24_DisplayMin << ":";
    cout << setw(2) << setfill('0') << Clock24_DisplaySec;
    cout << setw(8) << setfill(' ') << "" << "*" << setw(4) << setfill(' ') << "";
    cout << endl;
    // Fourth Row
    cout << setw(8) << setfill(' ') << "" << setfill('*') << setw(26) << "" << setw(4) << setfill(' ') << "" << setfill('*') << setw(26) << "" << endl;
    
    cout << endl;
}

void ClockFormat(tm* Clock12, tm* Clock24) {
    int Clock12_DisplayHrs; int Clock12_DisplayMin; int Clock12_DisplaySec; // Declare variables for hour, minutes, and seconds.
    int Clock24_DisplayHrs; int Clock24_DisplayMin; int Clock24_DisplaySec;
    bool period = true; // period used to display AM or PM
                                     
    if (Clock12->tm_hour == 0) {    // tm_hour ranges from 0-23.
        Clock12_DisplayHrs = 12;    // if tm_hour equals zero, assign 12
    }
    else if (Clock12->tm_hour > 12) {   // if tm_hour greater than 12, i.e 13-23, subtract 12 for standard clock time.
        Clock12_DisplayHrs = (Clock12->tm_hour) - 12;
    }
    else {
        Clock12_DisplayHrs = Clock12->tm_hour;  // else, display tm_hour 
    }

    Clock12_DisplayMin = Clock12->tm_min;  // tm_min ranges from 0-59
    Clock12_DisplaySec = Clock12->tm_sec; // tm_sec ranges from 0-59

    Clock24_DisplayHrs = Clock24->tm_hour;
    Clock24_DisplayMin = Clock24->tm_min;
    Clock24_DisplaySec = Clock24->tm_sec;

    if (Clock12->tm_hour < 12) {
        period = true;          // AM
    }
    else {
        period = false;         // PM
    }

    ClockDisplay(Clock12_DisplayHrs, Clock12_DisplayMin, Clock12_DisplaySec, Clock24_DisplayHrs, Clock24_DisplayMin, Clock24_DisplaySec, period);
}


int main() {
    time_t currentTime = time(0); // Declare and initialize currentTime variable of type time_t, time() returns the number of seconds elapsed since the epoch                               
    tm* Clock12 = localtime(&currentTime); // Convert time_t to tm as local time
    tm* Clock24 = localtime(&currentTime);
    int menuOption = 0;

    ClockFormat(Clock12, Clock24);
    MenuDisplay();
    
    while (menuOption != 4) {						// Execute while menuOption is not 4, exit.

        cin >> menuOption;
        
        switch (menuOption) {						// Used a switch statment for menu options

        case 1:
            cout << "Add One Hour" << endl;			// Return the menu option selected
            currentTime = currentTime + 3600;		// Add one hour to currentTime in seconds 3600
            Clock12 = localtime(&currentTime);		// Update both 12 and 24 hour clocks
            Clock24 = localtime(&currentTime);
            ClockFormat(Clock12, Clock24);		// Call the ClockFormat & MenuDisplay functions to display new updated clock and menu
            MenuDisplay();
            break;

        case 2:
            cout << "Add One Minute" << endl;
            currentTime = currentTime + 60;			// Add one min to currentTime in seconds 60	
            Clock12 = localtime(&currentTime);
            Clock24 = localtime(&currentTime);
            ClockFormat(Clock12, Clock24);
            MenuDisplay();
            break;

        case 3:
            cout << "Add One Second" << endl;
            currentTime = currentTime + 1;			// Add one second to currentTime
            Clock12 = localtime(&currentTime);
            Clock24 = localtime(&currentTime);
            ClockFormat(Clock12, Clock24);
            MenuDisplay();
            break;

        case 4:                                     // End expression
            break;

        default:
            cout << "Invalid Entry" << endl;
            cout << "Please Select An Option From The Menu." << endl;	// Validate input menuOption, direct the user to enter a correct entry from the menu.
            break;
        }
    }
    cout << "Exit Program" << endl;         // Exit the program

    return 0;

}