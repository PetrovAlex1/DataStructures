#pragma once

#include <string>
#include "Tree.h"

class TreeStructure
{
private:
	Tree<int> tree;
	std::string name;
	std::string fileName;

	void loadTree(const std::string& fileName);

	void setName(const std::string& name);

public:

	TreeStructure(const std::string& name, const std::string& fileName);

	void save(std::ofstream& file);

	bool contains(const TreeStructure& other);

	void remove(const TreeStructure& other);

	const std::string& getName() const;

	const std::string& getFileName() const;
};