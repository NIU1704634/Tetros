#include "Tauler.h"
#include <iostream>

using namespace std;

int Tauler::EliminarFila()
{
	int filesEliminades = 0;

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
			for (int c = 0; c < MAX_COL; c++)
			{
				for (int f2 = f; f2 > 0; f2--)
				{
					m_tauler[f2][c] = m_tauler[f2 - 1][c];
				}

			}
			filesEliminades++;
			f++;
		}
	}
	return filesEliminades;
}

bool Tauler::ComprobarEspai(Figura figura) const
{
	ColorFigura forma[MAXTAMANY][MAXTAMANY];
	figura.getForma(forma);

	int figuraX = figura.getPosX();
	int figuraY = figura.getPosY();

	//bucle de tota la fitxa
	for (int fx = 0; fx < figura.getTamany(); fx++)
	{
		for (int fy = 0; fy < figura.getTamany(); fy++)
		{
			int taulerX = figuraX + fx;
			int taulerY = figuraY - fy;

			if (taulerX < 0 || taulerX > MAX_COL || taulerY < 0 || taulerY > MAX_FILA)
			{
				return false;
			}

			if (forma[fx][fy] != COLOR_NEGRE)
			{
				if (m_tauler[taulerX][taulerY] != COLOR_NEGRE)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Tauler::ComprobarGir(Figura figura, DireccioGir direccio) const
{
	figura.gir(direccio);

	bool movimentPosible = ComprobarEspai(figura);

	if (movimentPosible)
	{
		if (direccio == GIR_HORARI)
		{
			figura.gir(GIR_ANTI_HORARI);
		}
		else
		{
			figura.gir(GIR_HORARI);
		}
		return false;
	}
	else
	{
		return true;
	}

}

void Tauler::AfegirFigura(Figura figura)
{
	ColorFigura forma[MAXTAMANY][MAXTAMANY];
	figura.getForma(forma);

	int figuraX = figura.getPosX();
	int figuraY = figura.getPosY();

	for (int fx = 0; fx < figura.getTamany(); fx++)
	{
		for (int fy = 0; fy < figura.getTamany(); fy++)
		{
			int taulerX = figuraX + fx;
			int taulerY = figuraY - fy;
			if (forma[fx][fy] != COLOR_NEGRE)
			{
				m_tauler[taulerX][taulerY] = forma[fx][fy];
			}
		}
	}
}

bool Tauler::ComprobarBaixada(Figura figura) const
{
	figura.baixa();

	bool movimentPosible = ComprobarEspai(figura);
	if (movimentPosible)
	{
		figura.puja();
		return false;
	}
	else
	{
		return true;
	}
}

bool Tauler::ComprobarMoviment(Figura figura, int dirX) const
{
	figura.mou(dirX);

	bool movimentPosible = ComprobarEspai(figura);

	if (movimentPosible)
	{
		figura.mou(-dirX);
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