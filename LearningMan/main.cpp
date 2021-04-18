#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    RenderWindow w(VideoMode(800, 600), "test");
    sleep(milliseconds(2000));
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
