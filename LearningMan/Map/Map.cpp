//
// Created by Mirii on 20/04/2021.
//

#include "Map.h"
using namespace std;
using namespace sf;

Map::Map(){

    backgroundMoon = loadBackground(backgroundTextureMoon,430,0,90,90,950,6, false);
    backgroundCloud = loadBackground(backgroundTextureCloud,400,210,120,60,900,40, false);
    /*
     *
     * Voir ou on la place car bizarre
     */
 /*
  * ADD MOUTAIN TO BACKGROUND
  * ZOOOM
  */
 backgroundMoutain = loadBackground(backgroundTextureMoutain,250,175,180,38,150,85, false);
   backgroundMoutain.setScale(4,2);
    backgroundGround = loadBackground(backgroundTexutreGround,250,105,300,38,-60,600,true);
    backgroundGround2 = loadBackground(backgroundTexutreGround2,250,105,300,38,30,600,true);
    addWall();

}
/**
 * FUNCTION TO LOAD BACKGROUND
 * @param spriteTexture
 * @param rl
 * @param rt
 * @param rw
 * @param rh
 * @param x
 * @param y
 * @param repeat
 * @return
 */
Sprite Map::loadBackground( sf::Texture &spriteTexture,int rl, int rt , int  rw,  int rh, int x , int y,bool repeat){
    Sprite bg;
    if (!spriteTexture.loadFromFile("../assets/map/Dungeon_Ruins_Tileset/Dungeon Ruins Tileset Day.png",sf::IntRect(rl,rt,rw,rh)))
    {
        cout << "Erreur durant le chargement de la texture." << endl;
    }
    else {
        spriteTexture.setRepeated(repeat);
        bg.setTexture(spriteTexture);
        if(repeat){
            bg.setTextureRect({100,0,2000,30});
        }
        bg.setPosition(x, y);
    }
    return bg;
}
void Map::addWall(){
    // TEST WALL POSITION

    /**
     * TODO: Preparer la génération aléatoire
     */
    bigWall = loadBackground(TextureBigWall,0,0,WALL_SIZE,WALL_SIZE,100,65, false);
}

void Map::drawBackground(RenderWindow &window)
{
    window.draw(backgroundMoon);
    window.draw(backgroundCloud);
    window.draw(backgroundMoutain);
    window.draw(backgroundGround);
    window.draw(backgroundGround2);
    window.draw(this->bigWall);
}