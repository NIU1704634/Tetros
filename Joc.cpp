#include "Joc.h"

ifstream& operator>>(ifstream& input, Tauler& tauler)
{
	//leer archivo

	//crear figura
	int tipus;
	int posX = 0;
	int posY = 0;
	int rotacio = 0;
	input >> tipus >> posY >> posX >> rotacio;
	posY--;
	posX--;
	TipusFigura fTipus;
	switch (tipus)
	{
	case 0:
		fTipus = NO_FIGURA;
		break;
	case 1:
		fTipus = FIGURA_O;
		break;
	case 2:
		fTipus = FIGURA_I;
		break;
	case 3:
		fTipus = FIGURA_T;
		break;
	case 4:
		fTipus = FIGURA_L;
		break;
	case 5:
		fTipus = FIGURA_J;
		break;
	case 6:
		fTipus = FIGURA_Z;
		break;
	case 7:
		fTipus = FIGURA_S;
		break;
	default:
		fTipus = NO_FIGURA;
		break;
	}
	TipusFigura formaFigura = fTipus;
	Figura novaFigura(formaFigura, posX, posY, rotacio);
	
	//crear taula
	ColorFigura taulerTemporal[MAX_FILA][MAX_COL];
	int color;
	for (int f = 0; f < MAX_FILA; f++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			input >> color;
            ColorFigura fColor;
        	switch (color)
        	{
        	case 0:
        		fColor = COLOR_NEGRE;
        		break;
        	case 1:
        		fColor = COLOR_GROC;
        	    break;
        	case 2:
        		fColor = COLOR_BLAUCEL;
        	    break;
        	case 3:
        		fColor = COLOR_MAGENTA;
        	    break;
        	case 4:
        		fColor = COLOR_TARONJA;
        	    break;
        	case 5:
        		fColor = COLOR_BLAUFOSC;
        	    break;
        	case 6:
        		fColor = COLOR_VERMELL;
        	    break;
        	case 7:
        		fColor = COLOR_VERD;
        		break;
        	default:
        		fColor = COLOR_NEGRE;
        		break;
        	}
            
			taulerTemporal[f][c] = fColor;
		}
	}

	Tauler nouTauler(taulerTemporal);	
	tauler = nouTauler;
	tauler.setColocada(false);
	tauler.setFigura(novaFigura);


	return input;
}


ofstream& operator<<(ofstream& output, Tauler taula)
{
	//escribir en archivo
	Tauler taulerTemporal = taula;
	if (!taulerTemporal.getColocada())
	{
		taulerTemporal.AfegirFigura();
	}

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
    return m_tauler.ComprobarGir(direccio);
}
bool Joc::mouFigura(int dirX)
{


    return m_tauler.ComprobarMoviment(dirX);
}
int Joc::baixaFigura()
{
    if (m_tauler.ComprobarBaixada())
    {
		return 0;
    }
    else 
    {
		int t = m_tauler.getFigura().getTipus();

        m_tauler.AfegirFigura();
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
