
#include <iostream>
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

}

void MCache::LoadCache(){
    return;
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

bool MCache::CreateCacheEntry(std::string hash){
    // std::string tmpDir = fs::temp_directory_path();
    fs::path home = fs::path(std::getenv("HOME"));
    std::cout << "home: " << home.string() << "\n";

    // fs::path tmpDir = boost::filesystem::temp_directory_path();
    std::cout << "tmp: " << home.string() << "\n";
    std::cout << "Temp directory is " << fs::temp_directory_path() << '\n';
    bool tmpDirExists = false;
    fs::path xdataframeDir = fs::path(fs::temp_directory_path().string() + "/XDataFrame");
    tmpDirExists = fs::is_directory(xdataframeDir);
    std::cout << "does xdataframe dir exist " << tmpDirExists << "\n";
    if(tmpDirExists == 0){
        // Create it
        fs::create_directories(xdataframeDir);
    } else {    }
    // Does exist
    try {
                // Create folder
        fs::path cacheDir = fs::path(xdataframeDir.string() + "/" + hash);
        if (fs::exists(cacheDir)){
            std::cout << "Cache entry already exists!\n";
            return 1; 
        }else {
            fs::create_directory(cacheDir);
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

