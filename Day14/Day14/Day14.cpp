// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>


std::string convertDecimalToBinary(int n)
{
	int binaryNumber[100], num = n;
	int i = 0;
	while (n > 0) {
		binaryNumber[i] = n % 2;
		n = n / 2;
		i++;
	}
	std::string binaryNumberString{};
	for (int j = i - 1; j >= 0; j--) {
		std::string charBin = std::to_string(binaryNumber[i]);
		binaryNumberString = binaryNumberString + charBin;
	}
	return binaryNumberString;
}

int convertBinaryToDecimal(long long n)
{
	int decimalNumber = 0, i = 0, remainder;
	while (n != 0)
	{
		remainder = n % 10;
		n /= 10;
		decimalNumber += remainder * pow(2, i);
		++i;
	}
	return decimalNumber;
}

int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");
	
	if (fileInput.is_open()) {
		std::string line = "";
		std::string mask{};
		std::map<std::string, std::string> memory;
		while (getline(fileInput, line)) {
			// check for mask
			if (line.substr(0, 4) == "mask") {
				mask = line.substr(7);
			}
			else {
				// get value: mem[8] = 11
				std::string mem = "", equals, value;
				std::stringstream ss(line);
				ss >> mem >> equals >> value;
				mem = mem.substr(4);
				mem.pop_back();

				int valueInt = std::stoi(value);
				std::string valueBin = convertDecimalToBinary(valueInt);
				valueBin.insert(valueBin.begin(), 36 - valueBin.size(), '0');
				// apply mask to value
				for (int i = 0; i < mask.size(); i++) {
					if (mask.at(i) == '0') {
						valueBin.at(i) = '0';
					}
					if (mask.at(i) == '1') {
						valueBin.at(i) = '1';
					}
				}

				// set value in memory
				memory[mem] = valueBin;
			}
		}
		
		unsigned long sum = 0;
		// sum up all values in memory
		for (auto it = memory.begin(); it != memory.end(); it++) {
			unsigned long long convertedNum = std::stoull(it->second);
			sum += convertBinaryToDecimal(convertedNum);
		}

		std::cout << "Sum of all values in memory: " << sum << std::endl;
	}
}
