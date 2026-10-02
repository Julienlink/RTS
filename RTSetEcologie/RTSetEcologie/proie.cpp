#include "proie.h"
#include <QRandomGenerator>

Proie::Proie(int x, int y, int ageInitial)
    : x(x), y(y), age(ageInitial), tempsAvantReproduction(0)
{
}

int Proie::getX() const
{
    return x;
}

int Proie::getY() const
{
    return y;
}

int Proie::getAge() const
{
    return age;
}

int Proie::getTempsAvantReproduction() const
{
    return tempsAvantReproduction;
}

bool Proie::peutSeReproduire() const
{
    return age >= 30 && tempsAvantReproduction == 0;
}

void Proie::vientDeSeReproduire()
{
    tempsAvantReproduction = 10;
}

void Proie::reduireTempsReproduction()
{
    if (tempsAvantReproduction > 0)
    {
        tempsAvantReproduction--;
    }
}

void Proie::vieillir(int dt)
{
    age += dt;
    faim -= 15;
    soif -= 33;
    insécurité -= 1;
}

void Proie::deplacer(int N)
{
    int direction = QRandomGenerator::global()->bounded(4);

    switch (direction)
    {
    case 0:
        y--;
        break;

    case 1:
        y++;
        break;

    case 2:
        x--;
        break;

    case 3:
        x++;
        break;
    }

    x = (x + N) % N;
    y = (y + N) % N;
}


void Proie::deplacer(
    int N,
    const std::vector<std::vector<POI*>>& poi)
{
    // Poids de base : permet de garder une part d'aléatoire
    double poidsHaut = 1.0;
    double poidsBas = 1.0;
    double poidsGauche = 1.0;
    double poidsDroite = 1.0;


    // ---------------------------------------------------------
    // POI le plus proche de chaque type
    // ---------------------------------------------------------

    POI* poiEau = nullptr;
    POI* poiNourriture = nullptr;
    POI* poiAbri = nullptr;

    double distanceEau =
        std::numeric_limits<double>::max();

    double distanceNourriture =
        std::numeric_limits<double>::max();

    double distanceAbri =
        std::numeric_limits<double>::max();


    // ---------------------------------------------------------
    // Recherche du POI le plus proche pour chaque type
    // ---------------------------------------------------------

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            POI* p = poi[i][j];

            if (p == nullptr)
                continue;


            // Distance torique
            int dx = i - x;
            int dy = j - y;

            int distanceX = std::abs(dx);
            int distanceY = std::abs(dy);

            distanceX = std::min(distanceX, N - distanceX);
            distanceY = std::min(distanceY, N - distanceY);

            double distance =
                std::sqrt(
                    distanceX * distanceX +
                    distanceY * distanceY
                );


            // Le POI est sur la case de la proie
            if (distance == 0.0)
                continue;


            // Garder uniquement le plus proche de chaque type
            switch (p->getType())
            {
            case POIType::Eau:

                if (distance < distanceEau)
                {
                    distanceEau = distance;
                    poiEau = p;
                }

                break;


            case POIType::Nourriture:

                if (distance < distanceNourriture)
                {
                    distanceNourriture = distance;
                    poiNourriture = p;
                }

                break;


            case POIType::Abri:

                if (distance < distanceAbri)
                {
                    distanceAbri = distance;
                    poiAbri = p;
                }

                break;
            }
        }
    }


    // ---------------------------------------------------------
    // Fonction qui applique l'influence d'un POI
    // ---------------------------------------------------------

    auto appliquerInfluence =
        [&](POI* p, double distance)
        {
            if (p == nullptr)
                return;


            // -----------------------------------------------------
            // Statistique associée au type du POI
            //
            // Eau         -> soif
            // Nourriture  -> faim
            // Abri        -> insécurité
            // -----------------------------------------------------

            double stat = getStat(p->getType());


            // -----------------------------------------------------
            // Influence du POI
            //
            // Une stat faible = besoin important
            //
            // influence =
            // poids POI * (10 - stat / 10) / distance
            // -----------------------------------------------------

            double influence =
                p->getWeight()
                * (10.0 - stat / 10.0)
                / distance;


            // -----------------------------------------------------
            // On retrouve la position du POI
            // -----------------------------------------------------

            int px = -1;
            int py = -1;

            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    if (poi[i][j] == p)
                    {
                        px = i;
                        py = j;
                        break;
                    }
                }

                if (px != -1)
                    break;
            }


            if (px == -1)
                return;


            // -----------------------------------------------------
            // Distance X/Y vers le POI
            // -----------------------------------------------------

            int dx = px - x;
            int dy = py - y;

            int distanceX = std::abs(dx);
            int distanceY = std::abs(dy);

            distanceX = std::min(distanceX, N - distanceX);
            distanceY = std::min(distanceY, N - distanceY);


            // -----------------------------------------------------
            // Direction X sur la map torique
            // -----------------------------------------------------

            int directionX = 0;

            if (distanceX != 0)
            {
                if (dx > 0)
                {
                    if (std::abs(dx) <= N / 2)
                        directionX = 1;
                    else
                        directionX = -1;
                }
                else
                {
                    if (std::abs(dx) <= N / 2)
                        directionX = -1;
                    else
                        directionX = 1;
                }
            }


            // -----------------------------------------------------
            // Direction Y sur la map torique
            // -----------------------------------------------------

            int directionY = 0;

            if (distanceY != 0)
            {
                if (dy > 0)
                {
                    if (std::abs(dy) <= N / 2)
                        directionY = 1;
                    else
                        directionY = -1;
                }
                else
                {
                    if (std::abs(dy) <= N / 2)
                        directionY = -1;
                    else
                        directionY = 1;
                }
            }


            // -----------------------------------------------------
            // Répartition de l'influence
            // -----------------------------------------------------

            if (distanceX > distanceY)
            {
                // Le POI est principalement à gauche/droite

                if (directionX > 0)
                    poidsDroite += influence;

                else if (directionX < 0)
                    poidsGauche += influence;
            }
            else if (distanceY > distanceX)
            {
                // Le POI est principalement en haut/bas

                if (directionY > 0)
                    poidsBas += influence;

                else if (directionY < 0)
                    poidsHaut += influence;
            }
            else
            {
                // Même distance sur X et Y :
                // on partage l'influence entre les deux directions.

                double demiInfluence =
                    influence / 2.0;


                if (directionX > 0)
                    poidsDroite += demiInfluence;

                else if (directionX < 0)
                    poidsGauche += demiInfluence;


                if (directionY > 0)
                    poidsBas += demiInfluence;

                else if (directionY < 0)
                    poidsHaut += demiInfluence;
            }
        };


    // ---------------------------------------------------------
    // On applique UNIQUEMENT les 3 POI sélectionnés
    // ---------------------------------------------------------

    appliquerInfluence(poiEau, distanceEau);
    appliquerInfluence(poiNourriture, distanceNourriture);
    appliquerInfluence(poiAbri, distanceAbri);


    // ---------------------------------------------------------
    // Tirage aléatoire pondéré
    // ---------------------------------------------------------

    double total =
        poidsHaut +
        poidsBas +
        poidsGauche +
        poidsDroite;


    if (total <= 0.0)
        return;


    double tirage =
        QRandomGenerator::global()->generateDouble()
        * total;


    if (tirage < poidsHaut)
    {
        --y;
    }
    else if (tirage < poidsHaut + poidsBas)
    {
        ++y;
    }
    else if (tirage <
        poidsHaut + poidsBas + poidsGauche)
    {
        --x;
    }
    else
    {
        ++x;
    }


    // ---------------------------------------------------------
    // Map torique
    // ---------------------------------------------------------

    x = (x + N) % N;
    y = (y + N) % N;
}



double Proie::getStat(POIType type) {
    switch (type)
    {
    case POIType::Eau:
        return soif;
    case POIType::Nourriture:
        return faim;
    case POIType::Abri:
        return insécurité;
    default:
        return -1;
    }
}
