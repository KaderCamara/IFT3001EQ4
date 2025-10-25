#pragma once
#include "ofMain.h"
#include "../objects/shape.h"

class SceneGraph {
public:
	std::vector<Shape> shapes;
	std::vector<int> selectedIndices;

	void addShape(const Shape& shape);
	void removeShape(int index);
	Shape * getShape(int index);
	void clear();
	void removeSelectedShapes();
	std::vector<Shape> & getAllShapes();

	void selectShapeAt(float x, float y, bool addToSelection = false);
	void deselectAll();
	void updateSelectedAttributes(const ofColor & color, float size);

	void draw();

	//JORDAN: transformation functions
	void updateSelectedTransform(float tx, float ty, float rot, float scale);
	//3D IMPORT functions
	void setShapes(const std::vector<Shape> & newShapes);

	private:
	int selectedIndex = -1;
	bool insideBounds(const Shape & shape, float x, float y);
};
