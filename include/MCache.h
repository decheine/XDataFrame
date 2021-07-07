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
        bool WriteRequestID(std::string hash, std::string requestId);
        std::string ReadRequestId(std::string hash);
        void SetCacheDir(std::string directory);
        std::string GetCacheDir();

        bool EntryExists(std::string hash);


        MCache(); // Constructor

    private:
        std::map<std::string, std::string> hashTable;
        std::string cacheDir;

};


#endif