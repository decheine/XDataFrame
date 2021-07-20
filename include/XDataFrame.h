#ifndef XDATAFRAME_H
#define XDATAFRAME_H

// Standard includes
#include <stdlib.h>
#include <iostream>



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



/**
 * @brief XDataFrame root level class. 
 * 
 * In the future, this could be implemented similar to how RDataFrame is implemented,
 * where it is an object that represents an RDataFrame instead of using a fetching
 * method to do it. 
 * 
 */
// class XDataFrame {
//     private:
//         Double_t x;
//     public:
//         // Constructor and intitializer. After the colon, variables are initialized with the values listed
//         XDataFrame() : x(2.5) {}
//         ROOT::RDataFrame GetRDataFrame(std::string input);
//         Double_t GetX() const;


//         ClassDef(XDataFrame, 1)

// };

ROOT::RDataFrame* XDataFrame(std::string inputString);

#endif