#include <cstring>
#include "SoundPlayer.hpp"
#include "SFML/Audio.hpp"

SoundPlayer::SoundPlayer() {
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    this->sb = soundBuffer;
    this->sound = sound;
    this->sound.setVolume(30);
}

int SoundPlayer::playSound(std::string filename){
    std::string path = SOUNDPATH;
    path.append(filename);

    if(!this->sb.loadFromFile(path)){
        return -1;
    }
    this->sb.loadFromFile(path);
    this->sound.setBuffer(this->sb);
    this->sound.play();

    return 0;
}

void SoundPlayer::setVolume(int value){
    this->sound.setVolume(value % 101);
}