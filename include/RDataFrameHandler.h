#ifndef RDATAFRAMEHANDLER_H
#define RDATAFRAMEHANDLER_H

// ROOT includes

#include <ROOT/RDataFrame.hxx>



// TODO: Some comments on what this is.
class RDataFrameHandler {
    public:
        // Vector of absolute paths of the files
        std::vector<std::string> filenames;

        int AddFile(std::string filename);
        int AddFiles(std::vector<std::string> filenames);
        ROOT::RDataFrame CreateRDataFrame();
        std::string GetTreeName(std::string filepath);



        RDataFrameHandler();
    private:
        ROOT::RDataFrame* RDataFrameObject;

};

#endif