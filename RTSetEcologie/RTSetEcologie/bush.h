#pragma once

class Bush {
public:
	Bush(int x, int y);
	double getBerries() { return berries; }
	double getWeight() { return weight; }
	int getX() { return PosX; }
	int getY() { return PosY; }

	void Grow();
	void EatBerries(double eatenBerries);
	void Update();

private:
	//Bush's position on the map
	int PosX;
	int PosY;
	//time it take to grow a new batch of berries
	double growthTime = 5;
	double growth = 0;
	//numbers of berries on the bush
	double berries = 0;
	//how much preys want to go to it
	double weight = 1;
};