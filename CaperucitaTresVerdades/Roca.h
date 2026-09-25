#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "ElementoMapa.h"
#include "Configuracion.h"

using namespace std;
using namespace System;

// La roca ya no quita vidas: ahora es un escondite. Si el lobo viene y
// Caperucita esta cerca de una roca, puede esconderse detras de ella
// (tecla S) para dejarlo pasar sin recibir danio.
class Roca : public ElementoMapa
{
private:
    vector<wstring> dibujo;

public:

    Roca(int posicionX)
    {
        x = posicionX;

        dibujo =
        {
            L"   ____",
            L" _/ /_ \\_",
            L"/ _/   \\ \\"
        };

        alto = static_cast<int>(dibujo.size());

        ancho = 0;
        for (const wstring& linea : dibujo)
        {
            if (static_cast<int>(linea.size()) > ancho)
            {
                ancho = static_cast<int>(linea.size());
            }
        }

        y = Y_SUELO - alto;
        visible = true;
    }

    void actualizar(int velocidad) override
    {
        x -= velocidad;

        // En vez de desaparecer para siempre al salir por la izquierda,
        // vuelve a aparecer por la derecha a una distancia variable,
        // como una nueva roca que llega en el camino.
        if (x < -ancho)
        {
            x = ANCHO_JUEGO + GAP_MINIMO_OBSTACULO +
                (rand() % (GAP_MAXIMO_OBSTACULO - GAP_MINIMO_OBSTACULO + 1));

            impactoAplicado = false;
        }
    }

    void mostrar() override
    {
        if (!visible) return;
        if (x < 0 || x + ancho >= ANCHO_JUEGO) return;

        Console::ForegroundColor = ConsoleColor::Gray;

        for (int fila = 0; fila < static_cast<int>(dibujo.size()); fila++)
        {
            for (int col = 0; col < static_cast<int>(dibujo[fila].size()); col++)
            {
                wchar_t caracter = dibujo[fila][col];

                if (caracter != L' ')
                {
                    Console::SetCursorPosition(x + col, y + fila);
                    Console::Write(caracter);
                }
            }
        }

        Console::ResetColor();
    }

    bool esPeligroso() override
    {
        return false;
    }

    bool esEscondite() override
    {
        return true;
    }
};
