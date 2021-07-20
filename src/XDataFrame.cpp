
#include "XDataFrame.h"

// Double_t XDataFrame::GetX() const {return x;}

// ClassImp(XDataFrame)


ROOT::RDataFrame* XDataFrame(std::string inputString){
    ServiceXHandler xHandler;
    std::vector<std::string> userYaml;
    std::map<std::string, std::string> values = xHandler.parseYaml("/servicex.yaml");

    Request testRequest;

    MCache cache;


    testRequest.SendRequest(values, "/submit_request.json", &cache);
    // std::cout << "Saving json of response\n"; 
    // testRequest.SaveJson(testRequest.SubmitRequestJson);


    Hasher hasher;
    std::string hashVal;
    hashVal = hasher.GetHashOf("/submit_request.json");
    std::cout << "request_id: " << testRequest.request_id << "\n";
    std::string pathkey;
    pathkey = cache.GetCacheDir() + "/" + hashVal + "/";
    // Only call this if user specifically wants to refresh the data or if there are no data files. 
    // For now, do it every time. 
    std::vector<std::string> filenameList;
    filenameList = xHandler.GetMinIOData(testRequest.request_id, pathkey);


    // RDataFrame Part

    RDataFrameHandler rdfHandler;
    rdfHandler.AddFiles(filenameList);
    ROOT::RDataFrame* myDataFrame = rdfHandler.CreateRDataFrame();
    // auto d1 = myDataFrame.Display();
    // d1->Print();
    // rdfHandler.DisplayRDF();

    std::cout << "Finished\n";
    return myDataFrame;
}
