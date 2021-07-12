#include "Hasher.h"
#include <iostream>
#include <fstream> 


/**
 * @brief Returns md5 hash of string filenameString
 * 
 * @param filenameString 
 * @return std::string 
 */
std::string Hasher::GetHash(std::string filenameString){
        md5 hash;
        md5::digest_type digest;

        hash.process_bytes(filenameString.data(), filenameString.size());
        hash.get_digest(digest);

        // std::cout << "md5(" << s << ") = " << toString(digest) << '\n';

        std::cout << "returning " << toString(digest) << std::endl;

        return toString(digest);
}

/**
 * @brief Gets hash of the file contents of filenameString
 * 
 * @param filenameString 
 * @return std::string 
 */
std::string Hasher::GetHashOf(std::string filenameString){
        md5 hash;
        md5::digest_type digest;

        const char* homeDir = getenv("HOME");
        // std::cout << "homedir: " << homeDir << "\n"; 
        const std::string fullDir = homeDir + filenameString ;

        // Read json file
        std::ifstream myFile(fullDir);
        std::ostringstream tmp;
        std::cout << "reading buffer \n";

        tmp << myFile.rdbuf();
        std::string s = tmp.str();
        std::cout << s << std::endl;


        hash.process_bytes(s.data(), s.size());
        hash.get_digest(digest);

        // std::cout << "md5(" << s << ") = " << toString(digest) << '\n';

        std::cout << "returning " << toString(digest) << std::endl;

        return toString(digest);
}


//   while(std::getline(my_file, s)) {
//             md5 hash;
//             md5::digest_type digest;

//             hash.process_bytes(s.data(), s.size());
//             hash.get_digest(digest);

//             std::cout << "md5(" << s << ") = " << toString(digest) << '\n';
//         }