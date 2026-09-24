#include "bush.h"
#include <QRandomGenerator>

Bush::Bush()
{
	berries = QRandomGenerator::global()->bounded(3);
}

void Bush::Grow()
{
	//berries spoiling
	berries -= QRandomGenerator::global()->bounded(berries ? berries : 0 );

	growth++;
	if (growth >= growthTime) {
		growth = 0;
		berries += QRandomGenerator::global()->bounded(15);
	}
}

void Bush::EatBerries(double eatenBerries)
{
	berries -= eatenBerries;
	weight = 1 * round(berries / 2);
}

void Bush::Update()
{
	Grow();
	weight = 1 * round(berries / 2);
}
