#pragma once
#define MAX2(a, b) a > b ? a : b
#define MAX3(a, b, c) MAX2(MAX2(a, b), c)
#define MAX4(a, b, c, d) MAX2(MAX3(a, b, c), d)
enum { UP, LEFT, RIGHT, DOWN };

class CellData {
public:
	double q[4] = { 0, 0, 0, 0 }, reward = 0;

	double getMaxQ();
	int getMaxQIndex();
};