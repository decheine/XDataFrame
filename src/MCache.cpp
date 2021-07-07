
#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>

#include "MCache.h"

namespace fs = boost::filesystem;


/**
 * @brief Construct a new MCache::MCache object
 * On construction, the filesystem is read and the hashmap is constructed based on this. 
 * 
 */
MCache::MCache() {
    std::cout << "Object is being created" << std::endl;
    fs::path cachePath = fs::path(fs::temp_directory_path().string() + "/XDataFrame");
    if(fs::is_directory(cachePath)){
    } else {
        fs::create_directory(cachePath);
    }
    cacheDir = cachePath.string();

}

void MCache::LoadCache(){
    return;
}

bool MCache::EntryExists(std::string hash){
    fs::path entryPath = fs::path(GetCacheDir() + "/" + hash + "/");
    bool exists = fs::is_directory(entryPath);
    if(exists){
        return true;
    } else {
        return false;
    }
}


/**
 * @brief Save request_id to the hash folder.
 * 
 * @param hash 
 * @param request_id 
 * @return true 
 * @return false 
 */
bool MCache::SaveRequestId(std::string hash, std::string request_id){
    const char* homeDir = getenv("HOME");

    // Check if hash exists.
    // If it doesn't, create it

    return 0;
}

void MCache::SetCacheDir(std::string directory){
    cacheDir = directory;
}

std::string MCache::GetCacheDir(){
    return cacheDir;
}

std::string MCache::ReadRequestId(std::string hash){
    fs::path hashFolderPath = fs::path(cacheDir + "/" + hash);
    if( fs::is_directory(hashFolderPath)) {
        fs::path reqidFilePath = fs::path(hashFolderPath.string() + "/request_id.txt" );
        if(fs::exists(reqidFilePath)){
            std::string line;
            std::ifstream myfile (reqidFilePath.string());
            std::string requestIdStr;
            if (myfile.is_open()){
                while ( getline (myfile,line) ) {
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

bool MCache::WriteRequestID(std::string hash, std::string requestId){
    fs::path cachePath = fs::path(cacheDir);
    if(fs::is_directory(cachePath)){
        fs::path reqidFilePath = fs::path(cachePath.string() + "/" + hash + "/request_id.txt");
        if(fs::exists(reqidFilePath)){
            std::cout << "Request_ID already written for " << hash << "\n Overwriting \n";
        }
        std::cout << "opening " << reqidFilePath.string() << "\n";
        std::ofstream myfile;
        myfile.open(reqidFilePath.string());
        if(myfile.is_open()){
            std::cout << "writing " << requestId << " to file\n";

            myfile << requestId;
            myfile.close();
            return 0;
        } else {
            std::cout << "could not open " << reqidFilePath.string() << " for writing.\n";
            return 1;
        }
            
        
    }else {
        std::cout << "hash directory " << cachePath.string() << " does not exist\n";
        return 1;
    }

    return 0;
}

bool MCache::CreateCacheEntry(std::string hash){
    // std::string tmpDir = fs::temp_directory_path();
    fs::path home = fs::path(std::getenv("HOME"));
    std::cout << "home: " << home.string() << "\n";
    // Does exist
    try {
                // Create folder
        fs::path cacheEntryDir = fs::path(cacheDir + "/" + hash);
        if (fs::exists(cacheEntryDir)){
            std::cout << "Cache entry already exists!\n";
            return 1; 
        }else {
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
    } catch (const fs::filesystem_error& ex){
        std::cout << ex.what() << '\n';
        return 1;
    }
    
    return 0;
}

