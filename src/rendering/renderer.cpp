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
		sceneGraph.removeShape(shapeSelectedIndex);
		shapeSelectedIndex = -1;
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
	ofEnableDepthTest();
	cam.begin();
	for (auto & s : sceneGraph.getAllShapes()) {
		if (s.is3D == false) {
			shapeManager.convertTo3d(s);
		}
		s.mesh3D.draw();
	}
	cam.end();
	ofDisableDepthTest();
}

void Renderer::mousePressed(int x, int y, int button) {
	if (currentShape != "none") {
		startPoint.set(x, y);
		drawing = true;
	}
	if (selecting) {
		shapeSelectedIndex = sceneGraph.selectShapeAt(x, y);
		if (shapeSelectedIndex != -1) {
			shapeSelected = true;
		}
	}
}

void Renderer::mouseReleased(int x, int y, int button) {
	if (drawing) {
		endPoint.set(x, y);
		shapeManager.drawShape(currentShape, startPoint, endPoint);
		drawing = false;
	}
}

