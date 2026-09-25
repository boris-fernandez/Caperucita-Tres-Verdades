#include "pch.h"
#include "PantallaInicio.h"

using namespace System;

void PantallaInicio()
{
    Console::Clear();

    Console::ForegroundColor = ConsoleColor::Cyan;
    Console::WriteLine("=====================================================");
    Console::WriteLine(" Sugerencia: usa la consola en PANTALLA COMPLETA");
    Console::WriteLine(" (Alt + Enter) para una mejor experiencia visual.");
    Console::WriteLine(" (CTRL + scroll) para ajustar la pantalla");
    Console::WriteLine("=====================================================");
    Console::ResetColor();
    Console::WriteLine();
    Console::WriteLine("[ Presiona cualquier tecla para comenzar... ]");
    Console::ReadKey(true);
    Console::Clear();
}