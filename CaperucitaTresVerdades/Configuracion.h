#pragma once

// TAMANIO DEL MUNDO DEL NIVEL
const int ANCHO_JUEGO = 150;

// Espaciado exclusivo del fondo del nivel 1.
const int GRUPOS_DECORACION = 8;
const int ESPACIO_GRUPO_DECORACION = 44;

const int Y_SUELO = 34;

const int X_JUGADOR = 12;

// Fila donde se muestran los controles (debajo del suelo, con margen
// para que entre en la ventana mas alta).
const int FILA_CONTROLES = Y_SUELO + 6;

// SALTO
const int IMPULSO_SALTO = -3; // fuerza hacia arriba de cada salto (mas negativo = salto mas alto)
const int GRAVEDAD = 1;       // cuanto frena/empieza a caer Caperucita en cada frame

// REAPARICION DE OBSTACULOS Y HUELLAS
// Cuando una roca, tronco, pinchos o par huella+roca sale de la
// pantalla por la izquierda, Escenario lo reubica por la derecha a una
// distancia aleatoria entre estos dos valores, medida siempre desde el
// peligro/huella/roca mas adelantado que ya este en pantalla (nunca
// menos que eso), para que nunca queden dos peligros pegados entre si.
const int GAP_MINIMO_OBSTACULO = 18;
const int GAP_MAXIMO_OBSTACULO = 45;

// ESCONDITE Y ALERTA DEL LOBO
// Que tan cerca (en columnas) tiene que estar Caperucita de una roca
// para poder esconderse detras de ella.
const int DISTANCIA_ESCONDITE = 4;

// Cuantos frames pasan, despues de pisar una huella, antes de que el
// lobo llegue. Si para entonces Caperucita no se escondio, pierde una
// vida.
const int FRAMES_ALERTA_LOBO = 55;

// Cada huella queda "enganchada" a la roca que le sigue: cuando la
// huella se reubica, la roca se reubica junto con ella, siempre esta
// misma cantidad de columnas por delante. Con esto la huella SIEMPRE
// aparece antes que su roca (nunca despues) y con margen de sobra para
// llegar a esconderse dentro de FRAMES_ALERTA_LOBO.
const int DISTANCIA_HUELLA_ANTES_DE_ROCA = 30;

