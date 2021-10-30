# XDataFrame
ServiceX to RDataFrame framework

## Installation

### Dependencies

Before building, some dependencies need to be installed. For Ubuntu, they are

```
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install libboost-all-dev
```

A list of all dependencies:

- ROOT
- Boost
- OpenSSL
- curl
- [ryml](https://github.com/biojppm/rapidyaml)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- [aws-sdk-cpp](https://github.com/aws/aws-sdk-cpp)

The last three are taken care of by the CMakeLists.txt and fetched from their github repositories and built for your machine upon configuration and so are ready to be used to build this project during the build step.

### Method 1 - add_subdirectory

The easiest method of incorporating XDataFrame into your project is to:

1. Navigate to your project directory and clone the repo
 
```bash
git clone https://github.com/decheine/XDataFrame
```

2. You will need to find the globally installed dependencies, like ROOT and boost, by adding these lines to your CMakeLists.txt

```cmake
find_package(ROOT CONFIG REQUIRED COMPONENTS Core RIO Net Hist Tree Thread MultiProc ROOTDataFrame Gpad Rint )
find_package(Boost REQUIRED COMPONENTS system filesystem )
find_package(OpenSSL REQUIRED)
find_package( CURL REQUIRED )
```

3. Then add the subdirectory to your CMakeLists.txt

```cmake
add_subdirectory(XDataFrame)
```

4. Lastly, when linking libraries to your executable, add the XDataFrame library "XDataFrameLib" to your `target_link_libraries`

```cmake
target_link_libraries(YourProject PRIVATE ROOT::Core
                                        ROOT::RIO
                                        ROOT::Net
                                        ROOT::Hist 
                                        ROOT::Tree 
                                        ROOT::Thread 
                                        ROOT::MultiProc
                                        ROOT::ROOTDataFrame
                                        ROOT::Gpad
                                        ROOT::Rint
                                        XDataFrameLib
)
```

5. To include the library in your source code, use 

```c++
#include "XDataFrame.h"
```

And you should be all set. When you build your project, XDataFrame will build all on it's own and take care of everything for itself. 

### Building manually

To install the project you can create an optional folder for it to include other projects in that will utilize XDataFrame, to keep it all together.

Clone the repo

```bash
git clone https://github.com/decheine/XDataFrame
cd XDataFrame
```

Create a build directory

```bash
mkdir build
```

If needed, edit the CMakeLists.txt to point to your own installations 

From build directory, run the following to generate build files

```
cmake ..
```

Then run this to build

```
cmake --build .
```

To run the demo, simply run

```
./bin/Demo
```

## Try it out with the Docker Demo

The demo image is located on docker hub [here](https://hub.docker.com/repository/docker/decheine/xdataframe-demo-image).

Pull the image with 

```
docker pull decheine/xdataframe-demo-image
```


Once the image has been pulled, you can run it from the docker application. Wait until it has completed and you can follow the following steps to explore it further.


To enter the demo image

```
docker run -it xdataframe-demo-image:latest /bin/bash
```

It should take you into a new bash prompt. From there, to run the demo, do

```
./build/bin/Demo
```

And wait for it to complete. The results will be output to a pdf titled "demoFilter1.pdf". If you want to copy that file from the container to your local machine, from a new terminal window, run (TODO)

```
docker cp <container id>:/usr/src/xdataframe/demoFilter1.pdf ~
```

This copies the file to your home directory. You could replace "~" with whatever destination you would want.

Remark that there are still some bugs, so if there are jobs that are returning Fatal, exit the image and try running again.

## Notes

curl statement for making the web API call for ServiceX
```bash
curl -X POST http://localhost:5000/servicex/transformation   -H "Content-Type: application/json" -d submit_requst.json
```
Where `localhost:5000` is the address and port of your local server, or replaced by the user's endpoint. This is found in their `servicex.yaml` file, which is commonly and assumed to be located in the user's home directory. It looks something like

```yaml
api_endpoints:
  - endpoint: https://xaod.servicex.ssl-hep.org/
    token: somebigtokenthatistoomanycharactersandmathematicallyso.sinceanysecuritykeyinacryptographicsystema277characterkeyisdefinitelyoverkillthenagainicouldbewrongsincemylevelofknowledgeofcryptographyislimitedatbesttheonlyreasonthisstringexistsatallisbecauseifoundwritingthisveryamusing
    type: xaod
```







## Features
Expanding as I think of and syntesize these ideas
- Read the `servicex.yaml` file from the user's home directory.

