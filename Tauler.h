#include "Figura.h"


const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
	Tauler();
	Tauler(ColorFigura tauler[MAX_FILA][MAX_COL]);

	void EliminarFila(int fila);
	bool ComprobarGir(Figura figura, DireccioGir direccio); //const
	bool ComprobarBaixada(Figura figura); //const
	bool ComprobarMoviment(Figura figura, int dirX); //const

private:
	bool ComprobarEspai(Figura figura); //const
	ColorFigura m_tauler[MAX_FILA][MAX_COL];
	Figura m_figuraActual;
};