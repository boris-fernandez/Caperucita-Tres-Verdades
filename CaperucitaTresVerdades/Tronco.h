#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "ElementoMapa.h"
#include "Configuracion.h"

using namespace std;
using namespace System;

class Tronco : public ElementoMapa
{
private:
    vector<wstring> dibujo;

public:

    Tronco(int posicionX)
    {
        x = posicionX;

        dibujo =
        {
            L" _____",
            L"(@----)"
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
        // como un nuevo tronco que llega en el camino.
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

        // Marrón aproximado en consola
        Console::ForegroundColor = ConsoleColor::DarkYellow;

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
        return true;
    }
};
