#include <iostream>

double populationSuivante(double P, double a, double b, double dt)
{
    return P + dt * (a * P - b * P * P);
}

void simuler(double P, double a, double b, double dt, double tempsMax)
{
    double temps = 0.0;

    while (temps <= tempsMax)
    {
        std::cout << temps
            << " ; "
            << P
            << std::endl;

        P = populationSuivante(P, a, b, dt);

        temps += dt;
    }
}

int main()
{
    double P = 2.0;

    double a = 0.05;
    double b = 0.01;

    double dt = 1.0;
    double tempsMax = 100.0;

    simuler(P, a, b, dt, tempsMax);

    return 0;
}