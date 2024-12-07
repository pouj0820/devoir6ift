// fichier : carte_.cpp
// auteur.es : METTEZ VOS NOMS ICI
// date : 2020
// modifications :
// description : Ce fichier contient la definition des methodes A IMPLEMENTER de la classe Carte d'un jeu de demineur

#include "carte.h"
#include "utilitaires.h"

#include <iomanip>
#include <cassert>
#include <stdio.h>

// Description: Methode qui calcule le nombre de mines adjacentes a une case
// param[E] Position de la case
// retour : nombre de mines adjacentes a la case
// post : on compte le nombre de mines adjacentes a la case (entre 0 et 8)

Compteur Carte::getNbMinesAdjacentes(Position e_pos)
{
    Compteur minesAdjacentes = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            Position adj(e_pos.ligne() + dx, e_pos.colonne() + dy);

            if (estDansCarte(adj) && getCase(adj).estUneMine()) {
                minesAdjacentes ++;
            }

        }
    }
    
    return minesAdjacentes;
}

// Description: Methode qui essaie d'ouvrir une case
// param[E] Position de la case
// retour : booleen - vrai si ce n'est pas une mine, faux sinon
// post : si la case a deja ete ouverte, ce n'est pas une mine -> retourne vrai, si la case n'est pas une mine, les cases voisines doivent etre ouvertes jusqu'a une prochaine mine

bool Carte::essaieCase(Position e_pos)
{
    if (m_cases[e_pos.ligne()][e_pos.colonne()].estOuverte() == true) {
        return true;
    }
    
    m_cases[e_pos.ligne()][e_pos.colonne()].ouvre();
    if (m_cases[e_pos.ligne()][e_pos.colonne()].estUneMine() == true) {
        return false;
    }

    if (m_cases[e_pos.ligne()][e_pos.colonne()].nbMinesAdj() == 0) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {

                Position adj(e_pos.ligne() + dx, e_pos.colonne() + dy);

                if (estDansCarte(adj) == false) { continue; }
                
                essaieCase(adj);

            }
        }
    }

    return true;
};

// Description: Methode qui calcule le nombre de mines adjacentes pour les cases libres de la carte
// post : pour chacune des cases qui ne contient pas une mine, on compte le nombre de mines adjacentes

void Carte::compteMinesAdjParCase()
{ 
    for (int i = 0; i < nbLignes(); i++) {
        for (int j = 0; j < nbColonnes(); j++) {
            Position pos(i, j);

            if (!getCase(pos).estUneMine()) {

                Compteur adj = getNbMinesAdjacentes(pos);

                for (Compteur count = 0; count < adj; ++count) {
                    ++m_cases[i][j]; // Utilise l'opérateur de pré-incrémentation
                }

            }


        }

    }
}
