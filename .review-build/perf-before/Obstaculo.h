#pragma once

#include <iostream>

#include "ElementoMapa.h"
#include "Configuracion.h"

using namespace std;
using namespace System;

class Obstaculo : public ElementoMapa 
{

public:

	Obstaculo(int posicionX)//, //int nuevoCarril
	{
		x = posicionX;

		//carril = nuevoCarril;

		ancho = 1;
		alto = 1;

		/*if (carril == 1)
		{
			y = Y_CARRIL_SUPERIOR;
		}
		else
		{
			y = Y_CARRIL_INFERIOR;
		}*/

		y = Y_SUELO - alto;
		visible = true;
	
	}

	void actualizar(int velocidad) override
	{
		// El mundo se mueve hacia Caperucita
		x -= velocidad;

		// Si desaparece por la izquierda,
		// reaparece por la derecha.
		if (x <= 0)
		{
			x = ANCHO_JUEGO - ancho;
		}
	
	}

	bool esPeligroso() override
	{
		return true;
	}

	void mostrar() override 
	{
		if (!visible)
			return;

		if (x < 0 || x >= ANCHO_JUEGO)
			return;

		Capture::SetCursorPosition(x, y);

		cout << "#";
	
	}

};