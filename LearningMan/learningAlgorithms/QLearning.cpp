#include "QLearning.hpp"
#include <fstream>
#include <iostream>
#include <dirent.h>

QLearning::QLearning(float alpha1, float epsilon1, float gamma1) {
    if(epsilon1 <= 0.0){
        epsilon1 = 1.0;
    }
    alpha = alpha1;
    epsilon = epsilon1;
    gamma = gamma1;
}

bool QLearning::canPlay() {
    if(actionIteration == canPlayEvery){
        actionIteration = 0;
        return true;
    }
    actionIteration++;
    return false;
}

//0 left / 1 right / 2 jump
void QLearning::debug(float seconds){
    if(debugClock.getElapsedTime().asSeconds() > seconds){
        std::cout << "Q : " << std::endl;
        for(std::map<int, std::map<int, float>>::iterator it = q.begin(); it != q.end(); ++it) {
            std::cout << "State " << it->first << std::endl;
            for(std::map<int, float>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                std::cout << "     Action " << it2->first << " -> " << it2->second << std::endl;
            }
        }
        std::cout << "B : " << std::endl;
        for(std::map<int, std::map<int, float>>::iterator it = b.begin(); it != b.end(); ++it) {
            std::cout << "State " << it->first << std::endl;
            for(std::map<int, float>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                std::cout << "     Action " << it2->first << " -> " << it2->second << std::endl;
            }
        }
        if(saveChosenActions){
            std::cout << "Choosen actions : " << std::endl;
            for(std::map<int, int>::iterator it = chosenActions.begin(); it != chosenActions.end(); ++it) {
                std::cout << "     Action " << it->first << " -> " << it->second << std::endl;
            }
        }
        debugClock.restart();
    }
}

int QLearning::randomChoice(std::map<int, float> probalities){
    float rd = ((double) rand() / (RAND_MAX));
    float probality = 0.0;
    for(std::map<int,float>::iterator it = probalities.begin(); it != probalities.end(); ++it){
        probality += it->second;
        if(probality >= rd && it->second != 0.0){
            return it->first;
        }
    }
    if(probality > 1) {
        std::cout << "error in QLearning random choice return" << std::endl;
    }
    return rand() % probalities.size();
}

PredefineAction QLearning::getAction(int state, int score) {
    if(pi.find(state) == pi.end()) {
        pi.insert(std::pair<int, std::map<int, float>>(state,{}));
        q.insert(std::pair<int, std::map<int, float>>(state,{}));
        b.insert(std::pair<int, std::map<int, float>>(state,{}));
        for(int a = 0; a < numberOfActions; a++) {
            pi[state].insert(std::pair<int, float>(a, 1.0 / numberOfActions));
            q[state].insert(std::pair<int, float>(a, 0.0));
            b[state].insert(std::pair<int, float>(a, 1.0 / numberOfActions));
        }
    }

    int optimal_a;
    float bestValue = 0.0;
    for(int a = 0; a < numberOfActions; a++) {
        if(q[state][a] > bestValue){
            optimal_a = a;
            bestValue = q[state][a];
        }
    }

    for(std::map<int,float>::iterator it = q[state].begin(); it != q[state].end(); ++it) {
        if(it->first == optimal_a){
            b[state][it->first] = 1 - epsilon + epsilon / numberOfActions;
        }
        else{
            b[state][it->first] = epsilon / numberOfActions;
        }
    }

    chosenAction = randomChoice(b[state]);
    scoreBeforeAction = score;
    stateBeforeAction = state;
    //debug
    if(saveChosenActions){
        if(chosenActions.find(chosenAction) == chosenActions.end()){
            chosenActions.insert(std::pair<int, int>(chosenAction,1));
        }
        else{
            chosenActions[chosenAction]++;
        }
    }
    return static_cast<PredefineAction>(chosenAction);
}

void QLearning::getActionReward(int state, int score, bool gameOver) {
    int reward = score - scoreBeforeAction;
    int s_p = state;

    if(gameOver) {
        q[stateBeforeAction][chosenAction] += alpha * (reward + 0.0 - q[stateBeforeAction][chosenAction]);
    }
    else {
        if(pi.find(s_p) == pi.end()) {
            pi.insert(std::pair<int, std::map<int, float>>(s_p,{}));
            q.insert(std::pair<int, std::map<int, float>>(s_p,{}));
            b.insert(std::pair<int, std::map<int, float>>(s_p,{}));
            for(int a = 0; a < numberOfActions; a++) {
                pi[s_p].insert(std::pair<int, float>(a, 1.0 / numberOfActions));
                q[s_p].insert(std::pair<int, float>(a, 0.0));
                b[s_p].insert(std::pair<int, float>(a, 1.0 / numberOfActions));
            }
        }
        float bestQ;
        for(std::map<int,float>::iterator it = q[s_p].begin(); it != q[s_p].end(); ++it){
            if(it == q[s_p].begin()){
                bestQ = it->second;
            }
            else if(it->second > bestQ){
                bestQ = it->second;
            }
        }
        q[stateBeforeAction][chosenAction] += alpha * (reward + gamma * bestQ - q[stateBeforeAction][chosenAction]);
    }
}

PolicyAndActionValueFunction QLearning::compile() {
    for(std::map<int, std::map<int, float>>::iterator it = q.begin(); it != q.end(); ++it) {
        int optimal_a;
        float bestValue = 0.0;
        for(std::map<int, float>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if(it2->second > bestValue){
                optimal_a = it2->first;
                bestValue = it2->second;
            }
        }
        for(std::map<int, float>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if(it2->first == optimal_a){
                pi[it->first][it2->first] = 1.0;
            }
            else{
                pi[it->first][it2->first] = 0.0;
            }
        }
    }
    return PolicyAndActionValueFunction{.pi =  pi, .q =  q};
}

void QLearning::save(PolicyAndActionValueFunction policyAndActionValueFunction) {
    DIR *dir;
    struct dirent *ent;
    int it = -2;
    if ((dir = opendir("../ressources/policyAndActionValueFunction")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            it++;
        }
        closedir (dir);
    } else {
       std::cout << "directory not find" << std::endl;
       return;
    }
    std::ofstream outfile;
    outfile.open("../ressources/policyAndActionValueFunction/model_" + std::to_string(it) + ".txt");
    for(std::map<int, std::map<int, float>>::iterator it = policyAndActionValueFunction.q.begin(); it != policyAndActionValueFunction.q.end(); ++it) {
        outfile << it->first << ":{";
        for(std::map<int, float>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            outfile << it2->first << ":" << it2->second;
        }
        outfile << "};";
    }
    outfile << std::endl;
    for(std::map<int, std::map<int, float>>::iterator it = policyAndActionValueFunction.pi.begin(); it != policyAndActionValueFunction.pi.end(); ++it) {
        outfile << it->first << ":{";
        for(std::map<int, float>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            outfile << it2->first << ":" << it2->second;
        }
        outfile << "};";
    }
    outfile << std::endl;
    outfile.close();
}