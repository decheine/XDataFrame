// Standard includes
#include <stdlib.h>
#include <iostream>
#include <string>


// ROOT
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RDF/RDisplay.hxx>

// XDataFrame
#include "XDataFrame.h"


int main(int argc, char* argv[]){

    std::cout << "Hello world, let's use RDataFrame\n"; 


    std::string requestString = "{    \"did\": \"cernopendata://1507\",     \"selection\": \"(call ResultTTree (call Select (call SelectMany (call EventDataset 'ServiceXSourceCMSRun1AOD') (lambda (list e) (call (attr e 'TrackMuons') 'globalMuons'))) (lambda (list m) (call (attr m 'pt')))) (list 'mu_pt') 'treeme' 'file.root')\",     \"result-destination\": \"object-store\",     \"result-format\": \"root-file\",     \"chunk-size\": \"1000\",     \"workers\": \"10\"}";
    // Getting the RDataFrame


    ROOT::RDataFrame* mydf = XDataFrame(requestString);




    return 0;

}