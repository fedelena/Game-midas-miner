#include <king/Engine.h>

class IDrawable {

public:
	/*This struct represents a point or position into window game screen.*/
	typedef struct PositionType
	{
		float x;
		float y;
	} Position;

	// pure virtual function
	virtual void draw(King::Engine& e) = 0;
	virtual ~IDrawable(){}
};