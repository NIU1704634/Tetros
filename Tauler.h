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
	void getTaulerActual(ColorFigura tauler[MAX_FILA][MAX_COL]) const;

	//Funcions
	int EliminarFila();
	bool ComprobarGir(const DireccioGir direccio);
	bool ComprobarBaixada();
	bool ComprobarMoviment(int dirX);
	void AfegirFigura(); 
	
	void setFigura(const Figura figura) {m_figuraActual = figura;}
	Figura getFigura() { return m_figuraActual; } const
	void setColocada(bool colocada) { m_fitxaColocada = colocada; }
	bool getColocada() { return m_fitxaColocada; }


private:
	bool m_fitxaColocada;
	bool ComprobarEspai();
	ColorFigura m_tauler[MAX_FILA][MAX_COL];
	Figura m_figuraActual;
};

#endif