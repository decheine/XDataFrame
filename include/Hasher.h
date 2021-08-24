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
   // converts an md5 digest to a readable string
   std::string toString(const md5::digest_type &digest);

   // returns the MD5 hash of a given string
   std::string GetHash(std::string string);

private:
   // Hashmap will map hashed submit.json's to their request_id's
   std::map<std::string, std::string> hashTable;
};

#endif