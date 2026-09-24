
#include <iostream>
#include <cmath>
#include <string>

int main()
{
    // initialisation des variables
    std::cout << "Choix des valeurs : \n";

    std::cout << "Population initiale des proies lapins_depart (lapins) : ";
    double lapins_depart;
    std::cin >> lapins_depart;

    std::cout << "Population initiale des predateurs renards_depart : ";
    double renards_depart;
    std::cin >> renards_depart;

    std::cout << "Taux de reproduction des proies (lapins_taux_croissance) : ";
    double lapins_taux_croissance;
    std::cin >> lapins_taux_croissance;

    std::cout << "Taux de reproduction des predateurs (renards_taux_croissance) : ";
    double renards_taux_croissance;
    std::cin >> renards_taux_croissance;

    std::cout << "Taux de mortalite des proies due aux predateurs (lapins_taux_mortalite) : ";
    double lapins_taux_mortalite;
    std::cin >> lapins_taux_mortalite;

    std::cout << "Taux de mortalite naturelle des predateurs (ranards_taux_mortalite) : ";
    double ranards_taux_mortalite;
    std::cin >> ranards_taux_mortalite;

    std::cout << "pas de temps (pas_temporelle)(envirron 0.01) : ";
    double pas_temporelle;
    std::cin >> pas_temporelle;

    std::cout << "Temps d'observation (0 = manuelle) (val = t) : \n";
    int temps_observation;
    std::cin >> temps_observation;

    int temps = 0;

    // Population actuelle des lapins
    double population_lapins = lapins_depart;

    // Population actuelle des renards
    double population_renards = renards_depart;

    // Etats d'equilibre
    double equilibre_lapins = ranards_taux_mortalite / renards_taux_croissance;
    double equilibre_renards = lapins_taux_croissance / lapins_taux_mortalite;

    std::cout << "\nEtats d'equilibre :\n";
    std::cout << "Lapins : " << equilibre_lapins << "\n";
    std::cout << "Renards : " << equilibre_renards << "\n\n";

    std::cout << "Temps d'observation : " << temps
        << " population de lapins : " << population_lapins
        << " population de renards : " << population_renards << "\n\n";

    std::cin.ignore();
    

    if (temps_observation == 0)
    {
        bool flag = true;

        while (flag)
        {
            // Equation de Lotka-Volterra :
            //
            // dH/dt = alpha H - beta H C
            // dC/dt = -gamma C + delta C H
            //
            // Methode d'Euler :
            //
            // H(t+1) = H(t) + alpha*H(t) - beta*H(t)*C(t)
            // C(t+1) = C(t) - gamma*C(t) + delta*C(t)*H(t)

            double nouv_population_lapins =
                population_lapins * (
				    lapins_taux_croissance * pas_temporelle 
                    - lapins_taux_mortalite * population_renards * pas_temporelle 
                    + 1

				);

            double nouv_population_renards =
                population_renards * (
                    -ranards_taux_mortalite * pas_temporelle
                    + renards_taux_croissance * population_renards * pas_temporelle
                    + 1
                );

            population_lapins = nouv_population_lapins;
            population_renards = nouv_population_renards;

            // Eviter d'avoir des populations negatives
            if (population_lapins < 0)
            {
                population_lapins = 0;
            }

            if (population_renards < 0)
            {
                population_renards = 0;
            }

            temps++;

            std::cout << "\nTemps d'observation : " << temps
                << " population de lapins : " << population_lapins
                << " population de renards : " << population_renards << "\n";

            std::cout << "Etats d'equilibre : "
                << "lapins = " << equilibre_lapins
                << ", renards = " << equilibre_renards << "\n";

            std::cout << "Appuyez sur Entree pour continuer ou entrez 0 pour arreter : \n";

            std::string choix;
            std::getline(std::cin, choix);

            if (choix == "0")
            {
                flag = false;
            }
        }
    }
    else
    {
        // Simulation automatique pendant temps_observation
        for (int i = 0; i < temps_observation; i++)
        {
            double nouveaux_lapins =
                population_lapins
                + lapins_taux_croissance * population_lapins
                - lapins_taux_mortalite * population_lapins * population_renards;

            double nouveaux_renards =
                population_renards
                - ranards_taux_mortalite * population_renards
                + renards_taux_croissance * population_renards * population_lapins;


            // Mise a jour des populations
            population_lapins = nouveaux_lapins;
            population_renards = nouveaux_renards;

            // Eviter d'avoir des populations negatives
            if (population_lapins < 0)
            {
                population_lapins = 0;
            }

            if (population_renards < 0)
            {
                population_renards = 0;
            }

            temps++;

            std::cout << "Temps d'observation : " << temps
                << " population de lapins : " << population_lapins
                << " population de renards : " << population_renards << "\n";
        }
    }

    return 0;
}

// Exécuter le projet : Ctrl+F5
// Démarrer le débogage : F5l


// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
