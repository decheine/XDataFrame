// File: MCache.h
#ifndef MCACHE_H
#define MCACHE_H

#include <stdlib.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <map>


class MCache {

    public:
        void LoadCache();
        bool SaveRequestId(std::string hash, std::string request_id);
        bool CreateCacheEntry(std::string hash);
        MCache(); // Constructor

    private:
        std::map<std::string, std::string> hashTable;

};


#endif