#include "IAController.hpp"

IAController::IAController(Character* character1) : Controller(character1)
{

}

Action IAController::play() {
    return Action::None;
}