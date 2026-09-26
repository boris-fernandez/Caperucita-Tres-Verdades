#pragma once


class Entidad {

protected:
	int x;
	int y;
	int ancho;
	int alto;

public:
	Entidad() {
	
		x = 0;
		y = 0;

		ancho = 1;
		alto = 1;
	
	}
	virtual ~Entidad()
	{
	
	}

	virtual void mostrar() = 0;

	int getX() { return x; }
	int getY() { return y; }

	int getAncho() { return ancho; }
	int getAlto() { return alto; }

};