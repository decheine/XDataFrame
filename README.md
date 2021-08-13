# XDataFrame
ServiceX to RDataFrame framework

## Installation

### Dependencies

Before building, some dependencies need to be installed. For Ubuntu, they are

```
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install libboost-all-dev

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

To run the demo, simply run

```
./Demo
```


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

