////
//// Created by Mirii on 09/07/2021.
////

#ifndef LEARNINGMAN_CURLFUNCTION_H
#include <curl/curl.h>
#include <string>
#include <ctime>
#define TOKENURL "https://b4xcv1e397.execute-api.eu-west-3.amazonaws.com/dev/token"
#define USERURL "https://b4xcv1e397.execute-api.eu-west-3.amazonaws.com/dev/user"
#define GAMEURL "https://b4xcv1e397.execute-api.eu-west-3.amazonaws.com/dev/partie"
#define MAPURL "https://b4xcv1e397.execute-api.eu-west-3.amazonaws.com/dev/map"
#define LEARNINGMAN_CURLFUNCTION_H

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);
std::string getInfo(std::string url);
int addUser(std::string username, std::string token);
int addGame(std::string start,std::string end,std::string token, int isDead, int playerType, int score, int nbKill, int deathPosition , std::string killer);
std::string dateFormat(tm* ltm);
int deathPosition(float startPosition, float currentPosition, float portalPosition, bool takePortal);
#endif //LEARNINGMAN_CURLFUNCTION_H
