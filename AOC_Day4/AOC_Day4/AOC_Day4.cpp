// AOC_Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "AOC_Day4.h"

std::string removeAllSpaces(std::string input) {
	input.erase(std::remove(input.begin(), input.end(), ' '),
		input.end());
	return input;
}

std::vector<std::string> tokenize(std::string input) {
	// Vector of string to save tokens 
	std::vector <std::string> tokens;

	// stringstream class check1 
	std::stringstream check1(input);

	std::string intermediate;

	// Tokenizing w.r.t. space ' ' 
	while (getline(check1, intermediate, ' '))
	{
		intermediate.erase(std::remove(intermediate.begin(), intermediate.end(), '\n'),
			intermediate.end());
		intermediate = removeAllSpaces(intermediate);
		if (intermediate != "")
			tokens.push_back(intermediate);
	}
	return tokens;
}

bool allRequiredFields(std::map<std::string, std::string> map) {
	return map.find("byr") != map.end()
		&& map.find("iyr") != map.end()
		&& map.find("eyr") != map.end()
		&& map.find("hgt") != map.end()
		&& map.find("hcl") != map.end()
		&& map.find("ecl") != map.end()
		&& map.find("pid") != map.end();
}


int main()
{
	std::fstream fileInput;
	fileInput.open("input.txt");
	if (fileInput.is_open()) {
		std::string line = "";
		auto passports = 0;
		std::string passport = "";
		
		while (getline(fileInput, line)) {
			if (removeAllSpaces(line) == "") {
				CheckPassportDetails(passport, passports);
			}
			else {
				passport += (" "+line);
			}
		}
		if (passport != "") {
			CheckPassportDetails(passport, passports);
		}
		fileInput.close();
		std::cout << "Num passports = " << passports << std::endl;
	}
}

void CheckPassportDetails(std::string &passport, int &passports)
{
	auto tokens = tokenize(passport);
	auto numValidFields = 0;
	std::map<std::string, std::string> map;
	for (auto it = tokens.begin(); it != tokens.end(); it++) {
		// split line by colon
		std::string field, value;
		std::string pair = *it;
		std::replace(pair.begin(), pair.end(), ':', ' ');
		std::stringstream ss(pair);
		ss >> field >> value;
		map[field] = value;
	}

	if (allRequiredFields(map) && validatePassport(map)) passports++;
	passport = "";
}

bool heightCalc(std::string height) {
	if (height.find("cm") != std::string::npos) {
		height = height.substr(0, height.size() - 2);
		int heightCm = std::stoi(height);
		return heightCm >= 150 && heightCm <= 193;
	}
	else if (height.find("in") != std::string::npos) {
		height = height.substr(0, height.size() - 2);
		int heightCm = std::stoi(height);
		return heightCm >= 59 && heightCm <= 76;
	}
	return false;
}

bool properUnitHair(char unit) {
	return unit == '0' ||
		unit == '1' ||
		unit == '2' ||
		unit == '3' ||
		unit == '4' ||
		unit == '5' ||
		unit == '6' ||
		unit == '7' ||
		unit == '8' ||
		unit == '9' ||
		unit == 'a' ||
		unit == 'b' ||
		unit == 'c' ||
		unit == 'd' ||
		unit == 'e' ||
		unit == 'f';
}

bool hairCalc(std::string height) {
	return height[0] == '#' &&
		properUnitHair(height[1]) &&
		properUnitHair(height[2]) && 
		properUnitHair(height[3]) && 
		properUnitHair(height[4]) && 
		properUnitHair(height[5]) && 
		properUnitHair(height[6]);
}



bool validatePassport(std::map<std::string, std::string> map) {

	// byr(Birth Year) - four digits; at least 1920 and at most 2002.
	//	iyr(Issue Year) - four digits; at least 2010 and at most 2020.
	//	eyr(Expiration Year) - four digits; at least 2020 and at most 2030.
	//	hgt(Height) - a number followed by either cm or in:
	//		If cm, the number must be at least 150 and at most 193.
	//		If in, the number must be at least 59 and at most 76.
	//	hcl(Hair Color) - a # followed by exactly six characters 0 - 9 or a - f.
	//	ecl(Eye Color) - exactly one of : amb blu brn gry grn hzl oth.
	//	pid(Passport ID) - a nine - digit number, including leading zeroes.
	//	cid(Country ID) - ignored, missing or not.

	bool byr = true;
	try {
		byr = map["byr"].size() == 4 && std::stoi(map["byr"]) >= 1920 && std::stoi(map["byr"]) <= 2002;
	}
	catch (...) {
		byr = false;
	};
	bool iyr = true;
	try {
		iyr = map["iyr"].size() == 4 && std::stoi(map["iyr"]) >= 2010 && std::stoi(map["iyr"]) <= 2020;
	}
	catch (...) {
		iyr = false;
	};

	bool eyr = true;
	try {
		eyr = map["eyr"].size() == 4 && std::stoi(map["eyr"]) >= 2020 && std::stoi(map["eyr"]) <= 2030;
	}
	catch (...) {
		eyr = false;
	};
	
	bool hgt = heightCalc(map["hgt"]);
	
	bool hcl = hairCalc(map["hcl"]);
	
	bool ecl = map["ecl"] == "amb" || map["ecl"] == "blu" || map["ecl"] == "brn" || map["ecl"] == "gry" || map["ecl"] == "grn" || map["ecl"] == "hzl" || map["ecl"] == "oth";

	bool pid = true;
	try {
		stol(map.at("pid"));
		pid = map["pid"].size() == 9;
	}
	catch (...) {
		pid = false;
	};

	return byr
		&& iyr
		&& eyr
		&& hgt
		&& hcl
		&& ecl
		&& pid;

	return true;
}