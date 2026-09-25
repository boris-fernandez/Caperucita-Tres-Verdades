#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "ElementoMapa.h"
#include "Configuracion.h"

using namespace std;
using namespace System;

// La huella ya no quita vidas: al tocarla se dispara la alerta de que
// el lobo viene (ver Nivel::verificarColisiones / EscenaLobo).
class HuellaLobo : public ElementoMapa
{
private:
    vector<wstring> dibujo;

public:

    HuellaLobo(int posicionX)
    {
        x = posicionX;

        dibujo =
        {
            L"o o",
            L" O "
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
        // vuelve a aparecer por la derecha a una distancia variable y
        // mas grande que el resto de obstaculos (GAP_*_HUELLA), para
        // que las huellas no salgan tan seguido (en promedio, una cada
        // ~100 columnas).
        if (x < -ancho)
        {
            x = ANCHO_JUEGO + GAP_MINIMO_HUELLA +
                (rand() % (GAP_MAXIMO_HUELLA - GAP_MINIMO_HUELLA + 1));

            impactoAplicado = false;
        }
    }

    void mostrar() override
    {
        if (!visible) return;
        if (x < 0 || x + ancho >= ANCHO_JUEGO) return;

        Console::ForegroundColor = ConsoleColor::White;

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

    bool activaAlertaLobo() override
    {
        return true;
    }
};
