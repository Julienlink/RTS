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

    fichierPopulation.open("population_proies.csv");
    fichierPopulation << "Temps;Population\n";
    fichierPopulation << "0;" << proies.size() << "\n";
}

void Grille::avancerSimulation()
{
    std::vector<Proie> nouvellesProies;

    double p = 0.05;

    for (Proie& proie : proies)
    {
        proie.deplacer(N);
        proie.vieillir(1);

        double hasard = QRandomGenerator::global()->generateDouble();

        if (hasard < p)
        {
            int x = QRandomGenerator::global()->bounded(N);
            int y = QRandomGenerator::global()->bounded(N);

            nouvellesProies.emplace_back(x, y);
        }
    }

    for (const Proie& nouvelleProie : nouvellesProies)
    {
        proies.push_back(nouvelleProie);
    }

    /*vider buffer dans le fichier imediatement = csv mis a jour tout de suite*/
    fichierPopulation << tempsSimulation
        << ";"
        << proies.size()
        << "\n";

    fichierPopulation.flush();

    tempsSimulation++;

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

    painter.drawText(
        10,
        20,
        "Nombre de proies : " + QString::number(proies.size())
    );
}