/* RDataFrame Handler Module
Much of this (for now) takes from theh RDataFrame tutorial 
*/

// Standard Includes
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <iterator> 
#include <map>

#include "RDataFrameHandler.h"

/**
 * @brief Creates the RDataFrame objecct with the file list in the RDataFrameHandler
 * Returns 0 if successful
 * Returns 1 if not successful
 * @return ROOT::RDataFrame
 */
ROOT::RDataFrame* RDataFrameHandler::CreateRDataFrame(){
    // TODO: read the files fetched and get the tree name they have
    auto treeName = "treeme";

    // We read the tree from the file and create a RDataFrame, a class that
    // allows us to interact with the data contained in the tree.
    // We select a default column, a *branch* to adopt ROOT jargon, which will
    // be looked at if none is specified by the user when dealing with filters
    // and actions.
    std::cout << "Filename1: " << filenames[0] << "\n";
    ROOT::RDataFrame df(treeName, filenames);

    RDataFrameObject = &df;

    // Testing for printing out the RDF.

    std::cout << "Displaying\n";

    auto d1 = df.Display();
    d1->Print();

    std::cout << "Displaying 2 \n";

    auto d2 = RDataFrameObject->Display();
    d2->Print();


    return RDataFrameObject;
}

/**
 * @brief Adds a file to the RDataFrameHandler's list of filenames. Want the absolute path to the file
 * Return 0 if no problems and the file exists.
 * Return 1 if the file does not exist
 * @param filename 
 * @return int 
 */
int RDataFrameHandler::AddFile(std::string filename){
    filenames.push_back(filename);
    // Check if exists first
    return 0;
}

/**
 * @brief adds multiple files
 * 
 */
int RDataFrameHandler::AddFiles(std::vector<std::string> filenames){
    for (auto iter = filenames.begin(); iter != filenames.end(); ++iter)
    {  
        // If iter is a valid file:
        // std::cout << "adding " << iter->c_str() << "\n";
        AddFile(iter->c_str());
        // attack->makeDamage();
    }
    return 0;
}

RDataFrameHandler::RDataFrameHandler(){}


void RDataFrameHandler::DisplayRDF(){
    // ROOT::RDataFrame rdf = *RDataFrameObject;
    std::cout << "Displaying\n";

    auto d1 = RDataFrameObject->Display();
    d1->Print();
}