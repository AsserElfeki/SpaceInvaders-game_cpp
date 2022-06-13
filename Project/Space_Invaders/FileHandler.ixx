module;

#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>

export module FileHandler;

export class FileHandler
{
private : 
	bool writing_done = false;
	std::filesystem::path scoresFile_path = "./scores.txt";

public:
	FileHandler(){}

	
	void write(std::string player_name, int& score) 
	{
		if (!writing_done)
		{
			std::ofstream file(scoresFile_path.filename(), std::ios::app);
			if (file && !player_name.empty())
			{
				file << player_name << " :  " << score << std::endl;
				file.close();
			}
		}
		writing_done = true;
	}

	void reset() {
		writing_done = false; 
	}
};
