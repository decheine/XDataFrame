// Standard includes
#include <map>
#include <iostream>
#include <fstream>

#include "../include/XDataFrameConfig.h.in"
// ROOT
#include "TF1.h"
#include "TRint.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TBrowser.h"

// ryml
#include <ryml.hpp>

// Curl
#include <curl/curl.h>

// Jsoncpp
#include <json/reader.h>
#include <json/value.h>
#include <json/writer.h>

// AWS SDK
#include <aws/core/Aws.h>
#include <aws/core/SDKConfig.h>

#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/GetObjectRequest.h>

#include <aws/s3/model/PutObjectRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

// Project
#include "ServiceXHandler.h"
#include "User.h"
#include "Request.h"
#include "Hasher.h"
#include "MCache.h"

using namespace std;

// size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
//     data->append((char*)ptr, size * nmemb);
//     return size * nmemb;
// }


// Helper Functions

/**
 * @brief Reads a json with file name filename from the user's homedirectory
 * 
 * @param filename 
 * @return std::string 
 */
std::string ReadJsonFromFile(std::string filename){
    const char* homeDir = getenv("HOME");
    // std::cout << "homedir: " << homeDir << "\n"; 
    const std::string fullDir = homeDir + filename;

    // Read json file
    std::ifstream myFile(fullDir);
    std::ostringstream tmp;
    tmp << myFile.rdbuf();
    std::string s = tmp.str();
    std::cout << s << std::endl;
    const char* jsonObj = s.c_str();
    return s;
}




int main(int argc, char* argv[]){
    if(argc > 1){
        if (strcmp(argv[1], "--version") == 0) {
            // report version
            // Show usage 
            std::cout << argv[0] << " Version " << XDataFrame_VERSION_MAJOR << "."
                    << XDataFrame_VERSION_MINOR << std::endl;
            std::cout << "Usage: " << argv[0] << " number" << std::endl;
            return 0;
        }
    }

    ServiceXHandler xHandler;
    std::vector<std::string> userYaml;
    // User theUser();
    std::map<std::string, std::string> values = xHandler.parseYaml("/servicex.yaml");

    // std::string jsonstringresponse = xHandler.FetchData("345974d4-d2ec-49bb-bef2-6683b7e461d5");

    Request testRequest;

    MCache cache;


    testRequest.SendRequest(values, "/submit_request.json", &cache);
    // std::cout << "Saving json of response\n"; 
    // testRequest.SaveJson(testRequest.SubmitRequestJson);

    std::string md5_string;

    User myUser;

    Hasher hasher;
    std::string hashVal;
    hashVal = hasher.GetHash("/submit_request.json");
    

    cache.CreateCacheEntry(hashVal);
    cache.WriteRequestID(hashVal, testRequest.request_id);
    // cache.SaveRequestId(hashVal, requestId);


    //Run and finish with ROOT prompt
    // app.Run();

    std::cout << "Finished\n";
    return 0;
}