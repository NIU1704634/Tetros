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

typedef enum
{
	GIR_HORARI = 0,
	GIR_ANTI_HORARI
} DireccioGir;



class Figura
{
public:
	//Constructors
	Figura();
	Figura(TipusFigura tipus, int posX, int posY, int rot);

	//Getters
	TipusFigura getTipus() { return m_tipus; };
	ColorFigura getColor() { return m_color; };
	int getPosX() { return m_posX; };
	int getPosY() { return m_posY; };
	int getTamany() { return m_tamany; };
	int getRot() { return m_rot; };
	void getForma(ColorFigura forma[MAXTAMANY][MAXTAMANY]);

	//Setters (El tipus, el color i el tamany van implicits a la figura i, per tant, no son editables)
	void setPosX(int posX) { m_posX = posX; };
	void setPosY(int posY) { m_posY = posY; };
	void setRot(int rot) { m_rot = rot; };

	//Moviments
	void mou(int dir) { m_posX += dir; };
	void baixa() { m_posY++; };
	void puja() { m_posY--; };
	void gir(DireccioGir dir);

private:
	int m_posX, m_posY, m_tamany, m_rot;
	TipusFigura m_tipus;
	ColorFigura m_color, m_forma[MAXTAMANY][MAXTAMANY];
};