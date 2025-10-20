#pragma once
#include "ofMain.h"
#include "../objects/shapeManager.h"

class SceneGraph {
public:
	using Shape = ShapeManager::Shape;
	std::vector<Shape> shapes; 

	void addShape(const Shape& shape);
	void removeShape(int index);
	Shape * getShape(int index);
	void clear();

	int selectShapeAt(float x, float y);
	void updateSelectedAttributes(const ofColor & color, float size);

	void draw();

	private:
	int selectedIndex = -1;
	bool insideBounds(const Shape & shape, float x, float y);
};
