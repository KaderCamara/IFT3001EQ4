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
	for (auto & s : sceneGraph.getAllShapes()) {
		if (!s.is3D) {
			shapeManager.convertTo3d(s, 2.0);
			s.is3D = true;
		}

		s.mesh3D.drawWireframe();

		if (showBoundingBoxes) {
			ofPushStyle();
			ofNoFill();
			ofSetColor(255, 0, 0);
			ofBoxPrimitive bbox = computeBoundingBox(s.mesh3D);
			bbox.drawWireframe();
			ofPopStyle();
		}
	}
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

void Renderer::toggleBoundingBoxes() {
	showBoundingBoxes = !showBoundingBoxes;
}

ofBoxPrimitive Renderer::computeBoundingBox(const ofMesh & mesh) {
	ofVec3f minPt(FLT_MAX, FLT_MAX, FLT_MAX);
	ofVec3f maxPt(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (auto & v : mesh.getVertices()) {
		minPt.x = std::min(minPt.x, v.x);
		minPt.y = std::min(minPt.y, v.y);
		minPt.z = std::min(minPt.z, v.z);
		maxPt.x = std::max(maxPt.x, v.x);
		maxPt.y = std::max(maxPt.y, v.y);
		maxPt.z = std::max(maxPt.z, v.z);
	}

	ofVec3f center = (minPt + maxPt) * 0.5f;
	ofVec3f size = maxPt - minPt;

	ofBoxPrimitive box;
	box.set(size.x, size.y, size.z);
	box.setPosition(center);

	return box;
}
