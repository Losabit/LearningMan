#include "BulletManager.hpp"

void BulletManager::manageBullets(Controller* shooter, std::list<IAController*>* ennemies, std::vector<sf::Sprite> walls, sf::RenderWindow* window) {
    std::list<Vector2f> :: iterator it;
    std::list<Vector2f> :: iterator itOrigin;
    std::list<IAController*> :: iterator itEnnemies;
    std::list<int> :: iterator itOrientation;

    for (it = shooter->bullets.begin(), itOrientation = shooter->bulletsOrientation.begin(), itOrigin = shooter->bulletsOrigin.begin();
         it != shooter->bullets.end(); it++, itOrientation++, itOrigin++) {
        if(*itOrientation == 1){
            it->x += shooter->character.bulletSpeed;
        }
        else{
            it->x -= shooter->character.bulletSpeed;
        }
        shooter->character.bullet.setPosition(it->x, it->y);
        shooter->character.bullet.setScale(-*itOrientation, 1);
        window->draw(shooter->character.bullet);
        for (itEnnemies = ennemies->begin(); itEnnemies != ennemies->end(); itEnnemies++) {
            if(shooter->character.id != "healer"){
                if (shooter->character.bullet.getGlobalBounds().intersects(
                        (*itEnnemies)->character.sprite.getGlobalBounds())) {
                    if (!(*itEnnemies)->character.takeDamage(1)) {
                        itEnnemies = ennemies->erase(itEnnemies);
                    }
                    it = shooter->bullets.erase(it);
                    itOrientation = shooter->bulletsOrientation.erase(itOrientation);
                    itOrigin = shooter->bulletsOrigin.erase(itOrigin);
                    continue;
                }
            }

        }

        for(int i = 0; i < walls.size(); i++){
            sf::Rect<float> rectBullet = shooter->character.bullet.getGlobalBounds();
            rectBullet.height -= 5;
            if (rectBullet.intersects(
                    walls.at(i).getGlobalBounds())) {
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);
                continue;
            }
        }

        if (it->x > (itOrigin->x + 2000) || it->x < (itOrigin->x- 2000)) {
            it = shooter->bullets.erase(it);
            itOrigin = shooter->bulletsOrigin.erase(itOrigin);
            itOrientation = shooter->bulletsOrientation.erase(itOrientation);
        }
    }
}

void BulletManager::manageBullets(Controller* shooter, Controller* ennemies, std::vector<sf::Sprite> walls, sf::RenderWindow* window) {
    std::list<Vector2f> :: iterator it;
    std::list<Vector2f> :: iterator itOrigin;
    std::list<int> :: iterator itOrientation;

    for (it = shooter->bullets.begin(), itOrientation = shooter->bulletsOrientation.begin(), itOrigin = shooter->bulletsOrigin.begin();
         it != shooter->bullets.end(); it++, itOrientation++, itOrigin++) {
        if(*itOrientation == 1){
            it->x += shooter->character.bulletSpeed;
        }
        else{
            it->x -= shooter->character.bulletSpeed;
        }
        shooter->character.bullet.setPosition(it->x, it->y);
        shooter->character.bullet.setScale(-*itOrientation, 1);
        window->draw(shooter->character.bullet);

        if (shooter->character.bullet.getGlobalBounds().intersects(
                ennemies->character.sprite.getGlobalBounds())) {
            printf("la");
            if(shooter->character.id != "healer"){
                if (ennemies->character.takeDamage(1)) {
                    // player  mort
                }
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);

            }
            else{
                printf("ici");
                std::cout<<ennemies->character.id << std::endl;
                if(ennemies->character.id != "null"){
                    printf("ici 2");
                    std::cout << ennemies->character.health << std::endl;
                    ennemies->character.takeDamage(-1);
                    std::cout << ennemies->character.health << std::endl;

                }
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);
            }

        }

        for(int i = 0; i < walls.size(); i++){
            sf::Rect<float> rectBullet = shooter->character.bullet.getGlobalBounds();
            rectBullet.height -= 5;
            if (rectBullet.intersects(
                    walls.at(i).getGlobalBounds())) {
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);
                continue;
            }
        }

        if (it->x > (itOrigin->x + 2000) || it->x < (itOrigin->x- 2000)) {
            it = shooter->bullets.erase(it);
            itOrientation = shooter->bulletsOrientation.erase(itOrientation);
        }
    }
}