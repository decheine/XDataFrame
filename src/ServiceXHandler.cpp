// Standard Includes
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <regex>
#include <iterator>
#include <map>
#include <unistd.h>

// Yaml processor
#include <c4/yml/preprocess.hpp>
#include <c4/yml/std/string.hpp>
#include <ryml.hpp>

// Curl
#include <curl/curl.h>

// Jsoncpp
#include <json/value.h>

// Boost filesystem
#include <boost/filesystem.hpp>

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

namespace fs = boost::filesystem;

/// YAML Methods

////////////////////////////////////////////////////////////////////////////////
// convenience functions to print a node
void ServiceXHandler::show_keyval(c4::yml::NodeRef n)
{
   assert(n.has_key());
   std::cout << n.key() << ": " << n.val() << "\n";
}
void ServiceXHandler::show_val(c4::yml::NodeRef n)
{
   // std::cout << "show_val" << std::endl;
   assert(n.has_val());
   std::cout << n.val() << "\n";
}

////////////////////////////////////////////////////////////////////////////////
// Used by curl to write retrieved data to memory
static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data)
{
   data->append((char *)ptr, size * nmemb);
   return size * nmemb;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief reads and parses the servicex.yaml file and stores
 * the endpoint, token, and type
 *
 * @return a tree of all the data?
 */
std::map<std::string, std::string> ServiceXHandler::parseYaml(std::string targetName)
{

   // Check if file exists
   // std::string myText;
   // std::ifstream infile("~/servicex.yaml");
   // if(!infile.good()){
   //     std::cout << "servicex.yaml not found in home directory. Exiting.\n";
   //     exit(1);
   // }
   std::map<std::string, std::string> properties;
   properties["endpoint"] = "";
   const char *homeDir    = getenv("HOME");
   // std::cout << "homedir: " << homeDir << "\n";

   std::string       line;
   const std::string fullDir = homeDir + targetName;
   std::cout << "Reading file " + fullDir + "\n";
   std::ifstream myfile(fullDir);
   if (myfile.is_open()) {
      std::cout << "file opened\n";
      std::string content;

      // content.assign(((std::istreambuf_iterator<char>(myfile)),
      //         std::istreambuf_iterator<char>()));

      content.assign((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());

      std::cout << "content assigned \n";

      // ryml can parse in situ (and read-only buffers too):

      std::string testyaml = "api_endpoints:\n  - endpoint: https://cmsopendata.servicex.ssl-hep.org/\n    type: "
                             "cms_run1_aod\n    token: xxx";

      // strcpy(src, content.c_str());
      // char src[];
      c4::substr srcview = c4::to_substr(testyaml); // a mutable view to the source buffer
      std::cout << "to substr \n";

      // there are also overloads for reusing the tree and parser
      ryml::Tree tree = ryml::parse(srcview);
      std::cout << "parsed \n";

      // get a reference to the "foo" node
      ryml::NodeRef node = tree["api_endpoints"];
      std::cout << "Number of children: " << node.num_children() << std::endl;
      // ryml::NodeRef subNode = node.find_child("sub2");
      // ryml::NodeRef subFirst = node.child(0);

      // ryml::NodeRef api_endpointNode = tree["api_endpoints"];
      char       src[]  = "type";
      c4::substr epName = src;
      // ryml::NodeRef endpointNode = tree["api_endpoints"].find_child(epName);
      std::cout << "getting api_endpoints child\n";
      ryml::NodeRef api_endpointNode = tree["api_endpoints"].child(0);
      // ryml::NodeRef typeNode = tree["api_endpoints"];

      ryml::NodeRef endpointNode = api_endpointNode.find_child("endpoint");
      ryml::NodeRef typeNode     = api_endpointNode.find_child("type");
      ryml::NodeRef tokenNode    = api_endpointNode.find_child("token");

      // TODO: Needs to search and verify that the nodes are there before they are referenced.
      std::cout << "Trying show_keyval...\n";
      show_val(endpointNode);

      std::string endpoint;
      std::string token;
      std::string mytype;

      std::cout << "getting endpoint\n";
      c4::from_chars(endpointNode.val(), &endpoint);

      myfile.close();

      // This will be expanded later
      std::map<std::string, std::string> properties;
      properties["endpoint"] = endpoint;
      // properties["token"] = token;
      // properties["type"] = mytype;

      std::cout << "returning properties\n";
      return properties;
   } else
      std::cout << "Unable to open servicex.yaml. Proceeding with default endpoint.\n";

   // std::cout << " - Read servicex.yaml\n";
   return properties;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Fetches data from a servicex endpoint specified by the request_id.
 *
 * @param request_id
 * @return std::string
 */
std::string ServiceXHandler::FetchData(std::string request_id)
{
   // CURL *curl = curl_easy_init();
   // std::string request_id = "345974d4-d2ec-49bb-bef2-6683b7e461d5";
   std::string serviceXURL = "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation/";
   std::string tmpURL      = (serviceXURL + request_id);
   // std::cout << "tmpurl: " << tmpURL << "\n";
   const char *targetURL = tmpURL.c_str();

   curl_global_init(CURL_GLOBAL_DEFAULT);

   // GET request
   // std::cout << "Doing GET request\n";
   CURL *      curl = curl_easy_init();
   std::string response_string;
   std::string header_string;
   // std::cout << "targeturl: " << targetURL << "\n";
   if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, targetURL);
      curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
      curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
      curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, -1L);
      // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
      // curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

      // curl_easy_setopt(curl, CURLOPT_VERBOSE, 2L);

      // std::cout << "easy perform\n";
      curl_easy_perform(curl);
      // std::cout << "done easy perform\n";
      // std::cout << response_string;
      curl_easy_cleanup(curl);
      curl_global_cleanup();
      curl = NULL;
   }

   // std::cout << "Response: " << response_string << std::endl;
   return response_string;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Checks the status of job <request_id> and waits until it's marked as "Complete"
 *
 * @param request_id
 * @return Int_t
 */
Int_t ServiceXHandler::WaitOnJob(std::string request_id)
{

   // Get status, check if it is "complete".

   // Get status
   std::string tmpStatus;
   Json::Value jsonStatus;
   std::string isCompleted = "";

   Int_t microsecond = 1000000;

   while (isCompleted != "Complete") {
      usleep(5 * microsecond); // sleeps for 5 second
      tmpStatus   = FetchData(request_id);
      jsonStatus  = JsonFromStr(tmpStatus);
      isCompleted = jsonStatus["status"].asCString();
      std::cout << "Job status of " + request_id + ":\t" + jsonStatus["status"].asCString() << std::endl;
      if (jsonStatus["status"].asCString() == "Complete") {
         return 0;
      } else if (jsonStatus["status"].asCString() == "Fatal") {
         std::cerr << "Error: ServiceX job ended Fatal. Exiting...\n";
         return 1;
      }
   }

   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Saves a json value to a json file named <request_id>.json
 *
 * @param value
 * @return Int_t
 */
Int_t ServiceXHandler::SaveJson(Json::Value value)
{
   Json::StreamWriterBuilder builder;
   builder["commentStyle"] = "None";
   builder["indentation"]  = "\t";
   // TODO: verify that a request_id value is present and if not, display a warning
   std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
   std::string                         savedir = "" + value["request_id"].asString() + ".json";
   std::cout << "Saving file as " << savedir << std::endl;
   std::ofstream outputFileStream(savedir);
   writer->write(value, &outputFileStream);

   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Helper function that takes in a string and returns a Json Value object that can be indexed
 * The old reader was deprecated and in its place much more complicated code
 *
 * @param str
 * @return Json::Value
 */
Json::Value ServiceXHandler::JsonFromStr(std::string jsonStr)
{
   Json::Value root;

   Json::CharReaderBuilder builder;
   Json::CharReader *      reader = builder.newCharReader();
   builder["collectComments"]     = false;
   Json::Value value;
   std::string errs;
   // std::cout << "parsing jsonfromstr\n";
   bool parsingSuccessful = reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &value, &errs);
   delete reader;

   if (!parsingSuccessful) {
      std::cout << "Failed to parse the JSON, errors:" << std::endl;
      std::cout << errs << std::endl;
      return 1;
   }

   // Json::Value reqId = value["request_id"];

   // std::cout << reqId << std::endl;
   return value;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Gets MinIO bucket data and prints it. Takes in a bucket name (request_id) and a pathkey
 * that specifies where the program will write the downloaded files to disk.
 *
 * @return A list of downloaded file names
 */
std::vector<std::string> ServiceXHandler::GetMinIOData(std::string bucketName, std::string pathkey)
{
   std::vector<std::string> filenames;

   std::string        BucketName = bucketName;
   Aws::SDKOptions    m_options;
   Aws::S3::S3Client *m_client = {NULL};

   Aws::InitAPI(m_options);
   Aws::Client::ClientConfiguration cfg;
   cfg.endpointOverride = "cmsopendata-minio.servicex.ssl-hep.org";
   cfg.scheme           = Aws::Http::Scheme::HTTP;
   cfg.verifySSL        = false;
   m_client             = new Aws::S3::S3Client(Aws::Auth::AWSCredentials("miniouser", "leftfoot1"), cfg,
                                    Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);

   Aws::S3::Model::ListObjectsRequest objRequest;
   objRequest.WithBucket(BucketName);

   auto outcome = m_client->ListObjects(objRequest);

   if (outcome.IsSuccess()) {
      // std::cout << "Objects in bucket '" << BucketName << "':"
      // << std::endl << std::endl;

      Aws::Vector<Aws::S3::Model::Object> objects = outcome.GetResult().GetContents();
      std::vector<std::string>            objectKeys;
      std::vector<std::string>::iterator  it;

      it = objectKeys.begin();
      // Gets all object keys
      for (Aws::S3::Model::Object &object : objects) {
         // std::cout << object.GetKey() << std::endl;
         objectKeys.push_back(object.GetKey());
      }

      // Path key
      std::cout << "Downloading to: " << pathkey << "\n";

      // Downloads files with object keys

      // This loop is the costly one, where making the RDataFrame dynamically will have to be done
      // The objects are donwloaded in order during this loop.q
      // After each item is downloaded, add it to the RDataFrame.
      for (std::string objectKey : objectKeys) {

         // Get object
         // std::cout << "Getting object " << objectKey << "\n";

         // std::string pathkey = "temp";
         Aws::S3::Model::PutObjectRequest putObjectRequest;
         putObjectRequest.WithBucket(BucketName.c_str()).WithKey(objectKey.c_str());

         Aws::S3::Model::GetObjectRequest object_request;
         object_request.SetBucket(BucketName);
         object_request.SetKey(objectKey);
         // if()
         Aws::S3::Model::GetObjectOutcome get_object_outcome = m_client->GetObject(object_request);

         if (get_object_outcome.IsSuccess()) {
            std::string   filepath = pathkey + objectKey;
            Aws::OFStream local_file;
            local_file.open(filepath.c_str(), std::ios::out | std::ios::binary);
            local_file << get_object_outcome.GetResult().GetBody().rdbuf();
            local_file.close();
            filenames.push_back(filepath);
            // std::cout << "Done!" << std::endl;

         } else {
            auto err = get_object_outcome.GetError();
            std::cout << "Error: GetObject: " << err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
         }
      }

      std::cout << "Done!" << std::endl;
      return filenames;
   } else {
      std::cout << "Error: ListObjects: " << outcome.GetError().GetMessage() << std::endl;
   }
   std::cerr << "Warning, end of method reached, should not have reached here.\n";
   return filenames;
}
