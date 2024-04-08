#include "Joc.h"


TipusFigura IntATipus(int figura)
{
	switch (figura)
	{
	case 0:
		return NO_FIGURA;
	case 1:
		return FIGURA_O;
	case 2:
		return FIGURA_I;
	case 3:
		return FIGURA_T;
	case 4:
		return FIGURA_L;
	case 5:
		return FIGURA_J;
	case 6:
		return FIGURA_Z;
	case 7:
		return FIGURA_S;
	default:
		return NO_FIGURA;
	}
}

ColorFigura IntAColor(int figura)
{
	switch (figura)
	{
	case 0:
		return COLOR_NEGRE;
	case 1:
		return COLOR_GROC;
	case 2:
		return COLOR_BLAUCEL;
	case 3:
		return COLOR_MAGENTA;
	case 4:
		return COLOR_TARONJA;
	case 5:
		return COLOR_BLAUFOSC;
	case 6:
		return COLOR_VERMELL;
	case 7:
		return COLOR_VERD;
	default:
		return COLOR_NEGRE;
	}
}

void Joc::inicialitza(const string& nomFitxer)
{
    ifstream inFitxer;
    inFitxer.open(nomFitxer);

    if (inFitxer.is_open())
    {
        inFitxer >> m_tauler;
        m_figura = m_tauler.getFigura();
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
        outFitxer << m_tauler;
    }
}

void mostrarTauler(Tauler tauler)
{
    ColorFigura nouTauler[MAX_FILA][MAX_COL];
    tauler.getTaulerActual(nouTauler);

    for (int f = 0; f < MAX_FILA; f++)
    {
        for (int c = 0; c < MAX_COL; c++)
        {
            cout << nouTauler[f][c];
        }
        cout << endl;
    }
}

int main()
{
    string nomFitxer = "./tests/test_baixa_figura.txt";
    Joc joc;
    joc.inicialitza(nomFitxer);
    //mostrarTauler(joc.getTauler());



    joc.escriuTauler("./tests/aaa.txt");
    return 0;
}