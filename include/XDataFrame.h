#ifndef XDATAFRAME_H
#define XDATAFRAME_H

// Standard includes
#include <stdlib.h>
#include <iostream>

#include <ROOT/RDataFrame.hxx>
#include <ROOT/RDF/RDisplay.hxx>


/**
 * @brief XDataFrame root level class. 
 * 
 * In the future, this could be implemented similar to how RDataFrame is implemented,
 * where it is an object that represents an RDataFrame instead of using a fetching
 * method to do it. 
 * 
 */
class XDataFrame {
    private:
        Double_t x;
    public:
        // Constructor and intitializer. After the colon, variables are initialized with the values listed
        XDataFrame() : x(2.5) {}
        ROOT::RDataFrame GetRDataFrame(std::string input);
        Double_t GetX() const;


        ClassDef(XDataFrame, 1)

};

#endif