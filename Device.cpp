#include "Device.h"
#include <fstream>
#include <iostream>
#include "include/json.hpp"

using json = nlohmann::json;
using namespace std;

Device::Device(const int id, const string& type, const string& name)
    : id(id), type(type), name(name) {
}

unordered_map<int, Device*> Device::BuildDevicesFromJsonFile(const string& path) {
    unordered_map<int, Device*> devicesMap;
    ifstream file(path);
    if (!file) {
        cerr << "Error: Unable to open file: " << path << endl;
        return devicesMap;
    }
    json j;
    file >> j;
    for (const auto& dev : j["devices"]) {
        int id = dev["id"];
        string type = dev["type"];
        string name = dev["name"];
        devicesMap[id] = new Device(id, type, name);
    }
    return devicesMap;
}
