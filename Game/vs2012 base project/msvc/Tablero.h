#pragma once
#include <king\Engine.h>
#include "..\\msvc\\gemas.h"

class Tablero
{
private:
	King::Engine *mEngine;

public:
	Tablero() : gemaSeleccionada(nullptr) {};
	void SetEnginee(King::Engine *eng);

	gemas tablero[8][8];

	void PupularMatriz();
	void DibujaMatriz();

	void SeleccionarGema(float x, float y);
	void LiberarGema(float x, float y);

	gemas *gemaSeleccionada;

		
	void swap();

};
