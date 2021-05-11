#include "BulletManager.hpp"

void BulletManager::manageBullets(Controller* shooter, std::list<IAController*>* ennemies, sf::RenderWindow* window) {
    std::list<Vector2f> :: iterator it;
    std::list<IAController*> :: iterator itEnnemies;
    std::list<int> :: iterator itOrientation;

    for (it = shooter->bullets.begin(), itOrientation = shooter->bulletsOrientation.begin();
         it != shooter->bullets.end(); it++, itOrientation++) {
        if(*itOrientation == 1){
            it->x += shooter->character.bulletSpeed;
        }
        else{
            it->x -= shooter->character.bulletSpeed;
        }
        shooter->character.bullet.setPosition(it->x, it->y);
        window->draw(shooter->character.bullet);
        for (itEnnemies = ennemies->begin(); itEnnemies != ennemies->end(); itEnnemies++) {
            if (shooter->character.bullet.getGlobalBounds().intersects(
                    (*itEnnemies)->character.sprite.getGlobalBounds())) {
                if (!(*itEnnemies)->character.takeDamage(1)) {
                    itEnnemies = ennemies->erase(itEnnemies);
                }
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);
            }
        }
        if (it->x > 800 || it->x < -200) {
            it = shooter->bullets.erase(it);
            itOrientation = shooter->bulletsOrientation.erase(itOrientation);
        }
    }
}

void BulletManager::manageBullets(Controller* shooter, Controller* ennemies, sf::RenderWindow* window) {
    std::list<Vector2f> :: iterator it;
    std::list<int> :: iterator itOrientation;

    for (it = shooter->bullets.begin(), itOrientation = shooter->bulletsOrientation.begin();
    it != shooter->bullets.end(); it++, itOrientation++) {
        if(*itOrientation == 1){
            it->x += shooter->character.bulletSpeed;
        }
        else{
            it->x -= shooter->character.bulletSpeed;
        }
        shooter->character.bullet.setPosition(it->x, it->y);
        window->draw(shooter->character.bullet);

        if (shooter->character.bullet.getGlobalBounds().intersects(
                ennemies->character.sprite.getGlobalBounds())) {
            if (ennemies->character.takeDamage(1)) {
                // player  mort
            }
            it = shooter->bullets.erase(it);
            itOrientation = shooter->bulletsOrientation.erase(itOrientation);
        }
        if (it->x > 800 || it->x < -200) {
            it = shooter->bullets.erase(it);
            itOrientation = shooter->bulletsOrientation.erase(itOrientation);
        }
    }
}