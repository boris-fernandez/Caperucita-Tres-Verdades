#pragma once

#include "Entidad.h"

class Personaje : public Entidad
{
protected:

	int vidas;

	// Indica si el personaje esta escondido (por ejemplo, detras de una
	// roca). Mientras esta escondido es invulnerable, pero tampoco puede
	// moverse ni saltar.
	bool escondido;

public: 
	Personaje() {

		vidas = 3;
		escondido = false;
	
	}

	virtual void mover(char tecla) = 0;
	virtual void actualizar() = 0;
	virtual void saltar() = 0;

	void esconderse()
	{
		escondido = true;
	}

	void dejarEsconderse()
	{
		escondido = false;
	}

	void recibirDanio()
	{
		if (vidas > 0)
		{
			vidas--;
		}

	}

	bool estaVivo() { return vidas > 0; }

	bool estaEscondido() { return escondido; }

	int getVidas() { return vidas; }
};
