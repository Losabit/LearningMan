#ifndef LEARNINGMAN_MAPMODEL_HPP
#define LEARNINGMAN_MAPMODEL_HPP

#include "../lib/json/json.h"
#include "../utils/CollisionManager.hpp"

class Colors {
public:
    Colors();
    Colors(Json::Value root);
    int red;
    int green;
    int blue;
    int alpha;
};

class ObjectReference {
public:
    ObjectReference(Json::Value root);
    int id;
    int top;
    int left;
    int width;
    int height;
    ObjectType type;
};

class Ennemie {
public:
    Ennemie();
    Ennemie(Json::Value root);
    std::string id;
    int positionX;
    int positionY;
};



class Boss {
public:
    Boss(){};
    Boss(Json::Value root);

    class BossCharacter {
    public:
        BossCharacter(){};
        BossCharacter(Json::Value root);
        std::string id;
        int positionX;
        int positionY;
    };
    BossCharacter character;

    class BossPortal {
    public:
        BossPortal(){};
        BossPortal(Json::Value root);
        std::string path;
        int positionX;
        int positionY;
    };
    BossPortal portal;
};

class Reference {
public:
    Reference(Json::Value root);
    std::string path;
    std::vector<ObjectReference> objects;
};

class Object{
public:
    Object(Json::Value root);
    int id;
    float scaleX;
    float scaleY;
    float positionX;
    float positionY;
};

class MapModel {
public:
    MapModel(Json::Value root);
    std::vector<Reference> references;
    std::vector<Object> objects;
    std::vector<Ennemie> ennemies;
    Boss boss;
    Colors colors;
};



#endif //LEARNINGMAN_MAPMODEL_HPP
