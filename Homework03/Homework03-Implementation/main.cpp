#include <iostream>
#include <fstream>
#include "interface.h"

int getCountOfWords(WordsMultiset set)
{
	return set.getListOfElements().size();
}

void printWords(WordsMultiset set)
{
	std::vector<std::string> words = set.getListOfElements();

	for (std::string word : words)
	{
		std::cout << word << std::endl;
	}
}

void printReport(ComparisonReport& report)
{
	int countFirstStreamWords = getCountOfWords(report.uniqueWords[0]);
	int countSecondStreamWords = getCountOfWords(report.uniqueWords[1]);
	int countCommonWords = getCountOfWords(report.commonWords);
	int totalWordsCount = countFirstStreamWords + countSecondStreamWords + countCommonWords * 2;

	std::cout << "Total count of words: " << totalWordsCount << std::endl;

	std::cout << "Count of unique words from first stream: " << countFirstStreamWords << " and they are:" << std::endl;
	printWords(report.uniqueWords[0]);
	std::cout << "Count of unique words from second stream: " << countSecondStreamWords << " and they are:" << std::endl;
	printWords(report.uniqueWords[1]);
	std::cout << "Count of common words: " << countCommonWords << " and they are:" << std::endl;
	printWords(report.commonWords);
}

int main()
{
	std::ifstream file1;
	file1.open("text1.txt");
	std::ifstream file2;
	file2.open("text2.txt");
	Comparator comparator;
	ComparisonReport report;
	report = comparator.compare(file1, file2);

	printReport(report);

	file1.close();
	file2.close();
	return 0;
}