#include <iostream>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

// define constants
#define disease_cases_file "./data/disease-cases.csv"

class DiseaseCases
{
public:
    int id;
    string locationName;
    string diseaseName;
    int cases;

    DiseaseCases()
    {
        this->cases = 0;
    }

    DiseaseCases(string locationName, string diseaseName, int cases)
    {
        this->id = generateId();
        this->locationName = locationName;
        this->diseaseName = diseaseName;
        this->cases = cases;
    }

    string toString()
    {
        return to_string(id) + "," + locationName + "," + diseaseName + "," + to_string(cases);
    }

    int generateId()
    {
        static int id = 1;
        return id++;
    }

    static DiseaseCases fromString(string str)
    {
        stringstream ss(str);
        string id, locationName, diseaseName, cases;
        getline(ss, id, ',');
        getline(ss, locationName, ',');
        getline(ss, diseaseName, ',');
        getline(ss, cases);
        return DiseaseCases(locationName, diseaseName, stoi(cases));
    }

    static vector<DiseaseCases> fromFile()
    {

        vector<DiseaseCases> diseases;
        ifstream file(disease_cases_file);
        string line;
        while (getline(file, line))
        {
            diseases.push_back(DiseaseCases::fromString(line));
        }
        return diseases;
    }

    static bool exists(string locationName, string diseaseName)
    {
        for (DiseaseCases disease : DiseaseCases::fromFile())
        {
            if (disease.locationName == locationName && disease.diseaseName == diseaseName)
            {
                return true;
            }
        }
        return false;
    }

    bool save()
    {
        // transform locationName and diseaseName to uppercase

        transform(locationName.begin(), locationName.end(), locationName.begin(), ::toupper);
        transform(diseaseName.begin(), diseaseName.end(), diseaseName.begin(), ::toupper);

        // check if this case already exists
        if (DiseaseCases::exists(this->locationName, this->diseaseName))
        {
            // update cases instead of adding a new one
            return DiseaseCases::updateCases(this->locationName, this->diseaseName, this->cases);
        }

        ofstream file(disease_cases_file, ios::app);
        file << toString() << endl;
        file.close();
        cout << "Case saved" << endl;
        return true;
    }

    // update cases of a disease given its location and disease name
    static bool updateCases(string locationName, string diseaseName, int cases)
    {
        for (DiseaseCases disease : DiseaseCases::fromFile())
        {
            if (disease.locationName == locationName && disease.diseaseName == diseaseName)
            {
                disease.cases += cases;
                ofstream file(disease_cases_file);
                for (DiseaseCases d : DiseaseCases::fromFile())
                {
                    file << d.toString() << endl;
                }
                file.close();
                cout << "Cases updated" << endl;
                return true;
            }
        }
        cout << "Case not found" << endl;
        return false;
    }

    static bool deleteDiseaseCases(string locationName)
    {
        transform(locationName.begin(), locationName.end(), locationName.begin(), ::toupper);
        ifstream file(disease_cases_file);
        string line;
        ofstream temp("temp.csv");
        while (getline(file, line))
        {
            if (DiseaseCases::fromString(line).locationName != locationName)
            {
                temp << line << endl;
            }
        }
        file.close();
        temp.close();
        remove(disease_cases_file);
        rename("temp.csv", disease_cases_file);
        cout << "DiseaseCases " << locationName << " deleted successfully" << endl;
        return true;
    }

    // find by locationName and diseaseName
    static DiseaseCases findByLocationNameAndDiseaseName(string locationName, string diseaseName)
    {
        // transform locationName and diseaseName to uppercase
        transform(locationName.begin(), locationName.end(), locationName.begin(), ::toupper);
        transform(diseaseName.begin(), diseaseName.end(), diseaseName.begin(), ::toupper);

        for (DiseaseCases disease : DiseaseCases::fromFile())
        {
            if (disease.locationName == locationName && disease.diseaseName == diseaseName)
            {
                return disease;
            }
        }
        return DiseaseCases();
    }
};