// Standard includes
#include <iostream>

#include "XDataFrameConfig.h.in"
// Include ROOT

// Include ServiceX ?



int main(int argc, char* argv[]){
    std::cout << "Hello world \n";

    if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << XDataFrame_VERSION_MAJOR << "."
                << XDataFrame_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }
    return 0;
}