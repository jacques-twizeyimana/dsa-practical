#include <iostream>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

// define constants
#define locationsFile "locations.csv"

class Location
{
public:
    int id;
    string name;

    Location() {}
    Location(int id, string name)
    {
        this->id = id;
        this->name = name;
    }
    Location(string name)
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

    static Location fromString(string str)
    {
        stringstream ss(str);
        string id, name;
        getline(ss, id, ',');
        getline(ss, name);
        return Location(stoi(id), name);
    }

    static vector<Location> fromFile()
    {

        vector<Location> locations;
        ifstream file(locationsFile);
        string line;
        while (getline(file, line))
        {
            locations.push_back(Location::fromString(line));
        }
        return locations;
    }

    static bool exists(string name)
    {
        for (Location location : Location::fromFile())
        {
            if (location.name == name)
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
            cout << "Invalid location name" << name << endl;
            return false;
        }
        transform(name.begin(), name.end(), name.begin(), ::toupper);

        // check if this location already exists
        if (Location::exists(this->name))
        {
            cout << "Location already exists." << endl;
            return false;
        }

        ofstream file(locationsFile, ios::app);
        file << toString() << endl;
        file.close();
        cout << "Location " << name << " added successfully" << endl;
        return true;
    }

    static bool deleteLocation(string name)
    {
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        ifstream file(locationsFile);
        string line;
        ofstream temp("temp.csv");
        while (getline(file, line))
        {
            if (Location::fromString(line).name != name)
            {
                temp << line << endl;
            }
        }
        file.close();
        temp.close();
        remove(locationsFile);
        rename("temp.csv", locationsFile);
        cout << "Location " << name << " deleted successfully" << endl;
        return true;
    }
};