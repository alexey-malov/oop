#include <map>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

void main()
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
			//auto it = charFreq.find(ch);
			//if (it != charFreq.end()) // Найдено
			//{
			//	++it->second;
			//}
			//else
			//{
			//	//charFreq.insert(pair<char, int>(ch, 1));
			//	//charFreq.insert(make_pair(ch, 1));
			//	charFreq.emplace(ch, 1);
			//}
		}
	}

	for (auto & chInfo : charFreq)
	{
		cout << chInfo.first << ": " << chInfo.second << endl;
	}

	cout << endl;
}