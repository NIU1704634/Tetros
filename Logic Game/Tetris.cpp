#include "Tetris.h"

string generaNumPuntuacio(int num) 
{
	string newNum = "";

	if (num > 999999) 
	{
		num = 999999;
	}
	else if (num < 100) 
	{
		newNum = "0000";
	}
	else if (num < 1000)
	{
		newNum = "000";
	}
	else if (num < 10000) 
	{
		newNum = "00";
	}
	else if (num < 100000)
	{
		newNum = "0";
	}
	
	return newNum + to_string(num);
}


void Tetris::carregaPuntuacions() 
{
	ifstream fitxer;
	fitxer.open("MillorsPuntuacions.txt");

	if (fitxer.is_open()) 
	{
		int punts;
		string nom;
		fitxer >> punts;
		while (!fitxer.eof())
		{
			fitxer >> nom;

			registraPuntuacio(punts, false, nom);
			fitxer >> punts;
		}

		fitxer.close();
	}
}

void Tetris::guardaPuntuacions() 
{
	ofstream fitxer;
	remove("MillorsPuntuacions.txt");
	fitxer.open("MillorsPuntuacions.txt");

	if (fitxer.is_open())
	{
		forward_list<int>::iterator iteradorPunts = m_puntuacions.begin();
		forward_list<string>::iterator iteradorNoms = m_noms.begin();
		string linea;
		for (int i = 0; i < min(m_maxNPuntuacions, m_nPuntuacions); i++)
		{
			linea = generaNumPuntuacio(*iteradorPunts) + " " + *iteradorNoms;
			fitxer << linea << endl;
			iteradorPunts++;
			iteradorNoms++;
		}

		fitxer.close();
	}
}

void Tetris::registraPuntuacio(int punts, bool escriurePuntuacio, const string& nomInicial)
{
	string nom;
	if (escriurePuntuacio) 
	{
		system("CLS");
		cout << endl << "   --------" << endl << "    TETRIS" << endl << "   --------" << endl << endl;
		cout << "Partida acabada. Has aconseguit " << to_string(punts) << " punts!" << endl;
		cout << "Introdueix el teu nom per guardar la teva puntuacio." << endl << endl;
		cin >> nom;
	}
	else
	{
		nom = nomInicial;
	}

	if (m_nPuntuacions == 0) 
	{
		m_puntuacions.push_front(punts);
		m_noms.push_front(nom);
	}
	else
	{
		forward_list<int>::iterator iteradorPunts = m_puntuacions.begin();
		forward_list<int>::iterator iteradorPreviPunts = m_puntuacions.before_begin();
		forward_list<string>::iterator iteradorNoms = m_noms.before_begin();

		bool posicioTrobada = false;
		int i = 0;

		while (!posicioTrobada && i < m_nPuntuacions)
		{
			if (punts > *iteradorPunts)
			{
				posicioTrobada = true;
			}
			else
			{
				i++;
				iteradorPunts++;
				iteradorPreviPunts++;
				iteradorNoms++;
			}
		}

		m_puntuacions.insert_after(iteradorPreviPunts, punts);
		m_noms.insert_after(iteradorNoms, nom);
	}
	m_nPuntuacions++;

	if (escriurePuntuacio) 
	{
		cout << "Puntuacio afegida amb exit!" << endl << endl;
		system("pause");
	}
}

void Tetris::mostraPuntuacions()
{
	system("CLS");
	cout << endl << "   --------" << endl << "    TETRIS" << endl << "   --------" << endl << endl;
	cout << "Millors Puntuacions: " << endl << endl;

	if (m_nPuntuacions > 0) 
	{
		forward_list<int>::iterator iteradorPunts = m_puntuacions.begin();
		forward_list<string>::iterator iteradorNoms = m_noms.begin();
		for (int i = 0; i < min(m_maxNPuntuacions, m_nPuntuacions); i++)
		{
			cout << (i + 1) << ". " << generaNumPuntuacio(*iteradorPunts) << " -      " << *iteradorNoms << endl;
			iteradorPunts++;
			iteradorNoms++;
		}
	}
	else
	{
		cout << " Aqui podras consultar les teves millors puntuacions pero..." << endl;
		cout << " Encara no tens cap puntuacio registrada!" << endl;
	}
	cout << endl << endl;
	system("pause");
}

void Tetris::borraPuntuacions() 
{
	remove("MillorsPuntuacions.txt");
	m_puntuacions.clear();
	m_noms.clear();
	m_nPuntuacions = 0;
}

int Tetris::menu() 
{
	int input;
	do
	{
		system("CLS");
		cout << endl << "   --------" << endl << "    TETRIS" << endl << "   --------" << endl << endl;
		cout << "Tria una opcio:" << endl;
		cout << " 1- Mode Normal" << endl;
		cout << " 2- Mode Test" << endl;
		cout << " 3- Millors Puntuacions" << endl;
		cout << " 4- Esborra Puntuacions" << endl;
		cout << " 5- Sortir" << endl << endl << " ";

		cin >> input;


	} while (input < 1 || input > 5);

	return input;
}

bool Tetris::llegirFitxer(string& partida, string& figures, string& moviments)
{
	string path = "./data/Games/";
	ifstream aux;
	bool tornaAlMenu = false;

	do
	{
		system("CLS");
		cout << endl << "   --------" << endl << "    TETRIS" << endl << "   --------" << endl << endl;
		if (!aux.good())
		{
			cout << "Error: Arxiu no valid" << endl << endl;
		}
		cout << "Nom del fitxer partida: " << endl << "(pots escriure 'menu' per tornar al menu)" << endl << endl;
		cin >> partida;
		if (partida == "menu") 
		{
			tornaAlMenu = true;
		}
		else
		{
			aux.open(path + partida);
		}
	} while (!aux.good() && !tornaAlMenu);

	if (!tornaAlMenu)
	{
		aux.close();
		do
		{
			system("CLS");
			cout << endl << "   --------" << endl << "    TETRIS" << endl << "   --------" << endl << endl;
			if (!aux.good())
			{
				cout << "Error: Arxiu no valid" << endl << endl;
			}
			cout << "Nom del fitxer de figures: " << endl << "(pots escriure 'menu' per tornar al menu)" << endl << endl;
			cin >> figures;
			if (figures == "menu")
			{
				tornaAlMenu = true;
			}
			else
			{
				aux.open(path + figures);
			}
		} while (!aux.good() && !tornaAlMenu);
		if (!tornaAlMenu)
		{
			aux.close();
			do
			{
				system("CLS");
				cout << endl << "   --------" << endl << "    TETRIS" << endl << "   --------" << endl << endl;
				if (!aux.good())
				{
					cout << "Error: Arxiu no valid" << endl << endl;
				}
				cout << "Nom del fitxer de moviments: " << endl << "(pots escriure 'menu' per tornar al menu)" << endl << endl;
				cin >> moviments;
				if (moviments == "menu")
				{
					tornaAlMenu = true;
				}
				else
				{
					aux.open(path + moviments);
				}
			} while (!aux.good() && !tornaAlMenu);
			if (!tornaAlMenu)
			{
				aux.close();
			}
		}
	}
	return tornaAlMenu;
}