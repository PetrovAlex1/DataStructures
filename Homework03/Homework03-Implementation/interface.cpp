#include "interface.h"

//WordsMultiset functions

void WordsMultiset::add(const std::string& word, size_t times)
{
	if (wordsList.find(word) != wordsList.cend())
	{
		for (int j = 0; j < times; j++)
		{
			++wordsList[word];
		}
	}
	else
	{
		wordsList[word] = times;
	}
}

bool WordsMultiset::contains(const std::string& word) const
{
	return wordsList.find(word) != wordsList.cend();
}

size_t WordsMultiset::countOf(const std::string& word) const
{
	if (contains(word))
	{
		HashTable<std::string, int>::constIterator it = wordsList.find(word);
		return (*it).second();
	}

	return 0;
}

size_t WordsMultiset::countOfUniqueWords() const
{
	size_t count = 0;

	for (HashTable<std::string, int>::constIterator it = wordsList.cbegin(); it != wordsList.cend(); ++it)
	{
		count++;
	}

	return count;
}

std::multiset<std::string> WordsMultiset::words() const
{
	std::multiset<std::string> wordsMultiset;

	for (HashTable<std::string, int>::constIterator it = wordsList.cbegin(); it != wordsList.cend(); ++it)
	{
		int count = (*it).second();

		for (int i = 0; i < count; i++)
		{
			wordsMultiset.insert((*it).first());
		}
	}

	return wordsMultiset;
}

void WordsMultiset::removeWord(const std::string& word, size_t times)
{
	if (contains(word))
	{
		for (int i = 0; i < times && wordsList[word] != 0; i++)
		{
			wordsList[word]--;
		}

		if (wordsList[word] == 0)
		{
			wordsList.erase(word);
		}
	}
	else
	{
		throw std::invalid_argument("Word does not exist!");
	}
}

std::vector<std::string> WordsMultiset::getListOfElements()
{
	std::vector<std::string> resultList;

	for (HashTable<std::string, int>::Iterator it = wordsList.begin(); it != wordsList.end(); ++it)
	{
		int count = (*it).second();

		for (int i = 0; i < count; i++)
		{
			resultList.push_back((*it).first());
		}
	}

	return resultList;
}

std::vector<std::string> WordsMultiset::getListOfUniqueWords() const
{
	std::vector<std::string> resultList;

	for (HashTable<std::string, int>::constIterator it = wordsList.cbegin(); it != wordsList.cend(); ++it)
	{
		resultList.push_back((*it).first());
	}

	return resultList;
}

//Comparator functions
std::vector<std::string> split(std::string data)
{
	std::vector<std::string> result;
	std::string currentWord;

	for (char c : data)
	{
		if (c == ' ')
		{
			result.push_back(currentWord);
			currentWord.clear();
		}
		else
		{
			currentWord += c;
		}
	}

	if (currentWord != "")
	{
		result.push_back(currentWord);
	}

	return result;
}

void fillWithWords(std::istream& file, WordsMultiset& set)
{
	std::string currentLine;

	while (std::getline(file, currentLine))
	{
		std::vector<std::string> wordsInLine = split(currentLine);

		for (std::string currentWord : wordsInLine)
		{
			set.add(currentWord);
		}
	}
}

ComparisonReport Comparator::compare(std::istream& a, std::istream& b)
{
	ComparisonReport report;

	fillWithWords(a, report.uniqueWords[0]);
	fillWithWords(b, report.uniqueWords[1]);

	std::vector<std::string> words = report.uniqueWords[0].getListOfUniqueWords();

	for (std::string word : words)
	{
		try
		{
			if (report.uniqueWords[1].contains(word))
			{
				size_t occurancesFromFirstStream = report.uniqueWords[0].countOf(word);
				size_t occurancesFromSecondStream = report.uniqueWords[1].countOf(word);
				size_t totalOccurances = occurancesFromFirstStream < occurancesFromSecondStream ? occurancesFromFirstStream : occurancesFromSecondStream;

				report.uniqueWords[0].removeWord(word, totalOccurances);
				report.uniqueWords[1].removeWord(word, totalOccurances);
				report.commonWords.add(word, totalOccurances);
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return report;
}