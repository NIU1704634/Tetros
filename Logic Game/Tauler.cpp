#include "Tauler.h"
#include <iostream>

using namespace std;

int Tauler::EliminarFila()
{
	int filesEliminades = 0;

	for (int f = N_FILES_TAULER - 1; f > 0; f--)
	{
		bool filaPlena = true;
		int c = 0;
		while (filaPlena && c < N_COL_TAULER)
		{
			if (m_tauler[f][c] == COLOR_NEGRE)
			{
				filaPlena = false;
			}
			c++;
		}
		if (filaPlena)
		{

			for (int c2 = 0; c2 < N_COL_TAULER; c2++)
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
				if (taulerC < 0 || taulerC >= N_COL_TAULER || taulerF < 0 || taulerF >= N_FILES_TAULER)
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
	if (movimentPosible)
	{
		return true;
	}
	else
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
	m_figuraActual.baixa();

	bool movimentPosible = ComprobarEspai();
	if (movimentPosible)
	{
		return true;
	}
	else
	{
		m_figuraActual.puja();
		return false;
	}
}

bool Tauler::ComprobarMoviment(int dirX)
{
	m_figuraActual.mou(dirX);

	bool movimentPosible = ComprobarEspai();
	if (movimentPosible)
	{
		return true;
	}
	else
	{
		m_figuraActual.mou(-dirX);
		return false;
	}
}

void Tauler::getTaulerActual(ColorFigura tauler[N_FILES_TAULER][N_COL_TAULER]) const
{
	//Dibuixa tauler
	for (int i = 0; i < N_FILES_TAULER; i++)
	{
		for (int j = 0; j < N_COL_TAULER; j++)
		{
			tauler[i][j] = m_tauler[i][j];
		}
	}
}

Tauler::Tauler()
{
	for (int f = 0; f < N_FILES_TAULER; f++)
	{
		for (int c = 0; c < N_COL_TAULER; c++)
		{
			m_tauler[f][c] = COLOR_NEGRE;
		}
	}
}

Tauler::Tauler(ColorFigura tauler[N_FILES_TAULER][N_COL_TAULER])
{
	for (int f = 0; f < N_FILES_TAULER; f++)
	{
		for (int c = 0; c < N_COL_TAULER; c++)
		{
			m_tauler[f][c] = tauler[f][c];
		}
	}
}


void Tauler::DibuixarTauler()
{
	for (int f = 0; f < N_FILES_TAULER; f++)
	{
		for (int c = 0; c < N_COL_TAULER; c++)
		{
			if (m_tauler[f][c] != COLOR_NEGRE)
			{
				IMAGE_NAME img;

				switch (m_tauler[f][c])
				{
				case(COLOR_BLAUCEL):
					img = GRAFIC_QUADRAT_BLAUCEL;
					break;
				case(COLOR_BLAUFOSC):
					img = GRAFIC_QUADRAT_BLAUFOSC;
					break;
				case(COLOR_GROC):
					img = GRAFIC_QUADRAT_GROC;
					break;
				case(COLOR_MAGENTA):
					img = GRAFIC_QUADRAT_MAGENTA;
					break;
				case(COLOR_TARONJA):
					img = GRAFIC_QUADRAT_TARONJA;
					break;
				case(COLOR_VERD):
					img = GRAFIC_QUADRAT_VERD;
					break;
				case(COLOR_VERMELL):
					img = GRAFIC_QUADRAT_VERMELL;
					break;
				default:
					img = GRAFIC_QUADRAT_BLAUCEL;
					break;
				}

				GraphicManager::getInstance()->drawSprite(img,
					POS_X_TAULER + ((c + 1) * MIDA_QUADRAT),
					POS_Y_TAULER + ((f) * MIDA_QUADRAT), false);
			}
		}
	}
}