#include <stdlib.h> 
#include <cassert>
#include "CandyBoard.h"


unsigned short CandyBoard::getStatus() const
{
	return gameStatus;
}

unsigned int CandyBoard::getScore() const
{
	return score;
}


void CandyBoard::setStatus(CandyBoard::CandyGameStatus state)
{
	gameStatus = state;
}


/*
This function fills the elements of the matrix with a random candy color
and verifies that the matches are not formed.
*/
void CandyBoard::init()
{
	//Load candies, randomize their colors
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
				board[row][col] = getRandomColor(col, row);	
		}
	}
}


/*
This function is in charge of drawing in the screen all candies based on matrix values 
using kinglib engine.
*/
void CandyBoard::draw(King::Engine& e)
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			// calculate position
			Position position = convertCoordsToPixels(row, col);
			e.Render(convertColorToTexture(board[row][col]), position.x, position.y);
		}
	}
}


/*
This function performs the exchange of candies after having controlled that the movement is valid.
*/
void CandyBoard::swap(float fromX, float fromY, float toX, float toY)
{	
	Coords from = convertPixelsToCoords(fromX, fromY);
	Coords to = convertPixelsToCoords(toX, toY);

	if (to.row >= 0 && to.row < ROWS && to.col >= 0 && to.col < COLS)
	{
		if (board[to.row][to.col] == NULL || board[from.row][from.col] == NULL)
		{
			//empty cell, invalid move
			return;
		}

		//if this is not set, it means previous click was at some invalid position
		if (from.col >= 0)
		{
			//check that we're not clicking on the same rock as previously clicked
			if (from.col == to.col && from.row == to.row)
			{
				//Since we released the mouse in the same position, we're NOT swiping
				return;
			}
			
			int deltaX = std::abs(to.col - from.col); 
			int deltaY = std::abs(to.row - from.row); 
			
			if (deltaX > 1 || deltaY > 1)
			{
				//invalid move... 
				return;
			}

			//Try to swap the rocks
			unsigned short toColor = board[to.row][to.col];
			board[to.row][to.col] = board[from.row][from.col];
			board[from.row][from.col] = toColor;
		}
	}
	// else: invalid position.
}
	
/*
After all the matches were eliminated, this function performs the filling of the holes of the board 
with the corresponding candies, depending on whether it is the first row or a downward displacement.
*/
void CandyBoard::fillingHoles()
{
	fillChainHoles();
	fillTop();	
}


//////  Private Functions   ///////


/*
This functions performs a mappong between candy color and engine texture. This is used when the board is drawed.
*/
King::Engine::Texture CandyBoard::convertColorToTexture(unsigned short color)
{
	King::Engine::Texture texture = King::Engine::TEXTURE_BLUE;

	switch (color)
	{
	case CandyColor::BLUE:
		texture = King::Engine::TEXTURE_BLUE;
		break;
	case CandyColor::GREEN:
		texture = King::Engine::TEXTURE_GREEN;
		break;
	case CandyColor::PURPLE:
		texture = King::Engine::TEXTURE_PURPLE;
		break;
	case CandyColor::RED:
		texture = King::Engine::TEXTURE_RED;
		break;
	case CandyColor::YELLOW:
		texture = King::Engine::TEXTURE_YELLOW;
	}
	return texture;
}


/*
This function refill holes into the matrix.
*/
void CandyBoard::fillTop()
{
	for (int col = 0; col < COLS; col++)
	{
		for (int row = 0; row < ROWS && board[row][col] == NULL; row++)
		{
			board[row][col] = getRandomColor(col, row);
		}
	}
}


/*
This function completes the holes into the matrix with the correct candy
simulating the cascade effect.
*/
void CandyBoard::fillChainHoles()
{
	for (int col = 0; col < COLS; col++)
	{
		//scan bottom-up for holes
		for (int row = ROWS - 1; row >= 0; row--)
		{
			if (board[row][col] == NULL)
			{
				//found a hole, lookup the next candy upwards
				for (int lookup = row - 1; lookup >= 0; lookup--)
				{
					unsigned short candy = board[lookup][col];
					if (candy != NULL)
					{
						//push down the candy
						board[lookup][col] = NULL;
						board[row][col] = candy;
						break;
					}
				}
			}
		}
	}
	fillTop();
}


/*
This function checks on each row if there are matches.
@returns: true if there is at least a match, false in otherwise.
*/
bool CandyBoard::findHorizontalChains()
{
	bool hasHoles = false;
	for (int row = 0; row < ROWS; row++)
	{
		//Don't need to check the last 2 columns, we could get out of bounds
		for (int col = 0; col < COLS-2;)
		{
			//check that coordinate has a valid candy
			if (board[row][col] != NULL)
			{
				//get current rock color to match neighbors' color
				unsigned short matchColor = board[row][col];
				
				if (board[row][col + 1] && 
					board[row][col + 1] == matchColor &&
					board[row][col + 2] && 
					board[row][col + 2] == matchColor)
				{
					//So we have at least 3 with the same color
					// Removes chain
					unsigned int count = 0;
					do {
						board[row][col] = NULL;
						col++;
						count++;
					} while (col < COLS && board[row][col] && board[row][col] == matchColor);
					hasHoles = true;
					score += count;
				}
			}
			col++;
		}
	}
	return hasHoles;
}


/*
This function checks on each column if there are matches.
@returns: true if there is at least a match, false in otherwise.
*/
bool CandyBoard::findVerticalChains()
{
	bool hasHoles = false;
	for (int col = 0; col < COLS; col++)
	{
		//Don't need to check the last 2 rows, we could get out of bounds
		for (int row = 0; row < ROWS - 2;)
		{
			//check that coordinate has a valid candy
			if (board[row][col] != NULL)
			{
				//get current rock color to match neighbors' color
				unsigned short matchColor = board[row][col];

				if (board[row + 1][col] &&
					board[row + 1][col] == matchColor &&
					board[row + 2][col] &&
					board[row + 2][col] == matchColor)
				{
					//So we have at least 3 with the same color
					//create a chain object and fill it with candies
					unsigned int count = 0;
					do {
						board[row][col] = NULL;
						row++;
						count++;
					} while (row < ROWS && board[row][col] && board[row][col] == matchColor);
					hasHoles = true;
					score += count;
				}
			}
			row++;
		}
	}
	return hasHoles;
}



/*
This function controls the exchange allows to have a match or not.
@returns: true if there is at least a match, false in otherwise.
*/
bool CandyBoard::checkSwap(float y, float x)
{	
	Coords c = convertPixelsToCoords(x, y);
	
	assert(c.col >= 0 && c.row >= 0);

	unsigned short color = board[c.row][c.col];
	int hLen = 1;
	int vLen = 1;

	//check for horizontal chains
	//while candy is not null and its color is equal to matching color, increment hLen or vLen
	for (int i = c.col - 1; i >= 0 && board[c.row][i] && board[c.row][i] == color; i--, hLen++);
	for (int i = c.col + 1; i < COLS && board[c.row][i] && board[c.row][i] == color; i++, hLen++);
	if (hLen >= 3) return true;

	//check for vertical chains
	for (int i = c.row - 1; i >= 0 && board[i][c.col] && board[i][c.col] && board[i][c.col] == color; i--, vLen++);
	for (int i = c.row + 1; i < ROWS && board[i][c.col] && board[i][c.col] == color; i++, vLen++);
	return (vLen >= 3);
}



/*
This function controls the exchange allows to have a match or not. This new color should not create a chain (match).
@returns: A number which it represents a candy color based on CandyColor enum type. False in otherwise.
*/
unsigned short CandyBoard::getRandomColor(int col, int row) const
{
	unsigned short color;

	//Try to get a color that does not produce a chain (3 or more of the same color)
	//useful when loading, so we don't present any pre-loaded chains
	do {
		color = CandyBoard::CandyColor::BLUE + (rand() % 5);
	} while (
		(col >= 2 &&
		board[row][col - 1] == color &&
		board[row][col - 2] == color)
		||
		(row >= 2 &&
		board[row - 1][col] == color &&
		board[row - 2][col] == color));

	return color;
}


/*
Converts a point into window game to a pair of row and column into board representation.
@returns: a pair row, column.
*/
CandyBoard::Coords CandyBoard::convertPixelsToCoords(float x, float y)
{
	assert(x >= 0 && y >= 0);
	Coords c;
	c.row = int((y - OFFSET_Y) / (CANDY_HEIGHT + PIXEL_SEPARATION));
	c.col = int((x - OFFSET_X) / (CANDY_WIDTH + PIXEL_SEPARATION));
	return c;
}


/*
Converts a pair of row and column from board representation to a point of window game screen.
@returns: a pair x, y.
*/
CandyBoard::Position CandyBoard::convertCoordsToPixels(unsigned short row, unsigned short col) 
{
	CandyBoard::Position result;
	result.x = float(OFFSET_X + (col * CANDY_WIDTH) + (PIXEL_SEPARATION * col));
	result.y = float(OFFSET_Y + (row * CANDY_HEIGHT) + (PIXEL_SEPARATION * row));
	return result;
}
