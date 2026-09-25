#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>

#include "Configuracion.h"
#include "ElementoMapa.h"

#include "Roca.h"
#include "Tronco.h"
#include "Pinchos.h"
#include "HuellaLobo.h"

#include "Arbol.h"
#include "Arbusto.h"

using namespace std;
using namespace System;

class Escenario
{
private:

    int velocidad;

    vector<ElementoMapa*> elementos;

    vector<pair<HuellaLobo*, Roca*>> paresHuellaRoca;

public:

    Escenario()
    {
        velocidad = 2;

        crearDecoracion();
        crearPeligros();
    }


    ~Escenario()
    {
        for (ElementoMapa* elemento : elementos)
        {
            delete elemento;
        }

        elementos.clear();
    }


    void crearDecoracion()
    {
        int x = 20;

        // El arbol grande ocupa unas 16 columnas de ancho: el espacio
        // entre grupos y los desfaces internos se agrandaron para que
        // no se encimen con el arte nuevo.
        for (int i = 0; i < 8; i++)
        {
            int tipo = i % 4;

            // 1. Arbol solo
            if (tipo == 0)
            {
                elementos.push_back(
                    new Arbol(x)
                );
            }

            // 2. Arbol + arbusto a la derecha
            else if (tipo == 1)
            {
                elementos.push_back(
                    new Arbol(x)
                );

                elementos.push_back(
                    new Arbusto(x + 18)
                );
            }

            // 3. Dos arbustos juntos
            else if (tipo == 2)
            {
                elementos.push_back(
                    new Arbusto(x)
                );

                elementos.push_back(
                    new Arbusto(x + 6)
                );
            }

            // 4. Arbusto izquierda + arbol
            else
            {
                elementos.push_back(
                    new Arbusto(x)
                );

                elementos.push_back(
                    new Arbol(x + 8)
                );
            }

            // Separacion entre grupos
            x += 36;
        }
    }


    void crearPeligros()
    {
        // Cada huella deja una roca cerca (DISTANCIA_HUELLA_ANTES_DE_ROCA
        // columnas por delante), para que siempre haya donde esconderse
        // si se reacciona a tiempo. Ambas se reubican juntas cuando
        // reciclan (ver reubicarParHuellaRoca).
        crearParHuellaRoca(60);

        elementos.push_back(new Tronco(130));
        elementos.push_back(new Pinchos(160));

        crearParHuellaRoca(210);

        elementos.push_back(new Tronco(280));
        elementos.push_back(new Pinchos(310));
    }

    void crearParHuellaRoca(int xHuella)
    {
        HuellaLobo* huella = new HuellaLobo(xHuella);
        Roca* roca = new Roca(xHuella + DISTANCIA_HUELLA_ANTES_DE_ROCA);

        elementos.push_back(huella);
        elementos.push_back(roca);

        paresHuellaRoca.push_back({ huella, roca });
    }


    void agregarElemento(ElementoMapa* elemento)
    {
        elementos.push_back(elemento);
    }


    void actualizar()
    {
        for (ElementoMapa* elemento : elementos)
        {
            elemento->actualizar(velocidad);
        }

        // Pares huella+roca: se reubican juntas solo cuando la roca (que
        // siempre va detras, mas cerca del jugador en el recorrido) ya
        // salio de pantalla. Si se disparara con solo la huella saliendo,
        // la roca se teletransportaria lejos mientras el jugador todavia
        // se esta acercando a ella.
        for (auto& par : paresHuellaRoca)
        {
            HuellaLobo* huella = par.first;
            Roca* roca = par.second;

            if (roca->getX() < -roca->getAncho())
            {
                reubicarParHuellaRoca(huella, roca);
            }
        }

        // Tronco y pinchos "sueltos" (no forman parte de un par): cada
        // uno que sale de pantalla se reubica por separado, siempre
        // respetando el hueco minimo con el peligro mas adelantado que
        // ya este en pantalla.
        for (ElementoMapa* elemento : elementos)
        {
            bool esSuelto =
                dynamic_cast<Tronco*>(elemento) != nullptr ||
                dynamic_cast<Pinchos*>(elemento) != nullptr;

            if (!esSuelto)
            {
                continue;
            }

            if (elemento->getX() < -elemento->getAncho())
            {
                int nuevaX = proximaPosicionLibre(elemento);
                elemento->reubicar(nuevaX);
            }
        }
    }

    // Reubica juntas una huella y su roca, dejando la huella primero y
    // la roca DISTANCIA_HUELLA_ANTES_DE_ROCA columnas por delante, sin
    // quedar pegadas a ningun otro peligro que ya este en pantalla.
    void reubicarParHuellaRoca(HuellaLobo* huella, Roca* roca)
    {
        int base = proximaPosicionLibre(huella, roca);

        huella->reubicar(base);
        roca->reubicar(base + DISTANCIA_HUELLA_ANTES_DE_ROCA);
    }

    // Calcula una posicion X para un peligro nuevo que deje siempre al
    // menos GAP_MINIMO_OBSTACULO columnas libres respecto al peligro (o
    // huella/roca) mas adelantado que ya este en pantalla. Asi nunca
    // salen dos peligros pegados o encimados, sin importar el orden en
    // el que cada uno haya reciclado.
    int proximaPosicionLibre(ElementoMapa* excluir1, ElementoMapa* excluir2 = nullptr)
    {
        int extremo = ANCHO_JUEGO;

        for (ElementoMapa* elemento : elementos)
        {
            if (elemento == excluir1 || elemento == excluir2)
            {
                continue;
            }

            bool ocupaEspacio =
                elemento->esPeligroso() ||
                elemento->esEscondite() ||
                elemento->activaAlertaLobo();

            if (!ocupaEspacio)
            {
                continue;
            }

            int derecha = elemento->getX() + elemento->getAncho();

            if (derecha > extremo)
            {
                extremo = derecha;
            }
        }

        int rango = GAP_MAXIMO_OBSTACULO - GAP_MINIMO_OBSTACULO + 1;

        return extremo + GAP_MINIMO_OBSTACULO + (rand() % rango);
    }


    void mostrarCamino()
    {
        Console::ForegroundColor =
            ConsoleColor::Green;

        Console::SetCursorPosition(
            0,
            Y_SUELO
        );

        for (int i = 0; i < ANCHO_JUEGO; i++)
        {
            cout << "~";
        }

        Console::ResetColor();
    }

    void mostrar()
    {
        mostrarCamino();

        for (ElementoMapa* elemento : elementos)
        {
            elemento->mostrar();
        }
    }


    vector<ElementoMapa*>& getElementos()
    {
        return elementos;
    }

    int getVelocidad()
    {
        return velocidad;
    }


    void setVelocidad(int nuevaVelocidad)
    {
        velocidad = nuevaVelocidad;
    }
};
