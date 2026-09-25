#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "ElementoMapa.h"
#include "Configuracion.h"

using namespace std;
using namespace System;

class Arbol : public ElementoMapa
{
private:

    vector<wstring> dibujo;

public:

    Arbol(int posicionX)
    {
        x = posicionX;

        dibujo =
        {
            L"       /\\",
            L"      /  \\",
            L"     /    \\",
            L"    «_    _»",
            L"    /      \\",
            L"   /        \\",
            L"  «_        _»",
            L"  /          \\",
            L" /            \\",
            L"«              »",
            L" ¯¯¯¯¯|  |¯¯¯¯¯",
            L"      |  |"
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

        // Pegado al suelo
        y = Y_SUELO - alto;

        visible = true;
    }


    void actualizar(int velocidad) override
    {
        x -= velocidad;

        if (x < -ancho)
        {
            x = ANCHO_JUEGO + GAP_MINIMO_OBSTACULO +
                (rand() % (GAP_MAXIMO_OBSTACULO - GAP_MINIMO_OBSTACULO + 1));
        }
    }


    void mostrar() override
    {
        if (!visible)
        {
            return;
        }

        // Evita posiciones inválidas
        if (x < 0 || x + ancho >= ANCHO_JUEGO)
        {
            return;
        }

        Console::ForegroundColor =
            ConsoleColor::Green;

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
};
