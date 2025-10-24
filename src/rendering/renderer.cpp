// IFT3100A25_BonjourMonde/renderer.cpp
// Classe responsable du rendu de l'application.  dessins etc

#include "renderer.h"
#include <cfloat>

bool g_showBoundingBox = false;
bool g_showWireframe = false;

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
	ofEnableDepthTest();
	cam.begin();

	for (auto & s : sceneGraph.getAllShapes()) {
		ofPushStyle();

		if (!s.is3D) {
			shapeManager.convertTo3d(s);
		}

		if (g_showWireframe) {
			ofNoFill();
			s.mesh3D.drawWireframe();
		} else {
			ofFill();
			ofSetColor(s.color);
			s.mesh3D.draw();
		}

		if (g_showBoundingBox) {
			ofNoFill();
			ofSetColor(ofColor::red);
			drawBoundingBox(s.mesh3D);
		}

		ofPopStyle();
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

void Renderer::drawBoundingBox(const ofMesh & mesh) {
	ofVec3f min(FLT_MAX, FLT_MAX, FLT_MAX);
	ofVec3f max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (auto & v : mesh.getVertices()) {
		min.x = std::min(min.x, v.x);
		min.y = std::min(min.y, v.y);
		min.z = std::min(min.z, v.z);

		max.x = std::max(max.x, v.x);
		max.y = std::max(max.y, v.y);
		max.z = std::max(max.z, v.z);
	}

	ofNoFill();
	ofSetColor(ofColor::red);
	ofDrawBox((min + max) / 2, max.x - min.x, max.y - min.y, max.z - min.z);
	ofFill();
}
