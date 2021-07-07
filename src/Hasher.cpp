#include "Hasher.h"
#include <iostream>
#include <fstream> 


std::string Hasher::GetHash(std::string filenameString){
        md5 hash;
        md5::digest_type digest;

        hash.process_bytes(filenameString.data(), filenameString.size());
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