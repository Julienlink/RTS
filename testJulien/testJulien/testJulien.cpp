// testJulien.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include<fstream>
#include<sstream>
#include<cmath>

double alpha = 0.05;
double beta = 0.001;
double gamma = 0.05;
double delta = 0.001;

double H = 50;
double C = 100;

double Hactual = H;
double Cactual = C;

std::ofstream File;

//jour
double dT = 1;

int it = 500;

void LoktaVolterra(double Hn, double Cn, double dt,double a,double b, double g,double d,int nbIt) {
	StartSim();
	Export(0, Hn, Cn);
	if (!(nbIt > 0)) {
		std::cout << "Iteration can't be lower then 1,";
		nbIt = 1;
	}
	for (int i = 0;i < nbIt;i++) {
		Hn = Hn + dt * Hn * (a - b * Cn);
		Cn = Cn + dt * Cn * (-g + d * Hn);
		Export(i + 1, Hn, Cn);
	}
	Hactual = Hn;
	Cactual = Cn;
	EndSim();
}

void Export(double temps,double Hn,double Cn) {
	File << temps << "," << Hn << "," << Cn << "\n";

}
void StartSim() {
	File.open("PopulationsEvolution.csv");
	File << "Temps,H,C\n";
}

void EndSim() {
	File.close();
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
