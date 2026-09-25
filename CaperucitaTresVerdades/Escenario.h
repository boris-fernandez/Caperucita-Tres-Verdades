#pragma once

#include <iostream>
#include <vector>

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

public:

    Escenario()
    {
        velocidad = 1;

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
        // Cada huella deja una roca cerca (a una distancia que el lobo
        // tarda en cruzar en FRAMES_ALERTA_LOBO), para que siempre haya
        // donde esconderse si se reacciona a tiempo.
        elementos.push_back(
            new HuellaLobo(60)
        );

        elementos.push_back(
            new Roca(90)
        );

        elementos.push_back(
            new Tronco(130)
        );

        elementos.push_back(
            new Pinchos(160)
        );

        elementos.push_back(
            new HuellaLobo(210)
        );

        elementos.push_back(
            new Roca(240)
        );

        elementos.push_back(
            new Tronco(280)
        );

        elementos.push_back(
            new Pinchos(310)
        );
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
