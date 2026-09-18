#include <iostream>
#include <fstream>

double populationSuivante(double P, double a, double b, double dt)
{
    return P + dt * (a * P - b * P * P);
}

void simuler(double P, double a, double b, double dt, double tempsMax)
{
    double temps = 0.0;

    /*fichier csv*/
    std::ofstream fichier("population.csv");
    fichier << "Temps;Population\n";

    while (temps <= tempsMax)
    {
        std::cout << temps
            << " ; "
            << P
            << std::endl;

        fichier << temps << ";" << P << "\n";

        P = populationSuivante(P, a, b, dt);

        temps += dt;
    }
    fichier.close();
}

void populationSuivanteLotka(
    double H,
    double C,
    double alpha,
    double beta,
    double gamma,
    double delta,
    double dt,
    double& nouveauH,
    double& nouveauC)
{
    nouveauH = H + dt * (alpha * H - beta * H * C);

    nouveauC = C + dt * (-gamma * C + delta * C * H);
}

void simulerLotka(
    double H,
    double C,
    double alpha,
    double beta,
    double gamma,
    double delta,
    double dt,
    int iterations)
{
    std::ofstream fichier("lotka_volterra.csv");
    fichier << "Temps;Proies;Predateurs\n";

    for (int i = 0; i < iterations; i++)
    {
        double temps = i * dt;

        std::cout << "Iteration " << i
            << " ; H = " << H
            << " ; C = " << C
            << std::endl;

        fichier << temps
            << ";"
            << H
            << ";"
            << C
            << "\n";

        double nouveauH;
        double nouveauC;

        populationSuivanteLotka(
            H,
            C,
            alpha,
            beta,
            gamma,
            delta,
            dt,
            nouveauH,
            nouveauC
        );

        H = nouveauH;
        C = nouveauC;
    }

    fichier.close();
}

//Le saint main
int main()
{
    double H = 50.0;
    double C = 100.0;

    double alpha = 0.05;
    double beta = 0.001;
    double gamma = 0.05;
    double delta = 0.001;

    double dt = 1.0;

    int iterations = 500;

    simulerLotka(
        H,
        C,
        alpha,
        beta,
        gamma,
        delta,
        dt,
        iterations
    );

    return 0;
}