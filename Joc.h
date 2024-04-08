#ifndef JOC_H
#define JOC_H

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
	Figura getFigura() const { return m_figura; };
	Tauler getTauler() const { return m_tauler; };
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



ifstream& operator>>(ifstream& input, Tauler& tauler)
{
	//leer archivo

	//crear figura
	int tipus;
	int posX = 0;
	int posY = 0;
	int rotacio = 0;
	input >> tipus >> posY >> posX >> rotacio;
	TipusFigura formaFigura = IntATipus(tipus);
	Figura novaFigura(formaFigura, posX, posY, rotacio);
	tauler.setFigura(novaFigura);

	//crear taula
	ColorFigura taulerTemporal[MAX_FILA][MAX_COL];
	int color;
	for (int f = 0; f < MAX_FILA; f++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			input >> color;

			taulerTemporal[f][c] = IntAColor(color);
		}
	}

	Tauler nouTauler(taulerTemporal);	
	tauler = nouTauler;

	tauler.AfegirFigura(novaFigura);

	return input;
}


ofstream& operator<<(ofstream& output, Tauler taula)
{
	//escribir en archivo
	Tauler taulerTemporal = taula;
	taulerTemporal.AfegirFigura(taula.getFigura());

	ColorFigura nouTauler[MAX_FILA][MAX_COL];
	taulerTemporal.getTaulerActual(nouTauler);

	for (int f = 0; f < MAX_FILA; f++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			output << nouTauler[f][c] << " ";
		}
		output << endl;
	}

	return output;
}


#endif