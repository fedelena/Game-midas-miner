#include "Tablero.h"
#include "gemas.h"

void Tablero::SetEnginee(King::Engine *eng)
{
	mEngine = eng;
	
}


void Tablero::PupularMatriz() {
	for (int i = 0; i < 8; i++)
	{

		for (int j = 0; j < 8; j++)
		{
		
			tablero[i][j].SetCoordenadas(320 + i * 45, 100 + j * 45);
			int ran = (rand() % 5 + 1 );
			tablero[i][j].SetTexture(static_cast<King::Engine::Texture>(ran));
		
		
		}
	}

}
void Tablero::DibujaMatriz()
{
	for (int i = 0; i < 8; i++)
	{

		for (int j = 0; j < 8; j++)
		{
			tablero[i][j].SetEnginee(mEngine);
			tablero[i][j].Dibujar();

		}
	}

}
void Tablero::swap()
{
	
}

void Tablero::SeleccionarGema(float x, float y)
{
	for (int i = 0; i < 8; i++)
	{

		for (int j = 0; j < 8; j++)
		{
			if (tablero[i][j].AmI(x, y))
				gemaSeleccionada = &tablero[i][j];
		}
	}
}

void Tablero::LiberarGema(float x, float y)
{
	if (gemaSeleccionada != nullptr)
	{
		gemaSeleccionada->SetCoordenadas(x, y);

	}


}
