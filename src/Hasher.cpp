#include "Hasher.h"
#include <iostream>
#include <fstream> 


std::string Hasher::GetHash(std::string filename){
    std::string s;

    const char* homeDir = getenv("HOME");
    // std::cout << "homedir: " << homeDir << "\n"; 
    const std::string fullDir = homeDir + filename;

    std::ifstream myFile(fullDir);
    if (!myFile) {
            std::cout << "No such file";
    } else {
        std::ostringstream tmp;
        tmp << myFile.rdbuf();
        std::string s = tmp.str();
        std::cout << s << std::endl;
        const char* jsonObj = s.c_str();

        md5 hash;
        md5::digest_type digest;

        hash.process_bytes(s.data(), s.size());
        hash.get_digest(digest);

        std::cout << "md5(" << s << ") = " << toString(digest) << '\n';

        myFile.close();
        return toString(digest);
    }
    

    return 0;
}


//   while(std::getline(my_file, s)) {
//             md5 hash;
//             md5::digest_type digest;

//             hash.process_bytes(s.data(), s.size());
//             hash.get_digest(digest);

//             std::cout << "md5(" << s << ") = " << toString(digest) << '\n';
//         }