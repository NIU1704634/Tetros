#ifndef TAULER_H
#define TAULER_H

#include "Figura.h"


const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
	//Constructors
	Tauler();
	Tauler(ColorFigura tauler[MAX_FILA][MAX_COL]);

	//Getters
	void getTaulerActual(ColorFigura tauler[MAX_FILA][MAX_COL]);

	//Funcions
	int EliminarFila();
	bool ComprobarGir(Figura figura, DireccioGir direccio) const; //const
	bool ComprobarBaixada(Figura figura) const; //const
	bool ComprobarMoviment(Figura figura, int dirX) const; //const
	void AfegirFigura(Figura figura);
	
	void setFigura(Figura figura) {m_figuraActual = figura;}
	Figura getFigura() { return m_figuraActual; }


private:
	bool ComprobarEspai(Figura figura) const; //const
	ColorFigura m_tauler[MAX_FILA][MAX_COL];
	Figura m_figuraActual;
};

#endif