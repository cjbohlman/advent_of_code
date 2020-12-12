// AOC_Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

# define M_PI           3.14159265358979323846  /* pi */

enum class Direction { North, East, South, West };

void moveCoords(std::pair<int, int> & coords, Direction direction, int amount) {
	if (direction == Direction::North) {
		coords.second += amount;
	}
	else if (direction == Direction::South) {
		coords.second -= amount;
	}
	else if (direction == Direction::East) {
		coords.first += amount;
	}
	else if (direction == Direction::West) {
		coords.first -= amount;
	}

}

void moveCoords(std::pair<int, int> & coords, int moveX, int moveY) {
	coords.first += moveX;
	coords.second += moveY;
}

void rotateShipClockwise(Direction &direction, int amount) {
	std::vector<Direction> changes{Direction::North, Direction::East, Direction::South, Direction::West};
	int startingValue = -1;
	for (auto i = 0; i < changes.size(); i++) {
		if (changes.at(i) == direction) startingValue = i;
	}

	for (auto i = 0; i < amount / 90; i++) {
		startingValue = (startingValue + 1) % 4;
	}

	direction = changes.at(startingValue);

}

void rotateShipCouterclockwise(Direction &direction, int amount) {
	std::vector<Direction> changes{ Direction::North, Direction::West, Direction::South, Direction::East };
	int startingValue = -1;
	for (auto i = 0; i < changes.size(); i++) {
		if (changes.at(i) == direction) startingValue = i;
	}

	for (auto i = 0; i < amount / 90; i++) {
		startingValue = (startingValue + 1) % 4;
	}

	direction = changes.at(startingValue);

}

void rotateWaypointCouterclockwise(std::pair<int, int> &waypoint, std::pair<int, int> ship,  int amount) {
	auto radians = amount * (M_PI / 180);

	double x1 = waypoint.first;
	double y1 = waypoint.second;

	double x2 = x1 * std::cos(radians) - y1 * std::sin(radians);
	double y2 = x1 * std::sin(radians) + y1 * std::cos(radians);

	waypoint.first = std::round(x2);
	waypoint.second = std::round(y2);
}

void rotateWaypointClockwise(std::pair<int, int> & waypoint, std::pair<int, int> ship, int amount) {
	rotateWaypointCouterclockwise(waypoint, ship, 360-amount);
}


void RegularManhattanDistance(std::string &line, std::pair<int, int> &coords, Direction &direction)
{
	auto amount = std::stoi(line.substr(1));
	if (line.at(0) == 'F') {
		moveCoords(coords, direction, amount);
	}
	else if (line.at(0) == 'N') {
		moveCoords(coords, Direction::North, amount);
	}
	else if (line.at(0) == 'S') {
		moveCoords(coords, Direction::South, amount);
	}
	else if (line.at(0) == 'E') {
		moveCoords(coords, Direction::East, amount);
	}
	else if (line.at(0) == 'W') {
		moveCoords(coords, Direction::West, amount);
	}
	else if (line.at(0) == 'L') {
		rotateShipCouterclockwise(direction, amount);
	}
	else if (line.at(0) == 'R') {
		rotateShipClockwise(direction, amount);
	}
}

void WaypointManhattanDistance(std::string &line, std::pair<int, int> &coords, std::pair<int, int> &waypoint)
{
	auto amount = std::stoi(line.substr(1));
	if (line.at(0) == 'F') {
		for (int i = 0; i < amount; i++) {
			moveCoords(coords, waypoint.first, waypoint.second);
		}
	}
	else if (line.at(0) == 'N') {
		moveCoords(waypoint, Direction::North, amount);
	}
	else if (line.at(0) == 'S') {
		moveCoords(waypoint, Direction::South, amount);
	}
	else if (line.at(0) == 'E') {
		moveCoords(waypoint, Direction::East, amount);
	}
	else if (line.at(0) == 'W') {
		moveCoords(waypoint, Direction::West, amount);
	}
	else if (line.at(0) == 'L') {
		rotateWaypointCouterclockwise(waypoint, coords, amount);
	}
	else if (line.at(0) == 'R') {
		rotateWaypointClockwise(waypoint, coords, amount);
	}
}

int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");
	// pair operates on an xy gird
	std::pair<int, int> coords{0, 0};
	std::pair<int, int> waypoint{ 10, 1 };
	auto direction = Direction::East;
	if (fileInput.is_open()) {
		std::string line = {};
		while (getline(fileInput, line)) {
			// RegularManhattanDistance(line, coords, direction);
			WaypointManhattanDistance(line, coords, waypoint);
		}
		std::cout << "manhattan distance: " << std::abs(coords.first) + std::abs(coords.second) << std::endl;
		fileInput.close();
	}
	return 0;
}