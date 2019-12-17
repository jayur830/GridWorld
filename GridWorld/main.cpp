#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include "GridWorld.h"

class Agent {
public:
	int i, j;
	double reward;

	Agent() : i(0), j(0), reward(0) {}
};

std::string toString(int n) {
	std::string s;
	if (n != 0) {
		s.append(toString(n / 10));
		s.push_back(n - ((n / 10) * 10) + '0');
	}
	return s;
}

int main() {
	const int height(7), width(4), episodeLength(3000), sleepTime(0);
	const double discountFactor(0.9), learningRate(0.1);
	GridWorld gridWorld(height, width);

	gridWorld.initReward(-0.1, GridWorld::Loc{ 6, 3, WIN }, 1, GridWorld::Loc{ 4, 2, LOSE });

	Agent agent;

	Sleep(sleepTime);
	gridWorld.print(agent.i, agent.j);

	for (int episode(0); episode < episodeLength; ++episode) {
		Sleep(sleepTime);
		system("cls");

		int i(agent.i), j(agent.j);
		int pre_i(i), pre_j(j);
		//const int action(rand() % 4);
		const int action(gridWorld.getCell(pre_i, pre_j).getMaxQIndex());

		switch (action) {
		case 0: --i; break;
		case 1: --j; break;
		case 2: ++j; break;
		case 3: ++i; break;
		}

		if (gridWorld.isInside(i, j)) {
			agent.i = i; agent.j = j;
			CellData& cell(gridWorld.getCell(i, j));
			agent.reward = cell.reward;
			gridWorld.getCell(pre_i, pre_j).q[action] += learningRate * (agent.reward + discountFactor * cell.getMaxQ() - gridWorld.getCell(pre_i, pre_j).q[action]);
			if (agent.reward == WIN || agent.reward == LOSE) agent.i = agent.j = 0;
		}
		else {
			agent.i = i = pre_i;
			agent.j = j = pre_j;
			gridWorld.getCell(pre_i, pre_j).q[action] += learningRate * ((agent.reward = -5.0) - gridWorld.getCell(pre_i, pre_j).q[action]);
		}

		gridWorld.print(agent.i, agent.j);
		std::cout << "[Episode " << episode << "/" << episodeLength << "] Agent status: (" << i << ", " << j << "), action: "
			<< (action == UP ? "   UP" : (action == LEFT ? " LEFT" : (action == RIGHT ? "RIGHT" : " DOWN")))
			<< ", reward: " << agent.reward;
	}
	
	system("cls");
	gridWorld.print(agent.i, agent.j);

	return 0;
}