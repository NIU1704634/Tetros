//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Tetris.h"
#include "./Partida.h"
#include "./InfoJoc.h"


int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    //Mostrem la finestra grafica

    Tetris tetris;
    Partida game = tetris.getPartida();
    tetris.carregaPuntuacions();
    bool jocObert = true;
    string partida, figures, moviments;
    bool aborta;
    string path = "./data/Games/";

    while (jocObert) 
    {
        int opcio = tetris.menu();
        switch (opcio)
        {
        case 1:
            game.inicialitza(0, "", "", "");
            break;
        case 2:
            aborta = tetris.llegirFitxer(partida, figures, moviments);
            if (!aborta) 
            {
                game.inicialitza(1, path + partida, path + figures, path + moviments);
            }
            break;
        case 3:
            tetris.mostraPuntuacions();
            break;
        case 4:
            tetris.borraPuntuacions();
            break;
        case 5:
            jocObert = false;
            break;
        default:
            break;
        }

        system("CLS");

        if (opcio == 1 || opcio == 2 && !aborta) 
        {
            cout << endl << "   --------" << endl << "    TETRIS" << endl << "   --------" << endl << endl;
            cout << " <PARTIDA EN CURS>" << endl << " Prem la tecla Escape per tornar al menu";
            pantalla.show();

            Uint64 NOW = SDL_GetPerformanceCounter();
            Uint64 LAST = 0;
            bool jocAcabat = false;
            int punts = 0;
            double deltaTime = 0;
            do
            {
                LAST = NOW;
                NOW = SDL_GetPerformanceCounter();
                deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

                // Captura tots els events de ratolí i teclat de l'ultim cicle
                pantalla.processEvents();

                jocAcabat = game.actualitza(deltaTime, punts);

                // Actualitza la pantalla
                pantalla.update();

                if (jocAcabat)
                {
                    SDL_HideWindow(g_Video.window);
                    if (opcio == 1) 
                    {
                        tetris.registraPuntuacio(punts, true, "");
                        tetris.guardaPuntuacions();
                    }
                }
            } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !jocAcabat);

            // Sortim del bucle si pressionem ESC
            SDL_HideWindow(g_Video.window);
        }
    }

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

