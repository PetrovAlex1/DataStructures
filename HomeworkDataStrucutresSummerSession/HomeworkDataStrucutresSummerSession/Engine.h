#pragma once

#include <unordered_map>
#include <string>

#include "TreeStructure.h"

class Engine
{
private:

	std::unordered_map<std::string, TreeStructure*> loadedTrees;

	void loadTree(const std::string& name, const std::string& fileName);

	void save(const std::string& name, const std::string& fileName);

	bool contains(const std::string& firstName, const std::string& secondName);

	void remove(const std::string& firstName, const std::string& secondName);

	void clearContainer();

	std::vector<std::string> split(const std::string command);

public:

	Engine();

	void StartUp();
};