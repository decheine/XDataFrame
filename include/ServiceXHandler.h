//File: ServiceXHandler.h
#ifndef SERVICEXHANDLER_H
#define SERVICEXHANDLER_H

// ROOT includes
#include <TFile.h>

class User {
    public:
        char* getEndpoint();
        // User(std::string end, std::string tok, std::string typ);
        User();
        void setEndpoint(char*endpoint);
        void setToken(char* token);
        void setType(char* type);

    private:
        const char* endpoint;
        const char* token; // todo use different class that supports long boi strings
        const char* apiType;
};


class ServiceXHandler {
    public:
        double x;
        // User user;

        void show_val(ryml::NodeRef n);
        void show_keyval(ryml::NodeRef n);


        // std::vector<std::string> readYaml();
        // void readYaml();

        std::map<std::string, std::string> parseYaml();
        char* getEndpoint();
        char* getType();
};


#endif