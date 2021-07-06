// File: MCache.h
#ifndef MCACHE_H
#define MCACHE_H

#include <stdlib.h>
#include <iostream>
#include <map>


class MCache {

    public:
        void LoadCache();
        MCache(); // Constructor
        void SaveRequestId(std::string hash, std::string request_id);

    private:
        std::map<std::string, std::string> hashTable;

};

/**
 * @brief Construct a new MCache::MCache object
 * On construction, the filesystem is read and the hashmap is constructed based on this. 
 * 
 */
MCache::MCache(void) {
    std::cout << "Object is being created" << std::endl;

}


#endif