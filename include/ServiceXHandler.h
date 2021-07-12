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

class ServiceXHandler {
    public:
        double x;
        // User user;
        // static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);

        std::vector<std::string> filenames;


        void show_val(ryml::NodeRef n);
        void show_keyval(ryml::NodeRef n);
        std::string FetchData(std::string request_id);
        void getStatus(std::string request_id);
        // std::vector<std::string> readYaml();
        // void readYaml();
        void GetMinIOData(std::string bucketName, std::string pathkey);

        void DoMD5(std::string filename);
        bool GetMd5(std::string &str_md5, const char  * const buffer, size_t buffer_size);

        std::map<std::string, std::string> parseYaml(std::string targetName);
        char* GetEndpoint();
        char* getType();
        int SaveJson(Json::Value val);

        static Json::Value JsonFromStr(std::string str);

        // Submit Request
        // Json::Value submitRequest(std::string submitJson)
};


#endif