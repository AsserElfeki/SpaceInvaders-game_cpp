module;

#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#include <map>

import Level; 

export module LevelManager;

export class LevelManager {

private:
	int speed, health;
	std::map<std::string, Level> levels; 
	std::vector<std::vector<bool>> shipsPos;

public:

	void readAlienHealth(std::string level_name)
	{
		//int health;
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

		//return health;
	}

	void readAlienSpeed(std::string level_name)
	{
		//int speed;
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

		//return speed;
	}

	int& getSpeed(std::string level_name) {
		readAlienSpeed(level_name);
		return speed;
	}

	int& getHealth(std::string level_name) {
		readAlienHealth(level_name);
		return health;
	}

	std::vector<std::vector<bool>>& readAlienPos(std::string level_name)
	{
		shipsPos.clear();
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
				std::vector<bool> temprow;
				for (int i = 3; i < row.size(); i++)
					temprow.emplace_back(std::stoi(row[i]));
				//so now the whole row is in one vector

				for (int i = 0; i < 5; i++)
				{
					std::vector<bool> tmp;
					for (int j = 0; j < 4; j++)
					{
						tmp.push_back(temprow[4 * i + j]);
					}
					shipsPos.push_back(tmp);
				}
			}
		}

		inFile.close();

		return shipsPos;
	}

	Level& getLevel(std::string level_name)
	{
		if (levels.find(level_name) == levels.end())
		{
			return createLevel(level_name);
		}
		else
			return levels[level_name];
	}

	Level& createLevel(std::string level_name)
	{
		levels[level_name] = Level(getSpeed(level_name), getHealth(level_name), readAlienPos(level_name));
		
		return levels[level_name];
	}
};