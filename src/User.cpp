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

// ROOT
#include "TFolder.h"
#include "TDirectory.h"
#include "TROOT.h"
#include "TString.h"
#include "TObject.h"
#include "TObjString.h"
// #include ""

// Curl
#include <curl/curl.h>

// Jsoncpp
// #include <json/value.h>

#include <User.h>

// DEPRECATED ?

/**
 * @brief Creates a folder for a new user if it doesn't exist already
 * 
 * @param userName Folder name
 * @return int success
 */
int User::CreateUserFolder(std::string userName){
    return 0;
}

int User::CreateROOTUserFolder(std::string userName){

    // Add the top folder of my hierary to //root
    TFolder *userfolder=gROOT->GetRootFolder()->AddFolder("userfolder",
                                    "userfolder top level folders");
    // Add the hierarchy to the list of browsables
    gROOT->GetListOfBrowsables()->Add(userfolder,userName.c_str());
 
    // Create and add the constants folder
    TFolder *requests=userfolder->AddFolder("Requests", "ServiceX requests this user has made");
 
    // make demo request

    std::string requestName = "r1";
    std::string request_id = "345974d4-d2ec-49bb-bef2-6683b7e461d5";

    TFolder *request1 = requests->AddFolder(requestName.c_str(), request_id.c_str() );
 
    // folders contain TObjString 's for the values?

    // TObjString req_id(request_id.c_str());
    // TObject* reqobj;
    // TList aList;

    TObjString* req_id = new TObjString(request_id.c_str());
    TObjString* request_id_title = new TObjString("request_id");
    TObjArray objArray;

    objArray.Add(req_id);

    TMap* map = new TMap();

    map->Add(request_id_title, req_id);

    request1->AddFolder("map", "desc", map);

    
    userfolder->SaveAs((userName+".root").c_str());
 
    return 0;
}

User::User(){

}
