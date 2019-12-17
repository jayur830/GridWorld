#pragma once
#include "CellData.h"

#define WIN 1
#define LOSE -5

class GridWorld {
public:
	const int height, width;
	CellData** gridCells = nullptr;

	GridWorld(const int height, const int width);
	~GridWorld();
	CellData& getCell(const int i, const int j);

	struct Loc {
		int i, j;
		double reward;
	};

	void initReward(const double general, const Loc goal, const int num_mistake, ...);
	bool isInside(const int i, const int j);
	void printSigned(const double value);
	void print(const int cur_i, const int cur_j);
};