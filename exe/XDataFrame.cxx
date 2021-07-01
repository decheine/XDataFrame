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

using namespace std;

// size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
//     data->append((char*)ptr, size * nmemb);
//     return size * nmemb;
// }

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
    //std::map<std::string, std::string> values = xHandler.parseYaml("/servicex.yaml");

    // std::string jsonstringresponse = xHandler.FetchData("345974d4-d2ec-49bb-bef2-6683b7e461d5");

    Request testRequest;

    std::string jsonStr = testRequest.GetStatus();

    Json::Value jsonResponse = xHandler.JsonFromStr(jsonStr);
    testRequest.SaveJson(jsonResponse);


    


    // testRequest.SendRequest(values, "/submit_request.json");

    User myUser;
    // myUser.CreateROOTUserFolder("user1");


//////////////
    // for (std::map<std::string, std::string>::iterator it = values.begin(); it != values.end(); ++it){
    //     std::cout << it->second << std::endl;
    // }
    // // std::for_each(values.begin(), values.end()){
    // //     std::cout << s << std::endl;
    // // }

    // // curlopt_post
    // // CURLOPT_HTTPGET


    // // Here, using a specialized Builder, we discard comments and
    // // record errors as we parse.
    // Json::CharReaderBuilder rbuilder;
    // rbuilder["collectComments"] = false;
    // std::string errs;
    // auto reader = rbuilder.newCharReader();
    // reader->parse(&response_string.front(), &response_string.back(), &root, &errs);
    // std::vector<string> members = root.getMemberNames();

    
    // // std::cout << members[0] << std::endl;

    // for (std::vector<std::string>::iterator it = members.begin(); it != members.end(); ++it){
    //     std::cout << *it << std::endl;
    // }
    // // bool ok = Json::parse(rbuilder, response_string, &root, &errs);

    // std::cout << "RequestID: " << root["request_id"] << std::endl;

    // std::string BucketName = "345974d4-d2ec-49bb-bef2-6683b7e461d5";


    // Aws::SDKOptions m_options;
    // Aws::S3::S3Client* m_client = { NULL };


    // Aws::InitAPI(m_options);
    // Aws::Client::ClientConfiguration cfg;
    // cfg.endpointOverride = "cmsopendata-minio.servicex.ssl-hep.org";
    // cfg.scheme = Aws::Http::Scheme::HTTP;
    // cfg.verifySSL = false;
    // m_client = new Aws::S3::S3Client(Aws::Auth::AWSCredentials("miniouser", "leftfoot1"), cfg, 
    //     Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);
    // std::string objectKey = "root:::eospublic.cern.ch::eos:opendata:cms:MonteCarlo2011:Summer11LegDR:SMHiggsToZZTo4L_M-125_7TeV-powheg15-JHUgenV3-pythia6:AODSIM:PU_S13_START53_LV6-v1:20000:08CD3ECC-4C92-E411-B001-0025907B4F20.root";
    // std::string pathkey = "temp";
    // Aws::S3::Model::PutObjectRequest putObjectRequest;
    // putObjectRequest.WithBucket(BucketName.c_str()).WithKey(objectKey.c_str());

    // Aws::S3::Model::ListObjectsRequest objRequest;
    // objRequest.WithBucket(BucketName);

    // auto outcome = m_client->ListObjects(objRequest);

    // if (outcome.IsSuccess()) {
    //     std::cout << "Objects in bucket '" << BucketName << "':" 
    //         << std::endl << std::endl;

    //     Aws::Vector<Aws::S3::Model::Object> objects =
    //         outcome.GetResult().GetContents();

    //     for (Aws::S3::Model::Object& object : objects)
    //     {
    //         std::cout << object.GetKey() << std::endl;
    //     }

    // }
    // else
    // {
    //     std::cout << "Error: ListObjects: " <<
    //         outcome.GetError().GetMessage() << std::endl;

    // }

    // // Get object
    // std::cout << "Getting object\n"; 

    // Aws::S3::Model::GetObjectRequest object_request;
    // object_request.SetBucket(BucketName);
    // object_request.SetKey(objectKey);

    // Aws::S3::Model::GetObjectOutcome get_object_outcome = 
    //     m_client->GetObject(object_request);

    // if (get_object_outcome.IsSuccess()) {
    //     // auto& retrieved_file = get_object_outcome.GetResultWithOwnership().
    //     //     GetBody();
    //     // std::cout << typeid(retrieved_file).name() << '\n';

    //     // // Print a beginning portion of the text file.
    //     // std::cout << "Beginning of file contents:\n";
    //     // char file_data[255] = { 0 };
    //     // retrieved_file.getline(file_data, 254);
    //     // std::cout << file_data << std::endl;

    //     std::cout << "attempting save\n";

    //     // TFile *myFile = new TFile("myfile.root", "CREATE");

    //     Aws::OFStream local_file;
	// 	local_file.open(objectKey.c_str(), std::ios::out | std::ios::binary);
	// 	local_file << get_object_outcome.GetResult().GetBody().rdbuf();
	// 	std::cout << "Done!" << std::endl;

    //     // myFile-

    //     // return true;
    // }
    // else {
    //     auto err = get_object_outcome.GetError();
    //     std::cout << "Error: GetObject: " <<
    //         err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

    //     // return false;
    // }
///////////////


    


    //Run and finish with ROOT prompt
    // app.Run();

    std::cout << "Finished\n";
    return 0;
}