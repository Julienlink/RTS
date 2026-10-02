#pragma once
#include"POI.h"

class Water : public POI {
public:
	Water() = default;

	POIType getType() const override { return POIType::Eau; }
	double getWeight() const override { return weight; }

	//will implement with season and freezing water
	void Update() override {};
private:
	double weight = 5;
};