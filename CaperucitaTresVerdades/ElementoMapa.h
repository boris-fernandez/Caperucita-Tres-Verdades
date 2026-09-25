#pragma once

#include <string>

#include "Entidad.h"

class ElementoMapa : public Entidad
{

protected:

	bool visible;
	bool impactoAplicado;

public:
	ElementoMapa()
	{
		visible = true;
		impactoAplicado = false;

	}

	virtual void actualizar(int velocidad) = 0;

	virtual void reubicar(int nuevaX)
	{
		x = nuevaX;
		impactoAplicado = false;
	}

	virtual bool esPeligroso()
	{
		return false;
	}

	virtual std::string getCausaMuerte()
	{
		return "obstaculo";
	}

	virtual bool esEscondite()
	{
		return false;
	}

	virtual bool activaAlertaLobo()
	{
		return false;
	}

	bool getVisible()
	{
		return visible;
	}

	bool getImpactoAplicado()
	{
		return impactoAplicado;
	}

	void marcarImpacto()
	{
		impactoAplicado = true;
	}
};
