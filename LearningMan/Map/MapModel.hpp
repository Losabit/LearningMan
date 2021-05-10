#ifndef LEARNINGMAN_MAPMODEL_HPP
#define LEARNINGMAN_MAPMODEL_HPP

#include "../lib/json/json.h"
class ObjectReference {
public:
    ObjectReference(Json::Value root);
    int id;
    int top;
    int left;
    int width;
    int height;
};

class Reference {
public:
    Reference(Json::Value root);
    std::string path;
    std::vector<ObjectReference> objects;
};

class MapModel {
public:
    MapModel(Json::Value root);
    std::vector<Reference> references;

};



#endif //LEARNINGMAN_MAPMODEL_HPP
