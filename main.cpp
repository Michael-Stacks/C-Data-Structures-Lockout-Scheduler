//TP3 – GESTION D’ORDONNANCEMENT


#include <fstream>
#include <iostream>
#include "Device.h"
#include "Machine.h"
#include "Manager.h"
#include "Team.h"

using namespace std;

int main() {
    const unordered_map<int, Device*> devices = Device::BuildDevicesFromJsonFile("./assets/devices.json");
    const unordered_map<int, Machine*> machines = Machine::BuildMachinesFromJsonFile("./assets/machines.json", devices);
    const vector<Team*> teams = Team::BuildTeamsFromJsonFile("./assets/teams.json");

    Manager manager(devices, machines);
    manager.displayNotConnectedDevices();

    manager.setupTeams(teams);

    manager.buildOrganization([](const Machine* m1, const Machine* m2) { return m1->getId() < m2->getId(); });

    return 0;
}
 