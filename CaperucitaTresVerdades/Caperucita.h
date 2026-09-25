#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Personaje.h"
#include "Configuracion.h"

using namespace std;
using namespace System;

class Caperucita : public Personaje
{

private:

	vector<wstring> dibujoNormal;
	vector<wstring> dibujoEscondida;

	bool saltando;
	int velocidadY;
	int yBase;

	// Permite un segundo impulso mientras esta en el aire (doble salto),
	// util para encadenar un salto extra y pasar un tronco y unos pinchos
	// que aparecen seguidos.
	bool saltoDobleDisponible;

public:

	Caperucita() 
	{
		x = X_JUGADOR;

		dibujoNormal =
		{
			L"  ___",
			L" / / \\",
			L" \\_\\_/",
			L" /|_\\-",
			L"/____\\ "
		};

		// Se dibuja cuando Caperucita se esconde detras de una roca cercana
		// para dejar pasar al lobo.
		dibujoEscondida =
		{
			L"    ___",
			L"   / _ \\",
			L"   \\|_|/",
			L"         ",
			L"          "
		};

		alto = static_cast<int>(dibujoNormal.size());
		ancho = 0;

		for (const wstring& linea : dibujoNormal)
		{
			if (static_cast<int>(linea.size()) > ancho)
			{
				ancho = static_cast<int>(linea.size());
			}
		}

		yBase = Y_SUELO - alto;
		y = yBase;

		saltando = false;
		velocidadY = 0;
		saltoDobleDisponible = true;

	}

	void mover(char tecla) override
	{
		// Esconderse ya no depende solo de una tecla: hace falta ademas que
		// el lobo este en camino y que haya una roca cerca, asi que esa
		// decision la toma Nivel (que llama directamente a esconderse() /
		// dejarEsconderse()). Aqui solo se procesa el salto.
		if (tecla == 'W' || tecla == 'w')
		{
			saltar();
		}
	}

	void saltar() override
	{
		if (escondido)
		{
			// No puede saltar mientras esta escondida detras de la roca.
			return;
		}

		if (!saltando)
		{
			// Primer salto: despega desde el suelo.
			saltando = true;
			// Valor negativo = subir
			velocidadY = IMPULSO_SALTO;

			// Al despegar, habilita el segundo salto en el aire.
			saltoDobleDisponible = true;
		}
		else if (saltoDobleDisponible)
		{
			// Segundo salto: se pulsa W otra vez mientras todavia esta en el
			// aire para ganar mas altura/alcance y alcanzar a pasar un
			// tronco y unos pinchos seguidos.
			velocidadY = IMPULSO_SALTO;

			saltoDobleDisponible = false;
		}

	}

	void actualizar() override
	{
		if (escondido)
		{
			// Mientras esta escondida no salta ni cae: espera quieta detras
			// de la roca hasta que el jugador decida salir.
			return;
		}

		if (saltando)
		{
			y += velocidadY;

			//gravedad
			velocidadY += GRAVEDAD;
			if (y >= yBase)
			{
				y = yBase;
				velocidadY = 0;

				saltando = false;

				// Al aterrizar, vuelve a tener disponible el doble salto.
				saltoDobleDisponible = true;
			
			}
		}
	
	}

	void mostrar() override
	{
		System::Console::ForegroundColor = System::ConsoleColor::Red;

		const vector<wstring>& dibujoActual =
			escondido ? dibujoEscondida : dibujoNormal;

		for (int fila = 0; fila < static_cast<int>(dibujoActual.size()); fila++)
		{
			for (int columna = 0;
				columna < static_cast<int>(dibujoActual[fila].size());
				columna++)
			{
				wchar_t caracter = dibujoActual[fila][columna];

				// Los espacios son transparentes
				if (caracter != L' ')
				{
					Console::SetCursorPosition(
						x + columna,
						y + fila
					);

					Console::Write(caracter);
				}
			}
		}
		
		Console::ResetColor();

	}

};
