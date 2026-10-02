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
    double getStat(POIType type);

    void deplacer(int N);
    void deplacer(int N, const std::vector<std::vector<POI*>>& poi);
    void vieillir(int dt);

    bool peutSeReproduire() const;
    void vientDeSeReproduire();
    void reduireTempsReproduction();

    

private:
    int x;
    int y;
    int age;

    //stats de la proie - 100 = max, 0 = mort
    double faim=100.0f;
    double soif = 100.0f;
    double insécurité = 100.0f;

    int tempsAvantReproduction;
};