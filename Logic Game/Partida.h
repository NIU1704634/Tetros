#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "Joc.h"

using namespace std;

class NodeFigura
{
public:
    Figura getFigura() { return m_figura; }
    NodeFigura* getNext() { return m_seguentNode; }
    void setFigura(Figura figura) { m_figura = figura; }
    void setNext(NodeFigura* seguent) { m_seguentNode = seguent; }

private:
    Figura m_figura;
    NodeFigura* m_seguentNode;
};

class NodeMoviment
{
public:
    TipusMoviment getMoviment() { return m_moviment; }
    NodeMoviment* getNext() { return m_seguentNode; }
    void setMoviment(TipusMoviment mov) { m_moviment = mov; }
    void setNext(NodeMoviment* seguent) { m_seguentNode = seguent; }

private:
    TipusMoviment m_moviment;
    NodeMoviment* m_seguentNode;
};

class Partida 
{
public:
    Partida();
    
    void incrementaPuntuacio(int puntuacio);
    void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
    bool actualitza(double deltaTime, int& punts);

    Figura generarFiguraAleatoria();

    void test(double deltaTime);
    void ferMoviment(TipusMoviment mov);
    void normal(double deltaTime);

private:
    int m_filesEliminades, m_filesEliminadesPrev;
    bool m_posada, m_guardada, m_jocActiu, m_partidaAcabada;
    int m_mode;

    double m_temps;
    Joc m_joc;
    int m_nivell, m_puntuacio, m_puntsSN;
    NodeFigura* m_sequenciaFigures;
    NodeMoviment* m_sequenciaMoviments;
    int m_nFigures, m_nMoviments;

};
#endif 
