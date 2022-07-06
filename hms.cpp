#include <iostream>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <fstream>
#include "location.cpp"
#include "disease.cpp"
#include "disease-cases.cpp"

using namespace std;

bool compareLocations(Location l1, Location l2) { return l1.name < l2.name; }
bool compareDiseases(Disease d1, Disease d2) { return d1.name < d2.name; }

void listLocations()
{
    vector<Location> locations = Location::fromFile();
    sort(locations.begin(), locations.end(), compareLocations);

    for (Location location : locations)
    {
        cout << "\t" << location.name << endl;
    }
}

void listDiseases()
{
    vector<Disease> diseases = Disease::fromFile();
    sort(diseases.begin(), diseases.end(), compareDiseases);

    for (Disease disease : diseases)
    {
        cout << "\t" << disease.name << endl;
    }
}

void printHelpMenu()
{
    // disease cases reporting system help menu
    cout << " ==============================================================" << endl;
    cout << " *                         HELP MENU                          *" << endl;
    cout << " ==============================================================" << endl;
    cout << " add <Location>\t\t\t\t: Add a new location" << endl;
    cout << " delete <Location>\t\t\t: Delete a location" << endl;
    cout << " record <Location> <disease> <cases>\t: Record a disease and its cases" << endl;
    cout << " list locations\t\t\t\t: List all existing locations" << endl;
    cout << " list diseases\t\t\t\t: List all existing diseases in locations" << endl;
    cout << " where <disease>\t\t\t\t: Find where a disease exists" << endl;
    cout << " cases <location> <disease>\t\t: Find cases of a disease in a location" << endl;
    cout << " cases <disease>\t\t\t\t: Find total cases of a given disease" << endl;
    cout << " help\t\t\t\t\t: Prints user manual" << endl;
    cout << " exit\t\t\t\t\t: Exit the program" << endl;
}

void invalidNumberOfArguments()
{
    cout << "\t* ********************************************** *" << endl;
    cout << "*\t\tError: Invalid number of arguments!\t*" << endl;
    cout << "\t* ********************************************** *" << endl;
}

void invalidCommand()
{
    cout << "\n\t* ********************************************** *" << endl;
    cout << "*\t\tError: Invalid command!\t\t\t*" << endl;
    cout << "\t* ********************************************** *" << endl;
}
char *get_current_time()
{
    time_t now = time(0);
    return ctime(&now);
}

int main(int argc, char const *argv[])
{

    string option;

    cout << "=========================================================" << endl;
    cout << "*\tWelcome to Disease Cases Reporting System!\t*" << endl;
    cout << "* ********************************************** *" << endl;
    cout << "*\t\t\t\t\t\t*" << endl;
    cout << "* It is developed by Twizeyimana Jacques as practical *" << endl;
    cout << "* evaluation for the end of Year 3." << endl;
    cout << "=========================================================" << endl;
    cout << "Starting Time: " << get_current_time() << endl;
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
            cout << "\n* ****************************************************** *" << endl;
            cout << "*\tThank you for using Disease Cases Reporting System!\t*" << endl;
            cout << "* ******************************************************* *" << endl;
            cout << "Ending Time: " << get_current_time() << endl;
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
                    else
                        invalidCommand();
                }
                else if (words[0] == "where")
                {
                    // find where a disease exists
                    vector<DiseaseCases> diseaseCases = DiseaseCases::findByDiseaseName(words[1]);

                    if (diseaseCases.size() == 0)
                        cout << "\tNo location with this disease" << endl;
                    else
                    {
                        cout << "\t[";
                        for (DiseaseCases diseaseCase : diseaseCases)
                            cout << diseaseCase.locationName << " ";
                        cout << "]" << endl;
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

                    cout << "\tTotal cases of '" << words[1] << "' = " << totalCases << endl;
                }
                else
                    invalidCommand();
            }
            else if (words.size() == 3 && words[0] == "cases")
            {
                DiseaseCases cs = DiseaseCases::findByLocationNameAndDiseaseName(words[1], words[2]);
                cout << "\tCases of " << words[2] << " at " << words[1] << " are: " << cs.cases << endl;
            }
            else if (words.size() == 4 && words[0] == "record")
            {
                // record disease cases in a location
                // check if the location exists
                if (Location::exists(words[1]))
                {
                    try
                    {
                        int nums_cases = stoi(words[3]);
                        Disease(words[2]).save();
                        DiseaseCases cases(words[1], words[2], nums_cases);
                        cases.save();
                    }
                    catch (const std::exception &e)
                    {
                        cout << "Cases must be number" << endl;
                    }
                }
                else
                {
                    cout << "\t* ********************************************** *" << endl;
                    cout << "*\t\tError: Location does not exist!\t*" << endl;
                    cout << "\t* ********************************************** *" << endl;
                }
            }
            else
                invalidCommand();
        }
    } while (option != "exit");

    return 0;
}
