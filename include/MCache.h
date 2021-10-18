// File: MCache.h
#ifndef MCACHE_H
#define MCACHE_H

#include <stdlib.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <map>

/**
 * @brief MCache is a class used as a cache for downloading root files retrieved from
 * ServiceX jobs.
 *
 * The cache is located at 'cacheDir' and contains folders named the hash of a
 * submission string. Inside the folders are the files downloaded from ServiceX
 */
class MCache {

public:
   // Creates an entry in the cache with key being the hash of an input submit json
   bool CreateCacheEntry(std::string hash);

   // Writes a given request_id into the cache entry corresponding to a given hash.
   bool WriteRequestID(std::string hash, std::string requestId);

   // Gets the request_id of a given hash entry
   std::string ReadRequestId(std::string hash);

   // sets the cache directory
   void SetCacheDir(std::string directory);

   // returns string of cache directory cacheDir
   std::string GetCacheDir();

   // Checks if a given hash entry exists in the cache already
   bool EntryExists(std::string hash);

   // Compute checksums after downloading for the first time and stored to a file in the cache directory.
   void ComputeChecksums(std::string hash);

   std::vector<std::string> GetFileNameList(std::string hash);

   MCache(); // Constructor

private:
   // Writes checksum map to a file - UNUSED
   int WriteFile(std::string fname, std::map<std::string, std::string> *m);

   // Reads checksum map from file - UNUSED
   int ReadFile(std::string fname, std::map<std::string, std::string> *m);

   // Hash map of request_id's and hashed submission strings
   std::map<std::string, std::string> hashTable;

   // directory of the cache location where folders and files are stored
   std::string cacheDir;
};

#endif