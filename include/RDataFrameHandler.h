#ifndef RDATAFRAMEHANDLER_H
#define RDATAFRAMEHANDLER_H

// ROOT includes
#include <ROOT/RDataFrame.hxx>
#include <Rtypes.h>

class RDataFrameHandler {
    public:
        // Vector of absolute paths of the files
        std::vector<std::string> filenames;
        
        // adds a file to "filenames"
        Int_t AddFile(std::string filename);

        // adds multiple files to "filenames"
        Int_t AddFiles(std::vector<std::string> filenames);

        // constructs and returns the RDataFrame based on
        // current files in "filenames"
        ROOT::RDataFrame CreateRDataFrame();

        // returns the name of the top level tree of a 
        // ROOT file. This is needed to construct the RDataFrame
        // properly
        std::string GetTreeName(std::string filepath);


        RDataFrameHandler();

};

#endif