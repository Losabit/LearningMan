#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.hpp"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LearningMan");
    window.setFramerateLimit(60);


    View viewBack(FloatRect(0.f, 0.f, 800, 700));
    Vector2f oldViewPos(viewBack.getCenter());



    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
