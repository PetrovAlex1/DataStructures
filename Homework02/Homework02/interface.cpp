#include "interface.h"
#include <vector>
#include <queue>

std::vector<std::string> splitData(std::string data)
{
	std::vector<std::string> result;
	std::string currentConnection;

	for (char c : data)
	{
		if (c == '\n')
		{
			if (currentConnection != "")
			{
				result.push_back(currentConnection);
				currentConnection.clear();
			}
		}
		else
		{
			currentConnection += c;
		}
	}

	if (currentConnection != "")
	{
		result.push_back(currentConnection);
	}

	return result;
}

bool isLetterOrDigit(const char& c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '1' && c <= '9');
}

bool checkConnection(std::string& connection)
{
	bool foundSpace = false;
	bool foundLetter = false;
	bool foundDash = false;

	for (char c : connection)
	{
		bool charIsLetter = isLetterOrDigit(c);

		if (c == '-' && foundLetter)
		{
			foundDash = true;
			foundLetter = false;
			foundSpace = false;
		}
		else if (c == '-' && (foundDash || !foundLetter))
		{
			return false;
		}
		else if (c == ' ')
		{
			foundSpace = true;
		}
		else if (foundSpace && foundLetter && charIsLetter)
		{
			return false;
		}
		else if (charIsLetter)
		{
			foundLetter = true;
			foundSpace = false;
		}
	}

	return true;
}

bool checkSplitInput(const std::vector<std::string>& input)
{
	for (std::string currentConnection : input)
	{
		if (!checkConnection(currentConnection))
		{
			return false;
		}
	}

	return true;
}

void splitConnection(const std::string& connection, std::string* parts)
{
	std::string currentPart;

	for (char c : connection)
	{
		if (c != '-' && c != ' ')
		{
			currentPart += c;
		}
		else if (c == '-')
		{
			parts[0] = currentPart;
			currentPart.clear();
		}
	}

	parts[1] = currentPart;
}

Hierarchy::Hierarchy(Hierarchy&& r) noexcept
{
	std::swap(this->hierarchy, r.hierarchy);
	std::swap(this->name, r.name);
	std::swap(this->isSaved, r.isSaved);
}

Hierarchy::Hierarchy(const Hierarchy& r)
{
	this->hierarchy = r.hierarchy;
	this->name = r.name;
	this->isSaved = r.isSaved;
}

Hierarchy::Hierarchy(const string& data)
{
	if (data != "")
	{
		std::vector<std::string> splitInput = splitData(data);

		if (!checkSplitInput(splitInput))
		{
			throw std::invalid_argument("Invalid format of connection.");
		}

		hierarchy.insert("", "Uspeshnia");

		for (std::string currentConnection : splitInput)
		{
			std::string parts[2];
			splitConnection(currentConnection, parts);
			hierarchy.insert(parts[0], parts[1]);
		}
	}

	isSaved = false;
}

Hierarchy::~Hierarchy() noexcept
{
}

bool isAhead(const std::string& firstName, const std::string& secondName)
{
	int i;

	for (i = 0; i < firstName.size() || i < secondName.size(); i++)
	{
		if (secondName[i] < firstName[i])
		{
			return true;
		}
		else if (secondName[i] != firstName[i])
		{
			return false;
		}
	}

	return i == firstName.size() ? false : true;
}

void orderLexicographically(std::vector<std::string>& employees)
{
	int size = employees.size();

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (isAhead(employees[j], employees[j + 1]))
			{
				std::string temp = employees[j];
				employees[j] = employees[j + 1];
				employees[j + 1] = temp;
			}
		}
	}
}

string Hierarchy::print() const
{
	if (hierarchy.getSize() == 0)
	{
		return "";
	}

	std::string result;
	std::vector<std::string> currentSubordinates;
	std::queue<std::string> namesQueue;

	namesQueue.push("Uspeshnia");

	while (!namesQueue.empty())
	{
		std::string currentName = namesQueue.front();
		namesQueue.pop();
		currentSubordinates = hierarchy.getChildren(currentName);

		orderLexicographically(currentSubordinates);

		for (int i = 0; i < currentSubordinates.size(); i++)
		{
			namesQueue.push(currentSubordinates[i]);
			std::string currentConnectoin = currentName;
			currentConnectoin += '-';
			currentConnectoin.append(currentSubordinates[i]);
			currentConnectoin += '\n';
			result.append(currentConnectoin);
		}
	}

	return result;
}

int Hierarchy::longest_chain() const
{
	return hierarchy.getHeight();
}

bool Hierarchy::find(const string& name) const
{
	return hierarchy.find(name);
}

int Hierarchy::num_employees() const
{
	return hierarchy.getSize();
}

int Hierarchy::getCountOfAllSubordinates(const std::string& name) const
{
	int count = 0;
	std::vector<std::string> subordinates;
	std::vector<std::string> currentSubordinates = hierarchy.getChildren(name);
	subordinates.insert(subordinates.end(), currentSubordinates.begin(), currentSubordinates.end());
	count += currentSubordinates.size();

	for (std::string name : subordinates)
	{
		count += getCountOfAllSubordinates(name);
	}

	return count;
}

int Hierarchy::num_overloaded(int level) const
{
	int count = 0;

	std::vector<std::string> employees = hierarchy.getListOfAllElements();

	for (std::string currentEmployeeName : employees)
	{
		if (getCountOfAllSubordinates(currentEmployeeName) >= level)
		{
			count++;
		}
	}

	return count;
}

string Hierarchy::manager(const string& name) const
{
	if (name == "Uspeshnia")
	{
		return "";
	}

	if (hierarchy.find(name))
	{
		return *hierarchy.getParent(name);
	}

	return "";
}

int Hierarchy::num_subordinates(const string& name) const
{
	if (hierarchy.find(name))
	{
		return hierarchy.getChildren(name).size();
	}

	return -1;
}

unsigned long Hierarchy::getSalary(const string& who) const
{
	int countIndirectEmployees;

	if (hierarchy.find(who))
	{
		std::vector<string> subordinates = hierarchy.getChildren(who);
		countIndirectEmployees = getCountOfAllSubordinates(who) - subordinates.size();
		return (500 * subordinates.size()) + (50 * countIndirectEmployees);
	}

	return -1;
}

bool Hierarchy::fire(const string& who)
{
	if (who != "Uspeshnia" && hierarchy.find(who))
	{
		hierarchy.remove(who);
		return true;
	}

	return false;
}

bool Hierarchy::hire(const string& who, const string& boss)
{
	if (hierarchy.find(boss))
	{
		if (hierarchy.find(who))
		{
			hierarchy.moveSubtree(who, boss);
		}
		else
		{
			hierarchy.insert(boss, who);
		}

		return true;
	}

	return false;
}

//Return the index of employee with highest salary
int Hierarchy::getIndexOfEmployee(std::vector<std::string> brotherhood) const
{
	int index = -1;
	int highestSalary = INT_MIN;

	for (int i = 0; i < brotherhood.size(); i++)
	{
		int currentSalary = getSalary(brotherhood[i]);

		if (currentSalary > highestSalary)
		{
			highestSalary = currentSalary;
			index = i;
		}
		else if (currentSalary == highestSalary)
		{
			return -1;
		}
	}

	return index;
}

std::vector<std::string> Hierarchy::getEmployeesWithSameSalary(std::vector<std::string> brotherhood)
{
	std::vector<std::string> employees;
	int highestSalary = INT_MIN;

	for (std::string name : brotherhood)
	{
		int currentSalary = getSalary(name);

		if (currentSalary > highestSalary)
		{
			highestSalary = currentSalary;
		}
	}
	for (std::string name : brotherhood)
	{
		int currentSalary = getSalary(name);

		if (highestSalary == currentSalary)
		{
			employees.push_back(name);
		}
	}

	return employees;
}

void Hierarchy::incorporate()
{
	std::vector<std::vector<std::string>> brotherhoods = hierarchy.getAllBrotherhoods();

	for (std::vector<std::string> brotherhood : brotherhoods)
	{
		int index = getIndexOfEmployee(brotherhood);

		if (index != -1)
		{
			hierarchy.incorporateTree(brotherhood[index]);
		}
		else
		{
			std::vector<std::string> employees = getEmployeesWithSameSalary(brotherhood);
			orderLexicographically(employees);
			hierarchy.incorporateTree(employees[0]);
		}
	}
}

void Hierarchy::modernize()
{
	hierarchy.modernizeTree();
}

bool Hierarchy::checkHierarchies(const Hierarchy& other) const
{
	std::vector<std::string> currentSubordinates = hierarchy.getListOfAllElements();
	std::vector<std::string> otherSubordinates = other.hierarchy.getListOfAllElements();

	for (int i = 0; i < currentSubordinates.size(); i++)
	{
		for (int j = 0; j < otherSubordinates.size(); j++)
		{
			if (hierarchy.find(otherSubordinates[j]) && other.hierarchy.find(currentSubordinates[i])
				&& hierarchy.existInSubtree(currentSubordinates[i], otherSubordinates[j])
				&& other.hierarchy.existInSubtree(otherSubordinates[j], currentSubordinates[i]))
			{
				return false;
			}
		}
	}

	return true;
}

void Hierarchy::addEmployeeToResultHierarchy(Hierarchy first, Hierarchy second, Hierarchy& result, const std::string& currentName, const std::string& currentBoss) const
{
	if (second.find(currentName))
	{
		std::string otherBoss = *second.hierarchy.getParent(currentName);

		if (currentBoss != otherBoss)
		{
			int currentBossLevel = first.hierarchy.getLevel(currentBoss);
			int otherBossLevel = second.hierarchy.getLevel(otherBoss);
			std::string resultBoss;

			if (currentBossLevel == otherBossLevel)
			{
				resultBoss = isAhead(currentBoss, otherBoss) ? otherBoss : currentBoss;
			}
			else
			{
				resultBoss = currentBossLevel < otherBossLevel ? currentBoss : otherBoss;
			}

			result.hire(currentName, resultBoss);
			return;
		}
	}

	result.hire(currentName, currentBoss);
}

Hierarchy Hierarchy::join(const Hierarchy& right) const
{
	if (checkHierarchies(right))
	{
		std::vector<std::string> currentListOfNames = hierarchy.getListOfAllElements();
		std::vector<std::string> otherListOfNames = right.hierarchy.getListOfAllElements();
		Hierarchy result;
		result.hierarchy.insert("", "Uspeshnia");

		for (int i = 1; i < currentListOfNames.size() || i < otherListOfNames.size(); i++)
		{
			if (i < currentListOfNames.size() && !result.find(currentListOfNames[i]))
			{
				std::string currentName = currentListOfNames[i];
				std::string currentBoss = *hierarchy.getParent(currentName);

				addEmployeeToResultHierarchy(*this, right, result, currentName, currentBoss);
			}
			if (i < otherListOfNames.size() && !result.find(otherListOfNames[i]))
			{
				std::string currentName = otherListOfNames[i];
				std::string currentBoss = *right.hierarchy.getParent(currentName);

				addEmployeeToResultHierarchy(right, *this, result, currentName, currentBoss);
			}
		}

		return result;
	}

	throw std::logic_error("Employee X in first hierarchy is subordinate of employee Y, but in the other is opposite");
}

void Hierarchy::replaceHierarchy(const Hierarchy& other)
{
	hierarchy = other.hierarchy;
}

void Hierarchy::makeItSave()
{
	isSaved = true;
}

bool Hierarchy::isObjectSaved() const
{
	return this->isSaved;
}

void Hierarchy::setName(const string& name)
{
	this->name = name;
}

string Hierarchy::getName() const
{
	return name;
}