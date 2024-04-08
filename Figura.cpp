#include "Figura.h"
#include <iostream>
using namespace std;

//Gira una peça cap a la direcció establerta al paràmetre
void Figura::gir(DireccioGir dir) 
{
	ColorFigura temp[MAXTAMANY][MAXTAMANY];
	//Transposició
	for (int i = 0; i < m_tamany; i++)
	{
		for (int j = 0; j < m_tamany; j++)
		{
			temp[i][j] = m_forma[j][i];
		}
	}
	if (dir == GIR_HORARI) 
	{
		//Inversió de columnes
		if (m_tamany % 2 == 1) {
			for (int f = 0; f < m_tamany; f++)
			{
				for (int c = 0; c < m_tamany; c++)
				{
					if ((m_tamany - 1) / 2 == c) m_forma[f][c] = temp[f][c];
					else m_forma[f][c] = temp[f][m_tamany - (c + 1)];

				}
			}
		}
		else
		{
			for (int f = 0; f < m_tamany; f++)
			{
				for (int c = 0; c < m_tamany; c++)
				{
					m_forma[f][c] = temp[f][m_tamany - (c + 1)];
				}
			}
		}
		m_rot++;
		if (m_rot > 3)
		{
			m_rot = 0;
		}
	}
	else 
	{
		//Inversió de files
		if (m_tamany % 2 == 1) {
			for (int f = 0; f < m_tamany; f++)
			{
				for (int c = 0; c < m_tamany; c++)
				{
					if ((m_tamany - 1) / 2 == f) m_forma[f][c] = temp[f][c];
					else m_forma[f][c] = temp[m_tamany - (f + 1)][c];
				}
			}
		}
		else
		{
			for (int f = 0; f < m_tamany; f++)
			{
				for (int c = 0; c < m_tamany; c++)
				{
					m_forma[f][c] = temp[m_tamany - (f + 1)][c];
				}
			}
		}
		m_rot--;
		if (m_rot < 0)
		{
			m_rot = 3;
		}
	}

}

//Retorna el color assignat al tipus
ColorFigura assignaColor(TipusFigura tipus)
{
	ColorFigura color;
	switch (tipus)
	{
	case FIGURA_O:
		color = COLOR_GROC;
		break;
	case FIGURA_I:
		color = COLOR_BLAUCEL;
		break;
	case FIGURA_T:
		color = COLOR_MAGENTA;
		break;
	case FIGURA_L:
		color = COLOR_TARONJA;
		break;
	case FIGURA_J:
		color = COLOR_BLAUFOSC;
		break;
	case FIGURA_Z:
		color = COLOR_VERMELL;
		break;
	case FIGURA_S:
		color = COLOR_VERD;
		break;
	default:
		color = NO_COLOR;
		break;
	}
	return color;
}

//Genera la forma, el tamany, el color i la rotació de la figura
int ajustaForma(TipusFigura tipus, ColorFigura forma[MAXTAMANY][MAXTAMANY])
{
	//Inicialitzem tot a 0
	int tamany = 0;
	for (int i = 0; i < MAXTAMANY; i++)
	{
		for (int j = 0; j < MAXTAMANY; j++)
		{
			forma[i][j] = COLOR_NEGRE;
		}
	}
	ColorFigura color = assignaColor(tipus);
	//Modifiquem els punts per fer la forma en rotació inicial
	switch (tipus)
	{
	case FIGURA_O:
		tamany = 2;
		forma[0][0] = color;
		forma[0][1] = color;
		forma[1][0] = color;
		forma[1][1] = color;
		break;
	case FIGURA_I:
		tamany = 4;
		forma[1][0] = color;
		forma[1][1] = color;
		forma[1][2] = color;
		forma[1][3] = color;
		break;
	case FIGURA_T:
		tamany = 3;
		forma[0][1] = color;
		forma[1][0] = color;
		forma[1][1] = color;
		forma[1][2] = color;
		break;
	case FIGURA_L:
		tamany = 3;
		forma[0][2] = color;
		forma[1][0] = color;
		forma[1][2] = color;
		forma[1][1] = color;
		break;
	case FIGURA_J:
		tamany = 3;
		forma[0][0] = color;
		forma[1][0] = color;
		forma[1][2] = color;
		forma[1][1] = color;
		break;
	case FIGURA_Z:
		tamany = 3;
		forma[0][0] = color;
		forma[0][1] = color;
		forma[1][1] = color;
		forma[1][2] = color;
		break;
	case FIGURA_S:
		tamany = 3;
		forma[0][1] = color;
		forma[0][2] = color;
		forma[1][0] = color;
		forma[1][1] = color;
		break;
	default:
		break;
	}
	return tamany;
}

//Constructor buit (genera una forma buida)
Figura::Figura() {
	m_tipus = NO_FIGURA;
	m_color = NO_COLOR;
	m_posX = 0;
	m_posY = 0;
	m_tamany = 0;
	m_rot = 0;
	for (int i = 0; i < MAXTAMANY; i++)
	{
		for (int j = 0; j < MAXTAMANY; j++)
		{
			m_forma[i][j] = NO_COLOR;
		}
	}
}

//Constructor amb paràmetres
Figura::Figura(TipusFigura tipus, int posX, int posY, int rot) {
	m_tipus = tipus;
	m_color = assignaColor(tipus);
	m_posX = posX;
	m_posY = posY;
	m_rot = 0;
	m_tamany = ajustaForma(tipus, m_forma);
	//Rota la peça per posar'la com ha d'anar
	switch (rot)
	{
	case 1:
		gir(GIR_HORARI);
		break;
	case 2:
		gir(GIR_HORARI);
		gir(GIR_HORARI);
		break;
	case 3:
		gir(GIR_ANTI_HORARI);
		break;
	default:
		break;
	}
}

//Getter de la array forma. Transforma la array passada en el paràmetre en la matriu forma de la figura.
void Figura::getForma(ColorFigura forma[MAXTAMANY][MAXTAMANY]) {
	for (int i = 0; i < MAXTAMANY; i++)
	{
		for (int j = 0; j < MAXTAMANY; j++)
		{
			forma[i][j] = m_forma[i][j];
		}
	}
}
