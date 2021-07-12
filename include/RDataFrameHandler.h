#pragma once

#include <TLorentzVector.h>

// ROOT includes

#include <ROOT/RDataFrame.hxx>

class RDFHandler {

private:
    std::vector<std::string> filenames;
    ROOT::RDataFrame RDataFrameObject;

public:
    RDFHandler();
    void fill_tree(const char *treeName, const char *fileName);
    int AddFile(std::string filename);
    int AddFiles(std::vector<std::string> filenames);

    int CreateRDataFrame();


    ClassDef(RDFHandler,1);

};