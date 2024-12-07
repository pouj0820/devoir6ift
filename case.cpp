// fichier : case.cpp
// auteur.e : Marie-Flavie Auclair-Fortier
// date : 2020
// description : Ce fichier contient la definition des methodes de la classe Case d'un jeu de demineur


#include "case.h"

#include <cassert>

// **************************************************************
// Definition des methodes de la classe Case
// **************************************************************

// description : constructeur qui met assigne une mine ou non dans la case
// post : initialise le nombre de mines adjacentes a 0

Case::Case(Contenu e_mine)
// liste d'initialisation des membres
: m_contenu{e_mine}
, m_nbMinesAdj{0}
, m_statut {Statut::FERMEE}
{};

// description : constructeur par defaut
// post : initialise la case a vide (pas de mine) et le nombre de mines adjacentes a 0

Case::Case()
// delegation de constructeur
: Case {Contenu::RIEN}
{};

// description : accesseur de la mine
// retour : booleen - statut de mine de la case

bool Case::estUneMine() const
{
    return m_contenu == Contenu::MINE;
}

// description : met une mine dans la case
// pre : le nb de mines adjacentes doit etre a 0
// pre : le statut doit etre a FERMEE
// post : le nb de mines adjacentes demeure a 0
// post : le contenu contient une mine
// post : le statut ne change pas
void Case::metUneMine()
{
    assert(m_nbMinesAdj==0);
    assert(m_statut==Statut::FERMEE);
    m_contenu = Contenu::MINE;
};

// description : accesseur du nombre de mines adjacentes
// retour : Compteur - nombre de mines adjacentes

Compteur Case::nbMinesAdj()
{
    return m_nbMinesAdj;
};

// description : verifie si la case a deja ete ouverte
// retour : booleen
// post : vrai le statut de la case est a OUVERTE
// post : faux le statut de la case est a FERMEE

bool Case::estOuverte() const
{
    return m_statut==Statut::OUVERTE;
}

// description : ouvre une case
// post : le statut de la case est a OUVERTE

void Case::ouvre()
{
    m_statut=Statut::OUVERTE;
};

// description : pre increment (++case) pour le nombre de mines adjacentes
// retour : Compteur - nombre de mines adjacentes mis a jour
// post : incremente de un le nombre de mines adjacentes

Compteur Case::operator++()
{
    return ++m_nbMinesAdj;
};


