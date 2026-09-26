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
    int limiteRecorrido;

    vector<ElementoMapa*> elementos;

    vector<pair<HuellaLobo*, Roca*>> paresHuellaRoca;

public:

    Escenario()
    {
        velocidad = 2;
        limiteRecorrido = 1000000;

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
        // Conserva los cuatro grupos, con aire entre copas y arbustos.
        for (int i = 0; i < GRUPOS_DECORACION; i++)
        {
            const int x = 20 + i * ESPACIO_GRUPO_DECORACION;
            switch (i % 4)
            {
            case 0:
                elementos.push_back(new Arbol(x));
                break;
            case 1:
                elementos.push_back(new Arbol(x));
                elementos.push_back(new Arbusto(x + 22));
                break;
            case 2:
                elementos.push_back(new Arbusto(x));
                elementos.push_back(new Arbusto(x + 10));
                break;
            case 3:
                elementos.push_back(new Arbusto(x));
                elementos.push_back(new Arbol(x + 12));
                break;
            }
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


    void actualizar(bool camaraDetenida = false, int casaX = 1000000)
    {
        // La casa pertenece al mundo: reserva su espacio antes de que entre
        // en pantalla, sin retirar objetos visibles durante la llegada.
        limiteRecorrido = casaX - 3;
        for (ElementoMapa* elemento : elementos)
        {
            elemento->actualizar(camaraDetenida ? 0 : velocidad);
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
        Capture::ForegroundColor =
            ConsoleColor::Green;

        Capture::SetCursorPosition(
            0,
            Y_SUELO
        );

        for (int i = 0; i < ANCHO_JUEGO; i++)
        {
            cout << "~";
        }

        Capture::ResetColor();
    }

    void mostrar()
    {
        mostrarCamino();

        for (ElementoMapa* elemento : elementos)
        {
            if (elementoEnRecorrido(elemento))
            {
                elemento->mostrar();
            }
        }
    }


    bool elementoEnRecorrido(ElementoMapa* elemento)
    {
        return elemento->getVisible() &&
            elemento->getX() + elemento->getAncho() <= limiteRecorrido;
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
