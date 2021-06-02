//File: ServiceXHandler.h
#ifndef SERVICEXHANDLER_H
#define SERVICEXHANDLER_H

// ROOT includes
#include <TFile.h>

class User {
    public:
        char* getEndpoint();
        User(std::string end, std::string tok, std::string typ);

    private:
        const char* endpoint;
        const char* token; // todo use different class that supports long boi strings
        const char* apiType;
};


class ServiceXHandler {
    public:
        double x;
        // User user;

        std::vector<std::string> readYaml();
        char* getEndpoint();
        char* getType();
};


#endif