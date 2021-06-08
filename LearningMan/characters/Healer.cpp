//
// Created by Mirii on 04/06/2021.
//

#include "Healer.h"
#include "../define.hpp"
Healer::Healer(): Character() {
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/healer/idle.png", IntRect(10,45,60,60));
   /**
    * Modifié la texture de hit
    */
    std::list<std::list<int>> lMov = {{0},
                                         {1},
                                         {2}};
    textureShoot = TextureManager(CHARACTER_ASSETS_PATH "/healer/heal charge up.png", IntRect(10,90,60,60),lMov,35,0);
    /**
     * remove
     */
    textureBullet = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/shotgun blast FX.png", IntRect(0,0,60,30));
    std::list<std::list<int>> lMoving = {{0},{1},
                                         {2},{3},
                                         {4},{5},
                                         {6},{7}};
    textureMoving = TextureManager(CHARACTER_ASSETS_PATH "/healer/run.png", IntRect(0, 0, 40, 33),
            lMoving, 35, 0);
    speed = 2;
    id = "healer";
    sprite = textureIdle.toSprite();
    bullet = textureBullet.toSprite();


}

void Healer::heal(Controller *shooter, std::list<IAController *> *ennemies) {
    std::list<Vector2f> :: iterator it;
    std::list<Vector2f> :: iterator itOrigin;
    std::list<IAController*> :: iterator itEnnemies;
    std::list<int> :: iterator itOrientation;

    for(itEnnemies = ennemies->begin();itEnnemies != ennemies->end();itEnnemies++){
        if(shooter->character.sprite.getGlobalBounds().intersects((*itEnnemies)->character.sprite.getGlobalBounds())){
            (*itEnnemies)->character.takeDamage(-1);

        }
    }
}

