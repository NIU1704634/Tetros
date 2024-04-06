#include "Figura.h"
#include <iostream>
using namespace std;

void Figura::gir(DireccioGir dir) 
{
	ColorFigura temp[MAXTAMANY][MAXTAMANY];
	//Transposici�
	for (int i = 0; i < m_tamany; i++)
	{
		for (int j = 0; j < m_tamany; j++)
		{
			temp[i][j] = m_forma[j][i];
		}
	}
	if (dir == GIR_HORARI) 
	{
		//Inversi� de columnes
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
	}
	else 
	{
		//Inversi� de files
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
//Genera la forma, el tamany, el color i la rotaci� de la figura
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
	//Modifiquem els punts per fer la forma en rotaci� inicial
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
	m_posX = N_COLUMNES / 2;
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

//Constructor amb par�metres
Figura::Figura(TipusFigura tipus, int posX, int rot) {
	m_tipus = tipus;
	m_color = assignaColor(tipus);
	m_posX = posX;
	m_posY = 0;
	m_rot = rot;
	m_tamany = ajustaForma(tipus, m_forma);
	//Rota la pe�a per posar'la com ha d'anar
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

//Getter de la array forma. Transforma la array passada en el par�metre en la matriu forma de la figura.
void Figura::getForma(ColorFigura forma[MAXTAMANY][MAXTAMANY]) {
	for (int i = 0; i < MAXTAMANY; i++)
	{
		for (int j = 0; j < MAXTAMANY; j++)
		{
			forma[i][j] = m_forma[i][j];
		}
	}
}

//Debug del generador de figures
/*
int main() 
{
	Figura f(FIGURA_L, 3, 3);
	ColorFigura forma[MAXTAMANY][MAXTAMANY];
	f.getForma(forma);
	for (int i = 0; i < MAXTAMANY; i++)
	{
		for (int j = 0; j < MAXTAMANY; j++)
		{
			cout << forma[i][j];
		}
		cout << endl;
	}
}
*/
