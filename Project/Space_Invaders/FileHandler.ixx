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
	std::string player_name;
	int score;
	std::filesystem::path scoresFile_path = "D:/POLSL/Year II/CP4/Repo/Project/Space_Invaders/scores.txt";

public:

	FileHandler(std::vector<char> name, int _score)
	{
		player_name = std::string(name.data(), name.size());
		score = _score;
		std::cout << "file handler was created\n";
	}


	void write() 
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

};
