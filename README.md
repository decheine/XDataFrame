# XDataFrame
ServiceX to RDataFrame framework




## Installation




### Dependencies

Before building, the project's dependencies need to be installed. These dependencies are
  * [AWS C++ sdk](https://github.com/aws/aws-sdk-cpp) (core, dynamodb, s3)
  * [ryml](https://github.com/biojppm/rapidyaml)
  * c4core
  * jsoncpp
  * Boost
      * system, filesystem, unit_test_framework
  * and obviously ROOT



#### AWS SDK

First follow the README for building the [AWS C++ SDK](https://github.com/aws/aws-sdk-cpp) from source. This has been tested and works smoothly with Linux, but building on Windows with Visual Studio might be a different story. 


This project depends on some projects that use [vcpkg](https://vcpkg.io/en/index.html) as a package manager.

If you haven't used vcpkg before, you can clone it anywhere, but it's probably best put in your home user directory. From there, run

```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
```




### Building

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

You can run 
```
./XDataFrame <args>
```
To run the program.


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

