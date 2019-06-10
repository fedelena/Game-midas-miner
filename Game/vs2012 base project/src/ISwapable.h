class ISwapable {

public:

	// pure virtual function
	virtual void swap(float fromX, float fromY, float toX, float toY) = 0;
	virtual ~ISwapable(){}
};