#pragma once
#include "interface.h"
#include <vector>

class Engine
{
private:
	std::vector<Hierarchy> hierarchies;
public:

	Engine() {}

	void startUp();

	std::vector<std::string> split(std::string command);

	bool objectExist(const std::string& objectName) const;

	void help();

	bool load(const std::string& objectName, std::string fileName);

	bool load(std::istream& in, const std::string& objectName);

	void save(const std::string& objectName, std::string fileName);

	void save(const std::string& objectName);

	bool find(const std::string& objectName, const std::string& employeeName) const;

	int numSubordinates(const std::string& objectName, const std::string& employeeName) const;

	std::string getManager(const std::string& objectName, const std::string& employeeName) const;

	int getNumEmployees(const std::string& objectName) const;

	int overloaded(const std::string& objectName) const;

	void join(const std::string& firstObjectName, const std::string& secondObjectName, const std::string& resultObjectName);

	void fire(const std::string& objectName, const std::string& employeeName);

	int salary(const std::string& objectName, const std::string& employeeName) const;

	void hire(const std::string& objectName, const std::string& employeeName, const std::string bossName);

	int longestChain(const std::string& objectName) const;

	void modernize(const std::string& objectName);

	void incorporate(const std::string& objectName);
};