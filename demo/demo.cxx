// Standard includes
#include <stdlib.h>
#include <iostream>
#include <string>


// ROOT
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RDF/RDisplay.hxx>
#include <TCanvas.h>

// XDataFrame
#include "XDataFrame.h"


int main(int argc, char* argv[]){

    std::string requestString = "{       \"did\": \"cernopendata://1507\",        \"selection\": \"(call ResultTTree (call Select (call SelectMany (call EventDataset 'ServiceXSourceCMSRun1AOD') (lambda (list e) (call (attr e 'TrackMuons') 'globalMuons'))) (lambda (list m) (call (attr m 'pt')))) (list 'mu_pt') 'treeme' 'file.root')\",     \"result-destination\": \"object-store\",     \"result-format\": \"root-file\",     \"chunk-size\": \"1000\",     \"workers\": \"10\"}";

    // Getting the RDataFrame
    ROOT::RDataFrame mydf = XDataFrame(requestString);

    std::cout << "Filtering\n";
    std::cout << "Using filter mydf.Filter(\"mu_pt > 10\").Filter(\"mu_pt < 1000\").Histo1D(\"mu_pt\");";

    // Setting up canvas to draw on
    TCanvas* canvas = new TCanvas();

    // Obtaining a 1D histogram after applying filters to mydf
    auto filtered_h = mydf.Filter("mu_pt > 10").Filter("mu_pt < 1000").Histo1D("mu_pt");


    std::cout << "Printing\n";
    // Draw and save histogram to pdf
    filtered_h->Draw();
    canvas->Update();
    canvas->Print("demoFilter1.pdf");

    std::cout << "A PDF of the output has been saved as \"demoFilter1.pdf\". \n";
    std::cout << "If you want to copy that file from the container to your local machine, from a new terminal window, run command\n";
    std::cout << "\n\t\t docker cp <container id>:/usr/src/xdataframe/demoFilter1.pdf ~\n\n";
    std::cout << "You can get the container id from running \n\n ";
    std::cout << "\t\t docker container ls  | grep 'decheine/xdataframe-demo-image' | awk '{print $1}' \n\n";
    std::cout << "In a new terminal window.\n\n Thank you for trying this demo!\n ";

    return 0;
}