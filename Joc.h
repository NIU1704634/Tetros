#pragma once
#include "Tauler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Joc
{
public:
	//Getters
	Figura getFigura() { return m_figura; };
	Tauler getTauler() { return m_tauler; };
	//Setters
	void setFigura(Figura figura) { m_figura = figura; };
	void setTauler(Tauler tauler) { m_tauler = tauler; };

	//Funcions
	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);
	
private:
	Tauler m_tauler;
	Figura m_figura;
};

istream& operator>>(istream& input, Joc joc)
{
	//Lectura i creació de la figura
	int tipusFig,figPosX, figPosY, figRot;
	input >> tipusFig >> figPosY >> figPosX >> figRot;
	Figura fig(static_cast<TipusFigura>(tipusFig), figPosX, figRot);
	//Lectura i creació del tauler
	ColorFigura punts[MAX_FILA][MAX_COL];
	int tempval;
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			input >> tempval;
			punts[i][j] = static_cast<ColorFigura>(tempval);
		}
	}
	Tauler tauler(punts);
	//Assignació de les variables de joc
	joc.setFigura(fig);
	joc.setTauler(tauler);
}

ostream& operator<<(ostream& output, Joc joc)
{
	Figura figura = joc.getFigura();
	ColorFigura colorFigura = figura.getColor(), tauler[MAX_FILA][MAX_COL], formaFigura[MAXTAMANY][MAXTAMANY];
	joc.getTauler().getTaulerActual(tauler);
	int tamanyFigura = figura.getTamany(), int figPosX = figura.getPosX(), int figPosY = figura.getPosY();
	figura.getForma(formaFigura);

	//Dibuixem la figura sobre el tauler
	for (int i = 0; i < tamanyFigura; i++)
	{
		for (int j = 0; j < tamanyFigura; j++)
		{
			if (formaFigura[i][j] != COLOR_NEGRE) {
				tauler[figPosX + i][figPosY + j] = colorFigura;
			}
		}
	}

	//Dibuixem el tauler
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			output << tauler[i][j] << " ";
		}
		output << endl;
	}
}
