#pragma once

#include <TLorentzVector.h>

// ROOT includes

#include <ROOT/RDataFrame.hxx>


class Simple {
    double x;

public:
    Simple() : x(2.5) {}
    double GetX() const;

    ClassDef(Simple,1)
};

class Handler {
    double y;
    ROOT::RDataFrame *RDataFramePointer;

public:
    Handler();
    void fill_tree(const char *treeName, const char *fileName);
    ROOT::RDataFrame CreateRDataFrame();


    ClassDef(Handler,1);

};