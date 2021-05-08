#include "Map.h"
using namespace std;
using namespace sf;
/**
 * Map génération
 */
Map::Map(){
    backgroundMoon = loadBackground(backgroundTextureMoon,430,0,90,90,950,15, false);
    backgroundMoon.setScale(2,2);
    backgroundCloud = loadBackground(backgroundTextureCloud,400,210,120,60,900,75, false);
    backgroundCloud.setScale(1.5,1.5);
    backgroundGround = loadBackground(backgroundTexutreGround,250,105,300,38,-60,118,true);
    backgroundGround2 = loadBackground(backgroundTexutreGround2,250,105,300,38,30,118,true);
    backgroundMoutain = loadBackground(backgroundTextureMoutain,250,175,180,38,430,545, false);
    backgroundMoutain.setScale(4,2);
    backgroundGround = loadBackground(backgroundTexutreGround,250,105,300,38,-60,600,true);
    backgroundGround2 = loadBackground(backgroundTexutreGround2,250,105,300,38,30,600,true);
    platform = loadBackground(texturePlatform,15,78,50,20,400,550, false);
    platform.setScale(1.2,1.2);
    addWall(100,560);
    addWall(150,560);
    //addWall(150,510);
    addWall(250,560);
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
void Map::addWall(float x, float y){
    // TEST WALL POSITION

    /**
     * TODO: Preparer la génération aléatoire
     */
    walls.push_back(loadBackground(TextureBigWall,15,15,WALL_SIZE,WALL_SIZE, x, y, false));

}

void Map::drawBackground(RenderWindow &window)
{
    window.draw(backgroundMoutain);
    window.draw(backgroundMoon);
    window.draw(backgroundCloud);
    window.draw(backgroundGround);
    window.draw(backgroundGround2);
    for(int i = 0; i < walls.size(); i++) {
        window.draw(walls.at(i));
    }
    window.draw(platform);
}