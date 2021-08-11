#ifndef XDATAFRAME_H
#define XDATAFRAME_H

// Standard includes
#include <string> 


// ROOT
#include <ROOT/RDataFrame.hxx>


/**
 * @brief XDataFrame root level class. 
 * 
 * In the future, this could be implemented similar to how RDataFrame is implemented,
 * where it is an object that represents an RDataFrame instead of using a fetching
 * method to do it. 
 * 
 */

ROOT::RDataFrame XDataFrame(std::string inputString);


#endif