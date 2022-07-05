#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

void printHelpMenu()
{
    // disease cases reporting system help menu
    cout << "==============================================================" << endl;
    cout << "*                         HELP MENU                          *" << endl;
    cout << "==============================================================" << endl;
    cout << "add <Location>\t\t\t\t: Add a new location" << endl;
    cout << "delete <Location>\t\t\t\t: Delete a location" << endl;
    cout << "record <Location> <disease> <cases>\t: Record a disease and its cases" << endl;
    cout << "list locations\t\t\t\t: List all existing locations" << endl;
    cout << "list diseases\t\t\t\t: List all existing diseases in locations" << endl;
    cout << "where <disease>\t\t\t\t: Find where a disease exists" << endl;
    cout << "cases <location> <disease>\t\t: Find cases of a disease in a location" << endl;
    cout << "cases <disease>\t\t\t\t: Find total cases of a given disease" << endl;
    cout << "help\t\t\t\t\t: Prints user manual" << endl;
    cout << "exit\t\t\t\t\t: Exit the program" << endl;
}

int main(int argc, char const *argv[])
{
    time_t now = time(0);
    char *dt = ctime(&now);

    string option;

    cout << "=========================================================" << endl;
    cout << "*\tWelcome to Disease Cases Reporting System!\t*" << endl;
    cout << "* ********************************************** *" << endl;
    cout << "*\t\t\t\t\t\t*" << endl;
    cout << "* It is developed by Twizeyimana Jacques as practical *" << endl;
    cout << "* evaluation for the end of Year 3." << endl;
    cout << "=========================================================" << endl;
    cout << "Starting Time: " << dt << endl;
    cout << "Need a help? Type 'help' then press Enter key." << endl;

    // do while loop to keep the program running until the user wants to exit

    do
    {
        cout << "> ";
        getline(cin, option);

        if (option == "help")
        {
            printHelpMenu();
        }
        else if (option == "exit")
        {
            cout << "* ********************************************** *" << endl;
            cout << "*\tThank you for using Disease Cases Reporting System!\t*" << endl;
            cout << "* ********************************************** *" << endl;
            return 0;
            break;
        }
        else
        {
            cout << "Invalid command. Type 'help' to see the list of commands." << endl;
        }
    } while (option != "exit");

    cout << "Console > ";
    getline(cin, option);

    return 0;
}
