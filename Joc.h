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
	void setFigura(const Figura figura) { m_figura = figura; };
	void setTauler(const Tauler tauler) { m_tauler = tauler; };

	//Funcions
	void inicialitza(const string& nomFitxer);
	bool giraFigura(const DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);

private:
	Tauler m_tauler;
	Figura m_figura;
};

#endif