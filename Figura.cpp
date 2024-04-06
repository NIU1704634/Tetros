#include "Figura.h"

void Figura::girHorari() 
{
	int temp[MAXTAMANY][MAXTAMANY];

	//Transposició
	for (int i = 0; i < m_tamany; i++)
	{
		for (int j = 0; j < m_tamany; j++)
		{
			temp[i][j] = m_forma[j][i];
		}
	}
	//Inversió de columnes
	if (m_tamany % 2 == 1) {
		for (int f = 0; f < m_tamany; f++)
		{
			for (int c = 0; c < m_tamany; c++)
			{
				if ((m_tamany - 1) / 2 == c)
				{
					m_forma[f][c] = temp[f][c];
				}
				else
				{
					m_forma[f][c] = temp[f][m_tamany - (c + 1)];
				}
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
}

void Figura::girAntiHorari()
{
	int temp[MAXTAMANY][MAXTAMANY];

	//Transposició
	for (int i = 0; i < m_tamany; i++)
	{
		for (int j = 0; j < m_tamany; j++)
		{
			temp[i][j] = m_forma[j][i];
		}
	}
	//Inversió de files
	if (m_tamany % 2 == 1) {
		for (int f = 0; f < m_tamany; f++)
		{
			for (int c = 0; c < m_tamany; c++)
			{
				if ((m_tamany - 1) / 2 == f)
				{
					m_forma[f][c] = temp[f][c];
				}
				else
				{
					m_forma[f][c] = temp[m_tamany - (f + 1)][c];
				}
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
}

//Genera la forma, el tamany, el color i la rotació de la figura
int ajustaForma(int tipus, int forma[MAXTAMANY][MAXTAMANY])
{
	//Inicialitzem tot a 0
	int tamany = 0;
	for (int i = 0; i < MAXTAMANY; i++)
	{
		for (int j = 0; j < MAXTAMANY; j++)
		{
			forma[i][j] = 0;
		}
	}
	//Modifiquem els punts per fer la forma en rotació inicial
	switch (tipus)
	{
	case FIGURA_O:
		tamany = 2;
		forma[0][0] = tipus;
		forma[0][1] = tipus;
		forma[1][0] = tipus;
		forma[1][1] = tipus;
		break;
	case FIGURA_I:
		tamany = 4;
		forma[1][0] = tipus;
		forma[1][1] = tipus;
		forma[1][2] = tipus;
		forma[1][3] = tipus;
		break;
	case FIGURA_T:
		tamany = 3;
		forma[0][1] = tipus;
		forma[1][0] = tipus;
		forma[1][1] = tipus;
		forma[1][2] = tipus;
		break;
	case FIGURA_L:
		tamany = 3;
		forma[0][2] = tipus;
		forma[1][0] = tipus;
		forma[1][2] = tipus;
		forma[1][1] = tipus;
		break;
	case FIGURA_J:
		tamany = 3;
		forma[0][0] = tipus;
		forma[1][0] = tipus;
		forma[1][2] = tipus;
		forma[1][1] = tipus;
		break;
	case FIGURA_Z:
		tamany = 3;
		forma[0][0] = tipus;
		forma[0][1] = tipus;
		forma[1][1] = tipus;
		forma[1][2] = tipus;
		break;
	case FIGURA_S:
		tamany = 3;
		forma[0][1] = tipus;
		forma[0][2] = tipus;
		forma[1][0] = tipus;
		forma[1][1] = tipus;
		break;
	default:
		break;
	}
	return tamany;
}

//Constructor buit (genera una forma buida)
Figura::Figura() {
	m_tipus = 0;
	m_color = 8;
	m_posX = N_COLUMNES / 2;
	m_posY = 0;
	m_tamany = 0;
	m_rot = 0;
	for (int i = 0; i < MAXTAMANY; i++)
	{
		for (int j = 0; j < MAXTAMANY; j++)
		{
			m_forma[i][j] = 0;
		}
	}
}

//Constructor amb paràmetres
Figura::Figura(int tipus, int posX, int rot) {
	m_tipus = tipus;
	m_color = tipus;
	m_posX = posX;
	m_posY = 0;
	m_rot = rot;
	m_tamany = ajustaForma(tipus, m_forma);
	//Rota la peça per posar'la com ha d'anar
	switch (rot)
	{
	case 1:
		girHorari();
		break;
	case 2:
		girHorari();
		girHorari();
		break;
	case 3:
		girAntiHorari();
		break;
	default:
		break;
	}
}

//Getter de la array forma. Transforma la array passada en el paràmetre en la matriu forma de la figura.
void Figura::getForma(int forma[MAXTAMANY][MAXTAMANY]) {
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
	Figura f(3, 3, 4);
	int forma[MAXTAMANY][MAXTAMANY];
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