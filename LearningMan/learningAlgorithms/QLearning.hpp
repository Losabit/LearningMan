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
    PredefineAction getAction(int state, int score, std::vector<int> availableActions);
    PredefineAction getBestAction(int state, int score, std::vector<int> availableActions);
    void getActionReward(int state, int score, bool gameOver);
    bool canPlay();
    void debug(float seconds);
    void loadModel(PolicyAndActionValueFunction model);
    PolicyAndActionValueFunction compile();
    static void save(PolicyAndActionValueFunction policyAndActionValueFunction, PolicyAndActionValueFunction policyAndActionValueFunctionBoss);
    static std::vector<PolicyAndActionValueFunction> loadFromFile(std::string fileName);
    static std::string getModel(PolicyAndActionValueFunction policyAndActionValueFunction, PolicyAndActionValueFunction policyAndActionValueFunctionBoss);

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
    int randomChoice(std::map<int, float> probalities, std::vector<int> availableActions);
    static std::string mapToString(std::map<int, std::map<int, float>> parameter);
    static std::map<int, std::map<int, float>> stringToMap(std::string parameter);
};


#endif //LEARNINGMAN_QLEARNING_HPP