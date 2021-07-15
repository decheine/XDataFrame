Designing this as a more effective library.

## Summary

Have header file/class that can be called like 
```
XDataFrame("<qastle string>")
```

And returned the XDataFrame created by that. 

## Ideas

XDataFrame.h will have the class that is called. 
CMake should create a library with all the functionality. And then link that library to an executable, like the demo. 
It should be enough on the future programmer's part to just
```
#include <XDataFrame.h>
```
