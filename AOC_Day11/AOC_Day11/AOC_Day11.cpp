// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

int countSeats(std::vector<std::vector<char>> & seats) {
	auto count = 0;
	for (auto &row : seats) {
		for (auto &elem : row) {
			if (elem == '#') count++;
		}
	}
	return count;
}

std::pair<int, int> nextSeat(std::vector<std::vector<char>> & seats, const int &row, const int &col, const int directionY, const int directionX) {
	std::pair<int, int> nextSeat{ -1, -1 };
	auto newRow = row;
	auto newCol = col;
		try {

			while (true) {
				newRow += directionY;
				newCol += directionX;
				if (seats.at(newRow).at(newCol) == 'L' || seats.at(newRow).at(newCol) == '#') {
					nextSeat.first = newRow;
					nextSeat.second = newCol;
					break;
				}
			}
		}
		catch (const std::out_of_range& oor) {

		}

	return nextSeat;
}

int adjacentViewSeatsOccupied(std::vector<std::vector<char>> & seats, const int &row, const int &col) {
	int seatCounts = 0;
	std::pair<int, int> seat{ -1, -1 };

	// check up
	seat = nextSeat(seats, row, col, -1, 0);
	if (row > 0 && (seat.first != -1 || seat.second != -1) && seats.at(seat.first).at(seat.second) == '#') seatCounts++;

	// check down
	seat = nextSeat(seats, row, col, 1, 0);
	if (row < seats.size() - 1 && (seat.first != -1 || seat.second != -1) && seats.at(seat.first).at(seat.second) == '#') seatCounts++;

	// check left
	seat = nextSeat(seats, row, col, 0, -1);
	if (col > 0 && (seat.first != -1 || seat.second != -1) && seats.at(seat.first).at(seat.second) == '#') seatCounts++;

	// check right
	seat = nextSeat(seats, row, col, 0, 1);
	if (col < seats.at(row).size() - 1 && (seat.first != -1 || seat.second != -1) && seats.at(seat.first).at(seat.second) == '#') seatCounts++;

	// check up left
	seat = nextSeat(seats, row, col, -1, -1);
	if (row > 0 && col > 0 && (seat.first != -1 || seat.second != -1) && seats.at(seat.first).at(seat.second) == '#') seatCounts++;

	// check up right
	seat = nextSeat(seats, row, col, -1, +1);
	if (row > 0 && col < seats.at(row).size() - 1 && (seat.first != -1 || seat.second != -1) && seats.at(seat.first).at(seat.second) == '#') seatCounts++;

	// check down left
	seat = nextSeat(seats, row, col, 1, -1);
	if (row < seats.size() - 1 && col > 0 && (seat.first != -1 || seat.second != -1) && seats.at(seat.first).at(seat.second) == '#') seatCounts++;

	// check down right
	seat = nextSeat(seats, row, col, 1, 1);
	if (row < seats.size() - 1 && col < seats.at(row).size() - 1 && (seat.first != -1 || seat.second != -1) && seats.at(seat.first).at(seat.second) == '#') seatCounts++;

	return seatCounts;
}

int adjacentSeatsOccupied(std::vector<std::vector<char>> & seats, const int &row, const int &col) {
	int seatCounts = 0;
	// check up
	if (row > 0 && seats.at(row - 1).at(col) == '#') seatCounts++;
	// check down
	if (row < seats.size() - 1 && seats.at(row + 1).at(col) == '#') seatCounts++;
	// check left
	if (col > 0 && seats.at(row).at(col - 1) == '#') seatCounts++;
	// check right
	if (col < seats.at(row).size() - 1 && seats.at(row).at(col + 1) == '#') seatCounts++;
	// check up left
	if (row > 0 && col > 0 && seats.at(row - 1).at(col - 1) == '#') seatCounts++;
	// check up right
	if (row > 0 && col < seats.at(row).size() - 1 && seats.at(row - 1).at(col + 1) == '#') seatCounts++;
	// check down left
	if (row < seats.size() - 1 && col > 0 && seats.at(row + 1).at(col - 1) == '#') seatCounts++;
	// check down right
	if (row < seats.size() - 1 && col < seats.at(row).size() - 1 && seats.at(row + 1).at(col + 1) == '#') seatCounts++;
	return seatCounts;
}

bool runSeats(std::vector<std::vector<char>> & seats) {
	bool movement = false;
	std::vector<std::vector<char>> oldSeats = seats;
	for (int row = 0; row < seats.size(); row++) {
		for (int col = 0; col < seats.at(0).size(); col++) {
			if (oldSeats.at(row).at(col) == 'L' && adjacentViewSeatsOccupied(oldSeats, row, col) == 0) {
				seats.at(row).at(col) = '#';
				movement = true;
			}
			if (oldSeats.at(row).at(col) == '#' && adjacentViewSeatsOccupied(oldSeats, row, col) >= 5) {
				seats.at(row).at(col) = 'L';
				movement = true;
			}
		}
	}
	return movement;
}

int main()
{
	std::vector<std::vector<char>> seats;
	std::ifstream fileInput;
	fileInput.open("input.txt");
	if (fileInput.is_open()) {
		std::string line = {};
		while (getline(fileInput, line)) {
			std::vector<char> newRow;
			for (auto &elem : line) {
				newRow.push_back(elem);
			}
			seats.push_back(newRow);
		}
		bool movement = true;
		while (movement) {
			movement = runSeats(seats);
		}
		std::cout << "Stabilized at " << countSeats(seats) << " seats." << std::endl;
		fileInput.close();
	}
}