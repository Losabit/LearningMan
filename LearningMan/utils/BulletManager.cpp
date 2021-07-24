#include "BulletManager.hpp"

void BulletManager::manageBullets(Controller* shooter, std::list<IAController*>* ennemies, std::vector<sf::Sprite> walls, sf::RenderWindow* window) {
    std::list<Vector2f> :: iterator it;
    std::list<Vector2f> :: iterator itOrigin;
    std::list<IAController*> :: iterator itEnnemies;
    std::list<int> :: iterator itOrientation;
    //std::cout << "1 : " << shooter->bullets.size() << " / " << shooter->bulletsOrientation.size() << " / " << shooter->bulletsOrigin.size() << std::endl;

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
            if (shooter->character.bullet.getGlobalBounds().intersects(
                    (*itEnnemies)->character.sprite.getGlobalBounds())) {
                if (!(*itEnnemies)->character.takeDamage(1)) {
                    itEnnemies = ennemies->erase(itEnnemies);
                }
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);
                itOrigin = shooter->bulletsOrigin.erase(itOrigin);
                if(it == shooter->bullets.end()){
                    break;
                }
            }
        }

        if(it == shooter->bullets.end()){
            break;
        }

        for(int i = 0; i < walls.size(); i++){
            sf::Rect<float> rectBullet = shooter->character.bullet.getGlobalBounds();
            rectBullet.height -= 5;
            if (rectBullet.intersects(
                    walls.at(i).getGlobalBounds())) {
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);
                itOrigin = shooter->bulletsOrigin.erase(itOrigin);
                if(it == shooter->bullets.end()){
                    break;
                }
            }
        }

        if(it == shooter->bullets.end()){
            break;
        }

        if (it->x > (itOrigin->x + bulletScope) || it->x < (itOrigin->x- bulletScope)) {
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
    //std::cout << "2 : " << shooter->bullets.size() << " / " << shooter->bulletsOrientation.size() << " / " << shooter->bulletsOrigin.size() << std::endl;

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
            if(shooter->character.id != "healer"){
                if (ennemies->character.takeDamage(1)) {
                    // player  mort
                }
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);
                itOrigin = shooter->bulletsOrigin.erase(itOrigin);

            }
            else{
                if(ennemies->character.id != "null"){
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

        if (it->x > (itOrigin->x + bulletScope) || it->x < (itOrigin->x - bulletScope)) {
            it = shooter->bullets.erase(it);
            itOrientation = shooter->bulletsOrientation.erase(itOrientation);
        }
    }
}

void BulletManager::manageBullets(Controller* shooter, BossController* ennemies, std::vector<sf::Sprite> walls, sf::RenderWindow* window) {
    std::list<Vector2f> :: iterator it;
    std::list<Vector2f> :: iterator itOrigin;
    std::list<int> :: iterator itOrientation;

    //std::cout << "3 : " << shooter->bullets.size() << " / " << shooter->bulletsOrientation.size() << " / " << shooter->bulletsOrigin.size() << std::endl;
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
                ennemies->character.takeDamage(1);
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);
                itOrigin = shooter->bulletsOrigin.erase(itOrigin);
                continue;
        }

        for(int i = 0; i < walls.size(); i++){
            sf::Rect<float> rectBullet = shooter->character.bullet.getGlobalBounds();
            rectBullet.height -= 5;
            if (rectBullet.intersects(
                    walls.at(i).getGlobalBounds())) {
                it = shooter->bullets.erase(it);
                itOrientation = shooter->bulletsOrientation.erase(itOrientation);
                itOrigin = shooter->bulletsOrigin.erase(itOrigin);
                continue;
            }
        }

        if (it->x > (itOrigin->x + bulletScope) || it->x < (itOrigin->x - bulletScope)) {
            it = shooter->bullets.erase(it);
            itOrientation = shooter->bulletsOrientation.erase(itOrientation);
            itOrigin = shooter->bulletsOrigin.erase(itOrigin);
            continue;
        }
    }
}