#include "pch.h"
#include "Casa.h"
#include "Configuracion.h"

#include <vector>
#include <string>

using namespace std;
using namespace System;

void mostrarCasaFinal()
{
    vector<wstring> dibujo =
    {
        L"            ´'",
        L"           ´´  ",
        L"          _'",
        L"  _______|_|__",
        L" /            \\",
        L"/______________\\",
        L" |     __     |",
        L" |    |. |    |",
        L" |____|__|____|"
    };

    int ancho = 0;
    for (const wstring& linea : dibujo)
    {
        if (static_cast<int>(linea.size()) > ancho)
        {
            ancho = static_cast<int>(linea.size());
        }
    }

    int x = (ANCHO_VENTANA - ancho) / 2;
    if (x < 0)
    {
        x = 0;
    }

    int y = 6;

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
