module;

#include <fstream>
#include <filesystem>
#include <vector>


export module FileHandler;

export class FileHandler
{
private : 
	std::string player_name;
	int score;
	std::filesystem::path scoresFile_path = "D:/POLSL/Year II/CP4/Repo/Project/Space_Invaders/scores.txt";

public:

	FileHandler(std::vector<char> name, int _score)
	{
		player_name = std::string(name.data(), name.size());
		score = _score;
	}


	void write() 
	{
		std::ofstream file(scoresFile_path.filename(), std::ios::app);
		if (file) 
		{
			file << player_name << " :  " << score << std::endl;
			file.close();
		}
	}

};
