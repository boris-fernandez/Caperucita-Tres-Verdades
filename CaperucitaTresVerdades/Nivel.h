#pragma once
#include <iostream>
#include <cstdlib>

#include "Caperucita.h"
#include "Escenario.h"
#include "Lobo.h"
#include "EscenaLobo.h"

class Nivel
{
private:

    int numero;

    int distancia;
    int distanciaMeta;

    bool completado;

    Caperucita* jugador;
    Escenario* escenario;

    // ---- ALERTA DEL LOBO ----
    // Se activa al tocar una huella: el lobo viene, y hay que
    // esconderse detras de una roca cercana antes de que se acabe la
    // cuenta regresiva, o Caperucita pierde una vida.
    bool loboEnCamino;
    int cuentaRegresivaLobo;

    // Mientras el lobo esta cruzando la pantalla (porque Caperucita se
    // escondio a tiempo), el mundo se congela: no se mueve el escenario
    // ni el jugador, solo se anima al lobo pasando.
    bool loboPasando;
    Lobo* lobo;

public:

    Nivel()
    {
        numero = 1;

        distancia = 0;
        // Antes terminaba en 100: con velocidad 1, eso son solo 100
        // "columnas" de recorrido, y ni la huella de lobo (colocada en
        // x = 130) llegaba a aparecer antes de que el nivel terminara.
        // Se alarga para que se note el reciclado de rocas/troncos/
        // pinchos/huellas.
        distanciaMeta = 400;

        completado = false;

        jugador = new Caperucita();

        escenario = new Escenario();

        loboEnCamino = false;
        cuentaRegresivaLobo = 0;

        loboPasando = false;
        lobo = new Lobo();
    }

    ~Nivel()
    {
        delete jugador;
        delete escenario;
        delete lobo;
    }

    void procesarEntrada(char tecla)
    {
        if (jugador->estaEscondido())
        {
            // Mientras esta escondida, la unica accion posible es salir
            // del escondite.
            if (tecla == 'E' || tecla == 'e')
            {
                jugador->dejarEsconderse();
            }

            return;
        }

        if ((tecla == 'S' || tecla == 's') &&
            loboEnCamino &&
            hayRocaCerca())
        {
            // Se esconde justo a tiempo: el lobo pasara de largo. La
            // roca se queda visible en todo momento (Caperucita se
            // agacha junto a ella, sin taparla).
            jugador->esconderse();

            loboEnCamino = false;

            loboPasando = true;
            lobo->reiniciar();

            return;
        }

        jugador->mover(tecla);
    }

    void actualizar()
    {
        if (jugador->estaEscondido())
        {
            // El mundo se congela mientras esta escondida: solo avanza
            // la animacion del lobo cruzando el camino.
            if (loboPasando)
            {
                lobo->avanzar(escenario->getVelocidad());

                if (lobo->salioDePantalla())
                {
                    loboPasando = false;
                }
            }

            return;
        }

        jugador->actualizar();

        escenario->actualizar();

        // Si el lobo esta cruzando porque Caperucita NO alcanzo a
        // esconderse (ver verificarAlertaLobo), el mundo sigue en
        // marcha con normalidad, pero el lobo tambien se anima
        // cruzando la pantalla.
        if (loboPasando)
        {
            lobo->avanzar(escenario->getVelocidad());

            if (lobo->salioDePantalla())
            {
                loboPasando = false;
            }
        }

        verificarColisiones();
        verificarAlertaLobo();

        distancia++;

        verificarMeta();
    }

    // Hay una roca lo bastante cerca (en X) del jugador como para
    // esconderse detras de ella.
    bool hayRocaCerca()
    {
        for (ElementoMapa* elemento : escenario->getElementos())
        {
            if (!elemento->getVisible())
            {
                continue;
            }

            if (!elemento->esEscondite())
            {
                continue;
            }

            int distanciaAlElemento =
                abs(elemento->getX() - jugador->getX());

            if (distanciaAlElemento <= DISTANCIA_ESCONDITE)
            {
                return true;
            }
        }

        return false;
    }

    void verificarColisiones()
    {
        for (ElementoMapa* elemento : escenario->getElementos())
        {
            if (!elemento->getVisible())
            {
                continue;
            }

            bool choqueX =
                jugador->getX() < elemento->getX() + elemento->getAncho() &&
                jugador->getX() + jugador->getAncho() > elemento->getX();

            bool choqueY =
                jugador->getY() < elemento->getY() + elemento->getAlto() &&
                jugador->getY() + jugador->getAlto() > elemento->getY();

            if (!(choqueX && choqueY) || elemento->getImpactoAplicado())
            {
                continue;
            }

            if (elemento->esPeligroso())
            {
                jugador->recibirDanio();

                elemento->marcarImpacto();
            }
            else if (elemento->activaAlertaLobo() &&
                !loboEnCamino &&
                !loboPasando)
            {
                elemento->marcarImpacto();

                loboEnCamino = true;
                cuentaRegresivaLobo = FRAMES_ALERTA_LOBO;

                EscenaLobo();
            }
        }
    }

    void verificarAlertaLobo()
    {
        if (!loboEnCamino)
        {
            return;
        }

        cuentaRegresivaLobo--;

        if (cuentaRegresivaLobo <= 0)
        {
            // El lobo llego y Caperucita no alcanzo a esconderse: se lo
            // ve cruzar la pantalla (sin congelar el mundo esta vez) y
            // pierde una vida.
            loboEnCamino = false;

            loboPasando = true;
            lobo->reiniciar();

            jugador->recibirDanio();
        }
    }

    void verificarMeta()
    {
        if (distancia >= distanciaMeta)
        {
            completado = true;
        }
    }

    void mostrar()
    {
        escenario->mostrar();

        jugador->mostrar();

        if (loboPasando)
        {
            lobo->mostrar();
        }

        System::Console::SetCursorPosition(0, 1);

        std::cout
            << "CAPERUCITA ROJA";

        std::cout
            << "Nivel 1: El sendero de las huellas";

        System::Console::SetCursorPosition(0, 2);

        std::cout
            << "Vidas: "
            << jugador->getVidas();

        System::Console::SetCursorPosition(0, 3);

        std::cout
            << "Distancia: "
            << distancia
            << " / "
            << distanciaMeta;

        System::Console::SetCursorPosition(0, 4);

        if (jugador->estaEscondido())
        {
            std::cout
                << "Escondida detras de la roca... presiona E para salir";
        }
        else if (loboEnCamino)
        {
            std::cout
                << "El lobo viene! Busca una roca cerca y presiona S para esconderte";
        }

        System::Console::SetCursorPosition(0, FILA_CONTROLES);

        std::cout
            << "W = Saltar | S = Esconderse junto a una roca | E = Salir del escondite | ESC = Salir";
    }

    bool estaCompletado()
    {
        return completado;
    }

    bool jugadorVivo()
    {
        return jugador->estaVivo();
    }
};
