#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

using boost::uuids::detail::md5;

class Hasher {
    public:
        std::string toString(const md5::digest_type &digest){
            const auto charDigest = reinterpret_cast<const char *>(&digest);
            std::string result;
            boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
            return result;
        }
        bool GetHash(std::string filename);
};