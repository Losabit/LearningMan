////
//// Created by Mirii on 09/07/2021.
////
//
#include <sstream>
#include <iostream>
#include "curlFunction.h"

size_t   writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

std::string getInfo(std::string url) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if (curl) {
        char *nurl = const_cast<char *>(url.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, nurl);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);

        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;
        return response_string;

    }
    return "NULL";
}

int addUser(std::string username, std::string token) {
    CURL *curl;

    std::string  output;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    CURLcode res;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, USERURL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        std::ostringstream out;
        out << "{\"token\":" << token<<R"(,"pseudo":")" << username << "\"}";
        std::string temp = out.str();
        char * postValue =  const_cast<char *>(temp.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postValue );
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            return 1;
        }
    }
    curl = NULL ;
    return 0;
}
int addGame(std::string start,std::string end,std::string token, int isDead, int playerType, int score, int nbKill, int deathPosition , std::string killer) {
    CURL *curl;

    std::string  output;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    CURLcode res;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, GAMEURL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        std::ostringstream out;
        out << "{\"token\": " << token<<R"(,"dateStart":")" << start << R"(" ,"isDead" : )" << isDead  << ", \"playerType\" : " << playerType  <<   ", \"scoreTotal\" :"  << score << ", \"nbKill\": " << nbKill << ", \"deathPosition\" :" << deathPosition<< R"(, "killer":" )" <<  killer   << R"(", "dateEnd":)"   "\""<< end <<    R"(","idMap":)"   << 1  << "}  ";

        std::cout << out.str() << std::endl;
        std::string temp = out.str();
        char * postValue =  const_cast<char *>(temp.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postValue );
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            return 1;
        }
    }
    curl = NULL ;
    return 0;
}



