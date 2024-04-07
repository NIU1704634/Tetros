#include "Figura.h"


const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
	Tauler();
	Tauler(ColorFigura tauler[MAX_FILA][MAX_COL]);

	void EliminarFila(int fila);
	bool ComprobarGir(Figura figura, DireccioGir direccio) const; //const
	bool ComprobarBaixada(Figura figura) const; //const
	bool ComprobarMoviment(Figura figura, int dirX) const; //const
	void AfegirFigura(Figura figura);

private:
	bool ComprobarEspai(Figura figura) const; //const
	ColorFigura m_tauler[MAX_FILA][MAX_COL];
	Figura m_figuraActual;
};