/* RDataFrame Handler Module
Much of this (for now) takes from theh RDataFrame tutorial 
*/

#include "RDataFrameHandler.h"

void RDFHandler::fill_tree(const char *treeName, const char *fileName){
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
 * @brief Creates the RDataFrame objecct with the file list in the RDFHandler
 * Returns 0 if successful
 * Returns 1 if not successful
 * @return int
 */
int RDFHandler::CreateRDataFrame(){
    auto fileName = "df001_introduction.root";
    auto treeName = "myTree";
    fill_tree(treeName, fileName);

    // We read the tree from the file and create a RDataFrame, a class that
    // allows us to interact with the data contained in the tree.
    // We select a default column, a *branch* to adopt ROOT jargon, which will
    // be looked at if none is specified by the user when dealing with filters
    // and actions.
    ROOT::RDataFrame d(treeName, fileName, {"b1"});

    RDataFrameObject = d;

    return 0;
}

/**
 * @brief Adds a file to the RDFHandler's list of filenames. Want the absolute path to the file
 * Return 0 if no problems and the file exists.
 * Return 1 if the file does not exist
 * @param filename 
 * @return int 
 */
int RDFHandler::AddFile(std::string filename){
    filenames.push_back(filename);
    // Check if exists first
    return 0;
}

/**
 * @brief adds multiple files
 * 
 */
int RDFHandler::AddFiles(std::vector<std::string> filenames){
    for (auto iter = filenames.begin(); iter != filenames.end(); ++iter)
    {  
        // If iter is a valid file:
        std::cout << "adding " << iter->c_str();
        AddFile(iter->c_str());
        // attack->makeDamage();
    }
    return 0;
}
