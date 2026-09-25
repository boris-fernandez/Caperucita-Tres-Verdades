#pragma once

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

	virtual bool esPeligroso()
	{
		return false;
	}

	// Indica si Caperucita puede esconderse junto a este elemento (por
	// ahora, solo las rocas) cuando el lobo esta en camino.
	virtual bool esEscondite()
	{
		return false;
	}

	// Indica si, al tocarlo, este elemento dispara la alerta de que el
	// lobo viene (por ahora, solo las huellas).
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
