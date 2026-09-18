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

    std::cout << "H actuel : " << H << std::endl;
    std::cout << "C actuel : " << C << std::endl;

    std::cout << "H suivant : " << nouveauH << std::endl;
    std::cout << "C suivant : " << nouveauC << std::endl;

    return 0;
}