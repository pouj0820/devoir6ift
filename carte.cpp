// fichier : carte.cpp
// auteur.e : Vincent Ducharme
// date : 2016
// modifications :
// 03/2018 Marie-Flavie Auclair-Fortier : refactoring du code
// 11/2019 Marie-Flavie Auclair-Fortier : refactoring du code
// 03/2020 Marie-Flavie Auclair-Fortier : refactoring du code
// 11/2020 Marie-Flavie Auclair-Fortier : refactoring du code
// description : Ce fichier contient la definition des methodes de la classe Carte d'un jeu de demineur

#include "carte.h"
#include "utilitaires.h"

#include <iomanip>
#include <cassert>

// **************************************************************
// Definition des methodes de la classe Carte
// **************************************************************

// Description: Constructeur de la carte a partir d'un fichier
// param[E/S] : fichier a lire
// pre : le flux doit etre deja ouvert et valide
// post : les mines sont placees, les mines adjacentes par case sont comptees et toutes les cases sont fermees

Carte::Carte(ifstream& es_fichier)
: m_nbMines {0}               // nb de mines initiales
{
    assert(es_fichier);
    
    // Lire le nombre de colonnes de la carte
    int col;
    es_fichier >> col;
    
    // Lire le nombre de lignes de la carte
    int lig;
    es_fichier >> lig;
       
    // assigne le bon nombre de cases (toutes libres)
    m_cases.assign(lig, vector<Case> (col, Case {} ));
   
    // Pour toutes les lignes de la carte
    for (int i = 0; i < lig; ++i)
    {
        // Pour toutes les colonnes de la carte
        for (int j = 0; j < col; ++j)
        {
            // Lire la valeur de la carte
            char c;
            es_fichier >> c;
            // Si c'est 1, ajouter une mine dans la carte
            if (c-'0' != 0)
            {
                // on met une mine dans la case
                m_cases[i][j].metUneMine();
                
                // Incrementer le nombre de mine dans la carte
                m_nbMines++;
            }
        }
    }

    // Calculer les cases contenant des nombres (mines adjacentes)
    compteMinesAdjParCase();
}

// Description: Methode qui lit le contenu d'une case de la carte
// param[E] Position de la case
// retour : contenu de la case
// post : Si la case est en dehors de la grille, retourne une case libre

Case Carte::getCase(Position e_pos) const
{
    // Si la position est en dehors de la grille
    if (estDansCarte(e_pos))
    {
        // Retourne la valeur de la case demandee
        return m_cases[e_pos.ligne()][e_pos.colonne()];
    }

    // 2. Sinon retourne une case libre, evite de gerer les bords
    return Case {};
}

// Description: Methode qui indique si une case a deja ete ouverte
// param[E] Position de la case
// retour : booleen - vrai si la case est ouverte, faux autrement
// post : Si la coordonnee est en dehors de la grille, c'est faux

bool Carte::caseEstOuverte(Position e_pos) const
{
    // Si la case est en dehors dans la grille
    if (estDansCarte(e_pos))
    {
        // Retourne l'indicateur d'ouverture de la case
        return m_cases[e_pos.ligne()][e_pos.colonne()].estOuverte();
    }
    
    // Sinon retourne faux
    return false;
}

// Description: Methode qui ouvre une case de la carte
// param[E] : Position de la case
// post : si la case est dans la grille, on assigne une valeur vrai a la grille de cases ouvertes, sinon, on ne fait rien

void Carte::ouvreCase(Position e_pos)
{
    // Si la case est dans la grille
    if (estDansCarte(e_pos))
    {
        // Indique que la case est ouverte
        m_cases[e_pos.ligne()][e_pos.colonne()].ouvre();
    }
}

// Description: Methode qui retourne le nombre de lignes de la carte
// retour : entier

int Carte::nbLignes() const
{
    return (int) m_cases.size();
}

// Description: Methode qui retourne le nombre de colonnes de la carte
// pre : il doit y avoir au moins une ligne de creee
// retour : entier

int Carte::nbColonnes() const
{
    // validation de la precondition
    assert(m_cases.size()>0);
    
    return (int) m_cases[0].size();
}

// Description: Methode qui vérifie si la coordonnée est dans la carte
// param[E] Position a verifier
// retour : booleen
// post : vrai si la coordonnee est a l'interieur des bornes de la carte, faux sinon

bool Carte::estDansCarte(Position e_position) const
{
    return (e_position.ligne() >= 0 && e_position.ligne() < nbLignes() && e_position.colonne() >= 0 && e_position.colonne() < nbColonnes());
};

// Description: Methode qui verifie si la partie est terminee
// retour : booleen
// post : vrai si les seules cases restantes a ouvrir sont les mines, faux sinon

bool Carte::partieEstTerminee() const
{
    Compteur nbFermes = 0;
    
    // Pour toutes les positions
    for (int lig = 0; lig < nbLignes(); ++lig)
    {
        for (int col = 0; col < nbColonnes(); ++col)
        {
            // Si la case n'est pas ouverte
            if (!caseEstOuverte(Position {lig, col}))
            {
                // Incremente le nombre de cases fermees
                nbFermes++;
            }
        }
    }

    // 2. Retourne vrai si le nombre de cases fermees est egal au nombre de mines
    return (nbFermes == m_nbMines);
}

// Description: Operateur d'affichage sur un flux
// param[E/S] : flux de sortie
// param[S] : Carte : etat du jeu
// retour : flux sur lequel on a fait l'affichage
// post : les cases sont soit
//    fermees,
//    avec rien d'affiche, si ouverte et pas de mines adjacentes
//    un nombre, si ouverte avec des mines adjacentes
//    X pour une mine qui vient d'etre decouverte

ostream& operator<<(ostream& es_sortie, const Carte& e_carte)
{
    void afficheEntete(const Carte &, std::ostream &);
    void afficheCases(int i, const Carte &, std::ostream &);
    
    // Permet d'aligner a gauche ()
    es_sortie.setf (ios_base::left, ios::adjustfield);
    
    // Indique a la console d'ecrire en blanc
    Console::setConsoleColor(Color::Defaut);

    // Afficher la ligne indicative des colonnes
    afficheEntete(e_carte, es_sortie);

    // Pour toutes les lignes de la carte
    for (int noLigne = 0; noLigne < e_carte.nbLignes(); ++noLigne)
    {
        // Afficher le numero de la ligne et la ligne de separation
        es_sortie.setf (ios_base::right, ios::adjustfield);
        es_sortie << setw(2);
        es_sortie << noLigne << " | ";
        es_sortie.setf (ios_base::left, ios::adjustfield);

        // Afficher les cases internes
        afficheCases(noLigne, e_carte, es_sortie);
        
        // Afficher la ligne verticale de fin de carte, suivi d'un saut de ligne
        es_sortie << "|" << endl;
    }

    // Pour toutes la largeur de la carte, afficher la ligne horizontale de fin de carte
    for (int noColonne = 0; noColonne < e_carte.nbColonnes() + 2; ++noColonne)
    {
        es_sortie << "---";
    }

    // Faire un saut de ligne
    es_sortie << endl;

    // Retourner le flux d'ecriture
    return es_sortie;
}

void afficheEntete(const Carte &e_carte, std::ostream &es_sortie)
{
    // Afficher l'espace du debut
    es_sortie << setw(5) << " ";
    
    // Pour toutes les colonnes
    for (int noColonne = 0; noColonne < e_carte.nbColonnes(); ++noColonne)
    {
        // Afficher le numero de la colonne
        es_sortie << setw(3);
        es_sortie << noColonne;
    }
    // Faire un saut de ligne
    es_sortie << endl;
    
    // Afficher la ligne de separation horizontale
    for (int noColonne = 0; noColonne < e_carte.nbColonnes() + 2; ++noColonne)
    {
        es_sortie << "---";
    }
    // Faire un saut de ligne
    es_sortie << endl;
}

void afficheCases(int e_noLigne, const Carte &e_carte, std::ostream &es_sortie)
{
    // module utilitaire
    void afficheNbMinesAdjacentes(Compteur, std::ostream&);
    
    // Pour toutes les colonnes de la ligne
    for (int noColonne = 0; noColonne < e_carte.nbColonnes(); ++noColonne)
    {
        // Si la case est ouverte
        if (e_carte.caseEstOuverte(Position {e_noLigne, noColonne}))
        {
            // Si la case est une mine, afficher le symbole de la mine
            if (e_carte.getCase(Position {e_noLigne, noColonne}).estUneMine())
            {
                es_sortie << setw(3);
                es_sortie << CMINE;
            }
            else
            {
                // on recupere le nombre de mines adjacentes
                Compteur nbMines = e_carte.getCase(Position {e_noLigne, noColonne}).nbMinesAdj();

                // si il y a des mines autour on affiche le nb de mines adjacentes
                if (nbMines != 0)
                {
                    afficheNbMinesAdjacentes(nbMines, es_sortie);
                }
                // Sinon, afficher une case vide
                else
                {
                    es_sortie << setw(3);
                    es_sortie << " ";
                }
            }
        }
        
        // Sinon, affiche une case fermee
        else
        {
            es_sortie << CFERME << "  ";
        }
    }
}

void afficheNbMinesAdjacentes(Compteur e_nbMines, std::ostream &es_sortie)
{
    unsigned int nbMines = e_nbMines;
    
    // choisir la couleur selon le nb de mines
    switch (nbMines)
    {
        case 1:  // En bleu pour une mine
            Console::setConsoleColor(Color::Bleu);
            break;
            
        case 2:  // En vert pour deux mines
            Console::setConsoleColor(Color::Vert);
            break;
            
        case 3:  // En rouge pour trois mines
            Console::setConsoleColor(Color::Rouge);
            break;
            
        case 4:  // En bleu fonce pour 4 mines
            Console::setConsoleColor(Color::BleuFonce);
            break;
            
        case 5:  // En magenta fonce pour 5 mines
            Console::setConsoleColor(Color::MagentaFonce);
            break;
            
        case 6:  // En rouge fonce pour 6 mines
            Console::setConsoleColor(Color::RougeFonce);
            break;
            
        case 7:  // En cyan fonce pour 7 mines
            Console::setConsoleColor(Color::CyanFonce);
            break;
            
        case 8:  // En jaune fonce pour 8 mines
            Console::setConsoleColor(Color::JauneFonce);
            break;
    }

    // Afficher le nombre de mines adjacentes sur 3 caracteres
    es_sortie << setw(3);
    es_sortie << nbMines;
    
    // Remettre la couleur a blanc
    Console::setConsoleColor(Color::Defaut);
}
