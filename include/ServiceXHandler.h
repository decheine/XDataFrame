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


class ServiceXHandler {
    public:
        double x;
        // User user;
        // static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);

        void show_val(ryml::NodeRef n);
        void show_keyval(ryml::NodeRef n);
        std::string fetchData(std::string request_id);
        void getStatus(std::string request_id);
        // std::vector<std::string> readYaml();
        // void readYaml();

        std::map<std::string, std::string> parseYaml(std::string targetName);
        char* getEndpoint();
        char* getType();

        // Submit Request
        // Json::Value submitRequest(std::string submitJson)
};


#endif