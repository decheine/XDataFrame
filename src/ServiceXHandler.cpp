// Standard Includes
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <regex>
#include <iterator> 
#include <map>

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

// Project
#include "ServiceXHandler.h"


using namespace std;

/// YAML Methods

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

static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

// TODO: Fix/build the servicex.yaml parser, correctly. Design what things we need from the file

/**
 * @brief reads and parses the servicex.yaml file and stores 
 * the endpoint, token, and type
 * 
 * @return a tree of all the data?
 */
std::map<std::string, std::string> ServiceXHandler::parseYaml(std::string targetName){

    // Check if file exists
    // std::string myText;
    // std::ifstream infile("~/servicex.yaml");
    // if(!infile.good()){
    //     std::cout << "servicex.yaml not found in home directory. Exiting.\n";
    //     exit(1);
    // }
    std::map<std::string, std::string> properties; 
    properties["endpoint"] = "";
    const char* homeDir = getenv("HOME");
    // std::cout << "homedir: " << homeDir << "\n"; 

    std::string line;
    const std::string fullDir = homeDir + targetName;
    std::ifstream myfile (fullDir);
    if (myfile.is_open())
    {
        // std::string fields;
        // while ( getline (myfile,line) ){
        //     std::cout << line << '\n';
        //     fields << line << std::endl;
        // }

        std::string content;
        content.assign( (std::istreambuf_iterator<char>(myfile) ),
                (std::istreambuf_iterator<char>()    ) );   

        // ryml can parse in situ (and read-only buffers too):

        // strcpy(src, content.c_str());
        // char src[];
        c4::substr srcview = c4::to_substr(content); // a mutable view to the source buffer
        // there are also overloads for reusing the tree and parser
        ryml::Tree tree = ryml::parse(srcview);

        // get a reference to the "foo" node
        ryml::NodeRef node = tree["api_endpoints"];
        std::cout << "Number of children: " << node.num_children() << std::endl;
        ryml::NodeRef subNode = node.find_child("sub2");
        ryml::NodeRef subFirst = node.child(0);

        // ryml::NodeRef api_endpointNode = tree["api_endpoints"];
        char src[] = "type";
        c4::substr epName = src; 
        // ryml::NodeRef endpointNode = tree["api_endpoints"].find_child(epName);
        ryml::NodeRef api_endpointNode = tree["api_endpoints"].child(0);
        // ryml::NodeRef typeNode = tree["api_endpoints"];
        
        ryml::NodeRef endpointNode = api_endpointNode.find_child("endpoint");
        ryml::NodeRef typeNode = api_endpointNode.find_child("type");
        ryml::NodeRef tokenNode = api_endpointNode.find_child("token");

        // TODO: Needs to search and verify that the nodes are there before they are referenced.

        // show_val(tree["sub"].child(0)[0]);  // "foo: 1"
        // show_val(subFirst[0]);
        // show_keyval(api_endpointNode[0]);
        std::cout << "Number of children of endpoint: " << api_endpointNode.num_children() << std::endl;

        // show_val(typeNode[0]);
        // show_val(tokenNode[0]);

        show_keyval(endpointNode);
        // show_keyval(tokenNode);
        // show_keyval(typeNode);
        
        std::string endpoint;
        std::string token;
        std::string mytype;

        c4::from_chars(endpointNode.val(), &endpoint);
        // c4::from_chars(tokenNode.val(), &token);
        // c4::from_chars(typeNode.val(), &mytype);

        // std::cout << "Endpoint: " << endpoint << std::endl;
        // std::cout << "Token: " << token << std::endl;
        // std::cout << "Type: " << mytype << std::endl;



        myfile.close();

        // This will be expanded later
        std::map<std::string, std::string> properties; 
        properties["endpoint"] = endpoint;
        // properties["token"] = token;
        // properties["type"] = mytype;
        

        return properties;
       
    } else std::cout << "Unable to open file\n"; 
    
    std::cout << " - Read servicex.yaml\n";
    return properties;
}

std::string ServiceXHandler::FetchData(std::string request_id){
    // CURL *curl = curl_easy_init();
    // std::string request_id = "345974d4-d2ec-49bb-bef2-6683b7e461d5";
    std::string serviceXURL = "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation/";
    const char* requestURL =  "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation/345974d4-d2ec-49bb-bef2-6683b7e461d5";
    std::string tmpURL =  (serviceXURL + request_id);
    std::cout << "tmpurl: " << tmpURL << "\n";
    const char* targetURL = tmpURL.c_str();
    
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // GET request
    std::cout << "Doing GET request\n";
    CURL *curl = curl_easy_init();
    std::string response_string;
    std::string header_string;
    std::cout << "targeturl: " << targetURL << "\n";
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, requestURL);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, -1L);
        // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        // curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 2L);


        std::cout << "easy perform\n";
        curl_easy_perform(curl);
        std::cout << "done easy perform\n";
        cout << response_string;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;
    }

    // std::cout << "Response: " << response_string << std::endl;
    return response_string;
}

void getStatus(std::string request_id){

}


void MakeDirectory(){

    // const char* homeDir = getenv("HOME");

    // const std::string fullDir = homeDir + ""



    // boost::filesystem::path dir("");
	// if(boost::filesystem::create_directory(dir)) {
	// 	std::cout << "Success" << "\n";
	// }
    return;
}




int ServiceXHandler::SaveJson(Json::Value value){
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


/**
 * @brief Helper function that takes in a string and returns a Json Value object that can be indexed
 * The old reader was deprecated and in its place much more complicated code
 * 
 * @param str 
 * @return Json::Value 
 */
Json::Value ServiceXHandler::JsonFromStr(std::string jsonStr){
    Json::Value root;
    
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    builder["collectComments"] = false;
    Json::Value value;
    std::string errs;
    std::cout << "parsing\n"; 
    bool parsingSuccessful = reader->parse(
        jsonStr.c_str(),
        jsonStr.c_str() + jsonStr.size(),
        &value,
        &errs
    );
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










