#ifndef XDATAFRAME_H
#define XDATAFRAME_H

// Standard includes
#include <string> 


// ROOT
#include <ROOT/RDataFrame.hxx>


/**
 * @brief XDataFrame root level class. 
 * 
 * Input a ServiceX input string to XDataFrame to submit the job and wait on the
 * results of the transformation. It will return an RDataFrame object populated 
 * with the resulting ROOT files from ServiceX.
 * 
 */

ROOT::RDataFrame XDataFrame(std::string inputString);


#endif