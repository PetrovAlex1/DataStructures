#include "Engine.h"

#pragma warning (disable : 4996)
#include <vector>
#include <fstream>

Engine::Engine()
{
}

void Engine::loadTree(const std::string& name, const std::string& fileName)
{
	if (loadedTrees.count(name) == 1)
	{
		std::ofstream file(loadedTrees[name]->getFileName(), std::ios::trunc);
		loadedTrees[name]->save(file);
		file.close();
	}
	else
	{
		TreeStructure* newTree = new TreeStructure(name, fileName.data());
		loadedTrees[name] = newTree;
	}
}

bool existFile(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

bool validateName(const std::string& name)
{
	for (int i = 0; name[i] != '\0'; i++)
	{
		if (name[i] == ' ')
		{
			return false;
		}
	}

	return true;
}

void Engine::save(const std::string& name, const std::string& fileName)
{
	if (!validateName(name))
	{
		throw std::invalid_argument("Name is not valid!");
	}
	if (existFile(fileName))
	{
		std::cout << "Do you want to overwrite the tree information in this file or save it as it is. Type y for 'Yes' of n for 'No'" << std::endl;
		char answer;
		std::cin >> answer;
		std::cin.ignore();

		if (answer == 'n')
		{
			return;
		}
	}
	if (loadedTrees.count(name) == 0)
	{
		throw std::invalid_argument("Tree with such name does not exist!");
	}

	std::ofstream file(fileName.data(), std::ios::trunc);

	if (!file.is_open())
	{
		throw std::invalid_argument("File cannot be opened!");
	}

	loadedTrees[name]->save(file);

	file.close();
}

bool Engine::contains(const std::string& firstName, const std::string& secondName)
{
	if (loadedTrees.count(firstName) == 0 || loadedTrees.count(secondName) == 0)
	{
		throw std::invalid_argument("One of the trees is not loaded in the program!");
	}

	return loadedTrees[firstName]->contains(*(loadedTrees[secondName]));
}

void Engine::remove(const std::string& firstName, const std::string& secondName)
{
	if (loadedTrees.count(firstName) == 0 || loadedTrees.count(secondName) == 0)
	{
		throw std::invalid_argument("One of the trees is not loaded in the program!");
	}

	loadedTrees[firstName]->remove(*(loadedTrees[secondName]));
}

void Engine::clearContainer()
{
	for (std::unordered_map<std::string, TreeStructure*>::iterator it = loadedTrees.begin(); it != loadedTrees.end(); it++)
	{
		delete it->second;
	}

	loadedTrees.clear();
}

void Engine::StartUp()
{
	std::string command;
	std::vector<std::string> splitCommand;
	getline(std::cin, command);

	while (command != "exit")
	{
		splitCommand = split(command);

		try
		{
			if (splitCommand[0] == "LOAD")
			{
				loadTree(splitCommand[1], splitCommand[2]);
				std::cout << "File successfully opened!" << std::endl;
			}
			else if (splitCommand[0] == "SAVE")
			{
				save(splitCommand[1], splitCommand[2]);
				std::cout << "File was successfully saved!" << std::endl;
			}
			else if (splitCommand[0] == "CONTAINS")
			{
				bool result = contains(splitCommand[1], splitCommand[2]);

				if (result)
				{
					std::cout << splitCommand[1] << " contains as subtree " << splitCommand[2] << std::endl;
				}
				else
				{
					std::cout << splitCommand[1] << " does not contains as subtree " << splitCommand[2] << std::endl;
				}
			}
			else if (splitCommand[0] == "REMOVE")
			{
				remove(splitCommand[1], splitCommand[2]);
				std::cout << "Remove was successfull!" << std::endl;
			}
			else
			{
				throw std::invalid_argument("Unknown command detected!");
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		getline(std::cin, command);
	}

	clearContainer();
}

std::vector<std::string> Engine::split(const std::string command)
{
	std::string currentPart;
	std::vector<std::string> splitCommand;

	for (int i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == ' ' && !command.empty())
		{
			splitCommand.push_back(currentPart);
			currentPart.clear();
			continue;
		}

		currentPart += command[i];
	}

	if (!command.empty())
	{
		splitCommand.push_back(currentPart);
	}

	return splitCommand;
}