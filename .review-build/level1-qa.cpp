#include <cassert>
#include <iostream>
#include "../CaperucitaTresVerdades/Caperucita.h"
#include "../CaperucitaTresVerdades/Escenario.h"
#include "../CaperucitaTresVerdades/Lobo.h"
#define private public
#include "../CaperucitaTresVerdades/Nivel.h"
#undef private

int muertes = 0;
void EscenaLobo() {}
void EscenaMuerte(const std::string&) { ++muertes; }

int main()
{
    for (int seed = 0; seed < 100; ++seed)
    {
        srand(seed);
        Nivel nivel;
        int casaAnterior = nivel.getCasaX();
        int frames = 0;
        while (!nivel.estaCompletado() && nivel.jugadorVivo() && frames < 450)
        {
            nivel.actualizar();
            ++frames;
            assert(nivel.getCasaX() <= casaAnterior);
            assert(nivel.getCasaX() >= ANCHO_JUEGO - 25);
            casaAnterior = nivel.getCasaX();
            int decoraciones = 0;
            for (auto* elemento : nivel.escenario->getElementos())
            {
                if (!nivel.escenario->elementoEnRecorrido(elemento)) continue;
                assert(elemento->getX() + elemento->getAncho() <= nivel.getCasaX() - 3);
                if ((dynamic_cast<Arbol*>(elemento) || dynamic_cast<Arbusto*>(elemento)) &&
                    elemento->getX() + elemento->getAncho() > 0 && elemento->getX() < ANCHO_JUEGO)
                    ++decoraciones;
            }
            assert(decoraciones >= 2);
            if (nivel.distancia > nivel.inicioLlegada())
                assert(!nivel.loboEnCamino && !nivel.loboPasando);
        }
        assert(nivel.estaCompletado());
        assert(nivel.jugador->getX() + nivel.jugador->getAncho() == nivel.getCasaX());
        assert(nivel.jugador->getY() + nivel.jugador->getAlto() == Y_SUELO);
    }
    Nivel temprana;
    temprana.distancia = 400;
    temprana.verificarMeta();
    assert(!temprana.estaCompletado());
    temprana.jugador->avanzarHastaMeta(temprana.getCasaX(), 200);
    temprana.jugador->saltar();
    temprana.jugador->actualizar();
    temprana.verificarMeta();
    assert(!temprana.estaCompletado());
    while (temprana.jugador->getY() + temprana.jugador->getAlto() != Y_SUELO)
        temprana.jugador->actualizar();
    temprana.verificarMeta();
    assert(temprana.estaCompletado());

    Nivel muerte;
    for (int i = 0; i < 20; ++i) muerte.jugador->recibirDanio("tronco");
    muerte.actualizar();
    assert(!muerte.jugadorVivo() && !muerte.estaCompletado() && muertes == 1);
    muerte.actualizar();
    assert(muertes == 1);

    Nivel escondida;
    escondida.jugador->esconderse();
    int x = escondida.escenario->getElementos()[0]->getX();
    escondida.actualizar();
    assert(escondida.distancia == 0 && escondida.escenario->getElementos()[0]->getX() == x);
    escondida.procesarEntrada('e');
    escondida.actualizar();
    assert(escondida.distancia == 1);
    std::cout << "PASS: 100 seeded runs, scenery bounds, arrival, airborne/no-early WIN, death and hiding.\n";
}
