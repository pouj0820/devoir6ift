//
//  position.h
//

#ifndef POSITION_H
#define POSITION_H
#include <iostream>
using namespace std;

class Position {
private:
	int plig = 0;
	int pcol = 0;

public:
	Position();
	Position(int, int);

	int ligne();
	int colonne();

	void lireValiderEntier(istream&, int&);

	friend istream& operator>>(istream&, Position&);
	friend ostream& operator<<(ostream&, const Position&);

};




#endif /* Position_h */
