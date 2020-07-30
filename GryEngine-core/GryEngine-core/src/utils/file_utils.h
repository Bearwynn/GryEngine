#pragma once
#include <string>

namespace GryEngine {

	class FileUtils 
	{
	public:
		static std::string read_file(const char* filepath)
		{
			// uses standard C because it's faster
			FILE* file = fopen(filepath, "rt");			//create a C file, and open the filepath ("rt" means readoonly text file)
			fseek(file, 0, SEEK_END);					//navigate to the end of the file
			unsigned long fileLength = ftell(file);		//gives the number of bytes read
			char* data = new char[fileLength + 1];		//create a new char array to contain the data, + 1 for termination char
			memset(data, 0, fileLength + 1);			//assign the memory for the data array to 0
			fseek(file, 0, SEEK_SET);					//go back to the beginning of the file
			fread(data, 1, fileLength, file);			//read the file to the data array
			fclose(file);								//close the file

			std::string result(data);					//setup a string based on the data array
			delete[] data;								//cleanup the data array from memory
			return result;
		}
	};
	
}