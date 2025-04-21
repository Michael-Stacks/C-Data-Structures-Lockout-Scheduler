#pragma once

#ifndef DEVICE_H
#define DEVICE_H
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Device {
private:
    int id;
    string type;
    string name;
public:
    Device(const int id, const string& type, const string& name);

    int getId() const { return id; }
    string getType() const { return type; }
    string getName() const { return name; }

    static unordered_map<int, Device*> BuildDevicesFromJsonFile(const string& path);
};

#endif 
