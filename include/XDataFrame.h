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
        int x;
    public:
        int y;
        ROOT::RDataFrame GetRDataFrame(std::string input);

    ClassDef(XDataFrame, 1)

};

#endif