#pragma once
#include "RenderNivel1.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "ElementoMapa.h"
#include "Configuracion.h"

using namespace std;
using namespace System;

class Arbusto : public ElementoMapa
{
private:

    vector<wstring> dibujo;

public:

    Arbusto(int posicionX)
    {
        x = posicionX;

        dibujo =
        {
            L"\\|/"
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

        if (x < -ancho)
        {
            // Repite el mismo grupo sin amontonar la decoracion al reciclarla.
            x += GRUPOS_DECORACION * ESPACIO_GRUPO_DECORACION;
        }
    }


    void mostrar() override
    {
        if (!visible)
        {
            return;
        }

        if (x + ancho <= 0 || x >= ANCHO_JUEGO)
        {
            return;
        }

        RenderNivel1::instancia().Color(ConsoleColor::Green);

        for (int fila = 0; fila < static_cast<int>(dibujo.size()); fila++)
        {
            for (int col = 0; col < static_cast<int>(dibujo[fila].size()); col++)
            {
                wchar_t caracter = dibujo[fila][col];

                if (caracter != L' ' && x + col >= 0 && x + col < ANCHO_JUEGO)
                {
                    RenderNivel1::instancia().SetCursorPosition(x + col, y + fila);
                    RenderNivel1::instancia().Write(caracter);
                }
            }
        }

        RenderNivel1::instancia().ResetColor();
    }


    bool esPeligroso() override
    {
        return false;
    }
};
