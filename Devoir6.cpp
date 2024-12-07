//
// fichier : main.cpp
// auteur.e : Vincent Ducharme
// date : 2016
// modifications :
// 03/2018 Marie-Flavie Auclair-Fortier : refactoring du code
// 11/2019 Marie-Flavie Auclair-Fortier : refactoring du code
// description : Ce fichier contient un jeu de Demineur
//

#include "carte.h"
#include "utilitaires.h"
#include "position.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Description: Programme principal pour le jeu Demineur

int main()
{
    void jouer(ifstream&);

    // Declaration des variables locales
    string nomFichierCarte;

    ifstream fichierTest;   // flux d'entree de type fichier

    // workaround pour avoir une entree redirigee dans le fichier de test
    fichierTest.open("test1");  // ouvre le fichier

    // redirige le flux standard vers le fichier, le cin pourra etre utilise normalement
    // ****** a mettre en commentaires cette ligne pour remettre le fonctionnement a normal
    //cin.rdbuf(fichierTest.rdbuf());

    // Lire le nom du fichier contenant la carte de jeu
//    nomFichierCarte = "carte1";
    cout << "Entrez le nom du fichier contenant la carte : ";
    cin >> nomFichierCarte;

    cout << endl;

    // Ouvrir le fichier
    ifstream fichierCarte(nomFichierCarte);

    // Tant que le nom du fichier est different de "quitter" et que le fichier demande n'a pas pu etre ouvert
    while (nomFichierCarte != "quitter" && !fichierCarte.is_open())
    {
        cout << "Fichier introuvable!" << endl << "Entrez le nom du fichier contenant la carte : ";
        cin >> nomFichierCarte;

        // Tenter d'ouvrir a nouveau le fichier
        fichierCarte.open(nomFichierCarte);
    }

    // Si le fichier a bien ete ouvert
    if (fichierCarte.is_open())
    {
        jouer(fichierCarte);
    }

    return 0;
}

void jouer(std::ifstream& es_fichierCarte)
{
    // signature de fonction locale
    bool jouerUnTour(Carte&);

    // Creer la carte a partir du fichier
    Carte carte{ es_fichierCarte };

    // Afficher la carte
    cout << carte;

    // Tant qu'on ne veut pas quitter
    while (jouerUnTour(carte))
    {
    };
}

// Description: Un tour du jeu
// param[E/S] : Carte
// retour : booleen
// post : retourne faux si la partie et terminee
// post : retourne vrai si la partie continue

bool jouerUnTour(Carte& es_carte)
{
    Position position;

    // Lecture de la position a essayer
    cin >> position;

    // Si la ligne entree est -1, le jeu est termine
    if (position.ligne() == -1)
        return false;

    if (!es_carte.estDansCarte(position))
    {
        cerr << "La position " << position << " n'est pas une case dans la carte, veuillez recommencer" << endl;
        return true;
    }

    // Effacer tout l'ecran
    Console::clearScreen();

    bool codeRetour{ true };

    // Essaie la case demandee si on trouve une mine
    if (!es_carte.essaieCase(position))
    {
        // Affiche un message d'erreur et indique de quitter le jeu
        cout << "Vous avez touche une mine!!!" << endl;
        codeRetour = false;
    }
    // Sinon, verifier si on vient de terminer la partie
    else if (es_carte.partieEstTerminee())
    {
        // Affiche un message de felicitation et indique de quitter le jeu
        cout << "Vous avez gagne!" << endl;
        codeRetour = false;
    }

    // Affiche la carte
    cout << endl << es_carte;

    return codeRetour;
}
