// AOC_Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include "AOC_Day10.h"

std::map<int, unsigned long long> cache;

void AddSumToTree(const std::vector<int> & numbers, int index, unsigned long long &sum, int modifier);


unsigned long long subtree(const std::vector<int> & numbers, int index) {
	if (index == numbers.size() - 1) return 1;

	unsigned long long sum = 0;

	if (index + 1 < numbers.size()) {
		if (numbers.at(index) + 1 == numbers.at(index + 1) || numbers.at(index) + 2 == numbers.at(index + 1) || numbers.at(index) + 3 == numbers.at(index + 1)) {
			AddSumToTree(numbers, index, sum, 1);
		}
	}
	if (index + 2 < numbers.size()) {
		if (numbers.at(index) + 1 == numbers.at(index + 2) || numbers.at(index) + 2 == numbers.at(index + 2) || numbers.at(index) + 3 == numbers.at(index + 2)) {
			AddSumToTree(numbers, index, sum, 2);
		}
	}
	if (index + 3 < numbers.size()) {
		if (numbers.at(index) + 1 == numbers.at(index + 3) || numbers.at(index) + 2 == numbers.at(index + 3) || numbers.at(index) + 3 == numbers.at(index + 3)) {
			AddSumToTree(numbers, index, sum, 3);
		}
	}
	return sum;
}

void AddSumToTree(const std::vector<int> & numbers, int index, unsigned long long &sum, int modifier)
{
	unsigned long long newSum = 0;

	if (cache.find(numbers.at(index + modifier)) != cache.end()) {
		newSum = cache[numbers.at(index + modifier)];
	}
	else {
		newSum = subtree(numbers, index + modifier);
		cache[numbers.at(index + modifier)] = newSum;
	}
	sum += newSum;
}

int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");

	if (fileInput.is_open()) {
		std::string line = "";
		std::vector<int> numbers{ 0 };
		int new_number;
		while (getline(fileInput, line)) {
			new_number = std::stoull(line);
			numbers.push_back(new_number);
		}
		fileInput.close();

		std::sort(numbers.begin(), numbers.end());
		numbers.push_back(*(--numbers.end()) + 3);
		auto oneDif = 0;
		auto twoDif = 0;
		auto threeDif = 0;
		for (auto it = ++numbers.begin(); it != numbers.end(); it++) {
			auto prevNumber = *(it - 1);
			auto curNumber = *it;
			if (curNumber - prevNumber == 1) {
				oneDif++;
			} else if (curNumber - prevNumber == 2) {
				twoDif++;
			} else if (curNumber - prevNumber == 3) {
				threeDif++;
			}
		}
		std::cout << "Number of 1 jolt diffs: " << oneDif << std::endl;
		std::cout << " Number of two jolt diffs = " << twoDif << std::endl;
		std::cout << " Number of three jolt diffs = " << threeDif << std::endl;
	
		unsigned long long paths = 0;
		paths = subtree(numbers, 0);
		std::cout << "Number of paths: " << paths << std::endl;
	}
	return 0;
}