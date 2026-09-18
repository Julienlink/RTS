#include "proie.h"
#include <QRandomGenerator>

Proie::Proie(int x, int y, int ageInitial)
    : x(x), y(y), age(ageInitial), tempsAvantReproduction(0)
{
}

int Proie::getX() const
{
    return x;
}

int Proie::getY() const
{
    return y;
}

int Proie::getAge() const
{
    return age;
}

int Proie::getTempsAvantReproduction() const
{
    return tempsAvantReproduction;
}

bool Proie::peutSeReproduire() const
{
    return age >= 30 && tempsAvantReproduction == 0;
}

void Proie::vientDeSeReproduire()
{
    tempsAvantReproduction = 10;
}

void Proie::reduireTempsReproduction()
{
    if (tempsAvantReproduction > 0)
    {
        tempsAvantReproduction--;
    }
}

void Proie::vieillir(int dt)
{
    age += dt;
}

void Proie::deplacer(int N)
{
    int direction = QRandomGenerator::global()->bounded(4);

    switch (direction)
    {
    case 0:
        y--;
        break;

    case 1:
        y++;
        break;

    case 2:
        x--;
        break;

    case 3:
        x++;
        break;
    }

    x = (x + N) % N;
    y = (y + N) % N;
}

