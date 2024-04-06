const int N_FILES = 8;
const int N_COLUMNES = 8;
const int MAXTAMANY = 4;

typedef enum
{
	NO_FIGURA = 0,
	FIGURA_O,
	FIGURA_I,
	FIGURA_T,
	FIGURA_L,
	FIGURA_J,
	FIGURA_Z,
	FIGURA_S
} TipusFigura;

typedef enum
{
	COLOR_NEGRE = 0,
	COLOR_GROC,
	COLOR_BLAUCEL,
	COLOR_MAGENTA,
	COLOR_TARONJA,
	COLOR_BLAUFOSC,
	COLOR_VERMELL,
	COLOR_VERD,
	NO_COLOR
} ColorFigura;

class Figura
{
public:
	//Constructors
	Figura();
	Figura(int tipus, int posX, int rot);
	//Getters
	int getTipus() { return m_tipus; };
	int getColor() { return m_color; };
	int getPosX() { return m_posX; };
	int getPosY() { return m_posY; };
	int getTamany() { return m_posY; };
	int getRot() { return m_rot; };
	void getForma(int forma[MAXTAMANY][MAXTAMANY]);
	//Setters (El tipus, el color i el tamany van implicits a la figura i, per tant, no son editables)
	void setPosX(int posX) { m_posX = posX; };
	void setPosY(int posY) { m_posY = posY; };
	void setRot(int rot) { m_rot = rot; };
	//Moviments
	void mouDreta() { m_posX++; };
	void mouEsquerra() { m_posX--; };
	void baixa() { m_posY++; };
	void puja() { m_posY--; };
	void girHorari();
	void girAntiHorari();
private:
	int m_tipus, m_color, m_posX, m_posY, m_tamany, m_rot,m_forma[MAXTAMANY][MAXTAMANY];
};