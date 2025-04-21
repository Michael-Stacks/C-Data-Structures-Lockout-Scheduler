#include "Manager.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

Manager::Manager(const unordered_map<int, Device*>& devices, const unordered_map<int, Machine*>& machines)
    : devices(devices), machines(machines) {
}

void Manager::displayNotConnectedDevices() {
    unordered_set<int> usedDevices;
    for (auto& pair : machines) {
        Machine* machine = pair.second;
        vector<Device*> devList = machine->getRelatedDevices();
        for (Device* dev : devList) {
            usedDevices.insert(dev->getId());
        }
    }
    cout << "Devices not connected to any machine:" << endl;
    for (auto& pair : devices) {
        if (usedDevices.find(pair.first) == usedDevices.end()) {
            cout << " - Device " << pair.first << " (" << pair.second->getName() << ")" << endl;
        }
    }
    cout << endl;
}

void Manager::setupTeams(const vector<Team*>& teams) {
    this->teams = teams;
    cout << "Teams available:" << endl;
    for (Team* team : teams) {
        cout << " - Team " << team->getName() << " (capabilities: ";
        vector<string> caps = team->getCapabilities();
        for (size_t i = 0; i < caps.size(); ++i) {
            cout << caps[i];
            if (i < caps.size() - 1) cout << ", ";
        }
        cout << ")" << endl;
    }
    cout << endl;
}

void Manager::buildOrganization(const function<bool(const Machine*, const Machine*)>& comparator) {
    // Tri des machines selon le comparateur
    vector<Machine*> orderedMachines;
    for (auto& pair : machines) {
        orderedMachines.push_back(pair.second);
    }
    sort(orderedMachines.begin(), orderedMachines.end(), comparator);

    // Première sortie : liste des machines
    cout << "Machines to be locked:" << endl;
    for (Machine* m : orderedMachines) {
        cout << " - " << m->getId() << " : " << m->getName() << endl;
    }
    cout << endl;

    unordered_set<int> lockedDevices;
    unordered_map<int, Team*> deviceLockedBy;

    // Deuxième sortie : par machine
    cout << "OUTPUT (by Machine) :" << endl;
    for (Machine* m : orderedMachines) {
        cout << "Machine " << m->getId() << " : " << m->getName() << endl;
        for (Device* d : m->getRelatedDevices()) {
            int deviceId = d->getId();
            if (lockedDevices.find(deviceId) != lockedDevices.end()) {
                cout << "  - Device " << deviceId << " ( " << d->getName() << " ) already locked out." << endl;
            }
            else {
                // Rechercher une équipe compétente
                Team* assignedTeam = nullptr;
                for (Team* team : teams) {
                    vector<string> caps = team->getCapabilities();
                    if (find(caps.begin(), caps.end(), d->getType()) != caps.end()) {
                        assignedTeam = team;
                        break;
                    }
                }
                if (assignedTeam) {
                    lockedDevices.insert(deviceId);
                    deviceLockedBy[deviceId] = assignedTeam;
                    cout << "  - Device " << deviceId << " ( " << d->getName() << " ) locked out by Team " << assignedTeam->getName() << endl;
                }
                else {
                    cout << "  - Device " << deviceId << " ( " << d->getName() << " ) cannot be locked - no team available" << endl;
                }
            }
        }
        cout << endl;
    }

    // Troisième sortie : par équipe
    cout << "OUTPUT (by Team) :" << endl;
    unordered_map<string, vector<pair<int, string>>> teamDevices;
    for (auto& pair : deviceLockedBy) {
        int deviceId = pair.first;
        Team* team = pair.second;
        teamDevices[team->getName()].push_back({ deviceId, devices.at(deviceId)->getName() });
    }
    for (Team* team : teams) {
        cout << " - Team " << team->getName() << " :" << endl;
        if (teamDevices.find(team->getName()) != teamDevices.end()) {
            for (auto& p : teamDevices[team->getName()]) {
                cout << "  -- " << p.first << " => " << p.second << endl;
            }
        }
        cout << endl;
    }
}
