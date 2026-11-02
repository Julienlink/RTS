#pragma once

#include "proie.h"

class Predateur
{
public:
    Predateur(int x, int y);

    int getX() const;
    int getY() const;

    void deplacer(int N);
    void deplacer(int N, const std::vector<Proie>& proies);

private:
    int x;
    int y;
};