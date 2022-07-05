#include <iostream>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

// define constants
#define diseasesFile "./data/diseases.csv"

class Disease
{
public:
    int id;
    string name;

    Disease() {}
    Disease(int id, string name)
    {
        this->id = id;
        this->name = name;
    }
    Disease(string name)
    {
        this->id = generateId();
        this->name = name;
    }

    string toString()
    {
        return to_string(id) + "," + name;
    }

    int generateId()
    {
        static int id = 1;
        return id++;
    }

    static Disease fromString(string str)
    {
        stringstream ss(str);
        string id, name;
        getline(ss, id, ',');
        getline(ss, name);
        return Disease(stoi(id), name);
    }

    static vector<Disease> fromFile()
    {

        vector<Disease> diseases;
        ifstream file(diseasesFile);
        string line;
        while (getline(file, line))
        {
            diseases.push_back(Disease::fromString(line));
        }
        return diseases;
    }

    static bool exists(string name)
    {
        for (Disease disease : Disease::fromFile())
        {
            if (disease.name == name)
            {
                return true;
            }
        }
        return false;
    }

    bool save()
    {
        if (this->name.empty() || !this->id)
        {
            cout << "Invalid disease name" << name << endl;
            return false;
        }
        transform(name.begin(), name.end(), name.begin(), ::toupper);

        // check if this disease already exists
        if (Disease::exists(this->name))
        {
            // cout << "Disease already exists." << endl;
            return false;
        }

        ofstream file(diseasesFile, ios::app);
        file << toString() << endl;
        file.close();
        // cout << "Disease " << name << " added successfully" << endl;
        return true;
    }

    static bool deleteDisease(string name)
    {
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        ifstream file(diseasesFile);
        string line;
        ofstream temp("temp.csv");
        while (getline(file, line))
        {
            if (Disease::fromString(line).name != name)
            {
                temp << line << endl;
            }
        }
        file.close();
        temp.close();
        remove(diseasesFile);
        rename("temp.csv", diseasesFile);
        cout << "Disease " << name << " deleted successfully" << endl;
        return true;
    }
};