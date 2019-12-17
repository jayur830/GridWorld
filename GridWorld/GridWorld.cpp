#include "GridWorld.h"
#include <iostream>
#include <cstdarg>

GridWorld::GridWorld(const int height, const int width) :
	height(height), width(width) {
	this->gridCells = new CellData * [this->height];
	for (int i(0); i < this->height; ++i)
		this->gridCells[i] = new CellData[this->width];
}

GridWorld::~GridWorld() {
	for (int i(0); i < this->height; ++i)
		delete[] this->gridCells[i];
	delete this->gridCells;
	this->gridCells = nullptr;
}

CellData& GridWorld::getCell(const int i, const int j) {
	return this->gridCells[i][j];
}

void GridWorld::initReward(const double general, const Loc goal, const int num_mistake, ...) {
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			this->gridCells[i][j].reward = general;
	this->gridCells[goal.i][goal.j].reward = goal.reward;
	va_list ap;
	va_start(ap, num_mistake);
	for (int k(0); k < num_mistake; ++k) {
		Loc loc(va_arg(ap, Loc));
		this->gridCells[loc.i][loc.j].reward = loc.reward;
	}
	va_end(ap);
}

bool GridWorld::isInside(const int i, const int j) {
	return i >= 0 && i < this->height &&
		j >= 0 && j < this->width;
}

void GridWorld::printSigned(const double value) {
	printf("%c%1.2f", value > 0 ? '+' : (value < 0 ? '-' : ' '), abs(value));
}

void GridWorld::print(const int cur_i, const int cur_j) {
	for (int i(0); i < this->height; ++i) {
		for (int j(0); j < this->width; ++j) {
			printf("     ");
			if (this->gridCells[i][j].reward == WIN ||
				this->gridCells[i][j].reward == LOSE) printf("     ");
			else printSigned(this->gridCells[i][j].q[UP]);
			printf("     ");
		}

		printf("\n");

		for (int j(0); j < this->width; ++j) {
			if (this->gridCells[i][j].reward == WIN ||
				this->gridCells[i][j].reward == LOSE) printf("     ");
			else printSigned(this->gridCells[i][j].q[LEFT]);
			printf("%s", i == cur_i && j == cur_j ? "  ¡Ü " :
				(this->gridCells[i][j].reward == WIN ? " GOAL" :
				(this->gridCells[i][j].reward == LOSE ? " DIE " : "     ")));
			if (this->gridCells[i][j].reward == WIN ||
				this->gridCells[i][j].reward == LOSE) printf("     ");
			else printSigned(this->gridCells[i][j].q[RIGHT]);
		}

		printf("\n");

		for (int j(0); j < this->width; ++j) {
			printf("     ");
			if (this->gridCells[i][j].reward == WIN ||
				this->gridCells[i][j].reward == LOSE) printf("     ");
			else printSigned(this->gridCells[i][j].q[DOWN]);
			printf("     ");
		}

		printf("\n");
	}
}