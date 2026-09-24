#pragma once
#include "POI.h"
#include<vector>
class Proie
{
public:
    Proie(int x, int y, int ageInitial = 30);

    int getX() const;
    int getY() const;
    int getAge() const;
    int getTempsAvantReproduction() const;

    void deplacer(int N);
    void deplacer(int N, std::vector<std::vector<POI>>);
    void vieillir(int dt);

    bool peutSeReproduire() const;
    void vientDeSeReproduire();
    void reduireTempsReproduction();

private:
    int x;
    int y;
    int age;

    int tempsAvantReproduction;
};