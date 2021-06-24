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
#include <streambuf>
#include <filesystem>
#include <regex>
#include <iterator> 
#include <map>

#include <c4/yml/preprocess.hpp>
#include <c4/yml/std/string.hpp>

#include <ryml.hpp>

#include <stdlib.h>

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


// TODO: Fix/build the servicex.yaml parser, correctly. Design what things we need from the file

/**
 * @brief reads and parses the servicex.yaml file and stores 
 * the endpoint, token, and type
 * 
 * @return a tree of all the data?
 */
std::map<std::string, std::string> ServiceXHandler::parseYaml(){

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
    std::string targetName = "/test.yml";
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
        show_keyval(tokenNode);
        show_keyval(typeNode);
        
        std::string endpoint;
        std::string token;
        std::string mytype;

        c4::from_chars(endpointNode.val(), &endpoint);
        c4::from_chars(tokenNode.val(), &token);
        c4::from_chars(typeNode.val(), &mytype);

        std::cout << "Endpoint: " << endpoint << std::endl;
        std::cout << "Token: " << token << std::endl;
        std::cout << "Type: " << mytype << std::endl;



        myfile.close();

        // This will be expanded later
        std::map<std::string, std::string> properties; 
        properties["endpoint"] = endpoint;
        properties["token"] = token;
        properties["type"] = mytype;
        

        return properties;
       
    } else std::cout << "Unable to open file\n"; 
    
    std::cout << " - Read servicex.yaml\n";
    return properties;
}



// User::User(std::string end, std::string tok, std::string typ){
//     endpoint = end.c_str();
//     token = tok.c_str();
//     apiType = typ.c_str();
// }

User::User(){

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