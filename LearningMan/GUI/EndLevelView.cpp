#include "EndLevelView.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../define.hpp"

EndLevelView::EndLevelView() {
    if(!font.loadFromFile("../ressources/policy/OrelegaOne-Regular.ttf")){
        std::cout << "font not find" << std::endl;
    }

    buttonTextureContinue.loadFromFile("../assets/button/simple/12.png");
    buttonSpriteContinue = sf::Sprite(buttonTextureContinue,  sf::IntRect(40, 140, 480, 200));
    buttonTextContinue.setFont(font);
    buttonSpriteContinue.setScale(0.5, 0.5);
    buttonTextContinue.setCharacterSize(24);
    buttonTextContinue.setFillColor(sf::Color::White);
    buttonTextContinue.setPosition(450, 480);
    buttonTextContinue.setString("Continue");
    buttonSpriteContinue.setPosition(sf::Vector2f(400, 450));

    textTime.setFont(font);
    textTime.setCharacterSize(24);
    textTime.setFillColor(sf::Color::White);
    textTime.setPosition(200, 150);
    textTime.setString("Time");

    textTimeValue.setFont(font);
    textTimeValue.setCharacterSize(24);
    textTimeValue.setFillColor(sf::Color::White);
    textTimeValue.setPosition(450, 150);
    textTimeValue.setString("0 sec");

    textTimeEqual.setFont(font);
    textTimeEqual.setCharacterSize(24);
    textTimeEqual.setFillColor(sf::Color::White);
    textTimeEqual.setPosition(650, 150);
    textTimeEqual.setString("=");

    textTimePoints.setFont(font);
    textTimePoints.setCharacterSize(24);
    textTimePoints.setFillColor(sf::Color::White);
    textTimePoints.setPosition(700, 150);
    textTimePoints.setString("0 pts");

    textKills.setFont(font);
    textKills.setCharacterSize(24);
    textKills.setFillColor(sf::Color::White);
    textKills.setPosition(200, 250);
    textKills.setString("Kills");

    textKillsValue.setFont(font);
    textKillsValue.setCharacterSize(24);
    textKillsValue.setFillColor(sf::Color::White);
    textKillsValue.setPosition(450, 250);
    textKillsValue.setString("0");

    textKillsEqual.setFont(font);
    textKillsEqual.setCharacterSize(24);
    textKillsEqual.setFillColor(sf::Color::White);
    textKillsEqual.setPosition(650, 250);
    textKillsEqual.setString("=");

    textKillsPoints.setFont(font);
    textKillsPoints.setCharacterSize(24);
    textKillsPoints.setFillColor(sf::Color::White);
    textKillsPoints.setPosition(700, 250);
    textKillsPoints.setString("0 pts");

    textTotal.setFont(font);
    textTotal.setCharacterSize(24);
    textTotal.setFillColor(sf::Color::White);
    textTotal.setPosition(200, 350);
    textTotal.setString("Total");

    textTotalEqual.setFont(font);
    textTotalEqual.setCharacterSize(24);
    textTotalEqual.setFillColor(sf::Color::White);
    textTotalEqual.setPosition(650, 350);
    textTotalEqual.setString("=");

    textTotalPoints.setFont(font);
    textTotalPoints.setCharacterSize(24);
    textTotalPoints.setFillColor(sf::Color::White);
    textTotalPoints.setPosition(700, 350);
    textTotalPoints.setString("0 pts");
}

void EndLevelView::setTime(sf::Time time) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << time.asSeconds();
    std::string s = stream.str();

    textTimeValue.setString(s + " sec");
    timePoints = time.asSeconds() > MAX_LEVEL_TIME ? 0 : (MAX_LEVEL_TIME - time.asSeconds()) * POINTS_BY_SECOND;
    textTimePoints.setString(std::to_string(timePoints));
    textTotalPoints.setString(std::to_string(killsPoints + timePoints));
}

void EndLevelView::setKill(int kills) {
    textKillsValue.setString(std::to_string(kills));
    textKillsPoints.setString(std::to_string(kills * POINTS_BY_KILL));
    killsPoints = kills * POINTS_BY_KILL;
    textTotalPoints.setString(std::to_string(killsPoints + timePoints));
}

void EndLevelView::draw(sf::RenderWindow* window) {
    window->draw(textTime);
    window->draw(textTimeValue);
    window->draw(textTimeEqual);
    window->draw(textTimePoints);
    window->draw(textKills);
    window->draw(textKillsValue);
    window->draw(textKillsEqual);
    window->draw(textKillsPoints);
    window->draw(textTotal);
    window->draw(textTotalEqual);
    window->draw(textTotalPoints);

    window->draw(buttonSpriteContinue);
    window->draw(buttonTextContinue);
}