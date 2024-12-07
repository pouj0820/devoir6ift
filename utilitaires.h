#ifndef _UTILITAIRES_H_
#define _UTILITAIRES_H_

#ifndef _XCODE_
    #define _CONSOLE_COLOR_ // mettre en commentaire au besoin
#endif

#include <cstdlib>
#include <iostream>

#if defined(_WIN32)
    #include <Windows.h>
    #ifdef max
        #undef max
    #endif
#else
    #include <string>
#endif

using namespace std;

// Constantes
const unsigned char CMINE = 'X';

// Caractere pour afficher une case fermee (NE PAS MODIFIER)
#if defined(_WIN32)
    const unsigned char CFERME = 0xFE; //=254
#else
    #include <string>
    const std::string CFERME = "\u2580";//"\u25A0";
#endif

enum class Color
{
    BleuFonce = 1,
    VertFonce = 2,
    CyanFonce = 3,
    RougeFonce = 4,
    MagentaFonce = 5,
    JauneFonce = 6,
    BlancFonce = 7,
    Gris = 8,
    Bleu = 9,
    Vert = 10,
    Cyan = 11,
    Rouge = 12,
    Magenta = 13,
    Jaune = 14,
    Blanc = 15,
    Defaut = 16,
};

class Console
{
public:
    //  description Change la couleur d'affichage a l'ecran
    //  note : Cette fonction contient du code specifique au systeme d'exploitation utilise
    //  param[E] c : couleur a utiliser

    static void setConsoleColor(Color c)
    {
        #if defined(_CONSOLE_COLOR_)
            #if defined(_WIN32)
                if (c == Color::Defaut)
                {
                    c = Color::BlancFonce;
                }
                
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, (int) c);
            
            #else
                std::string color = "\033[0m";
                switch (c)
                {
                    case Color::BleuFonce:
                        color = "\033[2;34m";
                        break;
                    case Color::VertFonce:
                        color = "\033[2;32m";
                        break;
                    case Color::CyanFonce:
                        color = "\033[2;36m";
                        break;
                    case Color::RougeFonce:
                        color = "\033[2;31m";
                        break;
                    case Color::MagentaFonce:
                        color = "\033[2;35m";
                        break;
                    case Color::JauneFonce:
                        color = "\033[2;33m";
                        break;
                    case Color::BlancFonce:
                        color = "\033[2;37m";
                        break;
                    case Color::Gris:
                        color = "\033[2;37m";
                        break;
                    case Color::Bleu:
                        color = "\033[0;34m";
                        break;
                    case Color::Vert:
                        color = "\033[0;32m";
                        break;
                    case Color::Cyan:
                        color = "\033[0;36m";
                        break;
                    case Color::Rouge:
                        color = "\033[0;31m";
                        break;
                    case Color::Magenta:
                        color = "\033[0;35m";
                        break;
                    case Color::Jaune:
                        color = "\033[1;33m";
                        break;
                    case Color::Blanc:
                        color = "\033[0;37m";
                        break;

                default:
                    color = "\033[0m";
                    break;
            }

                cout << color;
        #endif //defined(_WIN32)
    #endif //defined(_CONSOLE_COLOR_)
    }

    // description Efface completement l'ecran
    // note : Cette fonction contient du code specifique au systeme d'exploitation utilise

    static void clearScreen()
    {

        #if defined(_CONSOLE_COLOR_)
            #if defined(_WIN32)
                std::system("cls");
            #else // Assume POSIX
                std::system("clear");
            #endif
        #endif
        }
    };


#endif
