#ifndef TAULER_H
#define TAULER_H

#include "Figura.h"

class Tauler
{
public:
	//Constructors
	Tauler();
	Tauler(ColorFigura tauler[N_FILES_TAULER][N_COL_TAULER]);

	//Getters
	void getTaulerActual(ColorFigura tauler[N_FILES_TAULER][N_COL_TAULER]) const;

	//Funcions
	int EliminarFila();
	bool ComprobarGir(const DireccioGir direccio);
	bool ComprobarBaixada();
	bool ComprobarMoviment(int dirX);
	void AfegirFigura(); 
	
	void setFigura(const Figura figura) {m_figuraActual = figura;}
	Figura getFigura() const { return m_figuraActual; }
	void setColocada(bool colocada) { m_fitxaColocada = colocada; }
	bool getColocada() const { return m_fitxaColocada; }
	void DibuixarTauler();

private:
	bool m_fitxaColocada;
	bool ComprobarEspai();
	ColorFigura m_tauler[N_FILES_TAULER][N_COL_TAULER];
	Figura m_figuraActual;
};

#endif