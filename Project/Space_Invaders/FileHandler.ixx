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
	std::filesystem::path scoresFile_path = "./scores.txt";

public:
	FileHandler(){}

	FileHandler(std::vector<char> name, int _score)
	{
		player_name = std::string(name.data(), name.size());
		score = _score;
	}

	
	
	
	
	int readAlienHealth(std::string level_name)
	{
		int health;
		std::fstream inFile;
		inFile.open("levelInfo.csv", std::ios::in);

		std::vector<std::string> row;
		std::string temp, word;

		while (getline(inFile, temp)) //while there are lines in the file, save each line in temp
		{
			row.clear();
			std::stringstream ss(temp);

			while (getline(ss, word, ',')) //while getting words without ',' from temp save each word as a string in a vector
			{
				row.push_back(word);
			}
			if (row[0] == level_name)
				health = std::stoi(row[1]);
		}

		inFile.close();

		return health; 
	}

	int readAlienSpeed(std::string level_name)
	{
		int speed;
		std::fstream inFile;
		inFile.open("levelInfo.csv", std::ios::in);

		std::vector<std::string> row;
		std::string temp, word;

		while (getline(inFile, temp)) //while there are lines in the file, save each line in temp
		{
			row.clear();
			std::stringstream ss(temp);

			while (getline(ss, word, ',')) //while getting words without ',' from temp save each word as a string in a vector
			{
				row.push_back(word);
			}
			if (row[0] == level_name)
				speed = std::stoi(row[2]);
		}

		inFile.close();

		return speed;
	}

	std::vector<std::vector<int>>& readAlienPos(std::string level_name)
	{
		std::vector<std::vector<int>> shipsPos;
		std::fstream inFile;
		inFile.open("levelInfo.csv", std::ios::in);

		std::vector<std::string> row;
		std::string temp, word;

		while (getline(inFile, temp)) //while there are lines in the file, save each line in temp
		{
			row.clear();
			std::stringstream ss(temp);

			while (getline(ss, word, ',')) //while getting words without ',' from temp save each word as a string in a vector
			{
				row.push_back(word);
			}
			if (row[0] == level_name)
			{
				std::vector<std::string> temprow; 
				for (int i = 0; i < row.size()-3; i++)
					temprow[i] = row[i+3]; 

				for (int i = 0; i < 5; i++)
				{
					std::vector<int> tmp;
					for (int j = 0 ; j <4 ; j++)
					{
						tmp.push_back(std::stoi(temprow[4*i+j]));
					}
					shipsPos.push_back(tmp);
				}
				
			}
				
		}

		inFile.close();

		return shipsPos;
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
