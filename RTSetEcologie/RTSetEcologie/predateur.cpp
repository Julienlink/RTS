#include "predateur.h"

#include <QRandomGenerator>

Predateur::Predateur(int x, int y)
    : x(x), y(y)
{
}

int Predateur::getX() const
{
    return x;
}

int Predateur::getY() const
{
    return y;
}

void Predateur::deplacer(int N)
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