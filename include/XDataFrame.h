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
// class XDataFrame {
//     private:
//         Double_t x;
//     public:
//         // Constructor and intitializer. After the colon, variables are initialized with the values listed
//         XDataFrame() : x(2.5) {}
//         ROOT::RDataFrame GetRDataFrame(std::string input);
//         Double_t GetX() const;


//         ClassDef(XDataFrame, 1)

// };

// TODO: For what this is, this is a HUGE number of includes. Minimize as much as possible the
// number of includes?
// Done, moved the includes over to XDataFrame.cpp, where they are actually used.

ROOT::RDataFrame XDataFrame(std::string inputString);


#endif