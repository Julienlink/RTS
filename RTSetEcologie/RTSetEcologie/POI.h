#pragma once
class POI {
public:

	virtual POIType getType() const = 0;
	virtual double getWeight() const = 0;
	virtual void Update() = 0;
};

enum class POIType {
	Eau,
	Nourriture,
	Abri	
};