#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <cstdlib>
#define NOMINMAX
#include <Windows.h>
#define private public
#include "../CaperucitaTresVerdades/RenderNivel1.h"
#undef private

// Intercepta solamente la salida antigua para comparar caracteres y colores.
ref class Capture
{
public:
    static property System::ConsoleColor ForegroundColor
    {
        void set(System::ConsoleColor color) { RenderNivel1::instancia().Color(color); }
    }
    static void SetCursorPosition(int x, int y) { RenderNivel1::instancia().SetCursorPosition(x, y); }
    static void Write(wchar_t c) { RenderNivel1::instancia().Write(c); }
    static void ResetColor() { RenderNivel1::instancia().ResetColor(); }
};
class CaptureStream : public std::streambuf
{
    int overflow(int c) override
    {
        if (c != EOF) RenderNivel1::instancia().Write(static_cast<wchar_t>(c));
        return c;
    }
};

#define private public
#ifdef BASELINE
#include "perf-before/Nivel.h"
#else
#include "../CaperucitaTresVerdades/Nivel.h"
#endif
#undef private
void EscenaLobo() {}
void EscenaMuerte(const std::string&) {}

int main(int argc, char** argv)
{
    std::ofstream salida(argv[1]);
    CaptureStream captura;
    auto* original = std::cout.rdbuf(&captura);
    for (int seed = 0; seed < 100; ++seed)
    {
        srand(seed);
        Nivel nivel;
        for (int frame = 0; frame < 500 && !nivel.estaCompletado() && nivel.jugadorVivo(); ++frame)
        {
            char tecla = (seed % 2 && frame % 11 == 0) ? 'w' : 0;
            if (nivel.loboEnCamino && nivel.hayRocaCerca()) tecla = 's';
            if (nivel.jugador->estaEscondido() && !nivel.loboPasando) tecla = 'e';
            nivel.procesarEntrada(tecla);
            nivel.actualizar();
            auto& render = RenderNivel1::instancia();
            render.iniciar();
            nivel.mostrar();
            unsigned long long hash = 14695981039346656037ULL;
            for (const auto& celda : render.celdas)
            {
                hash = (hash ^ celda.Char.UnicodeChar) * 1099511628211ULL;
                hash = (hash ^ celda.Attributes) * 1099511628211ULL;
            }
            salida << seed << ' ' << frame << ' ' << hash << ' '
                << nivel.distancia << ' ' << nivel.jugador->getVidas() << ' '
                << nivel.jugador->getX() << ' ' << nivel.jugador->getY() << ' '
                << nivel.loboEnCamino << nivel.loboPasando << nivel.estaCompletado() << '\n';
        }
    }
    std::cout.rdbuf(original);
    std::cout << "Captured 100 seeded runs.\n";
}
