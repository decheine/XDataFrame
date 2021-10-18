
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

////////////////////////////////////////////////////////////////////////////////
/// @brief Main XDataFrame method that runs through all the processes of
/// sending the request, recieving, and returning the RDataFrame
ROOT::RDataFrame XDataFrame(std::string inputString)
{
   std::cout << "Beginning ServiceX to RDataFrame interface.\n";
   ServiceXHandler                    xHandler;
   std::vector<std::string>           userYaml;
   std::map<std::string, std::string> values = xHandler.parseYaml("/servicex.yaml");

   // Initialize a Request object.
   // Want to be able to extend functionality and add args to XDataFrame() to control behavior
   // of this
   Request testRequest(values);

   MCache cache;

   std::cout << "Data transformation request:\n" << inputString << "\n";

   testRequest.SendRequest(inputString, &cache);

   

   Hasher      hasher;
   std::string hashVal;
   hashVal = hasher.GetHash(inputString);
   // std::cout << "request_id: " << testRequest.GetRequestID() << "\n";
   std::string pathkey;
   pathkey = cache.GetCacheDir() + "/" + hashVal + "/";
   // Only call this if user specifically wants to refresh the data or if there are no data files.
   // Want to check the list of files to see if they're good? or if they're all there?

   // For now, do it every time.
   std::vector<std::string> filenameList;
   // Checks if the data files are in the cache already
   if(testRequest.IsInCache()){
      filenameList = cache.GetFileNameList(hashVal);
   } else{
      // Not in cache
      // Wait until job is done.
      // Check on status of job
      std::cout << "Checking status of job " + testRequest.GetRequestID() + "\n";
      std::string updateString;
      updateString = xHandler.FetchData(testRequest.GetRequestID());
      // std::cout << "Response: " + updateString + "\n";

      int waitResult;
      waitResult = xHandler.WaitOnJob(testRequest.GetRequestID());
      if (waitResult != 0) {
         std::cerr << "Job did not return complete. Exiting.\n";
         std::exit(1);
         // ROOT::RDataFrame d("", "");
         // return d;
      }
      filenameList = xHandler.GetMinIOData(testRequest.GetRequestID(), pathkey);
   }

   

   
   

   // RDataFrame Part

   RDataFrameHandler rdfHandler;
   rdfHandler.AddFiles(filenameList);
   ROOT::RDataFrame myDataFrame = rdfHandler.CreateRDataFrame();

   std::cout << "Finished\n";
   return myDataFrame;
}
