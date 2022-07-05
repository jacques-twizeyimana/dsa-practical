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
        return true;
    }

    // update cases of a disease given its location and disease name
    static bool updateCases(string locationName, string diseaseName, int cases)
    {
        vector<DiseaseCases> diseaseCases = DiseaseCases::fromFile();
        bool found = false;

        for (int i = 0; i < diseaseCases.size(); i++)
        {
            if (diseaseCases[i].locationName == locationName && diseaseCases[i].diseaseName == diseaseName)
            {
                diseaseCases[i].cases += cases;
                found = true;
                break;
            }
        }

        if (found)
        {
            fstream file(disease_cases_file, ios::out);
            for (DiseaseCases diseaseCase : diseaseCases)
            {
                file << diseaseCase.toString() << endl;
            }
            file.close();
            return true;
        }

        return found;
    }

    // delete disease case by location name
    static bool deleteCasesByLocation(string locationName)
    {
        // change location name to uppercase
        transform(locationName.begin(), locationName.end(), locationName.begin(), ::toupper);

        vector<DiseaseCases> diseases = DiseaseCases::fromFile();
        for (int i = 0; i < diseases.size(); i++)
        {
            if (diseases[i].locationName == locationName)
            {
                diseases.erase(diseases.begin() + i);
                fstream file(disease_cases_file, ios::out);
                for (DiseaseCases d : diseases)
                {
                    file << d.toString() << endl;
                }
                file.close();
                return true;
            }
        }

        return false;
    }

    // find by disease name
    static vector<DiseaseCases> findByDiseaseName(string diseaseName)
    {
        // transform diseaseName to uppercase
        transform(diseaseName.begin(), diseaseName.end(), diseaseName.begin(), ::toupper);

        vector<DiseaseCases> cases;
        for (DiseaseCases disease : DiseaseCases::fromFile())
        {
            if (disease.diseaseName == diseaseName)
            {
                cases.push_back(disease);
            }
        }
        return cases;
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