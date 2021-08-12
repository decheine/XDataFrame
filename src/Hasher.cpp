#include "Hasher.h"
#include <iostream>
#include <fstream> 


/**
 * @brief Returns md5 hash of string filenameString
 * 
 * @param filenameString 
 * @return std::string 
 */
 // TODO: Should this be a filename string?
std::string Hasher::GetHash(std::string filenameString){
        md5 hash;
        md5::digest_type digest;

        hash.process_bytes(filenameString.data(), filenameString.size());
        hash.get_digest(digest);

        // std::cout << "md5(" << s << ") = " << toString(digest) << '\n';
        // TODO: Remove text returns or use ROOT's logging infrastructure
        // std::cout << "returning " << toString(digest) << std::endl;

        return toString(digest);
}



std::string Hasher::toString(const md5::digest_type &digest){
        const auto charDigest = reinterpret_cast<const char *>(&digest);
        std::string result;
        boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
        return result;
}