#pragma once
#include "ofMain.h"
#include "../objects/shape.h"

class SceneGraph {
public:
	std::vector<Shape> shapes; 

	void addShape(const Shape& shape);
	void removeShape(int index);
	Shape * getShape(int index);
	void clear();
	std::vector<Shape> getAllShapes(); 

	int selectShapeAt(float x, float y);
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
