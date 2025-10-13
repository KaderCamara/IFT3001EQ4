#include "ofMain.h"

class ShapeManager {
public:
	void drawShape(const std::string & type, const ofPoint & start, const ofPoint & end);
	void draw();

private:
	struct Shape {
		std::string type;
		ofPoint start, end;
	};

	Shape currentShapeToDraw = { "x", { 0, 0 }, { 0, 0 } };
};
