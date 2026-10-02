#pragma once
#pragma once
#include"POI.h"

class Cave : public POI {
public:
	Cave() = default;
	POIType getType() const override { return POIType::Abri; }
	double getWeight() const override { return weight; }

	/*NOT IMPLEMENTED*/
	void Update() override {};
private:
	double weight = 2;
};