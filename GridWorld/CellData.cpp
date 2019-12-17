#include "CellData.h"

double CellData::getMaxQ() {
	return MAX4(this->q[UP], this->q[LEFT], this->q[RIGHT], this->q[DOWN]);
}

int CellData::getMaxQIndex() {
	int index(0);
	double _max(-1000);
	for (int i(0); i < 4; ++i)
		if (_max < this->q[i]) {
			_max = this->q[i];
			index = i;
		}
	return index;
}