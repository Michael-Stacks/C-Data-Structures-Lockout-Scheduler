#include "Team.h"
#include <fstream>
#include <iostream>
#include "include/json.hpp"

using json = nlohmann::json;
using namespace std;

Team::Team(const string& name, const vector<string>& capabilities)
    : name(name), capabilities(capabilities) {
}

vector<Team*> Team::BuildTeamsFromJsonFile(const string& filename) {
    vector<Team*> teams;
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return teams;
    }
    json j;
    file >> j;
    for (const auto& t : j["teams"]) {
        string name = t["name"];
        vector<string> caps = t["capabilities"].get<vector<string>>();
        teams.push_back(new Team(name, caps));
    }
    return teams;
}
