#include "Joc.h"


void Joc::inicialitza(const string& nomFitxer)
{
    Joc joc;
    ifstream inFitxer;
    inFitxer.open(nomFitxer);

    if (inFitxer.is_open())
    {
        inFitxer >> joc;
        m_tauler = joc.getTauler();
        m_figura = joc.getFigura();
    }
}

bool Joc::giraFigura(DireccioGir direccio)
{
    return m_tauler.ComprobarGir(m_figura, direccio);
}
bool Joc::mouFigura(int dirX)
{
    return m_tauler.ComprobarMoviment(m_figura, dirX);
}
int Joc::baixaFigura()
{
    if (m_tauler.ComprobarBaixada(m_figura))
    {
        return 0;
    }
    else 
    {
        m_tauler.AfegirFigura(m_figura);
        int files = m_tauler.EliminarFila();
        return files;
    }
}
void Joc::escriuTauler(const string& nomFitxer)
{
    ofstream outFitxer;
    outFitxer.open(nomFitxer);
    if (outFitxer.is_open())
    {
        outFitxer << this;
    }
}