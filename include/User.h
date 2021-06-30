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


/**
 * @brief Request object representing an instance of a ServiceX request
 * Contains the endpoint, token, type. 
 * 
 */
class Request {
    public:
        const char* name;

        static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);


        void setEndpoint(char*endpoint);
        void setToken(char* token);
        void setType(char* type);

        // Gets status of request. Returns a json output
        Json::Value getStatus();    
        char* getEndpoint();
        char* getToken();
        char* getType();

        const char* endpoint;
        const char* token; // todo use different class that supports long boi strings
        const char* apiType;
        const char* request_id;

        const Json::Value submitRequestJson;

        // Submission method. Call to send the curl request to ServiceX with a submit_request.json
        int sendRequest(std::map<std::string, std::string> values, std::string submitRequestJson);


        // Request(const char* endpoint, const char* token, const char* apiType, Json::Value requestJson) {
        // This version takes as input a map of servicex.yaml. submit_request.json
        Request();

    private:
        // Who needs private members? public is just easier and I'm lazy

};



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

