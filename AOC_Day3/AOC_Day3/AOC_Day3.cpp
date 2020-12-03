// AOC_Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>

// ideas to speed up:
// iterate through all lines of field
// maintain current positions for each slope, starting at 0, 0
//    for each path:
//    if y position on current line
//    calculate tree
//    move position by slope



int numTrees(const std::vector<std::string> & path, const int & deltaX, const int & deltaY) {
	auto posX = 0, posY = 0, trees = 0;
	auto height = path.size();
	auto length = path.at(0).size();
	while (posY < height) {
		posX = posX % length;
		char space = path.at(posY).at(posX);
		if (space == '#') {
			trees++;
		}
		posX += deltaX;
		posY += deltaY;
	}
	return trees;
}

int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");
	if (fileInput.is_open()) {
		std::string line = "";
		std::vector<std::string> path;
		while (getline(fileInput, line)) {
			path.push_back(line);
		}
		// encode delta pairs as elements in an array: evens are deltaX and subsequent element is deltaY
		std::vector<int> deltas = {1, 1, 3, 1, 5, 1, 7, 1, 1, 2};
		unsigned long long trees = 1;
		for (auto i = 0; i < deltas.size(); i += 2) {
			auto deltaX = deltas.at(i);
			auto deltaY = deltas.at(i + 1);
			trees *= numTrees(path, deltaX, deltaY);
		}
		std::cout << "Trees ran into : " << trees << std::endl;
		fileInput.close();
	}
	else {
		std::cerr << "Error opening input file" << std::endl;
	}

	
}