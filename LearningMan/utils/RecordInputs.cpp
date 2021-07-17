#include "RecordInputs.h"
#include <fstream>

void RecordInputs::save(std::vector<int> actions){
    std::string os;
    for (int i = 0; i < actions.size(); i++) {
        if(i != actions.size() - 1) {
            os += std::to_string(actions.at(i)) + ",";
        }
        else{
            os += std::to_string(actions.at(i));
        }
    }
    std::ofstream myfile;
    myfile.open ("../ressources/learning/logs/1/1.json");
    myfile << os;
    myfile.close();
}

std::vector<int> RecordInputs::load(std::string path){
    std::string os;
    std::ifstream myfile(path);
    std::getline(myfile, os);

    size_t pos = 0;
    std::string token;
    std::vector<int> actions;
    while ((pos = os.find(",")) != std::string::npos) {
        token = os.substr(0, pos);
        actions.push_back(stoi(token));
        os.erase(0, pos + 1);
    }
    return actions;
}