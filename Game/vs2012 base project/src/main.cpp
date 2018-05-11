#define GLM_FORCE_RADIANS

#include <king/Engine.h>
#include <king/Updater.h>
#include "..\\msvc\Tablero.h"

//#include <c:\Users\lautaro.losio\source\Game-midas-miner\Game\vs2012 base project\msvc\Tablero.h>

//---------------------------------------------------------------------------------------------------

class ExampleGame : public King::Updater {



public:

	ExampleGame()
		: mEngine("./assets")
		, mRotation(0.0f)
		, mGreenDiamondX(100.0f)
		, mGreenDiamondY(100.0f) {
	}

	void MouseEvent()
	{
		if (mEngine.GetMouseButtonDown()) 
		{
			float fromX = mEngine.GetMouseX();
			float fromY = mEngine.GetMouseY();
			mTablero.SeleccionarGema(fromX, fromY);

		}
		else
		{
			float toX = mEngine.GetMouseX();
			float toY = mEngine.GetMouseY();
			mTablero.LiberarGema(toX, toY);
		}

	}

	void Update() {	
		mTablero.DibujaMatriz(); 	
	}

	void Start() {
		mTablero.SetEnginee(&mEngine);
		mTablero.PupularMatriz();
		mEngine.Start(*this);	
	}


private:
	King::Engine mEngine;
	float mRotation;
	float mYellowDiamondX;
	float mYellowDiamondY;
	float mGreenDiamondX;
	float mGreenDiamondY;
	Tablero mTablero;
};

//---------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	ExampleGame game;
	game.Start();

	

	return 0;
}


