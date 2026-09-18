#pragma once

#include <QWidget>
#include <vector>
#include <fstream>
#include "proie.h"

class Grille : public QWidget
{
public:
    Grille(QWidget* parent = nullptr);

    void avancerSimulation();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    int N = 20;
    int tempsSimulation = 1;

    std::vector<Proie> proies;
    std::ofstream fichierPopulation;
};