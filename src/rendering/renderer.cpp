// IFT3100A25_BonjourMonde/renderer.cpp
// Classe responsable du rendu de l'application.  dessins etc

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetWindowShape(512, 512);
}

void Renderer::draw(){
	if (view3D) {
		draw3D();
	} else {
		sceneGraph.draw();
		if (currentShape != "none") {
			shapeManager.draw();
		}
	}
}

void Renderer::save() {
	sceneGraph.addShape(shapeManager.getCurrentShape());
}

void Renderer::deleteShape() {
	if (shapeSelected) {
		sceneGraph.removeSelectedShapes();
		shapeSelected = false;
	} else {
		cout << "no shape was selected" << endl;
		;
	}
}

void Renderer::selectingModeOn() {
	selecting = true;
	shapeManager.deleteCurrentShapeToDraw();
}

void Renderer::selectingModeOff() {
	selecting = false;
}

void Renderer::view3DMode() {
	view3D = true;
}

void Renderer::draw3D() {
	for (auto & s : sceneGraph.getAllShapes()) {
		if (!s.is3D) {
			shapeManager.convertTo3d(s, 2.0);
		}
		s.mesh3D.draw();
	}
}

void Renderer::mousePressed(int x, int y, int button) {
	if (currentShape != "none") {
		startPoint.set(x, y);
		drawing = true;
	}
	if (selecting) {
		sceneGraph.selectShapeAt(x, y, ofGetKeyPressed(OF_KEY_CONTROL) || ofGetKeyPressed(OF_KEY_COMMAND));
		shapeSelected = !sceneGraph.selectedIndices.empty();
		}
	}


void Renderer::mouseReleased(int x, int y, int button) {
	if (drawing) {
		endPoint.set(x, y);
		shapeManager.drawShape(currentShape, startPoint, endPoint);
		drawing = false;
	}
}

