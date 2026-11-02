#include "predateur.h"

#include <QRandomGenerator>
#include <algorithm>
#include <cmath>
#include <limits>

Predateur::Predateur(int x, int y)
    : x(x), y(y)
{
}

void Predateur::deplacer(int N, const std::vector<Proie>& proies)
{
    const Proie* cible = nullptr;
    double distanceCible = std::numeric_limits<double>::max();

    for (const Proie& proie : proies)
    {
        int dx = proie.getX() - x;
        int dy = proie.getY() - y;
        int distanceX = std::min(std::abs(dx), N - std::abs(dx));
        int distanceY = std::min(std::abs(dy), N - std::abs(dy));
        double distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

        if (distance > 10.0 || distance == 0.0)
            continue;

        if (distance < distanceCible)
        {
            distanceCible = distance;
            cible = &proie;
        }
    }

    if (cible == nullptr)
    {
        deplacer(N);
        return;
    }

    int dx = cible->getX() - x;
    int dy = cible->getY() - y;
    int distanceX = std::min(std::abs(dx), N - std::abs(dx));
    int distanceY = std::min(std::abs(dy), N - std::abs(dy));

    if (distanceX > distanceY || (distanceX == distanceY && QRandomGenerator::global()->bounded(2) == 0))
    {
        if (distanceX != 0)
            x += (std::abs(dx) <= N / 2) ? (dx > 0 ? 1 : -1) : (dx > 0 ? -1 : 1);
    }
    else if (distanceY != 0)
    {
        y += (std::abs(dy) <= N / 2) ? (dy > 0 ? 1 : -1) : (dy > 0 ? -1 : 1);
    }

    x = (x + N) % N;
    y = (y + N) % N;
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