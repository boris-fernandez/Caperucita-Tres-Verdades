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
    }

    void mostrar() override
    {
        if (!visible) return;
        if (x < 0 || x + ancho >= ANCHO_JUEGO) return;

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

    std::string getCausaMuerte() override
    {
        return "tronco";
    }
};
