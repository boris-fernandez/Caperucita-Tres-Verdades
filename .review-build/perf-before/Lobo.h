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

    vector<wstring> dibujoDerecha; // cruza de izquierda a derecha
    vector<wstring> dibujoIzquierda; // cruza de derecha a izquierda (espejado)

    bool haciaLaDerecha;

public:

    Lobo()
    {
        dibujoDerecha =
        {
            L"              /\\/\\   ",
            L"             '   •' ¬", // es gracioso que el • genere sonido cada que aparece el lobo
            L"      ______/    ───' ", // al menos es buen detalle, como un sonido de alarma xd
            L"  _┌─/          /   ",
            L" _/_/   /───|  |    ",
            L"¯¯ /_  |_    |_ |_   "
        };

        // Version espejada (izquierda-derecha invertidas)
        dibujoIzquierda =
        {
            L"   /\\/\\              ",
            L"¬ '•   '             ",
            L" '───    \\______      ",
            L"   \\          \\┐─_  ",
            L"    |  |───\\   \\_\\_ ",
            L"   _| _|    _|  _\\ ¯¯"
        };

        alto = static_cast<int>(dibujoDerecha.size());

        ancho = 0;
        for (const wstring& linea : dibujoDerecha)
        {
            if (static_cast<int>(linea.size()) > ancho)
            {
                ancho = static_cast<int>(linea.size());
            }
        }

        haciaLaDerecha = true;

        x = -ancho;
        y = Y_SUELO - alto;
    }

    void reiniciar(bool nuevaDireccionDerecha)
    {
        haciaLaDerecha = nuevaDireccionDerecha;

        // Entra por el lado opuesto al que va a salir.
        x = haciaLaDerecha ? -ancho : ANCHO_JUEGO;
    }

    void avanzar(int velocidad)
    {
        // Cruza mas rapido que el resto del escenario para que se note
        // que esta pasando de largo.
        int paso = velocidad * 4;

        x += haciaLaDerecha ? paso : -paso;
    }

    bool salioDePantalla()
    {
        return haciaLaDerecha ? (x >= ANCHO_JUEGO) : (x < -ancho);
    }

    void mostrar() override
    {
        if (x + ancho < 0 || x >= ANCHO_JUEGO)
        {
            return;
        }

        const vector<wstring>& dibujo = haciaLaDerecha ? dibujoDerecha : dibujoIzquierda;

        Capture::ForegroundColor = ConsoleColor::DarkGray;

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
                        Capture::SetCursorPosition(columna, y + fila);
                        Capture::Write(caracter);
                    }
                }
            }
        }

        Capture::ResetColor();
    }
};
