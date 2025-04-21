#pragma once

#ifndef TEAM_H
#define TEAM_H
#include <fstream>
#include <string>
#include <vector>
#include "include/json.hpp"

using nlohmann::json;
using namespace std;

class Team {
private:
    string name;
    vector<string> capabilities;
public:
    Team(const string& name, const vector<string>& capabilities);

    string getName() const {
        return name;
    }

    vector<string> getCapabilities() const {
        return capabilities;
    }

    static vector<Team*> BuildTeamsFromJsonFile(const string& filename);
};

#endif 
