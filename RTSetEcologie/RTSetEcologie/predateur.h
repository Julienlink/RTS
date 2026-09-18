#pragma once

class Predateur
{
public:
    Predateur(int x, int y);

    int getX() const;
    int getY() const;

    void deplacer(int N);

private:
    int x;
    int y;
};