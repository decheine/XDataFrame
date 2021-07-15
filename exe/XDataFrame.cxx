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
#include "ROOT/RDataFrame.hxx"

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
#include "RDataFrameHandler.h"
#include "Request.h"
#include "Hasher.h"
#include "MCache.h"

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
    std::map<std::string, std::string> values = xHandler.parseYaml("/servicex.yaml");

    Request testRequest;

    MCache cache;


    testRequest.SendRequest(values, "/submit_request.json", &cache);
    // std::cout << "Saving json of response\n"; 
    // testRequest.SaveJson(testRequest.SubmitRequestJson);


    Hasher hasher;
    std::string hashVal;
    hashVal = hasher.GetHashOf("/submit_request.json");
    std::cout << "request_id: " << testRequest.request_id << "\n";
    std::string pathkey;
    pathkey = cache.GetCacheDir() + "/" + hashVal + "/";
    // Only call this if user specifically wants to refresh the data or if there are no data files. 
    // For now, do it every time. 
    std::vector<std::string> filenameList;
    filenameList = xHandler.GetMinIOData(testRequest.request_id, pathkey);


    // RDataFrame Part

    RDataFrameHandler rdfHandler;
    rdfHandler.AddFiles(filenameList);
    ROOT::RDataFrame myDataFrame = rdfHandler.CreateRDataFrame();
    auto d1 = myDataFrame.Display();
    d1->Print();
    // rdfHandler.DisplayRDF();

    std::cout << "Finished\n";
    return 0;
}