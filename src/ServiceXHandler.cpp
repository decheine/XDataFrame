// // Check if file exists
//             ifstream infile("~/servicex.yaml");
//             if(!infile.good()){
//                 std::cout << "servicex.yaml not found in home directory. Exiting.\n";
//                 exit(1);
//             }
//             string myText;
//             ifstream ReadFile("~/servicex.yaml");

//             // Use a while loop together with the getline() function to read the file line by line
//             while (getline(ReadFile, myText)) {
//             // Output the text from the file
//                 cout << myText;
//             }

//             TFile readYaml("~/servicex.yaml");
            
//             // Make new file object from  /servicex.yaml
//             return 0;


#include <iostream>
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <string>
#include <filesystem>
#include <regex>
#include <iterator> 

#include <stdlib.h>

#include "ServiceXHandler.h"

using namespace std;
// ServiceXHandler::ServiceXHandler(){

// }
// ServiceXHandler::~ServiceXHandler() { }

/**
 * @brief reads and parses the servicex.yaml file and stores 
 * the endpoint, token, and type
 * 
 * @return std::vector<std::string> 
 */
std::vector<std::string> ServiceXHandler::readYaml(){

    // Check if file exists
    // std::string myText;
    // std::ifstream infile("~/servicex.yaml");
    // if(!infile.good()){
    //     std::cout << "servicex.yaml not found in home directory. Exiting.\n";
    //     exit(1);
    // }
    std::vector<std::string> outputStr;

    const char* homeDir = getenv("HOME");
    std::cout << "homedir: " << homeDir << "\n"; 

    std::string line;
    std::string targetName = "/servicex.yaml";
    const std::string fullDir = homeDir + targetName;
    std::ifstream myfile (fullDir);
    if (myfile.is_open())
    {
        std::vector<std::string> fields;
        while ( getline (myfile,line) ){
            //std::cout << line << '\n';
            fields.push_back(line);
        }

        // std::vector<std::string>::iterator ptr;
        // for (ptr = fields.begin(); ptr < fields.end(); ptr++)
        //     std::cout << *ptr << " \n";
        //     regex regexp("token: ");
        //     smatch m;

        //     regex_search(*ptr, m, regexp);
        //     std::cout << "Printing trimmed strings\n";
        //     for (auto x : m)
        //         std::cout << x << " \n";

        // 1
        
        string endpoint;
        std::string token;
        string mytype;
        
        regex regexEndpoint(" *- *endpoint: ");
        regex regexToken(" *token: ");
        regex regexType(" *type: ");
        endpoint = regex_replace(fields.at(1), regexEndpoint, "");
        token = regex_replace(fields.at(2), regexToken, "");
        mytype = regex_replace(fields.at(3), regexType, "");
        // regex_search(fields.at(2), m, regexToken);

        outputStr.push_back(endpoint);

        std::cout << endpoint << "\n";
        myfile.close();

       
    }

    // else std::cout << "Unable to open file\n"; 

    // Parse YAML

    // YAML::Node doc = YAML::LoadFile(fullDir);

    // YAML::Node node = YAML::LoadFile(fullDir.c_str());
    // if (doc["api_endpoints"]){
    //     std::cout << doc["api_endpoints"].as<std::string>();
    // }


    return outputStr;

    // // Use a while loop together with the getline() function to read the file line by line
    // while (getline(ReadFile, myText)) {
    // // Output the text from the file
    //     std::cout << myText;
    // }

    // TFile readYaml("~/servicex.yaml");
    
    // Make new file object from  /servicex.yaml
}

User::User(std::string end, std::string tok, std::string typ){
    endpoint = end.c_str();
    token = tok.c_str();
    apiType = typ.c_str();
}