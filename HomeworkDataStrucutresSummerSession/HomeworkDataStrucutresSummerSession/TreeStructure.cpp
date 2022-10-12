#include <fstream>
#include <queue>
#include "TreeStructure.h"

TreeStructure::TreeStructure(const std::string& name, const std::string& fileName)
{
	setName(name);
	loadTree(fileName);
	this->fileName = fileName;
}

void TreeStructure::save(std::ofstream& file)
{
	tree.saveToFile(file);
}

bool TreeStructure::contains(const TreeStructure& other)
{
	return this->tree.contains(other.tree);
}

void TreeStructure::remove(const TreeStructure& other)
{
	this->tree.remove(other.tree);
}

const std::string& TreeStructure::getName() const
{
	return this->name;
}

const std::string& TreeStructure::getFileName() const
{
	return this->fileName;
}

void TreeStructure::setName(const std::string& name)
{
	for (int i = 0; name[i] != '\0'; i++)
	{
		if (name[i] == ' ')
		{
			throw std::invalid_argument("There should be no intervals in tree's name!");
		}
	}

	this->name = name;
}

bool isFileEmpty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

void TreeStructure::loadTree(const std::string& fileName)
{
	std::ifstream file(fileName.data());//5

	if (!file.is_open())
	{
		throw std::invalid_argument("File with this name does not exist or cannot be opened!");
	}
	if (isFileEmpty(file))
	{
		file.close();
		return;
	}

	char buffer[128];
	std::queue<int> front;
	file.getline(buffer, 128, '\n');
	int root;

	for (int i = 0; i < buffer[i] != '\0'; i++)
	{
		if (buffer[i] >= '0' && buffer[i] <= '9')
		{
			root = buffer[i] - '0';
			break;
		}
	}

	front.push(root);
	this->tree.insert(0, root);
	int level = 0;

	while (file.getline(buffer, 256, '\n'))
	{
		int currentParent = front.front();
		int position = 0;
		level++;

		for (int i = 1; buffer[i] != '\0'; i++)
		{
			if (buffer[i] == '|')
			{
				front.pop();
				position++;

				if (front.empty())
				{
					break;
				}

				currentParent = front.front();
			}
			else if (buffer[i] >= '0' && buffer[i] <= '9' || buffer[i] == '-')
			{
				int currentNode = 0;
				int d = 1;

				bool hasMinus = false;

				if (buffer[i] == '-')
				{
					hasMinus = true;
					i++;
				}

				while (buffer[i] != ' ')
				{
					currentNode = currentNode * d + (buffer[i] - '0');
					d *= 10;
					i++;
				}

				currentNode = hasMinus ? 0 - currentNode : currentNode;

				this->tree.insert(currentParent, currentNode, level, position);
				front.push(currentNode);
			}
		}
	}

	file.close();
}