#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

void CountChars()
{
	map<char, int> charFreq;
	//Можно использовать unordered_map
	//unordered_map<char, int> charFreq;
	string text = "a quick brown fox jumps over the lazy dog";
	for (auto ch : text)
	{
		if (isalpha(ch))
		{
			++charFreq[ch];
		}
	}

	for (auto& chInfo : charFreq)
	{
		cout << chInfo.first << ": " << chInfo.second << endl;
	}

	cout << endl;
}

void AnimalLegs()
{
	map<string, int> legsCount = {
		{ "dog"s, 4 }, { "sparrow"s, 2 }, { "spider"s, 8 },
		{ "octopus"s, 8 }, { "ant"s, 6 }
	};

	for (const auto& [name, legs] : legsCount)
	{
		cout << name << " has " << legs << " legs" << endl;
	}

	cout << "Enter animal name: ";
	string animalName;
	getline(cin, animalName);
	if (auto it = legsCount.find(animalName);
		it != legsCount.end())
	{
		cout << animalName << " has " << it->second << " legs" << endl;
	}
	else
	{
		cout << "No info about " << animalName << endl;
	}
}

map<char, int> BuildCharCounters(const string& word)
{
	map<char, int> counters;
	for (char ch : word)
	{
		++counters[ch];
	}
	return counters;
}

void Anagrams()
{
	cout << "Enter two words: ";
	string word1, word2;
	cin >> word1 >> word2;
	if (BuildCharCounters(word1) == BuildCharCounters(word2))
	{
		cout << word1 << " and " << word2 << " are anagrams" << endl;
	}
	else
	{
		cout << word1 << " and " << word2 << " are not anagrams" << endl;
	}
}

int main()
{
	CountChars();
	AnimalLegs();
	Anagrams();
}