#include "shapeManager.h"
#include <rendering/ProceduralTexture.h>


void ShapeManager::setDrawingParameters(float lineW, ofColor stroke, ofColor fill) {
	lineWidth = lineW;
	strokeColor = stroke;
	fillColor = fill;
}


void ShapeManager::drawShape(const std::string & type, const ofPoint & start, const ofPoint & end) {
	currentShapeToDraw.type = type;
	currentShapeToDraw.start = start;
	currentShapeToDraw.end = end;
	currentShapeToDraw.color = fillColor;
}

void ShapeManager::deleteCurrentShapeToDraw() {
	currentShapeToDraw = {
		"x", { 0, 0 }, { 0, 0 }
	};
}

void ShapeManager::convertTo3d(Shape & shape) {
	shape.is3D = true;
	shape.mesh3D = shapeManager3D.to3DDraw(shape);

	// texture procédurale
	if (!shape.proceduralTexture.isAllocated()) {
		shape.proceduralTexture = generateSimpleProceduralTexture(128, 128);
	}
}
