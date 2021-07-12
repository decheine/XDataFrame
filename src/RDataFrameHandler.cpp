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

void RDataFrameHandler::fill_tree(const char *treeName, const char *fileName){
    ROOT::RDataFrame d(10);
    int i(0);
    d.Define("b1", [&i]() { return (double)i; })
        .Define("b2",
                [&i]() {
                    auto j = i * i;
                    ++i;
                    return j;
                })
        .Snapshot(treeName, fileName);
    return;
}

/**
 * @brief Creates the RDataFrame objecct with the file list in the RDataFrameHandler
 * Returns 0 if successful
 * Returns 1 if not successful
 * @return int
 */
int RDataFrameHandler::CreateRDataFrame(){
    // auto fileName = "df001_introduction.root";
    auto treeName = "treeme";
    // fill_tree(treeName, fileName);

    // We read the tree from the file and create a RDataFrame, a class that
    // allows us to interact with the data contained in the tree.
    // We select a default column, a *branch* to adopt ROOT jargon, which will
    // be looked at if none is specified by the user when dealing with filters
    // and actions.
    std::cout << "Filename1: " << filenames[0] << "\n";
    ROOT::RDataFrame df(treeName, filenames);

    RDataFrameObject = &df;

    std::cout << "Displaying\n";

    auto d1 = df.Display();
    d1->Print();

    return 0;
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
        std::cout << "adding " << iter->c_str() << "\n";
        AddFile(iter->c_str());
        // attack->makeDamage();
    }
    return 0;
}

RDataFrameHandler::RDataFrameHandler(){
    
}


void RDataFrameHandler::DisplayRDF(){
    ROOT::RDataFrame rdf = *RDataFrameObject;
    rdf.Display();
}