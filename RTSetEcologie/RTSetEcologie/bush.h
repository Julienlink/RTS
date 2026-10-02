#pragma once
#include"POI.h"

class Bush : public virtual POI {
public:
	Bush();
	POIType getType() const override { return POIType::Nourriture; }
	double getBerries() { return berries; }
	double getWeight() const override { return weight; }

	void Grow();
	void EatBerries(double eatenBerries);
	void Update() override;

private:
	//time it take to grow a new batch of berries
	double growthTime = 5;
	double growth = 0;
	//numbers of berries on the bush
	double berries = 0;
	//how much preys want to go to it
	double weight = 1;
};