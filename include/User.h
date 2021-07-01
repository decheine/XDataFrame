//File: User.h
#ifndef USER_H
#define USER_H

// ROOT includes
#include <TFile.h>

// Jsoncpp
#include <json/value.h>
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>

class User {
    public:
        // User(std::string end, std::string tok, std::string typ);
        User();
        int CreateROOTUserFolder(std::string username);
        int CreateUserFolder(std::string username);

    private:


};

#endif