#include "Controller.hpp"

Controller::Controller(Character *character1) {
    character = *character1;
}

Action Controller::play(Character ennemie) {
    return Action::None;
}

Action Controller::play() {
    return Action::None;
}