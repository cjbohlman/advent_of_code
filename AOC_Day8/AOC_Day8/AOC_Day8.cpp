// AOC_Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Instruction {
public:
	std::string instruction;
	std::string direction;
	int amount;

	bool visited;
	int visitedOrder;

	Instruction(std::string instruction, char direction, std::string amount) {
		this->instruction = instruction;
		std::string strDirection(1, direction);
		this->direction = strDirection;
		this->amount = std::stoi(amount);
		this->visited = false;
		this->visitedOrder = 0;
	}


};

void execute(int &i, std::vector<Instruction> &instructions, int &acc);

void resetInstructions(std::vector<Instruction> &instructions) {
	for (auto & element : instructions) {
		element.visited = false;
		element.visitedOrder = 0;
	}
}

int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");
	if (fileInput.is_open()) {
		std::string line = "";
		std::vector<Instruction> instructions;
		while (getline(fileInput, line)) {
			char charDirection;
			std::string instruction;
			std::string amount;
			std::stringstream ss(line);
			ss >> instruction >> charDirection >> amount;
			Instruction inst(instruction, charDirection, amount);
			instructions.push_back(inst);
		}
		int i = 0, acc = 0;
		execute(i, instructions, acc);
		resetInstructions(instructions);
		if (i >= instructions.size()) {
			std::cout << "No loops found..." << std::endl;
		}
		else {
			std::cout << "Acc value at loop: " << acc << std::endl;
		}

		// fix the loop: either a nop is supposed to be a jmp, or a jmp is supposed to be a nop
		for (auto & element : instructions) {
			i = 0, acc = 0;
			if (element.instruction == "jmp") {
				// change to nop, execute, and change back
				element.instruction = "nop";
				execute(i, instructions, acc);
				element.instruction = "jmp";
			}
			else if (element.instruction == "nop") {
				// change to jmp, execute, and change back
				element.instruction = "jmp";
				execute(i, instructions, acc);
				element.instruction = "nop";
			}
			if (i == instructions.size()) {
				std::cout << "Fixed instruction accumulator: " << acc << std::endl;
				break;
			}
			resetInstructions(instructions);
		}
	}
	return 0;
}

void execute(int &i, std::vector<Instruction> &instructions, int &acc)
{
	int cnt = 1;
	bool looped = false;
	while (!looped && i < instructions.size()) {
		Instruction *instr = &instructions.at(i);
		// check if looped
		if (instr->visited == true) {
			looped = true;
			continue;
		}

		// else execute instruction
		if (instr->instruction == "nop") {
			i++;
		}
		else if (instr->instruction == "acc") {
			if (instr->direction == "+") {
				acc += instr->amount;
			}
			else if (instr->direction == "-") {
				acc -= instr->amount;
			}
			i++;
		}
		else if (instr->instruction == "jmp") {
			if (instr->direction == "+") {
				i += instr->amount;
			}
			else if (instr->direction == "-") {
				i -= instr->amount;
			}
		}
		instr->visited = true;
		instr->visitedOrder = cnt;
		cnt++;
	}
}
