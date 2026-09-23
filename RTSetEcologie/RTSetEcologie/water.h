#pragma once
class Water {
public:
	Water(int x, int y);
	int getX();
	int getY();
private:
	int PosX;
	int PosY;
	double weight = 5;
};