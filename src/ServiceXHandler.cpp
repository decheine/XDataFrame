// Standard Includes
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <filesystem>
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

std::string ServiceXHandler::fetchData(std::string request_id){
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

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 2L);


        std::cout << "easy perform\n";
        curl_easy_perform(curl);
        std::cout << "done easy perform\n";
        cout << response_string;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;
    }

    std::cout << "Response: " << response_string << std::endl;
    return response_string;
}

void getStatus(std::string request_id){

}

// User::User(std::string end, std::string tok, std::string typ){
//     endpoint = end.c_str();
//     token = tok.c_str();
//     apiType = typ.c_str();
// }

User::User(){
//  Check if User folder exists
//      if it doesn't, make it
//  
}

void User::setEndpoint(char* endpoint){
    User::endpoint = endpoint;
}
void User::setToken(char* token){
    User::token = token;
}
void User::setType(char* type){
    User::apiType = type;
}



// Request

Json::Value Request::getStatus(){
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

        std::cout << response_string;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;
    }

    std::cout << "Response: " << response_string << std::endl;
    return response_string;
}


// Request::Request(){
//     this. 
    
// }
size_t Request::writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data){
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int Request::sendRequest(std::map<std::string, std::string> values, std::string submitRequestJson) {
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
            // curl_easy_setopt(curl, CURLOPT_POST, 1L);

            // curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
            
        
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 2L);

            // curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

            // curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
            // curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
            // curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
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

        std::cout << "Response: " << response_string << std::endl;
        // put response_string to a variable
    }catch (std::exception &ex)  
        {  
            printf("curl exception %s.\n", ex.what());  
        } 
    return 0;
}


Request::Request() {

}






















