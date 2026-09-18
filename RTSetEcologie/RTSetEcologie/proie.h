#pragma once

class Proie
{
public:
    Proie(int x, int y);

    int getX() const;
    int getY() const;
    int getAge() const;

    void deplacer(int N);
    void vieillir(int dt);

private:
    int x;
    int y;
    int age;
};