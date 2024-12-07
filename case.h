/*
* fichier : case.h
* auteur.e : Marie-Flavie Auclair-Fortier
* date : 2020
* modifications :
* description : Ce fichier contient la definition de la classe representant d'une case d'un jeu de demineur
*/

#ifndef CASE_H
#define CASE_H

#include <stdio.h>

// synonyme
using Compteur = unsigned char;

class Case
{
    enum class Contenu {MINE, RIEN};        // la case peut contenir seulement une mine ou rien
    enum class Statut {OUVERTE, FERMEE};    // une case est ouverte ou fermee

    Contenu        m_contenu;       // soit une mine, soit rien
    Compteur       m_nbMinesAdj;    // le nombre de mines autour de cette case
    Statut         m_statut;        // case ouverte ou fermee

    // description : constructeur qui met assigne une mine ou non dans la case
    // post : initialise le nombre de mines adjacentes a 0
    Case(Contenu i_mine);

public:
    
    // description : constructeur par defaut
    // post : initialise la case a vide (pas de mine)
    // post : le nombre de mines adjacentes a 0
    // post : le statut a ferme
    Case();
   
    // description : met une mine dans la case
    // pre : le nb de mines adjacentes doit etre a 0
    // pre : le statut doit etre a FERMEE
    // post : le nb de mines adjacentes demeure a 0
    // post : le contenu contient une mine
    // post : le statut ne change pas
    void metUneMine();

    // description : accesseur de la mine
    // retour : booleen - statut de mine de la case
    
    bool estUneMine() const;
        
    // description : accesseur du nombre de mines adjacentes
    // retour : Compteur - nombre de mines adjacentes

    Compteur nbMinesAdj();
    
    // description : verifie si la case a deja ete ouverte
    // retour : booleen
    // post : vrai le statut de la case est a OUVERTE
    // post : faux le statut de la case est a FERMEE
    bool estOuverte() const;

    // description : ouvre une case
    // post : le statut de la case est a OUVERTE
    void ouvre();
    
    // description : pre increment (++case) pour le nombre de mines adjacentes
    // retour : Compteur - nombre de mines adjacentes mis a jour
    // post : incremente de 1 le nombre de mines adjacentes
    Compteur operator++();

};

#endif /* CASE_H */
