module;

#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#include <map>
#include "Constants.h"

import Level; 

export module LevelManager;

export class LevelManager {

private:
	int current_level_speed, current_level_health;
	std::map<std::string, Level> levels; 
	std::vector<std::vector<bool>> shipsPos;

public:

	void readAlienHealth(std::string level_name)
	{
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
				current_level_health = std::stoi(row[1]);
		}

		inFile.close();

	}

	void readAlienSpeed(std::string level_name)
	{
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
				current_level_speed = std::stoi(row[2]);
		}
		inFile.close();
	}

	int& getSpeed(std::string level_name) {
		readAlienSpeed(level_name);
		return current_level_speed;
	}

	int& getHealth(std::string level_name) {
		readAlienHealth(level_name);
		return current_level_health;
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
				for (int i = otherConsts::shipsPosStartCellIndex; i < row.size(); i++)
					temprow.emplace_back(std::stoi(row[i]));
				//so now the whole row is in one vector

				for (int i = 0; i < shipsMatrixCount::rows; i++)
				{
					std::vector<bool> tmp;
					for (int j = 0; j < shipsMatrixCount::colomns; j++)
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
		levels[level_name] = Level(level_name, getSpeed(level_name), getHealth(level_name), readAlienPos(level_name));
		
		return levels[level_name];
	}

	
};