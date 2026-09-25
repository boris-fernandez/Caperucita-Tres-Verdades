#pragma once

// ---- TAMANIO DE LA VENTANA DE CONSOLA ----
// Se usan para fijar, una unica vez en main(), el mismo tamanio de
// ventana/buffer que usan las escenas cinematicas (Escena1/2/3), para que
// el nivel jugable ocupe el mismo espacio visual en pantalla.
const int ANCHO_VENTANA = 160;
const int ALTO_VENTANA = 46;

// ---- TAMANIO DEL MUNDO DEL NIVEL ----
// El ancho jugable y la altura del suelo se agrandaron para aprovechar
// la ventana mas grande de arriba. Esto es lo que realmente hace que el
// nivel "se vea mas grande": no es el tamanio de letra (la consola usa
// una sola fuente para todo, escenas y nivel), sino cuantas columnas y
// filas de caracteres usa el dibujo del nivel.
const int ANCHO_JUEGO = 150;

const int Y_SUELO = 34;

const int X_JUGADOR = 12;

// Fila donde se muestran los controles (debajo del suelo, con margen
// para que entre en la ventana mas alta).
const int FILA_CONTROLES = Y_SUELO + 6;

// ---- SALTO ----
// La gravedad vuelve a 1 (con 2 caia demasiado rapido y era muy dificil
// esquivar). El impulso se deja un poco mas fuerte que el original para
// que el salto siga sintiendose un poco mas agil/alto.
const int IMPULSO_SALTO = -4; // fuerza hacia arriba de cada salto (mas negativo = salto mas alto)
const int GRAVEDAD = 1;       // cuanto frena/empieza a caer Caperucita en cada frame

// ---- REAPARICION DE OBSTACULOS ----
// Cuando una roca, tronco, pinchos, arbol, arbusto o huella de lobo sale
// de la pantalla por la izquierda, vuelve a aparecer por la derecha a
// una distancia aleatoria entre estos dos valores (en vez de
// desaparecer para siempre).
const int GAP_MINIMO_OBSTACULO = 18;
const int GAP_MAXIMO_OBSTACULO = 45;

// ---- REAPARICION DE LA HUELLA DE LOBO ----
// Las huellas usan un espacio propio (mucho mas grande que el resto de
// obstaculos) para que no aparezcan tan seguido: en promedio, una cada
// ~100 columnas de distancia recorrida.
const int GAP_MINIMO_HUELLA = 90;
const int GAP_MAXIMO_HUELLA = 110;

// ---- ESCONDITE Y ALERTA DEL LOBO ----
// Que tan cerca (en columnas) tiene que estar Caperucita de una roca
// para poder esconderse detras de ella.
const int DISTANCIA_ESCONDITE = 8;

// Cuantos frames pasan, despues de pisar una huella, antes de que el
// lobo llegue. Si para entonces Caperucita no se escondio, pierde una
// vida.
const int FRAMES_ALERTA_LOBO = 55;
