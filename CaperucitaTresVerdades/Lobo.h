#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Entidad.h"
#include "Configuracion.h"

using namespace std;
using namespace System;


class Lobo : public Entidad
{
private:

    vector<wstring> dibujo;

public:

    Lobo()
    {
        dibujo =
        {
            L"              /\\/\\   ",
            L"             '   •' ¬", // es gracioso que el • genere sonido cada que aparece el lobo
            L"      ______/    ───' ", // al menos es buen detalle, como un sonido de alarma xd
            L"  _┌─/          /   ",
            L" _/_/   /───|  |    ",
            L"¯¯ /_  |_    |_ |_   "
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

        x = -ancho;
        y = Y_SUELO - alto;
    }

    // Se llama cada vez que empieza a cruzar (cuando Caperucita se
    // esconde a tiempo): vuelve a entrar por la izquierda.
    void reiniciar()
    {
        x = -ancho;
    }

    void avanzar(int velocidad)
    {
        // Cruza mas rapido que el resto del escenario para que se note
        // que esta pasando de largo. Ahora avanza de izquierda a
        // derecha.
        x += velocidad * 4;
    }

    bool salioDePantalla()
    {
        return x >= ANCHO_JUEGO;
    }

    void mostrar() override
    {
        if (x + ancho < 0 || x >= ANCHO_JUEGO)
        {
            return;
        }

        Console::ForegroundColor = ConsoleColor::DarkGray;

        for (int fila = 0; fila < static_cast<int>(dibujo.size()); fila++)
        {
            for (int col = 0; col < static_cast<int>(dibujo[fila].size()); col++)
            {
                wchar_t caracter = dibujo[fila][col];

                if (caracter != L' ')
                {
                    int columna = x + col;

                    if (columna >= 0 && columna < ANCHO_JUEGO)
                    {
                        Console::SetCursorPosition(columna, y + fila);
                        Console::Write(caracter);
                    }
                }
            }
        }

        Console::ResetColor();
    }
};
