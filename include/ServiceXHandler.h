//File: ServiceXHandler.h
#ifndef SERVICEXHANDLER_H
#define SERVICEXHANDLER_H

// ROOT includes
#include <TFile.h>

// Jsoncpp
#include <json/value.h>
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>

// ryml
#include <ryml.hpp>

// TODO: Comments! :-)
// TODO: Make as much of this private as you can, including the indcludes!
class ServiceXHandler {
    public:



        // Gets the response string from the endpoint with request_id
        std::string FetchData(std::string request_id);

        // Checks the status of job <request_id> and waits until it's marked as "Complete"
        int WaitOnJob(std::string request_id);

        // gets the status of the job request_id
        void getStatus(std::string request_id);

        // Gets the minio bucket data from a given bucket and a download location specified by pathkey
        std::vector<std::string> GetMinIOData(std::string bucketName, std::string pathkey);

        // Parses a yaml file at targetName to a string-string map. Gets the endpoint, type, and token
        std::map<std::string, std::string> parseYaml(std::string targetName);
        
        //converts a given valid json string to a Json::Value
        static Json::Value JsonFromStr(std::string str);

        // Submit Request
        // Json::Value submitRequest(std::string submitJson)
    private:
        // helper functions for displaying yaml nodes and values
        void show_val(ryml::NodeRef n);
        void show_keyval(ryml::NodeRef n);
    
        // Saves a json val to a file named val["request_id"].json
        int SaveJson(Json::Value val);



};


#endif