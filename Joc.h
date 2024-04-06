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
	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);
private:
	Tauler m_tauler;
	Figura m_figura;
};