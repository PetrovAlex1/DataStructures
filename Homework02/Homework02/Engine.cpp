#include "Engine.h"
#include <iostream>
#include <fstream>

void Engine::startUp()
{
	std::string command;
	getline(std::cin, command);
	std::vector<std::string> splitCommand = split(command);

	while (splitCommand[0] != "exit")
	{
		try
		{
			if (splitCommand[0] == "help")
			{
				help();
			}
			else if (splitCommand[0] == "load")
			{
				if (splitCommand.size() == 3)
				{
					if (load(splitCommand[1], splitCommand[2]))
					{
						std::cout << splitCommand[1] << " Loaded successfully!" << std::endl;
					}
				}
				else
				{
					if (load(std::cin, splitCommand[1]))
					{
						std::cout << splitCommand[1] << " Loaded successfully!" << std::endl;
						std::cin.clear();
					}
				}
			}
			else if (splitCommand[0] == "save")
			{
				if (splitCommand.size() == 3)
				{
					save(splitCommand[1], splitCommand[2]);
					std::cout << splitCommand[1] << " saved successfully!" << std::endl;
				}
				else
				{
					save(splitCommand[1]);
					std::cout << splitCommand[1] << " saved successfully!" << std::endl;
				}
			}
			else if (splitCommand[0] == "find")
			{
				if (find(splitCommand[1], splitCommand[2]))
				{
					std::cout << splitCommand[2] << " exist in " << splitCommand[1] << " object." << std::endl;
				}
				else
				{
					std::cout << splitCommand[2] << " does not exist in " << splitCommand[1] << " object." << std::endl;
				}
			}
			else if (splitCommand[0] == "num_subordinates")
			{
				int count = numSubordinates(splitCommand[1], splitCommand[2]);

				if (count != -1)
				{
					std::cout << count << std::endl;
				}
			}
			else if (splitCommand[0] == "manager")
			{
				std::string name = getManager(splitCommand[1], splitCommand[2]);

				if (name != "")
				{
					std::cout << name << std::endl;
				}
			}
			else if (splitCommand[0] == "num_employees")
			{
				int count = getNumEmployees(splitCommand[1]);

				if (count != -1)
				{
					std::cout << count << std::endl;
				}
			}
			else if (splitCommand[0] == "overloaded")
			{
				int count = overloaded(splitCommand[1]);

				if (count > 0)
				{
					std::cout << count << std::endl;
				}
				else if (count == 0)
				{
					std::cout << "No overloaded employees in " << splitCommand[1] << std::endl;
				}
			}
			else if (splitCommand[0] == "join")
			{
				join(splitCommand[1], splitCommand[2], splitCommand[3]);
				std::cout << splitCommand[3] << " created." << std::endl;
			}
			else if (splitCommand[0] == "fire")
			{
				fire(splitCommand[1], splitCommand[2]);
				std::cout << splitCommand[2] << " is fired!" << std::endl;
			}
			else if (splitCommand[0] == "hire")
			{
				hire(splitCommand[1], splitCommand[2], splitCommand[3]);
				std::cout << splitCommand[2] << " is hired." << std::endl;
			}
			else if (splitCommand[0] == "salary")
			{
				std::cout << salary(splitCommand[1], splitCommand[2]) << " BGN" << std::endl;
			}
			else if (splitCommand[0] == "incorporate")
			{
				incorporate(splitCommand[1]);
				std::cout << splitCommand[1] << " is incorporated!" << std::endl;
			}
			else if (splitCommand[0] == "modernize")
			{
				modernize(splitCommand[1]);
				std::cout << splitCommand[1] << " is modernized." << std::endl;
			}
			else if (splitCommand[0] == "longest_chain")
			{
				std::cout << longestChain(splitCommand[1]) << std::endl;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		getline(std::cin, command);
		splitCommand = split(command);
	}

	for (int i = 0; i < hierarchies.size(); i++)
	{
		if (!hierarchies[i].isObjectSaved())
		{
			std::cout << hierarchies[i].getName() << " not saved! Enter file name to save: ";
			std::string fileName;
			getline(std::cin, command);
			save(hierarchies[i].getName(), fileName);
			std::cout << hierarchies[i].getName() << " is saved!" << std::endl;
		}
	}
}

std::vector<std::string> Engine::split(std::string command)
{
	std::vector<std::string> parts;
	std::string currentPart;
	int countParts = 0;

	for (char c : command)
	{
		if (parts.size() > 1 && parts[0] == "load" && countParts > 2 && c != ' ')
		{
			currentPart += c;
		}
		if (c != ' ')
		{
			currentPart += c;
		}
		else
		{
			parts.push_back(currentPart);
			currentPart.clear();
			countParts++;
		}
	}

	parts.push_back(currentPart);

	return parts;
}

bool Engine::objectExist(const std::string& objectName) const
{
	for (Hierarchy h : hierarchies)
	{
		if (h.getName() == objectName)
		{
			return true;
		}
	}

	return false;
}

void Engine::help()
{
	std::cout << "Command list and their function:" << std::endl;
	std::cout << "load <name of object> <name of file>" << std::endl;
	std::cout << "Load data for hierarchy from file and creates tree. If the name si missing it is supposed to read data from the console" << std::endl;
	std::cout << "save <name of object> <name of file>" << std::endl;
	std::cout << "Saves the information for the hierarchy on file. If the name si missing it is supposed to print the information on the console" << std::endl;
	std::cout << "find <name of object> <name of employee>" << std::endl;
	std::cout << "Check if in the indicated object exist an employee with indicated name" << std::endl;
	std::cout << "num_subordinates <name of object> <name oj employee>" << std::endl;
	std::cout << "Show the number of direct subordinates" << std::endl;
	std::cout << "manager <name of object> <name oj employee>" << std::endl;
	std::cout << "Displays the name of the head of the employee in the specified object" << std::endl;
	std::cout << "num_employees <name of object>" << std::endl;
	std::cout << "Display the number employees in the indicated object" << std::endl;
	std::cout << "overloaded <name of object>" << std::endl;
	std::cout << "Display the number employees in the indicated object, but with 20 subordinates" << std::endl;
	std::cout << "join <name of object 1> <name of object 2> <name of object result>" << std::endl;
	std::cout << "Unite two object in one with name <name of object result>" << std::endl;
	std::cout << "fire <name of object> <name of employee>" << std::endl;
	std::cout << "Remove the employee from the object" << std::endl;
	std::cout << "hire <name of object> <name of employee> <name of manager>" << std::endl;
	std::cout << "Hire the employee in the object like subordinate of the manager" << std::endl;
	std::cout << "salary <name of object> <name of employee>" << std::endl;
	std::cout << "Display the salary of the employee" << std::endl;
	std::cout << "incorporate <name of object>" << std::endl;
	std::cout << "Incorporate the object" << std::endl;
	std::cout << "modernize <name of object>" << std::endl;
	std::cout << "Modernize the firm" << std::endl;
	std::cout << "exit" << std::endl;
	std::cout << "Stop the program" << std::endl;
}

bool checkName(const std::string& name)
{
	for (char c : name)
	{
		if (!(c >= '0' && c <= '9'
			|| c >= 'a' && c <= 'z'
			|| c >= 'A' && c <= 'Z'))
		{
			return false;
		}
	}

	return true;
}

bool Engine::load(const std::string& objectName, std::string fileName)
{
	if (!checkName(objectName))
	{
		throw std::invalid_argument("Object name is invalid! Try again.");
	}

	std::ifstream currentFile;
	fileName.append(".txt");
	currentFile.open(fileName);
	bool existFile = false;
	char buffer[32];
	std::string resultString;

	while (currentFile.getline(buffer, 32, '\n'))
	{
		std::string currentLine;
		existFile = true;

		for (int i = 0; buffer[i] != '\0'; i++)
		{
			currentLine += buffer[i];
		}

		currentLine += '\n';
		resultString.append(currentLine);
	}

	if (existFile)
	{
		Hierarchy currrentHierarchy(resultString);
		currrentHierarchy.setName(objectName);

		if (objectExist(objectName))
		{
			for (int i = 0; i < hierarchies.size(); i++)
			{
				if (hierarchies[i].getName() == objectName)
				{
					hierarchies[i].replaceHierarchy(currrentHierarchy);
					break;
				}
			}
		}

		hierarchies.push_back(currrentHierarchy);
		currentFile.close();
		return true;
	}

	currentFile.close();
	throw std::invalid_argument("File does not exist! Try again");
}

bool Engine::load(std::istream& in, const std::string& objectName)
{
	if (!checkName(objectName))
	{
		throw std::invalid_argument("Object name is invalid! Try again.");
	}

	std::string resultString;
	std::string currentLine;
	getline(std::cin, currentLine);

	while (!in.eof())
	{
		currentLine += '\n';
		resultString.append(currentLine);
		getline(std::cin, currentLine);
	}

	Hierarchy currrentHierarchy(resultString);
	currrentHierarchy.setName(objectName);

	if (objectExist(objectName))
	{
		for (int i = 0; i < hierarchies.size(); i++)
		{
			if (hierarchies[i].getName() == objectName)
			{
				hierarchies[i].replaceHierarchy(currrentHierarchy);
				break;
			}
		}
	}

	hierarchies.push_back(currrentHierarchy);
	return true;
}

void Engine::save(const std::string& objectName, std::string fileName)
{
	if (objectExist(objectName))
	{
		for (int i = 0; i < hierarchies.size(); i++)
		{
			if (hierarchies[i].getName() == objectName)
			{
				fileName.append(".txt");
				std::ofstream currentFile(fileName, std::ios::app);
				currentFile << hierarchies[i].print();
				hierarchies[i].makeItSave();
				currentFile.close();
				break;
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

void Engine::save(const std::string& objectName)
{
	if (objectExist(objectName))
	{
		for (int i = 0; i < hierarchies.size(); i++)
		{
			if (hierarchies[i].getName() == objectName)
			{
				std::cout << hierarchies[i].print();
				hierarchies[i].makeItSave();
				break;
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

bool Engine::find(const std::string& objectName, const std::string& employeeName) const
{
	if (objectExist(objectName))
	{
		for (Hierarchy h : hierarchies)
		{
			if (h.getName() == objectName)
			{
				return h.find(employeeName);
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

int Engine::numSubordinates(const std::string& objectName, const std::string& employeeName) const
{
	if (objectExist(objectName))
	{
		for (Hierarchy h : hierarchies)
		{
			if (h.getName() == objectName)
			{
				int numSubordiantes = h.num_subordinates(employeeName);

				if (numSubordiantes != -1)
				{
					return numSubordiantes;
				}

				throw std::invalid_argument("Employee with this name does not exist in current hierarchy!");
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

std::string Engine::getManager(const std::string& objectName, const std::string& employeeName) const
{
	if (objectExist(objectName))
	{
		for (Hierarchy h : hierarchies)
		{
			if (h.getName() == objectName)
			{
				std::string manager = h.manager(employeeName);

				if (manager != "")
				{
					return manager;
				}

				throw std::invalid_argument("Employee with this name does not exist in current hierarchy!");
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

int Engine::getNumEmployees(const std::string& objectName) const
{
	if (objectExist(objectName))
	{
		for (Hierarchy h : hierarchies)
		{
			if (h.getName() == objectName)
			{
				return h.num_employees();
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

int Engine::overloaded(const std::string& objectName) const
{
	if (objectExist(objectName))
	{
		for (Hierarchy h : hierarchies)
		{
			if (h.getName() == objectName)
			{
				return h.num_overloaded();
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

void Engine::join(const std::string& firstObjectName, const std::string& secondObjectName, const std::string& resultObjectName)
{
	if (objectExist(firstObjectName) && objectExist(secondObjectName))
	{
		bool isCreated = false;

		for (Hierarchy first : hierarchies)
		{
			if (first.getName() == firstObjectName)
			{
				for (Hierarchy second : hierarchies)
				{
					if (second.getName() == secondObjectName)
					{
						Hierarchy newHierarchy = first.join(second);
						newHierarchy.setName(resultObjectName);
						hierarchies.push_back(newHierarchy);
						isCreated = true;
						break;
					}
				}
			}
			if (isCreated)
			{
				break;
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

void Engine::fire(const std::string& objectName, const std::string& employeeName)
{
	if (objectExist(objectName))
	{
		for (int i = 0; i < hierarchies.size(); i++)
		{
			if (hierarchies[i].getName() == objectName)
			{
				if (!hierarchies[i].fire(employeeName))
				{
					throw std::invalid_argument("Employee with such name does not exist!");
				}
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

int Engine::salary(const std::string& objectName, const std::string& employeeName) const
{
	if (objectExist(objectName))
	{
		for (Hierarchy h : hierarchies)
		{
			if (h.getName() == objectName)
			{
				int salary = (int)h.getSalary(employeeName);

				if (salary != -1)
				{
					return salary;
				}

				throw std::invalid_argument("Employee with this name does not exist in current hierarchy!");
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

void Engine::hire(const std::string& objectName, const std::string& employeeName, const std::string bossName)
{
	if (objectExist(objectName))
	{
		for (int i = 0; i < hierarchies.size(); i++)
		{
			if (hierarchies[i].getName() == objectName)
			{
				if (!hierarchies[i].hire(employeeName, bossName))
				{
					throw std::invalid_argument("Boss with such name does not exist!");
				}
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

int Engine::longestChain(const std::string& objectName) const
{
	if (objectExist(objectName))
	{
		for (Hierarchy h : hierarchies)
		{
			if (h.getName() == objectName)
			{
				return h.longest_chain();
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

void Engine::modernize(const std::string& objectName)
{
	if (objectExist(objectName))
	{
		for (int i = 0; i < hierarchies.size(); i++)
		{
			if (hierarchies[i].getName() == objectName)
			{
				hierarchies[i].modernize();
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}

void Engine::incorporate(const std::string& objectName)
{
	if (objectExist(objectName))
	{
		for (int i = 0; i < hierarchies.size(); i++)
		{
			if (hierarchies[i].getName() == objectName)
			{
				hierarchies[i].incorporate();
			}
		}
	}
	else
	{
		throw std::invalid_argument("Object does not exist!");
	}
}