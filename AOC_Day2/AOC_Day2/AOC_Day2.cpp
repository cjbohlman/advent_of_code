// AOC_Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

int countLetter(const std::string & password, const char & letter) {
	int count = 0;
	for (const char & c : password) {
		if (c == letter) count++;
	}
	return count;
}


int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");
	if (fileInput.is_open()) {
		std::string line = "";
		std::vector<int> nums;
		const int sum = 2020;
		auto validPasswords = 0;
		while (getline(fileInput, line)) {
			//// parse line
			//auto min = 0, max = 0;
			//char letter, hyphen, colon;
			//std::string password = "";
			//std::stringstream ss(line);
			//ss >> min >> hyphen >> max >> letter >> colon >> password;

			//// check password validity
			//int count = countLetter(password, letter);
			//if (count >= min && count <= max) validPasswords++;

			auto firstPos = 0, secondPos = 0;
			char letter, hyphen, colon;
			std::string password = "";
			std::stringstream ss(line);
			ss >> firstPos >> hyphen >> secondPos >> letter >> colon >> password;
			firstPos--;
			secondPos--;
			if (password.at(firstPos) == letter && password.at(secondPos) != letter ||
				password.at(firstPos) != letter && password.at(secondPos) == letter) validPasswords++;
		}
		std::cout << "Valid password count: " << validPasswords << std::endl;
		fileInput.close();
	}
	else {
		std::cerr << "Error opening input file" << std::endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
