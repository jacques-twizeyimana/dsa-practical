#include <iostream>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <fstream>
#include "location.cpp"
#include "disease.cpp"
#include "disease-cases.cpp"

using namespace std;

void listLocations()
{
    vector<Location> locations = Location::fromFile();
    for (Location location : locations)
    {
        cout << "\t" << location.name << endl;
    }
}

void listDiseases()
{
    vector<Disease> diseases = Disease::fromFile();
    for (Disease disease : diseases)
    {
        cout << "\t" << disease.name << endl;
    }
}

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

void invalidNumberOfArguments()
{
    cout << "* ********************************************** *" << endl;
    cout << "*\tError: Invalid number of arguments!\t*" << endl;
    cout << "* ********************************************** *" << endl;
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
        cout << "Console > ";
        getline(cin, option);
        // change option to lowercase
        transform(option.begin(), option.end(), option.begin(), ::tolower);

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
            // split the option into words
            stringstream ss(option);
            string word;
            vector<string> words;
            while (ss >> word)
            {
                words.push_back(word);
            }

            if (words.size() == 2)
            {
                if (words[0] == "add")
                {
                    Location location(words[1]);
                    location.save();
                }
                else if (words[0] == "delete")
                {
                    Location::deleteLocation(words[1]);
                    DiseaseCases::deleteCasesByLocation(words[1]);
                }

                else if (words[0] == "list")
                {
                    if (words[1] == "locations")
                        listLocations();
                    else if (words[1] == "diseases")
                        listDiseases();
                }
                else if (words[0] == "where")
                {
                    // find where a disease exists
                    vector<DiseaseCases> diseaseCases = DiseaseCases::findByDiseaseName(words[1]);
                    for (DiseaseCases diseaseCase : diseaseCases)
                    {
                        cout << "\t" << diseaseCase.locationName << " : " << diseaseCase.cases << endl;
                    }
                }
                else if (words[0] == "cases")
                {
                    // find cases of a disease in a location
                    int totalCases = 0;
                    vector<DiseaseCases> reported = DiseaseCases::findByDiseaseName(words[1]);
                    for (DiseaseCases diseaseCases : reported)
                    {
                        totalCases += diseaseCases.cases;
                    }

                    cout << "Total cases of " << words[1] << ": " << totalCases << endl;
                }
            }
            else if (words.size() == 3)
            {
                if (words[0] == "cases")
                {
                    DiseaseCases cs = DiseaseCases::findByLocationNameAndDiseaseName(words[1], words[2]);
                    cout << "There are " << cs.cases << " cases of " << words[2] << " in " << words[1] << endl;
                }
            }
            else if (words.size() == 4 && words[0] == "record")
            {
                // record disease cases in a location
                Disease(words[2]).save();

                DiseaseCases cases(words[1], words[2], stoi(words[3]));
                cases.save();
            }
            else
                invalidNumberOfArguments();
        }
    } while (option != "exit");

    return 0;
}
