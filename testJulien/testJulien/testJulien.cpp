// testJulien.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include<cmath>


float lokta_Euler(float entity_rate, int P0, int n) {
	return pow(1 + entity_rate, n) * P0;
}



int main()
{
	float prey = 0.05f;
	float hunter = -0.1f;
	int P0 = 2;

	std::cout << "data: proie = 0.05 , predateur= -0.1, P0=1 " << std::endl;
	float j1 = lokta_Euler(prey, P0, 1);
	float j5 = lokta_Euler(prey, P0, 5);
	float j15 = lokta_Euler(prey, P0, 15);
	float j25 = lokta_Euler(prey, P0, 25);
	std::cout << "proie j1, j5, j15, j25 :" << j1 << " , " << j5 << " , " << j15  << " , " << j25 << std::endl;

	j1 = lokta_Euler(hunter, P0, 1);
	j5 = lokta_Euler(hunter, P0, 5);
	j15 = lokta_Euler(hunter, P0, 15);
	j25 = lokta_Euler(hunter, P0, 25);

	std::cout << "predateur j1, j5, j15, j25 :" << j1 << " , " << j5 << " , " << j15 << " , " << j25 << std::endl;

	float j14 = lokta_Euler(hunter, P0, 200);

	std::cout << "predateur j14 : " << j14<< std::endl;
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
