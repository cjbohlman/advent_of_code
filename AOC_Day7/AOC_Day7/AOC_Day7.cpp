// AOC_Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map> 

class AdjList {
private:
	int vertices;
	std::map<std::string, std::vector<std::pair<std::string, int>>> adjList;
	int paths;
	std::vector<std::string> bags;
	int goldBagCapacity;

public:
	AdjList() {
		this->vertices = 0;
		this->paths = 0;
		this->goldBagCapacity = 0;
	}

	void addEdge(std::string colorFrom, std::string colorTo, int number) {
		if (adjList.find(colorFrom) != adjList.end()) {
			std::pair <std::string, int> pair(colorTo, number);
			adjList[colorFrom].push_back(pair);
		}
		else {
			std::pair <std::string, int> initPair(colorFrom, 0);
			std::pair <std::string, int> newPair(colorTo, number);

			adjList[colorFrom].push_back(initPair);
			adjList[colorFrom].push_back(newPair);
		}
	}

	void addBlankEdge(std::string colorFrom) {
		std::pair <std::string, int> initPair(colorFrom, 0);
		adjList[colorFrom] = {};
	}

	void printMap() {
		for (std::map<std::string, std::vector<std::pair<std::string, int>>>::iterator it = adjList.begin(); it != adjList.end(); ++it) {
			for (auto color : it->second) {
				std::cout << color.first << " ";
			}
			std::cout << std::endl;
		}
	}

	int goldBagFit(std::string destination) {
		auto destList = adjList[destination];
		for (int i = 1; i < destList.size(); i++) {
			std::string getBag = destList.at(i).first;
			goldBagCapacity += destList.at(i).second + destList.at(i).second * bagsInside(getBag);
		}
		return goldBagCapacity;
	}

	int bagsInside(std::string destination) {
		if (adjList[destination].size() == 0) {
			return 0;
		}
		else {
			auto bags = 0;
			auto destList = adjList[destination];
			for (int i = 1; i < destList.size(); i++) {
				std::string getBag = destList.at(i).first;
				bags += destList.at(i).second + destList.at(i).second * bagsInside(getBag);
			}
			return bags;
		}

	}


	int countPaths(std::string dest) {
		for (std::map<std::string, std::vector<std::pair<std::string, int>>>::iterator it = adjList.begin(); it != adjList.end(); ++it) {
			if (it->first != dest) {
				if (count(dest, it->first)) {
					bags.push_back(it->first);
				}
			}
		}
		return bags.size();
	}

	bool count(std::string dest, std::string source) {
		if (dest == source) {
			return true;
		}
		else {
			for (int i = 1; i < adjList[source].size(); i++) {
				auto adjacentVertex = adjList[source].at(i).first;
				if (count(dest, adjacentVertex)) {
					return true;
				}
			}
		}
		return false;
	}
};

std::vector<std::string> tokenize(std::string input) {
	// Vector of string to save tokens 
	std::vector <std::string> tokens;

	// stringstream class check1 
	std::stringstream check1(input);

	std::string intermediate;

	// Tokenizing w.r.t. space ' ' 
	while (getline(check1, intermediate, ' '))
	{
		tokens.push_back(intermediate);
	}
	return tokens;
}



int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");
	if (fileInput.is_open()) {
		std::string line = "";
		auto intBagFit = 0;
		AdjList list;
		while (getline(fileInput, line)) {
			// layout of lines:
			// 0: color adjective
			// 1: color
			// 2: bags
			// 3: contain
			// 4: number
			// 5: color adj
			// 6: color
			// 7: bag(s),
			// 8: number
			// 9: color adj
			// 10: color
			// 11: bag(s),
			// etc.
			// each bag clause has 4 tokens
			auto tokens = tokenize(line);

			// Get first clause
			std::string mainColor = tokens.at(0) + tokens.at(1);

			// check base case of no other bags
			if (tokens.at(4) == "no") {
				list.addBlankEdge(mainColor);
				continue;
			}
			auto numberClauses = (tokens.size() - 8) / 4 + 1;



			for (auto i = 1; i <= numberClauses; i++) {
				auto number = std::stoi(tokens.at(4 * i));
				auto color = tokens.at(4 * i + 1) + tokens.at(4 * i + 2);
				list.addEdge(mainColor, color, number);
			}
		}

		std::string destination = "shinygold";
		intBagFit = list.countPaths(destination);

		std::cout << "Bag able to fit in " << intBagFit << " other bags."<< std::endl;

		auto intGoldBagFit = list.goldBagFit(destination);
		std::cout << "Gold bag able to fit " << intGoldBagFit << " other bags." << std::endl;

	}
	return 0;
}
