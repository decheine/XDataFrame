#include "Hasher.h"
#include <iostream>
#include <fstream> 


bool Hasher::GetHash(std::string filename){
    std::string s;

    // std::ofstream ofs;
    // ofs.open(filename, std::ofstream::out | std::ofstream::app);
    // ofs.close();

    std::fstream my_file;
	my_file.open(filename, std::ios::in);
	if (!my_file) {
		std::cout << "No such file";
	}
	else {
		char ch;

		while (1) {
			my_file >> ch;
			if (my_file.eof())
				break;

			std::cout << ch;
		}

	}
	my_file.close();


    // while(std::getline(std::cin, s)) {
    //     md5 hash;
    //     md5::digest_type digest;

    //     hash.process_bytes(s.data(), s.size());
    //     hash.get_digest(digest);

    //     std::cout << "md5(" << s << ") = " << toString(digest) << '\n';
    // }

    return 0;
}