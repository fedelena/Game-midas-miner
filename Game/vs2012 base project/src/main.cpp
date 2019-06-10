#define GLM_FORCE_RADIANS 

#include <string>
#include <king/Engine.h>
#include <king/Updater.h>
#include "CandyBoard.h"

//**********************************************************************

class ExampleGame : public King::Updater 
{
public:

	ExampleGame()
		: myEngine("./assets")
		, myBoard()
		, swapFromX(0.0f)
		, swapFromY(0.0f)
	    , swapToX(0.0f)
		, swapToY(0.0f)
		, shouldSwap(false) 
		, swapping(false)
	{}

	void Start()
	{
		myEngine.Start(*this);	
	}

	void Update()
	{
		myEngine.Render(King::Engine::TEXTURE_BACKGROUND, 20.0f, 0.0f);
		myEngine.Write("Score: ", 70.0f, 100.0f);
		std::string scoreStr = std::to_string(myBoard.getScore());
		myEngine.Write(scoreStr.c_str(), 180.0f, 100.0f);
		
		switch (myBoard.getStatus())
		{

			case CandyBoard::CandyGameStatus::IDLE:
				if (myEngine.GetMouseButtonDown() && !swapping) {
					swapFromX = myEngine.GetMouseX();
					swapFromY = myEngine.GetMouseY();
					swapping = true;
				}

				if (!myEngine.GetMouseButtonDown() && swapping) {
					swapToX = myEngine.GetMouseX();
					swapToY = myEngine.GetMouseY();
					shouldSwap = true;
					swapping = false;
				}

				if (shouldSwap)
				{
					myBoard.swap(swapFromX, swapFromY, swapToX, swapToY);
					shouldSwap = false;
					if (myBoard.checkSwap(swapFromY, swapFromX) || myBoard.checkSwap(swapToY, swapToX))
						myBoard.setStatus(CandyBoard::CandyGameStatus::CHECKING);
					else
						myBoard.swap(swapFromX, swapFromY, swapToX, swapToY);
				}
				break;


			case CandyBoard::CandyGameStatus::CHECKING:
				bool hasHorizontalHoles = false;
				bool hasVerticalHoles = false;
				do
				{
					hasHorizontalHoles = myBoard.findHorizontalChains();
					hasVerticalHoles = myBoard.findVerticalChains();
					if(hasHorizontalHoles || hasVerticalHoles)
						myBoard.fillingHoles();
				} while (hasVerticalHoles || hasHorizontalHoles);
				myBoard.setStatus(CandyBoard::CandyGameStatus::IDLE);
				break;
		}

		myBoard.draw(myEngine);		
	}


private:
	King::Engine myEngine;
	CandyBoard myBoard;
	float swapFromX;
	float swapFromY;
	float swapToX;
	float swapToY;
	bool shouldSwap;
	bool swapping;
};

//**********************************************************************

int main(int argc, char *argv[])
{
	ExampleGame game;
	game.Start();

	return 0;
}


