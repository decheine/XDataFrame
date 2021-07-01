// Standard Includes
#include <stdlib.h>
#include <iostream>
#include <fstream>

// Curl
#include <curl/curl.h>

// Jsoncpp
#include <json/value.h>

// Header
#include "Request.h"

std::string Request::GetStatus(){
    // Check if the endpoint exists

    // if(this->endpoint)

    std::string servicexURL = "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation/";
    const char* requestURL = "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation/345974d4-d2ec-49bb-bef2-6683b7e461d5";
    const char* targetURL = (servicexURL + request_id).c_str();
    
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // GET request
    std::cout << "Doing GET request\n";
    CURL *curl = curl_easy_init();
    std::string response_string;
    std::string header_string;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, requestURL);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
        std::cout << "easy perform\n";
        curl_easy_perform(curl);
        std::cout << "done easy perform\n";

        // std::cout << response_string;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;
    }

    // std::cout << "Response: " << response_string << std::endl;
    return response_string;
}

size_t Request::writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data){
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int Request::SendRequest(std::map<std::string, std::string> values, std::string submitRequestJson) {
    std::cout << "Reading json\n"; 

    const char* homeDir = getenv("HOME");
    // std::cout << "homedir: " << homeDir << "\n"; 
    const std::string fullDir = homeDir + submitRequestJson ;

    // Read json file
    std::ifstream myFile(fullDir);
    std::ostringstream tmp;
    tmp << myFile.rdbuf();
    std::string s = tmp.str();
    std::cout << s << std::endl;
    const char* jsonObj = s.c_str();
    std::string requestURL = values["endpoint"] + "servicex/transformation";
    std::cout << "api endpoint: " << requestURL << "\n";
    // make post request

    const char* targetURL = requestURL.c_str();

    curl_global_cleanup();
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // GET request
    std::cout << "Doing POST request\n";
    CURL *curl = curl_easy_init();
    std::string response_string;
    CURLcode res = CURLE_FAILED_INIT;
    char errbuf[CURL_ERROR_SIZE] = { 0, };
    struct curl_slist *header_string=NULL;
    char agent[1024] = { 0, };

    char szJsonData[1024];  
    memset(szJsonData, 0, sizeof(szJsonData));
    strcpy(szJsonData, s.c_str());  
    try{
        if (curl) {
            

            // agent[sizeof(agent) - 1] = 0;
            // curl_easy_setopt(curl, CURLOPT_USERAGENT, agent);
            const char* requestURL = "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation";

            curl_easy_setopt(curl, CURLOPT_URL, requestURL);
            // header_string = curl_slist_append(header_string, "Expect:");
            header_string = curl_slist_append(header_string, "Content-Type: application/json");
            // header_string = curl_slist_append(header_string, "charset: utf-8");
            std::cout << "Set up headers\n";
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_string);
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        
            // curl_easy_setopt(curl, CURLOPT_VERBOSE, 2L);

            // curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

            std::cout << "Trying write function\n";

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, szJsonData);


            std::cout << "Performing curl request\n";
            res = curl_easy_perform(curl);
            std::cout << "Finished curl request\n";
            curl_slist_free_all(header_string);
            std::cout << response_string;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            curl = NULL;
        }

        // std::cout << "Response: " << response_string << std::endl;
        // put response_string to a variable
    }catch (std::exception &ex)  
        {  
            printf("curl exception %s.\n", ex.what());  
        } 
    return 0;
}

int Request::SaveJson(Json::Value value){
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "\t";

    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    std::string savedir = "" + value["request_id"].asString() + ".json";
    std::cout << "Saving file as " << savedir << std::endl;
    std::ofstream outputFileStream(savedir);
    writer -> write(value, &outputFileStream);

    return 0;
}


Request::Request() {

}



