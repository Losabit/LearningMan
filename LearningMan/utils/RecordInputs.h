#ifndef LEARNINGMAN_RECORDINPUTS_H
#define LEARNINGMAN_RECORDINPUTS_H
#include <iostream>
#include <vector>
#include "../controllers/PredefineController.hpp"

class RecordInputs {
public:
    static void save(std::vector<int> actions);
    static std::vector<int> load(std::string path);
};


#endif //LEARNINGMAN_RECORDINPUTS_H
