#ifndef LEARNINGMAN_QLEARNING_HPP
#define LEARNINGMAN_QLEARNING_HPP
#include <map>
#include "../controllers/PredefineController.hpp"

struct PolicyAndActionValueFunction {
    std::map<int, std::map<int, float>> pi;
    std::map<int, std::map<int, float>> q;
};


class QLearning {
public:
    QLearning(float alpha1, float epsilon1, float gamma1);
    PredefineAction getAction(int state, int score);
    void getActionReward(int state, int score, bool gameOver);
    bool canPlay();
    void debug(float seconds);
    PolicyAndActionValueFunction compile();
    void save(PolicyAndActionValueFunction policyAndActionValueFunction);

private:
    const static int canPlayEvery = 0;
    const static bool saveChosenActions = true;
    std::map<int, int> chosenActions;
    float alpha;
    float epsilon;
    float gamma;
    std::map<int, std::map<int, float>> pi;
    std::map<int, std::map<int, float>> q;
    std::map<int, std::map<int, float>> b;
    int numberOfActions = 7;
    int scoreBeforeAction;
    int stateBeforeAction;
    int chosenAction;
    sf::Clock debugClock;
    int actionIteration = 0;
    int randomChoice(std::map<int, float> probalities);
};


#endif //LEARNINGMAN_QLEARNING_HPP