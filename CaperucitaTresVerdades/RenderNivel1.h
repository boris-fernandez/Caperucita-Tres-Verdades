#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "Configuracion.h"

// Solo la presentacion del nivel 1. Las entidades conservan mostrar() virtual.
class RenderNivel1
{
private:
    CHAR_INFO celdas[ANCHO_JUEGO * (FILA_CONTROLES + 1)];
    int x = 0;
    int y = 0;
    WORD color = 7;

public:
    void prepararConsola()
    {
        // Evita que la escritura por bloques recorte el HUD en buffers pequenos.
        CONSOLE_SCREEN_BUFFER_INFO info;
        HANDLE salida = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(salida, &info))
        {
            COORD tamano = info.dwSize;
            if (tamano.X < ANCHO_JUEGO) tamano.X = ANCHO_JUEGO;
            if (tamano.Y <= FILA_CONTROLES) tamano.Y = FILA_CONTROLES + 1;
            if (tamano.X != info.dwSize.X || tamano.Y != info.dwSize.Y)
                SetConsoleScreenBufferSize(salida, tamano);
        }
    }

    static RenderNivel1& instancia()
    {
        static RenderNivel1 render;
        return render;
    }

    void iniciar()
    {
        color = 7;
        x = y = 0;
        for (auto& celda : celdas)
        {
            celda.Char.UnicodeChar = L' ';
            celda.Attributes = color;
        }
    }

    void Color(System::ConsoleColor nuevoColor)
    {
        color = static_cast<WORD>(nuevoColor);
    }

    void ResetColor() { color = 7; }
    void SetCursorPosition(int columna, int fila) { x = columna; y = fila; }

    void Write(wchar_t caracter)
    {
        if (x >= 0 && x < ANCHO_JUEGO && y >= 0 && y <= FILA_CONTROLES)
        {
            CHAR_INFO& celda = celdas[y * ANCHO_JUEGO + x];
            celda.Char.UnicodeChar = caracter;
            celda.Attributes = color;
        }
        ++x;
    }

    void texto(int columna, int fila, const char* texto)
    {
        SetCursorPosition(columna, fila);
        for (; *texto; ++texto) Write(static_cast<unsigned char>(*texto));
    }

    void presentar()
    {
        const COORD tamano = { ANCHO_JUEGO, FILA_CONTROLES + 1 };
        const COORD origen = { 0, 0 };
        SMALL_RECT destino = { 0, 0, ANCHO_JUEGO - 1, FILA_CONTROLES };
        WriteConsoleOutputW(GetStdHandle(STD_OUTPUT_HANDLE), celdas, tamano, origen, &destino);
    }
};
