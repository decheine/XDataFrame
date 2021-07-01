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

// Project includes
#include "Request.h"

/**
 * @brief User class that manages the requests and actions done by a user. An actual user could have
 * multiple User "profiles" (maybe?) for different purposes. For now, only 1 instance is being used.
 * 
 */
class User {
    public:
        // User(std::string end, std::string tok, std::string typ);
        User();
        int CreateROOTUserFolder(std::string username);
        int CreateUserFolder(std::string username);

        // Loads user data from folder. If none exists, return 1. For now, no name. Maybe add in future.
        int LoadUserData();
        //

    private:
        // Map of requests by request_id?
        std::map<std::string, Request> Requests;


};

#endif