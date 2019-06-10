#pragma once

#include <vector>
#include "IBoard.h"
#include "IDrawable.h"
#include "ISwapable.h"

using namespace std;


/*
Class which it represent Candy Crush game
*/
class CandyBoard : public IBoard, public IDrawable, public ISwapable
{
public:	
	
	/* This enum represents different kinds of candies */
	static enum CandyColor { BLUE=1, GREEN, PURPLE, RED, YELLOW };
	static const int CANDY_WIDTH = 35;
	static const int CANDY_HEIGHT = 35;

	static const int PIXEL_SEPARATION = 10;

	// Size of background
	static const int WIDTH = 800;
	static const int HEIGHT = 600;

	// Offset of candy board into the window game.
	static const int OFFSET_X = 345;
	static const int OFFSET_Y = 100;

	static enum CandyGameStatus {IDLE=1, SWAPING, CHECKING, FILLING};

	//Default Constructor
	CandyBoard()
	{
		score = 0;
		ROWS = COLS = 8;
		
		// Allocs memory for baord matrix
		board = new unsigned short*[ROWS];
		for(unsigned int i = 0; i < ROWS; ++i)
			board[i] = new unsigned short[COLS];

		gameStatus = CandyGameStatus::IDLE;
		init();
	}

	//Constructor with params
	CandyBoard(unsigned short r, unsigned short c)
	{
		score = 0;
		ROWS = r;
		COLS = c;
		
		// Allocs memory for baord matrix
		board = new unsigned short*[ROWS];
		for(unsigned int i = 0; i < ROWS; ++i)
			board[i] = new unsigned short[COLS];

		gameStatus = CandyGameStatus::IDLE;
		init();
	}

	// Destructor
	virtual ~CandyBoard()
	{
		// Deletes memory allocated for baord matrix
		for(unsigned int i = 0; i < ROWS; ++i)
		{
			delete[] board[i];
		}
		delete[] board;
	}


	virtual void init();
	virtual void draw(King::Engine& e);
	virtual void swap(float fromX, float fromY, float toX, float toY);
	unsigned int getScore() const;
	unsigned short getStatus() const;
	void setStatus(CandyGameStatus state);
	void fillingHoles();
	bool findHorizontalChains();
	bool findVerticalChains();
	bool checkSwap(float y, float x);

private:
	CandyGameStatus gameStatus;
	Coords convertPixelsToCoords(float x, float y);
	Position convertCoordsToPixels(unsigned short row, unsigned short col);
	King::Engine::Texture convertColorToTexture(unsigned short color);
	unsigned short getRandomColor(int col, int row) const;
	void fillChainHoles();
	void fillTop();
	
};