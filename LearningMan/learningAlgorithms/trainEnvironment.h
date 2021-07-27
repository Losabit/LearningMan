//
// Created by quent on 26/07/2021.
//

#ifndef LEARNINGMAN_TRAINENVIRONMENT_H
#define LEARNINGMAN_TRAINENVIRONMENT_H
#include "QLearning.hpp"
class TrainEnvironment{
public:
    TrainEnvironment();
    void train();
    QLearning model;
    QLearning modelBoss;
};
#endif //LEARNINGMAN_TRAINENVIRONMENT_H
