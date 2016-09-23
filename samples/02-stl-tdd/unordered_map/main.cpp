#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

enum class Gender
{
	Male,
	Female,
};

string GenderToString(Gender gender)
{
	return (gender == Gender::Male) ? "male" : "female";
}

void main()
{
	unordered_map<string, Gender> nameToGender = {
		{"Sarah", Gender::Female},
		{"John", Gender::Male},
		{"Leonardo", Gender::Male},
		{"Richard", Gender::Male},
		{"Tanya", Gender::Female}
	};
	cout << "Tanya is a " << GenderToString(nameToGender.at("Tanya")) << " name.\n";
	cout << "John is a " << GenderToString(nameToGender.at("John")) << " name.\n";
}
