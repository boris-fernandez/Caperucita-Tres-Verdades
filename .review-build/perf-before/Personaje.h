#pragma once

#include <string>

#include "Entidad.h"

class Personaje : public Entidad
{
protected:

	int vidas;
	bool escondido;

	std::string causaMuerte;

public: 
	Personaje() {

		vidas = 20;
		escondido = false;
		causaMuerte = "";
	
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

	void recibirDanio(const std::string& causa)
	{
		causaMuerte = causa;

		if (vidas > 0)
		{
			vidas--;
		}

	}

	bool estaVivo() { return vidas > 0; }

	bool estaEscondido() { return escondido; }

	int getVidas() { return vidas; }

	std::string getCausaMuerte() { return causaMuerte; }
};
