#ifndef LEARNINGMAN_SOUNDPLAYER_HPP
#define LEARNINGMAN_SOUNDPLAYER_HPP
#define SOUNDPATH "../assets/sounds/"
#include "SFML/Audio.hpp"

class SoundPlayer {
public:
    SoundPlayer();
    int playSound(std::string filename);
    void setVolume(int value);

private:
    sf::SoundBuffer sb;
    sf::Sound sound;
};


#endif //LEARNINGMAN_SOUNDPLAYER_HPP
