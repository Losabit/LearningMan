#ifndef LEARNINGMAN_ENDLEVELVIEW_H
#define LEARNINGMAN_ENDLEVELVIEW_H
#include <SFML/Graphics.hpp>
#include "Button.hpp"

class EndLevelView {
public:
    EndLevelView();
    void draw(sf::RenderWindow* window);
    void setTime(sf::Time time);
    void setKill(int kills);
    sf::Sprite buttonSpriteContinue;

private:
    int timePoints;
    int killsPoints;
    sf::Texture buttonTextureContinue;
    sf::Text buttonTextContinue;
    sf::Font font;
    sf::Text textTime;
    sf::Text textTimeValue;
    sf::Text textTimeEqual;
    sf::Text textTimePoints;
    sf::Text textKills;
    sf::Text textKillsValue;
    sf::Text textKillsEqual;
    sf::Text textKillsPoints;
    sf::Text textTotal;
    sf::Text textTotalEqual;
    sf::Text textTotalPoints;
};


#endif //LEARNINGMAN_ENDLEVELVIEW_H
