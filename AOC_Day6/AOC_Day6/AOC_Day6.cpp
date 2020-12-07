// AOC_Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

int main()
{
	std::fstream fileInput;
	fileInput.open("input.txt");
	if (fileInput.is_open()) {
		std::string line = "";
		std::set<char> totalAnswers;
		std::map<char, int> consensusAnswers;

		auto intTotalAnswers = 0;
		auto intConsensusAnswers = 0;

		auto numPeopleInGroup = 0;
		while (getline(fileInput, line)) {
			if (line == "") {
				// tally individual answers
				intTotalAnswers += totalAnswers.size();
				totalAnswers.clear();

				// tally group answers
				for (auto& x : consensusAnswers) {
					if (x.second == numPeopleInGroup) {
						intConsensusAnswers++;
					}
				}
				numPeopleInGroup = 0;
				consensusAnswers.clear();
			}
			else {
				for (auto answer : line) {
					// tally individual answers
					totalAnswers.insert(answer);

					//tally group answers
					if (consensusAnswers.find(answer) != consensusAnswers.end()) {
						consensusAnswers.at(answer) = consensusAnswers.at(answer) + 1;
					}
					else {
						consensusAnswers.insert(std::pair<char, int> (answer, 1));
					}
				}
				numPeopleInGroup++;

			}
		}
		if (totalAnswers.size() != 0) {
			// tally individual answers
			intTotalAnswers += totalAnswers.size();
			totalAnswers.clear();
		}
		if (consensusAnswers.size() != 0) {
			// tally group answers
			for (auto& x : consensusAnswers) {
				if (x.second == numPeopleInGroup) {
					intConsensusAnswers++;
				}
			}
			numPeopleInGroup = 0;
			consensusAnswers.clear();
		}
		fileInput.close();
		std::cout << "Number of unique group answers = " << intTotalAnswers << std::endl;
		std::cout << "Number of consensus group answers = " << intConsensusAnswers << std::endl;
	}
}