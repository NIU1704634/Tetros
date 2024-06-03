#include "Partida.h"
#include <forward_list>

class Tetris 
{
public:
	Tetris() { m_nPuntuacions = 0; m_maxNPuntuacions = N_MAX_PUNTUACIONS; }
	Partida getPartida() { return m_partida; }
	void carregaPuntuacions();
	void guardaPuntuacions();
	void registraPuntuacio(int punts, bool escriurePuntuacio, const string& nomInicial);
	void mostraPuntuacions();
	void borraPuntuacions();
	bool llegirFitxer(string& partida, string& figures, string& moviments);
	int menu();
private:
	Partida m_partida;
	forward_list<int> m_puntuacions;
	forward_list<string> m_noms;
	int m_maxNPuntuacions, m_nPuntuacions;
};