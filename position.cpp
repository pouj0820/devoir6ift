#include "position.h"
#include <iostream>
using namespace std;
#include <cassert>
#include <string>

Position::Position() {}
Position::Position(int x, int y) {
    plig = x;
    pcol = y;
};

int Position::ligne() {
    return plig;
}

int Position::colonne() {
    return pcol;
};

// description : fonction utilitaire qui permet de lire et valider si c'est bien un entier qui est lu
// param[ES] : flux d'entree sur lequel on lit l'entier
// param[S] : entier lu
// pre : le flux est existant et ouvert (diff. de NULL)
// post : lit une valeur dans le flux jusqu'à ce qu'elle soit un entier


void lireValiderEntier(istream& es_entree, int& s_entier)
{
    assert(es_entree);

    while (!(es_entree >> s_entier))
    {
        // Afficher un message d'erreur et redemander le numero de ligne
        cout << "Erreur! Vous devez entrer une nombre entier! " << endl << "Entrez la ligne : ";
        // Vider le tampon de lecture
        es_entree.clear();
        // Ignorer tous les caracteres deja entres
        es_entree.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    assert(es_entree);
}


istream& operator>>(istream& is, Position& pos) {
    cout << "Entrez la ligne (-1 pour quitter) : ";
    lireValiderEntier(is, pos.plig);
    cout << "Entrez la colonne : ";
    lireValiderEntier(is, pos.pcol);
    return is;
}

ostream& operator<<(ostream& os, const Position& pos) {
    os  << "(" << pos.plig << "," << pos.pcol << ")";
    return os;
}



