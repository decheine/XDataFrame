// Standard includes


#include "../include/XDataFrameConfig.h.in"
// Include ROOT
#include "TF1.h"
#include "TRint.h"
#include "TCanvas.h"

// Include ServiceX ?
#include "ServiceXHandler.h"

using namespace std;

int main(int argc, char* argv[]){
    std::cout << "Hello world \n";

    // if (argc < 2) {
    //     // report version
    //     // Show usage 
    //     std::cout << argv[0] << " Version " << XDataFrame_VERSION_MAJOR << "."
    //             << XDataFrame_VERSION_MINOR << std::endl;
    //     std::cout << "Usage: " << argv[0] << " number" << std::endl;
    //     return 1;
    // }

    ServiceXHandler xHandler;
    std::vector<std::string> userYaml;
    userYaml = xHandler.readYaml();
    // 1 - endpoint
    // 2 - token
    // 3 - type
    // userYaml.at(1);




    // Runs basic ROOT app with the arguments given for main
    // TRint app("app", &argc, argv);

    // Testing. Makes some drawings on a TCanvas
    // TCanvas* c = new TCanvas("c", "Something", 0, 0, 800, 600);
    // TF1 *f1 = new TF1("f1","sin(x)", -5, 5);
    // f1->SetLineColor(kBlue+1);
    // f1->SetTitle("My graph;x; sin(x)");
    // f1->Draw();
    // c->Modified(); c->Update();
    //


    // Run and finish with ROOT prompt
    // app.Run();
    return 0;
}