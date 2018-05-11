#pragma once


#include <iostream>
#include <king/Engine.h>
using namespace std;




	class gemas {
	
	public:
		float X;
			float	Y;
		
			enum TEXTURE
			{
				TEXTURE_BLUE,
				TEXTURE_GREEN,
				TEXTURE_RED,
				TEXURE_YELLOW,
			};


		King::Engine::Texture t;
		King::Engine *mEngine;

		void  SetCoordenadas(float x, float y);
		void  SetTexture(King::Engine::Texture color);
		void Dibujar();
		void SetEnginee(King::Engine *e);
		bool AmI(float x, float y);

			
		

	};
	


