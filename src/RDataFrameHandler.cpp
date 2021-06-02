/* RDataFrame Handler Module
Much of this (for now) takes from theh RDataFrame tutorial 
*/

#include "RDataFrameHandler.h"

Double_t Simple::GetX() const {return x;}


void Handler::fill_tree(const char *treeName, const char *fileName){
    ROOT::RDataFrame d(10);
    int i(0);
    d.Define("b1", [&i]() { return (double)i; })
        .Define("b2",
                [&i]() {
                    auto j = i * i;
                    ++i;
                    return j;
                })
        .Snapshot(treeName, fileName);
    return;
}


ROOT::RDataFrame Handler::CreateRDataFrame(){
    auto fileName = "df001_introduction.root";
    auto treeName = "myTree";
    fill_tree(treeName, fileName);

    // We read the tree from the file and create a RDataFrame, a class that
    // allows us to interact with the data contained in the tree.
    // We select a default column, a *branch* to adopt ROOT jargon, which will
    // be looked at if none is specified by the user when dealing with filters
    // and actions.
    ROOT::RDataFrame d(treeName, fileName, {"b1"});

    return d;
}