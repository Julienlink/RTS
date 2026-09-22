// projet_math_part_1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <cmath>
#include <string>

int main()
{
	//initialisation des variables
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

	std::cout << "Temps d'observation (0 = manuelle) (val = t) : \n";
	int temps_observation;
	std::cin >> temps_observation;
	int temps = 0;
	std::cout << "Temps d'observation : " << temps++ << " population de lapins : " << lapins_depart << "\n\n";
	std::cin.ignore();


	double population = lapins_depart;

	double equilibre = lapins_taux_croissance / lapins_taux_mortalite;

	if (temps_observation == 0)
	{
		bool flag = true;

		while (flag)
		{
			// Équation : P(t+1) = P(t) + aP(t) - bP(t)²
			population = population + lapins_taux_croissance * population
				- lapins_taux_mortalite * population * population;

			std::cout << "Temps d'observation : " << temps++
				<< " population de lapins : " << population << "\n";

			std::cout << "états d’équilibre : " << equilibre << "\n";

			std::cout << "Appuyez sur Entree pour continuer ou entrez 0 pour arreter : \n";

			std::string choix;
			std::getline(std::cin, choix);

			if (choix == "0")
			{
				flag = false;
			}
		}
	}

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
