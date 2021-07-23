#include "Environment.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Environment::Environment(sf::Vector2f initialPosition1, sf::Vector2f portalPosition1){
    initialPosition = initialPosition1;
    portalPosition = portalPosition1;
}

int Environment::getReward(sf::Vector2f position, int newHealth){
    //std::cout << "reward " << (int)((position.x - initialPosition.x) / lagForReward) << std::endl;
    //(int)((position.x - initialPosition.x) / lagForReward);
    int healthDifference = health - newHealth;
    if(healthDifference != 0){
        health = newHealth;
    }
    return (int)((position.x - initialPosition.x) / lagXForReward + (initialPosition.y - position.y) / lagYForReward
    + healthDifference * loseHealthReward);
}

int Environment::getReward(sf::Vector2f position){
    return (int)((position.x - initialPosition.x) / lagXForReward + (initialPosition.y - position.y) / lagYForReward);
}

int Environment::getState(sf::Vector2f position){
    int availablesXStates = (portalPosition.x - initialPosition.x) / sizeXState;
    int xState = (position.x - initialPosition.x) / sizeXState;
    int yState = (initialPosition.y - position.y) / sizeYState;
    return (int)(xState + availablesXStates * yState);
}

void Environment::drawStateCases(sf::RenderWindow* window, sf::View view){
    drawCases(window, view, sizeXState, sizeYState, sf::Color::Red);
}

void Environment::drawRewardCases(sf::RenderWindow *window, sf::View view) {
    drawCases(window, view, lagXForReward, lagYForReward, sf::Color::Blue);
}

void Environment::drawCases(sf::RenderWindow* window, sf::View view, float xLag, float yLag, sf::Color color){
    //y center +- 120
    //x center +- 200
    int xLimit = 200;
    int yLimit = 120;
    int start = (view.getCenter().x - xLimit - initialPosition.x) / xLag;
    int end =  (view.getCenter().x + xLimit - initialPosition.x) / xLag;
    for(int i = start; i < end; i++) {
        sf::Vertex line[2];
        line[0].position = sf::Vector2f(i * xLag + initialPosition.x, view.getCenter().y - yLimit);
        line[0].color = color;
        line[1].position = sf::Vector2f(i * xLag + initialPosition.x, view.getCenter().y + yLimit);
        line[1].color = color;
        window->draw(line, 2, sf::Lines);
    }

    start = (view.getCenter().y - yLimit - initialPosition.y) / yLag;
    end =  (view.getCenter().y + yLimit - initialPosition.y) / yLag;
    for(int i = start; i < end; i++) {
        sf::Vertex line[2];
        line[0].position = sf::Vector2f(view.getCenter().x - xLimit, i * yLag + initialPosition.y);
        line[0].color = color;
        line[1].position = sf::Vector2f(view.getCenter().x + xLimit, i * yLag + initialPosition.y);
        line[1].color = color;
        window->draw(line, 2, sf::Lines);
    }
}
