#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void SearchingForTheAnswerToTheUltimateQuestionOfLifeTheUniverseAndEverything()
{
	int someNumbers[] = {3, 8, 100500, 42, 16, 99, 8, -9};

	auto it = find(begin(someNumbers), end(someNumbers), 42);
	if (it != end(someNumbers))
	{
		cout << "The Answer to the Ultimate Question of Life, the Universe, and Everything has been found at position: " << it - begin(someNumbers) << endl;
	}
	else
	{
		cout << "Sorry, I wasn't able to find The Answer to the Ultimate Question of Life, the Universe, and Everything" << endl;
	}
}

void SearchingForRabbit()
{
	string animals[] = {"fox", "wolf", "snake", "turtle", "bear", "rabbit", "hare"};

	if (find(begin(animals), end(animals), "rabbit") != end(animals))
	{
		cout << "There is a rabbit among the animals" << endl;
	}
	else
	{
		cout << "There are no any rabbits" << endl;
	}
}

void main()
{
	SearchingForTheAnswerToTheUltimateQuestionOfLifeTheUniverseAndEverything();
	SearchingForRabbit();
}