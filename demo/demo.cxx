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

    std::string requestString = "{     \"did\": \"cernopendata://1507\",       \"selection\": \"(call ResultTTree (call Select (call SelectMany (call EventDataset 'ServiceXSourceCMSRun1AOD') (lambda (list e) (call (attr e 'TrackMuons') 'globalMuons'))) (lambda (list m) (call (attr m 'pt')))) (list 'mu_pt') 'treeme' 'file.root')\",     \"result-destination\": \"object-store\",     \"result-format\": \"root-file\",     \"chunk-size\": \"1000\",     \"workers\": \"10\"}";

    // Getting the RDataFrame
    ROOT::RDataFrame mydf = XDataFrame(requestString);

    std::cout << "Filtering\n";

    // Setting up canvas to draw on
    TCanvas* canvas = new TCanvas();

    // Obtaining a 1D histogram after applying filters to mydf
    auto filtered_h = mydf.Filter("mu_pt > 10").Filter("mu_pt < 1000").Histo1D("mu_pt");

    // Draw and save histogram to pdf
    filtered_h->Draw();
    canvas->Update();
    canvas->Print("demoFilter1.pdf");

    return 0;
}