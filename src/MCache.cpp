
#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/crc.hpp>

#include <TFile.h>

#include "MCache.h"

namespace fs = boost::filesystem;

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Construct a new MCache::MCache object
 * On construction, the filesystem is read and the hashmap is constructed based on this.
 *
 */
MCache::MCache()
{
   // TODO: Get rid of printout debugging messages. Can move to log message...
   // std::cout << "Object is being created" << std::endl;
   fs::path cachePath = fs::path(fs::temp_directory_path().string() + "/XDataFrame");
   if (fs::is_directory(cachePath)) {
   } else {
      fs::create_directory(cachePath);
   }
   cacheDir = cachePath.string();
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief checks if a hash entry exists
 *
 * @param hash
 * @return true
 * @return false
 */
bool MCache::EntryExists(std::string hash)
{
   fs::path entryPath = fs::path(GetCacheDir() + "/" + hash + "/");
   bool     exists    = fs::is_directory(entryPath);
   if (exists) {
      return true;
   } else {
      return false;
   }
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Sets the cache directory to the absolute file directory "directory"
 *
 * @param directory
 */
void MCache::SetCacheDir(std::string directory)
{
   cacheDir = directory;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief getter for cacheDir
 *
 * @return std::string
 */
std::string MCache::GetCacheDir()
{
   return cacheDir;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Gets the request_id of a given hash entry
 *
 * @param hash
 * @return std::string
 */
std::string MCache::ReadRequestId(std::string hash)
{
   fs::path hashFolderPath = fs::path(cacheDir + "/" + hash);
   if (fs::is_directory(hashFolderPath)) {
      fs::path reqidFilePath = fs::path(hashFolderPath.string() + "/request_id.txt");
      if (fs::exists(reqidFilePath)) {
         std::string   line;
         std::ifstream myfile(reqidFilePath.string());
         std::string   requestIdStr;
         if (myfile.is_open()) {
            while (getline(myfile, line)) {
               std::cout << line << '\n';
               requestIdStr = line;
            }
            myfile.close();
            return requestIdStr;
         } else {
            std::cerr << "Unable to open file";
            return "";
         }
      } else {
         std::cerr << "specified hash " + hash + "has not been created in the cache";
         return "error";
      }
   }
   return "";
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Writes a given request_id into the cache entry corresponding to a given hash.
 * Stores this in a file in the hash folder called "request_id.txt"
 *
 * @param hash
 * @param requestId
 * @return true
 * @return false
 */
bool MCache::WriteRequestID(std::string hash, std::string requestId)
{
   fs::path cachePath = fs::path(cacheDir);
   if (fs::is_directory(cachePath)) {
      fs::path reqidFilePath = fs::path(cachePath.string() + "/" + hash + "/request_id.txt");
      if (fs::exists(reqidFilePath)) {
         // std::cout << "Request_ID already written for " << hash << "\n Overwriting \n";
      }
      // std::cout << "opening " << reqidFilePath.string() << "\n";
      std::ofstream myfile;
      myfile.open(reqidFilePath.string());
      if (myfile.is_open()) {
         std::cout << "writing " << requestId << " to cache\n";

         myfile << requestId;
         myfile.close();
         return 0;
      } else {
         std::cout << "could not open " << reqidFilePath.string() << " for writing.\n";
         return 1;
      }

   } else {
      std::cout << "hash directory " << cachePath.string() << " does not exist\n";
      return 1;
   }

   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Creates an entry in the cache from a given hash
 *
 * @param hash
 * @return true
 * @return false
 */
bool MCache::CreateCacheEntry(std::string hash)
{
   // std::string tmpDir = fs::temp_directory_path();
   fs::path home = fs::path(std::getenv("HOME"));
   // std::cout << "home: " << home.string() << "\n";
   // Does exist
   try {
      // Create folder
      fs::path cacheEntryDir = fs::path(cacheDir + "/" + hash);
      if (fs::exists(cacheEntryDir)) {
         std::cout << "Cache entry already exists!\n";
         return 1;
      } else {
         fs::create_directory(cacheEntryDir);
         return 0;
      }

      // Iterating
      // fs::path p = xdataframeDir;
      // if (fs::exists(p)) {
      //     if (fs::is_regular_file(p))
      //         std::cout << p << " size is " << fs::file_size(p) << '\n';
      //     else if (fs::is_directory(p)) {
      //         std::cout << p << " is a directory containing:\n";

      //         for (fs::directory_entry& x : fs::directory_iterator(p))
      //         std::cout << "    " << x.path() << '\n';
      //     }
      //     else
      //         std::cout << p << " exists, but is not a regular file or directory\n";
      // }
      // else
      // std::cout << p << " does not exist\n";
   } catch (const fs::filesystem_error &ex) {
      std::cout << "Create Cache Entry error: " << ex.what() << '\n';
      return 1;
   }


   return 0;
}


/**
 * @brief writes checksum map to file
 * 
 *    UNUSED
 * 
 * @param fname 
 * @param m 
 * @return int 
 */
int MCache::WriteFile(std::string fname, std::map<std::string, std::string> *m) {
   int count = 0;
   if (m->empty())
            return 0;

   FILE *fp = fopen(fname.c_str(), "w");
   if (!fp)
            return -errno;

   for(std::map<std::string, std::string>::iterator it = m->begin(); it != m->end(); it++) {
            fprintf(fp, "%s=%s\n", it->first.c_str(), it->second.c_str());
            count++;
   }

   fclose(fp);
   return count;
}

/**
 * @brief reads checksum map from file
 * 
 *  UNUSED
 * 
 * @param fname 
 * @param m 
 * @return int 
 */
int MCache::ReadFile(std::string fname, std::map<std::string, std::string> *m) {
      int count = 0;
      if (access(fname.c_str(), R_OK) < 0)
               return -errno;

      FILE *fp = fopen(fname.c_str(), "r");
      if (!fp)
               return -errno;

      m->clear();

      char *buf = 0;
      size_t buflen = 0;

      while(getline(&buf, &buflen, fp) > 0) {
               char *nl = strchr(buf, '\n');
               if (nl == NULL)
                     continue;
               *nl = 0;

               char *sep = strchr(buf, '=');
               if (sep == NULL)
                     continue;
               *sep = 0;
               sep++;

               std::string s1 = buf;
               std::string s2 = sep;

               (*m)[s1] = s2;

               count++;
      }

      if (buf)
               free(buf);

      fclose(fp);
      return count;
}


/**
 * @brief Compute checksums after downloading for the first time and stored to a file in the cache directory.
 * Implement a checksum for the cache files to perform before using them in the RDataFrame. 
 * Checksums are computed after downloading for the first time and stored to a file in the cache directory. 
 * Use a map to map file names to that file's checksum.
 * 
 *  UNIMPLEMENTED
 * 
 * @param hash 
 */
void MCache::ComputeChecksums(std::string hash){
   // lookup the entry with the hash string
   fs::path hashFolderPath = fs::path(cacheDir + "/" + hash);
   std::string ext(".root");
   if (fs::is_directory(hashFolderPath)) {

      // iterate over all ROOT files
      for (auto &p : fs::recursive_directory_iterator(hashFolderPath))
      {
         if (p.path().extension() == ext){
               // std::cout << p.path().string() << '\n';
               TFile f(p.path().string().c_str());
               // f.ShowStreamerInfo();

         }
      }


   } else {
         std::cerr << "specified hash " + hash + "has not been created in the cache";
         return;
   }
}