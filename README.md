# XDataFrame
ServiceX to RDataFrame framework

### Building
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

