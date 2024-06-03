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
	Figura getFiguraGuardada() const { return m_figuraGuardada; };
	//Setters
	void setFigura(const Figura figura) { m_figura = figura; };
	void setTauler(const Tauler tauler) { m_tauler = tauler; };

	//Funcions
	void inicialitza(const string& nomFitxer);
	bool giraFigura(const DireccioGir direccio);
	bool mouFigura(int dirX);
	bool baixaFigura(int& files);
	void escriuTauler(const string& nomFitxer);
	void DibuixarJoc();
	void generarNovaFigura(Figura f);
	void GuardarFigura();
	void DibuixarFiguraGuardada();

private:
	Tauler m_tauler;
	Figura m_figura;
	Figura m_figuraGuardada;
};

#endif