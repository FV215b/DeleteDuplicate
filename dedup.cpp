#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <cstdio>
#include <cstdlib>

void dirSearch(std::string dirName, std::vector<std::list<std::pair<std::string, size_t> > > * hashTable){
	DIR * dir = NULL;
	struct dirent * childDir;
	//std::cout << dirName.c_str() << std::endl;
	dir = opendir(dirName.c_str());
	if(dir == NULL){
		std::cerr << "Could not open root directory" << std::endl;
		exit(EXIT_FAILURE);
	}
	while((childDir = readdir(dir)) != NULL){
		//std::cout << childDir->d_name << std::endl;
		if(!strcmp(childDir->d_name, ".") || !strcmp(childDir->d_name, "..")){
			continue;
		}
		std::string file(childDir->d_name);
		std::string path = dirName + "/" + file;
		//path.append(childDir->d_name);
		if(childDir->d_type == DT_DIR){
			dirSearch(path, hashTable);
		}
		else if(childDir->d_type == DT_REG){
			std::ifstream fs;//(path, std::ifstream::in);
			fs.open(path, std::ifstream::in);
			if(fs.is_open()){
				char c;
				std::stringstream temp;
				std::hash<std::string> strHash; 
				while(fs.get(c)){
					temp << c;
				}
				size_t value = strHash(temp.str());
				std::list<std::pair<std::string, size_t> >::iterator it;
				for(it = (*hashTable)[value % 1021].begin(); it != (*hashTable)[value % 1021].end(); it++){
					if(it->second == value){
						std::cout << "#Removing " << path << " (duplicate of " << it->first << ")." << std::endl;
						std::cout << "rm " << path << std::endl;
						break;
					}
				}
				if(it == (*hashTable)[value % 1021].end()){
					std::pair<std::string, size_t> node(path, value);
					(*hashTable)[value % 1021].push_front(node);
					fs.close();
				}
			}
		}
		
	}
	closedir(dir);
}

int main(int argc, char ** argv){
	//std::cout << argc << std::endl;
	if(argc <= 1){
		std::cerr << "Could not find a file path" <<std::endl;
		exit(EXIT_FAILURE);
	}
	std::vector<std::list<std::pair<std::string, size_t> > >  hashTable;
	std::cout << "#!/bin/bash" << std::endl;
	hashTable.resize(1021);
	for(int i = 1; i < argc; i++){
		std::string str(argv[i]);
		//std::cout << str.c_str() << std::endl;
		dirSearch(str, &hashTable);
	}
	return EXIT_SUCCESS;
}
