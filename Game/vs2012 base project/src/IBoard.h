
class IBoard {

public:

	/*Struct to represent a point of window game.*/
	typedef struct MatrixCoords
	{
		int row;
		int col;
	} Coords;

	// pure virtual function
	virtual void init() = 0;
	virtual ~IBoard(){}

protected:
	unsigned int score;
	unsigned short ROWS;
	unsigned short COLS;
	unsigned short** board;
};