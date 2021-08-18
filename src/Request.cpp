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

// Include ServiceXHandler ??
// This might be a bad idea
#include "ServiceXHandler.h"

#include "Hasher.h"

#include "MCache.h"

/**
 * @brief Gets the status of a servicex endpoint. Only for one hardcoded endpoint, can be extended/refactored
 * to fetch the status from an endpoint specified by an argument. Not needed at the moment.
 * 
 * DEPRECATED
 * 
 * @return std::string 
 */
std::string Request::GetStatus(){
    // Check if the endpoint exists

    // if(this->endpoint)

    std::string servicexURL = "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation/";
    const char* targetURL = (servicexURL + GetRequestID()).c_str();
    
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // GET request
    std::cout << "Doing GET request\n";
    CURL *curl = curl_easy_init();
    std::string response_string;
    std::string header_string;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, targetURL);
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

/**
 * @brief Helper function for curl request sending, it helps write the returned values of curl requests
 * 
 * @param ptr 
 * @param size 
 * @param nmemb 
 * @param data 
 * @return size_t 
 */
size_t Request::writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data){
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

/**
 * @brief 
 * 
 * @param values 
 * @param submitRequestJson 
 * @param cache 
 * @return int 
 */
int Request::SendRequest(std::string submitRequestJson, MCache* cache) {
    std::cout << "Sending ServiceX request...\n"; 

    const char* homeDir = getenv("HOME");
    // std::cout << "homedir: " << homeDir << "\n"; 
    // const std::string fullDir = homeDir + submitRequestJson ;

    // Read json file
    // std::ifstream myFile(fullDir);
    // std::ostringstream tmp;
    // tmp << myFile.rdbuf();
    // std::string s = tmp.str();
    // std::cout << "Getting hash of request string" << std::endl;
    // const char* jsonObj = s.c_str();

    // Hash and check
    Hasher hasher;
    std::string hashString = hasher.GetHash(submitRequestJson);
    // std::cout << "got hash: " << hashString << "\n";

    
    // Look for hash entry on disk
    bool hashFound = true;
    // std::cout << "checking cache for " + hashString + "\n";
    std::cout << "Checking cache for previously fetched data.\n";

    hashFound = cache->EntryExists(hashString);


    if(hashFound == false){
        std::cout << "Cache entry not found, submitting request\n";
        std::string requestURL = GetValues()["endpoint"] + "servicex/transformation";
        // std::cout << "api endpoint: " << requestURL << "\n";
        // Store submitrequestjson to variable
        SubmitRequestJson = ServiceXHandler::JsonFromStr(submitRequestJson);

        // make post request

        const char* targetURL = requestURL.c_str();

        curl_global_cleanup();
        curl_global_init(CURL_GLOBAL_DEFAULT);

        // GET request
        // std::cout << "Doing POST request\n";
        CURL *curl = curl_easy_init();
        std::string response_string;
        CURLcode res = CURLE_FAILED_INIT;
        char errbuf[CURL_ERROR_SIZE] = { 0, };
        struct curl_slist *header_string=NULL;
        char agent[1024] = { 0, };

        char szJsonData[1024];  
        memset(szJsonData, 0, sizeof(szJsonData));
        strcpy(szJsonData, submitRequestJson.c_str());  
        try{
            if (curl) {
                // agent[sizeof(agent) - 1] = 0;
                // curl_easy_setopt(curl, CURLOPT_USERAGENT, agent);
                const char* requestURL = "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation";

                curl_easy_setopt(curl, CURLOPT_URL, requestURL);
                // header_string = curl_slist_append(header_string, "Expect:");
                header_string = curl_slist_append(header_string, "Content-Type: application/json");
                // header_string = curl_slist_append(header_string, "charset: utf-8");
                // std::cout << "Set up headers\n";
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_string);
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
            
                // curl_easy_setopt(curl, CURLOPT_VERBOSE, 2L);

                // curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

                // std::cout << "Trying write function\n";

                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, szJsonData);

                // std::cout << "Performing curl request\n";
                res = curl_easy_perform(curl);
                // std::cout << "Finished curl request\n";
                curl_slist_free_all(header_string);
                std::cout << "Response: " << response_string << "\n";
                curl_easy_cleanup(curl);
                curl_global_cleanup();
                curl = NULL;
            }

            // std::cout << "Response: " << response_string << std::endl;
            // put response_string to a variable
        }catch (std::exception &ex)  
            {  
                printf("curl exception %s.\n", ex.what());  
                return 1;
            }
        // All finished, so set the Request variables
        // Make the response into a Json object
        Json::Value responseJson = ServiceXHandler::JsonFromStr(response_string);
        // std::cout << "setting request_id " << responseJson["request_id"].asCString() << "\n";
        request_id = responseJson["request_id"].asCString();
        cache->CreateCacheEntry(hashString);
        cache->WriteRequestID(hashString, request_id);
        return 0; 
    } else {
        // Hash was found
        // request_id = hash
        // std::cout << "Hash found\n";

        std::string reqId = cache->ReadRequestId(hashString);
        // std::cout << "setting hashes, " << request_id << " " << reqId << "\n";
        request_id = reqId;
        // fs::path reqidPath = fs::path(cache->GetCacheDir() + "/" + hashString);


        return 0;

    }
    // std::cout << "outside returning\n";
    return 0;
}

/**
 * @brief Saves a json value to a json file named <request_id>.json
 * 
 * @param value 
 * @return int 
 */
int Request::SaveJson(Json::Value value){
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "\t";

    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    std::string savedir = request_id + ".json";

    // std::string savedir = "" + value["request_id"].asString() + ".json";
    std::cout << "Saving file as " << savedir << std::endl;
    std::ofstream outputFileStream(savedir);
    writer -> write(value, &outputFileStream);

    return 0;
}

/**
 * @brief request_id getter
 * 
 * @return std::string 
 */
std::string Request::GetRequestID(){
    return request_id;
}

void Request::SetRequestID(std::string requestid){
    request_id = requestid;
}


std::map<std::string, std::string> Request::GetValues(){
    return values;
}

Request::Request() {

}

Request::Request(std::map<std::string, std::string> myValues) {
    values = myValues;
}

