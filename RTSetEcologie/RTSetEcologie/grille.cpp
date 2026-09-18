#include "grille.h"

#include <QPainter>

#include <QRandomGenerator>

#include <QString>

Grille::Grille(QWidget* parent)
    : QWidget(parent)
{
    int H0 = 50;

    for (int i = 0; i < H0; i++)
    {
        int x = QRandomGenerator::global()->bounded(N);
        int y = QRandomGenerator::global()->bounded(N);

        proies.emplace_back(x, y);
    }

    int C0 = 20;

    for (int i = 0; i < C0; i++)
    {
        int x = QRandomGenerator::global()->bounded(N);
        int y = QRandomGenerator::global()->bounded(N);

        predateurs.emplace_back(x, y);
    }

    fichierPopulation.open("population_proies.csv");
    fichierPopulation << "Temps;Population\n";
    fichierPopulation << "0;" << proies.size() << "\n";
}

void Grille::avancerSimulation()
{
    std::vector<Proie> nouvellesProies;

    /*Deplacement et vieillissement des proies*/
    for (Proie& proie : proies)
    {
        proie.deplacer(N);
        proie.vieillir(1);
        proie.reduireTempsReproduction();
    }

    /*Deplacement predateurs*/
    for (Predateur& predateur : predateurs)
    {
        predateur.deplacer(N);
    }

    /*Mort des predateurs*/
    double probabiliteMort = 0.05;

    for (size_t i = 0; i < predateurs.size(); )
    {
        double tirage = QRandomGenerator::global()->generateDouble();

        if (tirage < probabiliteMort)
        {
            predateurs.erase(predateurs.begin() + i);
        }
        else
        {
            i++;
        }
    }

    /*Recherche de partenaire entre les differentes proies*/
    for (size_t i = 0; i < proies.size(); i++)
    {
        for (size_t j = i + 1; j < proies.size(); j++)
        {
            if (proies[i].getX() == proies[j].getX()
                && proies[i].getY() == proies[j].getY())
            {
                if (proies[i].peutSeReproduire()
                    && proies[j].peutSeReproduire())
                {
                    nouvellesProies.emplace_back(
                        proies[i].getX(),
                        proies[i].getY(),
                        0
                    );

                    proies[i].vientDeSeReproduire();
                    proies[j].vientDeSeReproduire();
                }
            }
        }
    }

    /*Nouvelles proies*/
    for (const Proie& nouvelleProie : nouvellesProies)
    {
        proies.push_back(nouvelleProie);
    }

    /*Vider buffer dans le fichier imediatement = CSV mis a jour tout de suite*/
    fichierPopulation << tempsSimulation
        << ";"
        << proies.size()
        << "\n";

    fichierPopulation.flush();

    tempsSimulation++;

    /*Affichage grille*/
    update();
}


void Grille::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    int largeurCase = width() / N;
    int hauteurCase = height() / N;

    for (int i = 0; i <= N; i++)
    {
        painter.drawLine(
            i * largeurCase,
            0,
            i * largeurCase,
            height()
        );

        painter.drawLine(
            0,
            i * hauteurCase,
            width(),
            i * hauteurCase
        );
    }

    for (const Proie& proie : proies)
    {
        int x = proie.getX() * largeurCase;
        int y = proie.getY() * hauteurCase;

        painter.drawEllipse(
            x + 5,
            y + 5,
            largeurCase - 10,
            hauteurCase - 10
        );
    }

    for (const Predateur& predateur : predateurs)
    {
        int x = predateur.getX() * largeurCase;
        int y = predateur.getY() * hauteurCase;

        painter.drawRect(
            x + 5,
            y + 5,
            largeurCase - 10,
            hauteurCase - 10
        );
    }

    painter.drawText(
        10,
        20,
        "Nombre de proies : " + QString::number(proies.size())
    );

    painter.drawText(
        10,
        40,
        "Nombre de predateurs : " + QString::number(predateurs.size())
    );
}