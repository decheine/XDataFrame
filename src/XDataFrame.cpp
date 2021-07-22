#include <string>

#include "XDataFrame.h"

ROOT::RDataFrame XDataFrame(std::string inputString){
    std::cout << "begin\n";
    ServiceXHandler xHandler;
    std::vector<std::string> userYaml;
    std::map<std::string, std::string> values = xHandler.parseYaml("/servicex.yaml");

    Request testRequest;

    MCache cache;

    //Change this to 
    testRequest.SendRequest(values, inputString, &cache);
    // std::cout << "Saving json of response\n"; 
    // testRequest.SaveJson(testRequest.SubmitRequestJson);


    Hasher hasher;
    std::string hashVal;
    hashVal = hasher.GetHashOf(inputString);
    std::cout << "request_id: " << testRequest.request_id << "\n";
    std::string pathkey;
    pathkey = cache.GetCacheDir() + "/" + hashVal + "/";
    // Only call this if user specifically wants to refresh the data or if there are no data files. 
    // For now, do it every time. 

    // Wait until job is done.
    
    // Check on status of job
    std::cout << "Checking status of job " + testRequest.request_id + "\n";
    std::string updateString;
    updateString = xHandler.FetchData(testRequest.request_id);
    // std::cout << "Response: " + updateString + "\n";

    xHandler.WaitOnJob(testRequest.request_id);


    std::vector<std::string> filenameList;
    filenameList = xHandler.GetMinIOData(testRequest.request_id, pathkey);

    // std::cout << "Filename 1: " + filenameList.at(0) + "\n";

    // RDataFrame Part

    RDataFrameHandler rdfHandler;
    rdfHandler.AddFiles(filenameList);
    ROOT::RDataFrame myDataFrame = rdfHandler.CreateRDataFrame();
    // auto d1 = myDataFrame.Display();
    // d1->Print();
    // rdfHandler.DisplayRDF();

    std::cout << "Finished\n";
    return myDataFrame;
}
