
// Standard includes
#include <stdlib.h>
#include <iostream>
#include <string> 

// ROOT
#include "TF1.h"
#include "TRint.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TBrowser.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RDF/RDisplay.hxx>

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


#include "XDataFrame.h"

ROOT::RDataFrame XDataFrame(std::string inputString){
    std::cout << "begin\n";
    ServiceXHandler xHandler;
    std::vector<std::string> userYaml;
    std::map<std::string, std::string> values = xHandler.parseYaml("/servicex.yaml");

    // Initialize a Request object.
    // Want to be able to extend functionality and add args to XDataFrame() to control behavior
    // of this
    Request testRequest(values);

    MCache cache;

    //Change this to 
    testRequest.SendRequest(inputString, &cache);
    // std::cout << "Saving json of response\n"; 
    // testRequest.SaveJson(testRequest.SubmitRequestJson);


    Hasher hasher;
    std::string hashVal;
    hashVal = hasher.GetHash(inputString);
    std::cout << "request_id: " << testRequest.GetRequestID() << "\n";
    std::string pathkey;
    pathkey = cache.GetCacheDir() + "/" + hashVal + "/";
    // Only call this if user specifically wants to refresh the data or if there are no data files. 
    // For now, do it every time. 

    // Wait until job is done.
    
    // Check on status of job
    std::cout << "Checking status of job " + testRequest.GetRequestID() + "\n";
    std::string updateString;
    updateString = xHandler.FetchData(testRequest.GetRequestID());
    // std::cout << "Response: " + updateString + "\n";

    xHandler.WaitOnJob(testRequest.GetRequestID());

    std::vector<std::string> filenameList;
    filenameList = xHandler.GetMinIOData(testRequest.GetRequestID(), pathkey);

    // RDataFrame Part

    RDataFrameHandler rdfHandler;
    rdfHandler.AddFiles(filenameList);
    ROOT::RDataFrame myDataFrame = rdfHandler.CreateRDataFrame();

    std::cout << "Finished\n";
    return myDataFrame;
}
