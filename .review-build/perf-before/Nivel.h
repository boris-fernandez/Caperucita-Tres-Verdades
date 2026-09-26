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

    int inicioLlegada()
    {
        const int recorrido = ANCHO_JUEGO - 25 - X_JUGADOR - jugador->getAncho();
        const int paso = escenario->getVelocidad();
        return distanciaMeta - (recorrido + paso - 1) / paso;
    }

    int getCasaX()
    {
        const int restante = inicioLlegada() - distancia;
        return ANCHO_JUEGO - 25 +
            (restante > 0 ? restante * escenario->getVelocidad() : 0);
    }

    bool cercaDeCasa()
    {
        // Incluye el fotograma en que la casa empieza a entrar en pantalla.
        return getCasaX() <= ANCHO_JUEGO;
    }

    // Casa de la abuela: meta exclusiva del nivel 1.
    void mostrarCasaMeta()
    {
        static const wchar_t* dibujo[] =
        {
            LR"CASA(             )                              )CASA",
            LR"CASA(            (                                 )CASA",
            LR"CASA(    ________[]_                        )CASA",
            LR"CASA(   /^=^-^-^=^-^\                  )CASA",
            LR"CASA(  /^-^-^-^-^-^-^\              )CASA",
            LR"CASA( /__^_^_^_^^_^_^_\         )CASA",
            LR"CASA(  |  .==.       |       )CASA",
            LR"CASA(^^|  |LI|  [}{] |^^)CASA",
            LR"CASA(&&|__|__|_______|&&)CASA",
        };
        const int alto = sizeof(dibujo) / sizeof(dibujo[0]);
        const int y = Y_SUELO - alto;
        const int x = getCasaX();

        if (x >= ANCHO_JUEGO)
        {
            return;
        }

        // Limpia el fondo para que los arboles no atraviesen la casa.
        const int ancho = 19;
        for (int fila = 0; fila < alto; fila++)
        {
            for (int col = 0; col < ancho; col++)
            {
                if (x + col >= 0 && x + col < ANCHO_JUEGO)
                {
                    Capture::SetCursorPosition(x + col, y + fila);
                    Capture::Write(L' ');
                }
            }
        }

        Capture::ForegroundColor = System::ConsoleColor::DarkYellow;
        for (int fila = 0; fila < alto; fila++)
        {
            for (int col = 0; dibujo[fila][col] != '\0'; col++)
            {
                const int columna = x + col;
                if (columna >= 0 && columna < ANCHO_JUEGO && dibujo[fila][col] != L' ')
                {
                    Capture::SetCursorPosition(columna, y + fila);
                    Capture::Write(dibujo[fila][col]);
                }
            }
        }
        Capture::ResetColor();
    }

public:

    Nivel()
    {
        numero = 1;

        distancia = 0;
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
            loboEnCamino && !cercaDeCasa() &&
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
        if (cercaDeCasa())
        {
            loboEnCamino = false;
            loboPasando = false;
            cuentaRegresivaLobo = 0;
        }

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

        // Mantiene la llegada a la casa sin suspender el resto del nivel.
        if (distancia >= inicioLlegada())
        {
            jugador->avanzarHastaMeta(getCasaX(), escenario->getVelocidad());
        }

        // La casa y el bosque comparten la misma parada de camara.
        // Se conservan los objetos y se siguen comprobando las colisiones.
        const bool camaraDetenida = distancia >= inicioLlegada();
        escenario->actualizar(camaraDetenida,
            getCasaX() - (camaraDetenida ? 0 : escenario->getVelocidad()));

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

        if (distancia < distanciaMeta)
        {
            distancia++;
        }

        verificarMeta();
    }

    bool hayRocaCerca()
    {
        for (ElementoMapa* elemento : escenario->getElementos())
        {
            if (!escenario->elementoEnRecorrido(elemento))
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
            if (!escenario->elementoEnRecorrido(elemento))
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
            else if (elemento->activaAlertaLobo() && !cercaDeCasa() &&
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
        const int puertaX = getCasaX();
        if (distancia >= inicioLlegada() && jugador->estaVivo() &&
            jugador->getX() + jugador->getAncho() >= puertaX &&
            jugador->getY() + jugador->getAlto() == Y_SUELO)
        {
            completado = true;
        }
    }

    void mostrar()
    {
        escenario->mostrar();
        mostrarCasaMeta();

        jugador->mostrar();

        if (loboPasando && !cercaDeCasa())
        {
            lobo->mostrar();
        }

        Capture::SetCursorPosition(0, 1);

        std::cout
            << "CAPERUCITA ROJA ";

        std::cout
            << "Nivel 1: El sendero de las huellas";

        Capture::SetCursorPosition(0, 2);

        std::cout
            << "Vidas: "
            << jugador->getVidas();

        Capture::SetCursorPosition(0, 3);

        std::cout
            << "Distancia: "
            << distancia
            << " / "
            << distanciaMeta;

        Capture::SetCursorPosition(0, 4);

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

        Capture::SetCursorPosition(0, FILA_CONTROLES);

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
