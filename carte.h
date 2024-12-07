/*
* fichier : carte.h
* auteur.e : Vincent Ducharme
* date : 2016
* modifications :
* 03/2018 Marie-Flavie Auclair-Fortier : refactoring du code
* 11/2019 Marie-Flavie Auclair-Fortier : refactoring du code
* 11/2020 Marie-Flavie Auclair-Fortier : refactoring du code
* description : Ce fichier contient la definition de la classe representant la carte d'un jeu de demineur
*/

#ifndef _CARTE_H_
#define _CARTE_H_

#include "position.h"
#include "case.h"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Carte
{
    vector<vector<Case> >    m_cases;         // tableau des mines
    Compteur                 m_nbMines;        // nb total de mines

    // Description: Methode utilitaire qui calcule le nombre de mines adjacentes pour les cases libres de la carte
    // post : pour chacune des cases qui ne contient pas une mine, on compte le nombre de mines adjacentes

    void compteMinesAdjParCase();
    
    // Description: Methode qui calcule le nombre de mines adjacentes a une case
    // param[E] Position de la case
    // retour : nombre de mines adjacentes a la case
    // post : on compte le nombre de mines adjacentes a la case (entre 0 et 8)
    
    //****** changer le nom et enlever le retour

    Compteur getNbMinesAdjacentes(Position);
    
public:

    // Description: Constructeur de la carte a partir d'un fichier
    // param[E/S] : fichier a lire
    // pre : le flux doit etre deja ouvert et valide
    // post : les mines sont placees, les mines adjacentes par case sont comptees et toutes les cases sont fermees

    Carte(ifstream&);

    // Description: Methode qui lit le contenu d'une case de la carte
    // param[E] Position de la case
    // retour : contenu de la case
    // post : Si la case est en dehors de la grille, retourne une case libre

    Case getCase(Position) const;
    
    // Description: Methode qui retourne le nombre de lignes de la carte
    // retour : entier

    int nbLignes() const;
    
    // Description: Methode qui retourne le nombre de colonnes de la carte
    // pre : il doit y avoir au moins une ligne de creee
    // retour : entier

    int nbColonnes() const;
    
    // Description: Methode qui vérifie si la coordonnée est dans la carte
    // param[E] Position a verifier
    // retour : booleen
    // post : vrai si la coordonnee est a l'interieur des bornes de la carte, faux sinon

    bool estDansCarte(Position) const;
    
    // Description: Methode qui essaie d'ouvrir une case
    // param[E] Position de la case
    // retour : booleen - vrai si ce n'est pas une mine, faux sinon
    // post : si la case a deja ete ouverte, ce n'est pas une mine -> retourne vrai, si la case n'est pas une mine, les cases voisines doivent etre ouvertes jusqu'a une prochaine mine

    bool essaieCase(Position);
       
    // Description: Methode qui ouvre une case de la carte
    // param[E] : Position de la case
    // post : si la case est dans la grille, on assigne une valeur vrai a la grille de cases ouvertes, sinon, on ne fait rien

    void ouvreCase(Position);
    
    // Description: Methode qui indique si une case a deja ete ouverte
    // param[E] Position de la case
    // retour : booleen - vrai si la case est ouverte, faux autrement
    // post : Si la coordonnee est en dehors de la grille, c'est faux

    bool caseEstOuverte(Position) const;
    
    // Description: Methode qui verifie si la partie est terminee
    // retour : booleen
    // post : vrai si les seules cases restantes a ouvrir sont les mines, faux sinon

    bool partieEstTerminee() const;
    
};

// Description: Operateur d'affichage sur un flux
// param[E/S] : flux de sortie
// param[S] : Carte : etat du jeu
// retour : flux sur lequel on a fait l'affichage
// post : les cases sont soit
//    fermees,
//    avec rien d'affiche, si ouverte et pas de mines adjacentes
//    un nombre, si ouverte avec des mines adjacentes
//    X pour une mine qui vient d'etre decouverte

ostream& operator<<(ostream&, const Carte&);

#endif
