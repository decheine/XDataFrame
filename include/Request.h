//File: ServiceXHandler.h
#ifndef REQUEST_H
#define REQUEST_H

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
        // Request(const char* endpoint, const char* token, const char* apiType, Json::Value requestJson) {
        // This version takes as input a map of servicex.yaml. submit_request.json
        Request();
        // Function utilized by curl methods to write down return values as they are received.
        static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);

        void SetEndpoint(char*endpoint);
        void SetToken(char* token);
        void SetType(char* type);

        std::string GetStatus();    
        char* GetEndpoint();
        char* GetToken();
        char* GetType();
        std::string GetRequestID();

        // Submission method. Call to send the curl request to ServiceX with a submit_request.json
        int SendRequest(std::map<std::string, std::string> values, std::string submitRequestJson);

        int SaveJson(Json::Value val);

        // Loads data into the request object. Called with initializer?
        int LoadRequest();

        const char* name;
        const char* endpoint;
        const char* token; // todo use different class that supports long boi strings
        const char* apiType;
        std::string request_id;

        Json::Value SubmitRequestJson;



    private:
        // Who needs private members? public is just easier and I'm lazy
        // Will change them over later

};

#endif