// Standard includes
#include <map>
#include <iostream>

#include "../include/XDataFrameConfig.h.in"
// Include ROOT
#include "TF1.h"
#include "TRint.h"
#include "TCanvas.h"

// ryml
#include <ryml.hpp>

// Curl
#include <curl/curl.h>



// ServiceX
#include "ServiceXHandler.h"

using namespace std;

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int main(int argc, char* argv[]){
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
    User theUser();
    std::map<std::string, std::string> values = xHandler.parseYaml();

    for (std::map<std::string, std::string>::iterator it = values.begin(); it != values.end(); ++it){
        std::cout << it->second << std::endl;
    }
    // std::for_each(values.begin(), values.end()){
    //     std::cout << s << std::endl;
    // }

    // curlopt_post
    // CURLOPT_HTTPGET

    // CURL *curl = curl_easy_init();
    std::string request_id = "345974d4-d2ec-49bb-bef2-6683b7e461d5";
    std::string serviceXURL = "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation/";
    const char* requestURL = "https://cmsopendata.servicex.ssl-hep.org/servicex/transformation/345974d4-d2ec-49bb-bef2-6683b7e461d5";
    const char* targetURL = (serviceXURL + request_id).c_str();
    

    std::string response_string = xHandler.fetchData(request_id);
    std::cout << "Response: " << response_string << std::endl;


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
    std::cout << "Finished\n";
    return 0;
}