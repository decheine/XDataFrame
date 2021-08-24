//File: ServiceXHandler.h
#ifndef REQUEST_H
#define REQUEST_H

// ROOT
#include <Rtypes.h>


// Jsoncpp
#include <json/value.h>
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>

#include "MCache.h"

/**
 * @brief Request object representing an instance of a ServiceX request
 * Contains the endpoint, token, type. 
 * 
 * First created with a set of values, consisting of an endpoint and optional token, and type.
 * Then a transformation request can be made with an input request json, and a pointer to
 * an MCache. 
 * 
 */
// TODO: This feels like it is meant for a single request. However the API seems to imply one can
// run multiple requests, etc. Redesign API so object has clear purpose?
class Request {
    public:
        // This version takes as input a map of servicex.yaml. submit_request.json
        Request();

        // constructor
        Request(std::map<std::string, std::string> myValues);

        // Function utilized by curl methods to write down return values as they are received.
        static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);

        // DEPRECATED. Makes a curl request to ServiceX with current request_id and returns the response 
        std::string GetStatus();    

        void SetRequestID(std::string requestid);
        std::string GetRequestID();

        // Submission method. Call to send the curl request to ServiceX with a submit_request.json
        Int_t SendRequest(std::string submitRequestJson, MCache* cache);

        // saves a json val to a file <request_id>.json
        Int_t SaveJson(Json::Value val);

        // returns the private member "values"
        std::map<std::string, std::string> GetValues();

    private:
        // Json value that stores the submit request data. 
        Json::Value SubmitRequestJson;

        // A job's returned request_id
        std::string request_id;

        // values like endpoint, token, and type, parsed from the servicex.yaml file
        std::map<std::string, std::string> values;


};

#endif