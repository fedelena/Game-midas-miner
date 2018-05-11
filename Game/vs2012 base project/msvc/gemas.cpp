#include "gemas.h"
#include <iostream>	

using namespace std;

	void gemas::SetEnginee(King::Engine *e)
	{
		mEngine = e;
	}
	
	void  gemas::SetCoordenadas(float x, float y)
	{
		X = x;
		Y = y;
	}

	void  gemas::SetTexture(King::Engine::Texture color)
	{
		t = color;	
	}

	void gemas::Dibujar()
	{
		mEngine->Render(t, X, Y);
	}

	bool  gemas::AmI(float x, float y)
	{
		if (X < x && x < X + 20) {
			if (Y < y && y < Y + 20)
				return true;
			else
				return false;
		}
		else
			return false;

		
	}


