// File: Hasher.h

#ifndef HASHER_H
#define HASHER_H

#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <map>


using boost::uuids::detail::md5;

class Hasher {
    public:
        // TODO: Make this a local function, remove md5 include (hex to?) from this header?
        std::string toString(const md5::digest_type &digest){
            const auto charDigest = reinterpret_cast<const char *>(&digest);
            std::string result;
            boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
            return result;
        }
        std::string GetHash(std::string string);
        std::string GetHashOf(std::string filename);
    private:
        // Hashmap will map hashed submit.json's to their request_id's
        std::map<std::string, std::string> hashTable;
};

#endif