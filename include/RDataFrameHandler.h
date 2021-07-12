#ifndef RDATAFRAMEHANDLER_H
#define RDATAFRAMEHANDLER_H

#include <TLorentzVector.h>

// ROOT includes

#include "ROOT/RDataFrame.hxx"

class RDataFrameHandler {
    public:
        std::vector<std::string> filenames;

        void fill_tree(const char *treeName, const char *fileName);
        int AddFile(std::string filename);
        int AddFiles(std::vector<std::string> filenames);
        void DisplayRDF();
        int CreateRDataFrame();

        RDataFrameHandler();
    private:
        ROOT::RDataFrame* RDataFrameObject;

};

#endif