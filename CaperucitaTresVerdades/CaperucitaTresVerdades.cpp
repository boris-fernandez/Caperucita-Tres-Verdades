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

// Fija el tamanio de la ventana de consola una unica vez, al arrancar el
// juego, para que las escenas cinematicas y el nivel jugable usen siempre
// el mismo espacio en pantalla (en vez de que el nivel se vea "chico"
// dentro de una ventana pensada para las escenas). Si la pantalla o la
// fuente actual no permiten ese tamanio, Windows lo recorta solo al
// maximo posible: por eso se deja envuelto en try/catch.
void ajustarVentanaConsola()
{
    try
    {
        // 1) Primero se encoge la ventana a algo pequenio y seguro,
        //    porque Windows no deja agrandar la ventana mas alla del
        //    buffer actual.
        Console::SetWindowSize(1, 1);

        // 2) Se agranda el buffer (el "lienzo" donde se puede dibujar).
        int anchoBuffer = Math::Min(ANCHO_VENTANA, Console::LargestWindowWidth);
        int altoBuffer = Math::Min(ALTO_VENTANA, Console::LargestWindowHeight);

        Console::SetBufferSize(anchoBuffer, altoBuffer);

        // 3) Y por ultimo se agranda la ventana hasta ese mismo tamanio.
        Console::SetWindowSize(anchoBuffer, altoBuffer);
    }
    catch (...)
    {
        // Si la consola no permite cambiar el tamanio (por ejemplo, al
        // ejecutar dentro de algunos terminales o con la salida
        // redirigida), simplemente se sigue con el tamanio que ya tenia.
    }
}

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
                break;
            }
        }

        nivel1.procesarEntrada(tecla);
        nivel1.actualizar();

        Console::Clear();
        nivel1.mostrar();

        System::Threading::Thread::Sleep(70);
    }

    Console::Clear();

    if (nivel1.estaCompletado())
    {
        mostrarCasaFinal();

        Console::SetCursorPosition(0, 17);
        cout << "NIVEL COMPLETADO - Llegaste a la casa de la abuela";
    }
    else if (nivel1.jugadorVivo())
    {
        cout << "GAME OVER";
    }

    _getch();
}

int main()
{
    Console::CursorVisible = false;

    // Semilla para que las rocas, troncos y huellas reaparezcan con
    // espaciados aleatorios distintos en cada partida.
    srand(static_cast<unsigned int>(time(nullptr)));

    ajustarVentanaConsola();

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