#include "proie.h"
#include <QRandomGenerator>

Proie::Proie(int x, int y)
    : x(x), y(y), age(0)
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

