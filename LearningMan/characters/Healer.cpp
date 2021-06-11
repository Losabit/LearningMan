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
    std::list<std::list<int>> lMov = {{0},{1},
                                      {2},{3},
                                      {4},{5},
                                      {6},{7}};
    textureShoot = TextureManager(CHARACTER_ASSETS_PATH "/healer/heal charge up.png", IntRect(10,45,70,50)
                                  , lMov,91,0);
    /**
     * remove
     */
    textureBullet = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/shotgun blast FX.png", IntRect(0,0,60,30));
    std::list<std::list<int>> lMoving = {{0},{1},
                                         {2},{3},
                                         {4},{5}};
    textureMoving = TextureManager(CHARACTER_ASSETS_PATH "/healer/run.png", IntRect(15, 40, 40, 45),
            lMoving, 91, 0);
    speed = 2;
    id = "healer";
    sprite = textureIdle.toSprite();
    bullet = textureBullet.toSprite();
    gravityDecalage = -15;

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

