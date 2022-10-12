#pragma once
#include <string>
#include "Tree.h"

using std::string;

class Hierarchy
{
public:
	//Interface methods
	Hierarchy(Hierarchy&& r) noexcept;
	Hierarchy(const Hierarchy& r);
	Hierarchy(const string& data);
	~Hierarchy() noexcept;
	void operator=(const Hierarchy&) = delete;

	string print()const;

	int longest_chain() const;
	bool find(const string& name) const;
	int num_employees() const;
	int num_overloaded(int level = 20) const;

	string manager(const string& name) const;
	int num_subordinates(const string& name) const;
	unsigned long getSalary(const string& who) const;

	bool fire(const string& who);
	bool hire(const string& who, const string& boss);

	void incorporate();
	void modernize();

	Hierarchy join(const Hierarchy& right) const;

	//My methods
	Hierarchy() : isSaved(false) {}

	void replaceHierarchy(const Hierarchy& other);

	void makeItSave();

	bool isObjectSaved() const;

	void setName(const string& name);

	string getName() const;

	void addEmployeeToResultHierarchy(Hierarchy first, Hierarchy second, Hierarchy& result, const std::string& currentName, const std::string& currentBoss) const;

	int getCountOfAllSubordinates(const std::string& name) const;

	int getIndexOfEmployee(std::vector<std::string> brotherhood) const;

	std::vector<std::string> getEmployeesWithSameSalary(std::vector<std::string> brotherhood);

	bool checkHierarchies(const Hierarchy& other) const;

private:
	Tree<std::string> hierarchy;
	bool isSaved;
	string name;
};
