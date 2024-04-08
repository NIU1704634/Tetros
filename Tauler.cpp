#include "Tauler.h"
#include <iostream>

using namespace std;

int Tauler::EliminarFila()
{
	int filesEliminades = 0;
	int t = m_figuraActual.getTipus();

	for (int f = MAX_FILA - 1; f > 0; f--)
	{
		bool filaPlena = true;
		int c = 0;
		while (filaPlena && c < MAX_COL)
		{
			if (m_tauler[f][c] == COLOR_NEGRE)
			{
				filaPlena = false;
			}
			c++;
		}
		if (filaPlena)
		{

			for (int c2 = 0; c2 < MAX_COL; c2++)
			{
				for (int f2 = f; f2 > 0; f2--)
				{
					m_tauler[f2][c2] = m_tauler[f2 - 1][c2];
				}
				m_tauler[0][c2] = COLOR_NEGRE;
			}
			filesEliminades++;
			f++;
			m_fitxaColocada = true;
		}
	}
	return filesEliminades;
}

bool Tauler::ComprobarEspai()
{
	ColorFigura forma[MAXTAMANY][MAXTAMANY];
	m_figuraActual.getForma(forma);

	int figuraC = m_figuraActual.getPosX();
	int figuraF = m_figuraActual.getPosY();

	//bucle de tota la fitxa
	for (int fx = 0; fx < m_figuraActual.getTamany(); fx++)
	{
		for (int fy = 0; fy < m_figuraActual.getTamany(); fy++)
		{
			int taulerC = figuraC + fy;
			int taulerF = figuraF + fx;



			if (forma[fx][fy] != COLOR_NEGRE)
			{
				if (taulerC < 0 || taulerC >= MAX_COL || taulerF < 0 || taulerF >= MAX_FILA)
				{
					return false;
				}

				if (m_tauler[taulerF][taulerC] != COLOR_NEGRE)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Tauler::ComprobarGir(DireccioGir direccio)
{
	m_figuraActual.gir(direccio);

	bool movimentPosible = ComprobarEspai();

	if (!movimentPosible)
	{
		if (direccio == GIR_HORARI)
		{
			m_figuraActual.gir(GIR_ANTI_HORARI);
		}
		else
		{
			m_figuraActual.gir(GIR_HORARI);
		}
		return false;
	}
	else
	{
		return true;
	}

}

void Tauler::AfegirFigura()
{
	ColorFigura forma[MAXTAMANY][MAXTAMANY];
	m_figuraActual.getForma(forma);

	int figuraC = m_figuraActual.getPosX();
	int figuraF = m_figuraActual.getPosY();

	for (int ff = 0; ff < m_figuraActual.getTamany(); ff++)
	{
		for (int fc = 0; fc < m_figuraActual.getTamany(); fc++)
		{
			int taulerC = figuraC + ff;
			int taulerF = figuraF + fc;
			if (forma[fc][ff] != COLOR_NEGRE)
			{
				m_tauler[taulerF][taulerC] = forma[fc][ff];
			}
		}
	}
}

bool Tauler::ComprobarBaixada()
{
	int t = m_figuraActual.getTipus();


	m_figuraActual.baixa();

	bool movimentPosible = ComprobarEspai();
	if (!movimentPosible)
	{
		m_figuraActual.puja();
		return false;
	}
	else
	{
		return true;
	}
}

bool Tauler::ComprobarMoviment(int dirX)
{
	m_figuraActual.mou(dirX);

	bool movimentPosible = ComprobarEspai();



	if (!movimentPosible)
	{
		m_figuraActual.mou(-dirX);
		return false;
	}
	else
	{
 		return true;
	}
}

void Tauler::getTaulerActual(ColorFigura tauler[MAX_FILA][MAX_COL])
{
	//Dibuixa tauler
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			tauler[i][j] = m_tauler[i][j];
		}
	}
}

Tauler::Tauler()
{
	for (int f = 0; f < MAX_FILA; f++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			m_tauler[f][c] = COLOR_NEGRE;
		}
	}
}

Tauler::Tauler(ColorFigura tauler[MAX_FILA][MAX_COL])
{
	for (int f = 0; f < MAX_FILA; f++)
	{
		for (int c = 0; c < MAX_COL; c++)
		{
			m_tauler[f][c] = tauler[f][c];
		}
	}
}