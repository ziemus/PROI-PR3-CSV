/*
 * CSVinterface.cpp
 *
 *  Created on: 01.06.2017
 *      Author: Ziemek
 */
#include"CSV.h"
#include<iostream>

std::string& fixFilepath(std::string& path);
std::string& readPath(std::string& path);

int main(){
	std::string command;
	CSV table;
	std::fstream file;

	command.clear();
    file.open("C:/Users/Ziemek/Desktop/infa/proi3/in.txt", std::fstream::in);
    table<<file;
    file.close();
    file.open("C:/Users/Ziemek/Desktop/infa/proi3/out.txt", std::fstream::out);
    table>>file;
    file.close();
    return 0;
	do {
		std::cin>>command;
		std::cin.get();

		if( command == "open" ){

			file.open( fixFilepath(readPath(command)) , std::fstream::in);

			if( !file.is_open() )
				std::cout << "Invalid directory:  " << command << std::endl;
			else{
				table<<file;
				file.close();
			}
		}

		else
		if( command == "save" ){

			file.open( fixFilepath(readPath(command)), std::fstream::out);

			if( !file.is_open() )
				std::cout << "Invalid directory: " << command << std::endl;
			else{
				table>>file;
				file.close();
			}
		}

	} while ( command != "q" || command != "quit" );

	return 0;
}

std::string& fixFilepath(std::string& path){
	while( path.find('\\') != std::string::npos)
		path[ path.find('\\') ] = '/';
	return path;
}

std::string& readPath(std::string& path){
	std::cout << "Enter the file directory:" << std::endl << "> " ;
	std::getline(std::cin,path);
	return path;
}
