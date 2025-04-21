#include "Machine.h"
#include <fstream>
#include <iostream>
#include "include/json.hpp"
#include <vector>
#include <unordered_map>
#include <algorithm>

using json = nlohmann::json;
using namespace std;

Machine::Machine(const int id, const string& name) : id(id), name(name) {}

vector<Device*> Machine::getRelatedDevices() const {
    return related_devices;
}

unordered_map<int, Machine*> Machine::BuildMachinesFromJsonFile(const string& path, const unordered_map<int, Device*>& devices) {
    unordered_map<int, Machine*> machinesMap;
    ifstream file(path);
    if (!file) {
        cerr << "Error: Unable to open file: " << path << endl;
        return machinesMap;
    }
    json j;
    file >> j;
    for (const auto& m : j["machines"]) {
        int id = m["id"];
        string name = m["name"];
        Machine* machine = new Machine(id, name);
        for (const auto& devId : m["related_devices"]) {
            int idDevice = devId;
            if (devices.find(idDevice) != devices.end()) {
                machine->related_devices.push_back(devices.at(idDevice));
            }
        }
        machinesMap[id] = machine;
    }
    return machinesMap;
}
