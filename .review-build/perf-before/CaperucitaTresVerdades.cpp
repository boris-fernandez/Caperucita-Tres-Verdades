#include "pch.h"

#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Configuracion.h"
#include "PantallaInicio.h"
#include "Escena1.h"
#include "Escena2.h"
#include "Escena3.h"
#include "SelectorNiveles.h"
#include "Nivel.h"
#include "Casa.h"

using namespace System;
using namespace std;

void ejecutarNivel1()
{
    Nivel nivel1;

    while (!nivel1.estaCompletado() && nivel1.jugadorVivo())
    {
        char tecla = 0;

        if (_kbhit())
        {
            tecla = _getch();

            if (tecla == 27)
            {
                Console::Clear();
                return;
            }
        }

        nivel1.procesarEntrada(tecla);
        nivel1.actualizar();

        if (!nivel1.jugadorVivo())
        {
            break;
        }

        Console::Clear();
        nivel1.mostrar();

        System::Threading::Thread::Sleep(70);
    }

    Console::Clear();

    if (nivel1.estaCompletado())
    {
        Console::ForegroundColor = ConsoleColor::Green;
        Console::WriteLine(R"ASCIIART(


                 __        __  ___   _   _
                 \ \      / / |_ _| | \ | |
                  \ \ /\ / /   | |  |  \| |
                   \ V  V /    | |  | |\  |
                    \_/\_/    |___| |_| \_|

                 Llegaste a la casa de la abuela.

)ASCIIART");
        Console::ResetColor();
    }
    else if (!nivel1.jugadorVivo())
    {
        Console::ForegroundColor = ConsoleColor::Red;
        Console::WriteLine(R"ASCIIART(


                ____      _      __  __   _____      ___   __     __  _____   ____  
               / ___|    / \    |  \/  | | ____|    / _ \  \ \   / / | ____| |  _ \ 
              | |  _    / _ \   | |\/| | |  _|     | | | |  \ \ / /  |  _|   | |_) |
              | |_| |  / ___ \  | |  | | | |___    | |_| |   \ V /   | |___  |  _ < 
               \____| /_/   \_\ |_|  |_| |_____|    \___/     \_/    |_____| |_| \_\


)ASCIIART");
    }

    Console::ResetColor();
    Console::WriteLine("Presiona cualquier tecla para volver al menu.");
    // WIN y GAME OVER esperan una pulsacion nueva, sin teclas del juego.
    while (_kbhit())
    {
        _getch();
    }
    const int teclaFin = _getch();
    if (teclaFin == 0 || teclaFin == 224)
    {
        _getch();
    }
}

int main()
{
    Console::CursorVisible = false;

    // Semilla para que las rocas, troncos y huellas reaparezcan con
    // espaciados aleatorios distintos en cada partida.
    srand(static_cast<unsigned int>(time(nullptr)));

    PantallaInicio();

    bool salir = false;

    while (!salir)
    {
        int opcion = SelectorNiveles();

        switch (opcion)
        {
        case 1:
            Escena1();
            ejecutarNivel1();
            break;

        case 2:
            Escena2();
            cout << "NIVEL 2";
            _getch();
            break;

        case 3:
            Escena3();
            cout << "NIVEL 3";
            _getch();
            break;

        case 4:
            salir = true;
            break;
        }
    }

    Console::Clear();

    return 0;
}
