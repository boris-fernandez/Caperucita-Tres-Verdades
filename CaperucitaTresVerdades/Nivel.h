#pragma once
#include <iostream>
#include <cstdlib>

#include "Caperucita.h"
#include "Escenario.h"
#include "Lobo.h"
#include "EscenaLobo.h"
#include "EscenaMuerte.h"

class Nivel
{
private:

    int numero;

    int distancia;
    int distanciaMeta;

    bool completado;

    Caperucita* jugador;
    Escenario* escenario;

    bool loboEnCamino;
    int cuentaRegresivaLobo;

    bool loboPasando;
    Lobo* lobo;

    int vecesQueCruzoLobo;

    bool muerteMostrada;

public:

    Nivel()
    {
        numero = 1;

        distanciaMeta = 400;

        completado = false;

        jugador = new Caperucita();

        escenario = new Escenario();

        loboEnCamino = false;
        cuentaRegresivaLobo = 0;

        loboPasando = false;
        lobo = new Lobo();

        vecesQueCruzoLobo = 0;

        muerteMostrada = false;
    }

    ~Nivel()
    {
        delete jugador;
        delete escenario;
        delete lobo;
    }

    // Primera vez: izquierda->derecha. Segunda: derecha->izquierda. Y
    // asi se va alternando en cada cruce.
    bool siguienteDireccionLoboEsDerecha()
    {
        bool esDerecha = (vecesQueCruzoLobo % 2 == 0);

        vecesQueCruzoLobo++;

        return esDerecha;
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
            jugador->esconderse();

            loboEnCamino = false;

            loboPasando = true;
            lobo->reiniciar(siguienteDireccionLoboEsDerecha());

            return;
        }

        jugador->mover(tecla);
    }

    void actualizar()
    {
        if (jugador->estaEscondido())
        {
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

        if (!jugador->estaVivo() && !muerteMostrada)
        {
            muerteMostrada = true;

            EscenaMuerte(jugador->getCausaMuerte());
        }

        distancia++;

        verificarMeta();
    }

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
                jugador->recibirDanio(elemento->getCausaMuerte());

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
            lobo->reiniciar(siguienteDireccionLoboEsDerecha());

            jugador->recibirDanio("lobo");
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
