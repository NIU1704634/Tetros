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
	bool ComprobarGir(DireccioGir direccio); //const
	bool ComprobarBaixada(); //const
	bool ComprobarMoviment(int dirX); //const
	void AfegirFigura();
	
	void setFigura(Figura figura) {m_figuraActual = figura;}
	Figura getFigura() { return m_figuraActual; }
	void setColocada(bool colocada) { m_fitxaColocada = colocada; }
	bool getColocada() { return m_fitxaColocada; }


private:
	bool m_fitxaColocada;
	bool ComprobarEspai(); //const
	ColorFigura m_tauler[MAX_FILA][MAX_COL];
	Figura m_figuraActual;
};

#endif