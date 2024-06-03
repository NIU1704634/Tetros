#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"

Partida::Partida()
{
    m_temps = 0;
    m_nFigures = 0;
    m_nMoviments = 0;
    m_puntuacio = 0;
    m_puntsSN = 1000;
    m_nivell = 0;
    m_filesEliminades = 0;
    m_filesEliminadesPrev = 0;
    m_sequenciaFigures = nullptr;
    m_sequenciaMoviments = nullptr;
    m_posada = false;
    m_guardada = false;
    m_jocActiu = true;
    m_mode = 0;
    m_partidaAcabada = false;
}

void Partida::incrementaPuntuacio(int puntuacio) 
{
    m_puntuacio += puntuacio;
    m_puntsSN -= puntuacio;
    if (m_puntsSN <= 0) 
    {
        m_puntsSN += 1000;
        m_nivell++;
    }
}

bool Partida::actualitza(double deltaTime, int& punts)
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    if (m_mode == 0)
    {
        normal(deltaTime);
    }
    else
    {
        test(deltaTime);
    }

    m_joc.DibuixarJoc();
    string msgp = "Puntuacio: " + to_string(m_puntuacio);
    string msgn = "Nivell: " + to_string(m_nivell);
    m_joc.DibuixarFiguraGuardada();
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 80, 1.0, msgp);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msgn);
    if (!m_jocActiu && !m_partidaAcabada) 
    {
        string p = "PAUSA";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 127, POS_Y_TAULER + 273, 1.0, p);
    }
    else if (m_partidaAcabada) 
    {
        punts = m_puntuacio;
    }

    return m_partidaAcabada;
}

void Partida::normal(double deltaTime)
{
    if (Keyboard_GetKeyTrg(KEYBOARD_P) && !m_partidaAcabada)
    {
        m_jocActiu = !m_jocActiu;
    }

    if (!m_posada && m_jocActiu)
    {
        if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
        {
            m_joc.mouFigura(1);
        }
        else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
        {
            m_joc.mouFigura(-1);
        }
        else if (Keyboard_GetKeyTrg(KEYBOARD_UP))
        {
            m_joc.giraFigura(GIR_ANTI_HORARI);
        }
        else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
        {
            m_joc.giraFigura(GIR_HORARI);
        }
        else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
        {
            while (!m_posada)
            {
                m_posada = m_joc.baixaFigura(m_filesEliminades);
            }
        }
        else if (Keyboard_GetKeyTrg(KEYBOARD_Z))
        {
            if (!m_guardada)
            {
                m_joc.GuardarFigura();
                if (m_joc.getTauler().getFigura().getTipus() == NO_FIGURA)
                {
                    m_joc.generarNovaFigura(generarFiguraAleatoria());
                }

                m_guardada = true;
            }

        }

        m_temps += deltaTime;
        float tempsSeguent = 0.6 - m_nivell * 0.05;
        if (tempsSeguent < 0.05)
        {
            tempsSeguent = 0.05;
        }
        if (m_temps > tempsSeguent)
        {
            m_posada = m_joc.baixaFigura(m_filesEliminades);
            m_temps = 0;
        }
    }
    else if (m_jocActiu)
    {
        m_joc.generarNovaFigura(generarFiguraAleatoria());
        m_guardada = false;
        if (!m_joc.mouFigura(0))
        {
            m_jocActiu = false;
            m_partidaAcabada = true;
        }
        else
        {
            incrementaPuntuacio(10);
            if (m_filesEliminadesPrev < m_filesEliminades)
            {
                switch (m_filesEliminades - m_filesEliminadesPrev)
                {
                case 1:
                    incrementaPuntuacio(100);
                    break;
                case 2:
                    incrementaPuntuacio(250);
                    break;
                case 3:
                    incrementaPuntuacio(375);
                    break;
                case 4:
                    incrementaPuntuacio(500);
                    break;
                default:
                    break;
                }
                m_filesEliminadesPrev = m_filesEliminades;
            }
        }
        m_posada = false;
    }
}

void Partida::test(double deltaTime)
{
    m_temps += deltaTime;

    if (m_temps > 0.1)
    {
        if (!m_posada && m_jocActiu)
        {
            ferMoviment(m_sequenciaMoviments->getMoviment());
            
            NodeMoviment* aux = m_sequenciaMoviments;
            m_sequenciaMoviments = m_sequenciaMoviments->getNext();
            delete aux;

            m_temps = 0;
        }
        else if (m_jocActiu)
        {
            NodeFigura* aux = m_sequenciaFigures;
            m_joc.generarNovaFigura(m_sequenciaFigures->getFigura());
            m_sequenciaFigures = m_sequenciaFigures->getNext();
            delete aux;

            m_guardada = false;
            if (!m_joc.mouFigura(0))
            {
                m_jocActiu = false;
                m_partidaAcabada = true;
            }
            else
            {
                incrementaPuntuacio(10);
                if (m_filesEliminadesPrev < m_filesEliminades)
                {
                    switch (m_filesEliminades - m_filesEliminadesPrev)
                    {
                    case 1:
                        incrementaPuntuacio(100);
                        break;
                    case 2:
                        incrementaPuntuacio(250);
                        break;
                    case 3:
                        incrementaPuntuacio(375);
                        break;
                    case 4:
                        incrementaPuntuacio(500);
                        break;
                    default:
                        break;
                    }
                    m_filesEliminadesPrev = m_filesEliminades;
                }
            }
            m_posada = false;
        }

        
        if (m_sequenciaFigures == nullptr || m_sequenciaMoviments == nullptr)
        {
            m_jocActiu = false;
            m_partidaAcabada = true;
        }
        
    }

}

void Partida::ferMoviment(TipusMoviment mov)
{

    switch (mov)
    {
    case MOVIMENT_DRETA:
        m_joc.mouFigura(1);
        break;
    case MOVIMENT_ESQUERRA:
        m_joc.mouFigura(-1);
        break;
    case MOVIMENT_BAIXA:
        m_posada = m_joc.baixaFigura(m_filesEliminades);
        break;
    case MOVIMENT_BAIXA_FINAL:
        while (!m_posada)
        {
            m_posada = m_joc.baixaFigura(m_filesEliminades);
        }
        break;
    case MOVIMENT_GIR_ANTI_HORARI:
        m_joc.giraFigura(GIR_ANTI_HORARI);
        break;
    case MOVIMENT_GIR_HORARI:
        m_joc.giraFigura(GIR_HORARI);
        break;
    default:
        break;
    }

}

TipusFigura IntAFigura(int tipus)
{
    TipusFigura fTipus;
    switch (tipus)
    {
    case 0:
        fTipus = NO_FIGURA;
        break;
    case 1:
        fTipus = FIGURA_O;
        break;
    case 2:
        fTipus = FIGURA_I;
        break;
    case 3:
        fTipus = FIGURA_T;
        break;
    case 4:
        fTipus = FIGURA_L;
        break;
    case 5:
        fTipus = FIGURA_J;
        break;
    case 6:
        fTipus = FIGURA_Z;
        break;
    case 7:
        fTipus = FIGURA_S;
        break;
    default:
        fTipus = NO_FIGURA;
        break;
    }
    return fTipus;
}

TipusMoviment IntATipusMoviment(int tipus)
{
    TipusMoviment fTipus;
    switch (tipus)
    {
    case 0:
        fTipus = MOVIMENT_ESQUERRA;
        break;
    case 1:
        fTipus = MOVIMENT_DRETA;
        break;
    case 2:
        fTipus = MOVIMENT_GIR_HORARI;
        break;
    case 3:
        fTipus = MOVIMENT_GIR_ANTI_HORARI;
        break;
    case 4:
        fTipus = MOVIMENT_BAIXA;
        break;
    case 5:
        fTipus = MOVIMENT_BAIXA_FINAL;
        break;
    default:
        fTipus = MOVIMENT_ESQUERRA;
        break;
    }
    return fTipus;
}

Figura Partida::generarFiguraAleatoria()
{
    int n = rand() % 7 + 1;
    Figura novaFigura(TipusFigura(n), rand() % (5) + 2, 0, rand() % 4);
    return novaFigura;
}

void Partida::inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments) 
{
    m_temps = 0;
    m_nFigures = 0;
    m_nMoviments = 0;
    m_puntuacio = 0;
    m_puntsSN = 1000;
    m_nivell = 0;
    m_filesEliminades = 0;
    m_filesEliminadesPrev = 0;
    m_sequenciaFigures = nullptr;
    m_sequenciaMoviments = nullptr;
    m_posada = false;
    m_guardada = false;
    m_jocActiu = true;
    m_partidaAcabada = false;
    m_mode = mode;
    //modes: 0-Normal, 1-Test
    if(mode == 1)
    {
        //Inicialitzem Tauler inicial a partir de fitxer
        m_joc.inicialitza(fitxerInicial);

        m_nFigures = 0;
        m_nMoviments = 0;
        m_sequenciaFigures = nullptr;
        m_sequenciaMoviments = nullptr;

        ifstream fitxer;
        fitxer.open(fitxerFigures);

        if (fitxer.is_open())
        {
            int tipus, fila, columna, rot;

            fitxer >> tipus >> fila >> columna >> rot;
            NodeFigura* nodeFA = nullptr;
            while (!fitxer.eof())
            {
                m_nFigures++;
                NodeFigura* nodeF = new NodeFigura;
                Figura fig(IntAFigura(tipus), fila, columna, rot);

                nodeF->setFigura(fig);

                if (nodeFA == nullptr) 
                {
                    m_sequenciaFigures = nodeF;
                }
                else
                {
                    nodeFA->setNext(nodeF);
                }

                nodeFA = nodeF;

                fitxer >> tipus >> fila >> columna >> rot;
            }
            nodeFA->setNext(nullptr);
            fitxer.close();
        }

        fitxer.open(fitxerMoviments);
        if (fitxer.is_open())
        {
            int mov;
            fitxer >> mov;

            NodeMoviment* nodeMA = nullptr;
            while (!fitxer.eof())
            {
                m_nMoviments++;
                NodeMoviment* nodeM = new NodeMoviment;
                nodeM->setMoviment(IntATipusMoviment(mov));

                if (nodeMA == nullptr)
                {
                    m_sequenciaMoviments = nodeM;
                }
                else
                {
                    nodeMA->setNext(nodeM);
                }

                nodeMA = nodeM;

                fitxer >> mov;
            }
            nodeMA->setNext(nullptr);

            fitxer.close();
        }

        NodeFigura* aux = m_sequenciaFigures;
        m_joc.generarNovaFigura(m_sequenciaFigures->getFigura());
        m_sequenciaFigures = m_sequenciaFigures->getNext();
        delete aux;
    }
    else
    {
        m_joc.~Joc();
        m_joc = Joc();
        m_joc.generarNovaFigura(generarFiguraAleatoria());
    }
}

