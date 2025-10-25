// IFT3100A25_BonjourMonde/application.cpp
// Classe principale de l'application.
//notre controller basically il va uniquement se charger de la communication entre renderer et uiWindow
//de ce fait ces instances sont créés une seule fois ( un seul cycle de vie )

#include "application.h"

// fonction appelée à l'initialisation de l'application
void Application::setup()
{
  ofSetWindowTitle("3D app");

  ofLog() << "<app::setup>";

  renderer.setup();
  uiWindow.setup();
}

void Application::update() {
	uiWindow.update();

	if (uiWindow.isSaveShapeRequested()) {
		renderer.setCurrentShape(uiWindow.getCurrentShape());
		renderer.save();
	}

	if (uiWindow.isDeleteShapeRequested()) {
		renderer.deleteShape();
	}

	if (uiWindow.isSelectShapeRequested()) {
		renderer.selectingModeOn();
	} else {
		renderer.selectingModeOff();
	}

	if (uiWindow.isQuadViewRequested()) {
		renderer.viewQuadMode();
	} else if (uiWindow.is3DviewRequested()) {
		renderer.view3DMode();
	} else if (uiWindow.is2DviewRequested()) {
		renderer.view2DMode();
	}

	// 3D IMPORT
	if (uiWindow.isImport3DModelRequested()) {
		renderer.import3DModel();
		renderer.view3DMode();
		uiWindow.clearImport3DModelRequest();
	}

	if (uiWindow.isClear3DModelRequested()) {
		renderer.clear3DModels();
		uiWindow.clearClear3DModelRequest();
	}

	uiWindow.clearRequests();
}

void Application::draw() {
	renderer.setDrawingArea(uiWindow.getDrawingArea());

	renderer.applyDrawingParameters(
		uiWindow.getLineWidth(),
		uiWindow.getStrokeColor(),
		uiWindow.getFillColor(),
		uiWindow.getBackgroundColor(),
		uiWindow.isHSBMode(),
		uiWindow.getHue(),
		uiWindow.getSaturation(),
		uiWindow.getBrightness());
	renderer.updateShapeManagerParams(
		uiWindow.getLineWidth(),
		uiWindow.getStrokeColor(),
		uiWindow.getFillColor());
	uiWindow.getBackgroundColor();

	renderer.applyTransformationToSelectedShape(
		uiWindow.getTranslateX(),
		uiWindow.getTranslateY(),
		uiWindow.getRotation(),
		uiWindow.getScale());

  renderer.draw();
  uiWindow.draw();
}


void Application::keyPressed(int key) {
	renderer.keyPressed(key);
}

void Application::mousePressed(int x, int y, int button) {
	if (uiWindow.getDrawingArea().inside(x, y)) {
		renderer.setCurrentShape(uiWindow.getCurrentShape());
		renderer.mousePressed(x, y, button);
	} else {
		uiWindow.mousePressed(x, y, button);
	}
}

void Application::mouseReleased(int x, int y, int button) {
	if (uiWindow.getDrawingArea().inside(x, y)) {
		renderer.mouseReleased(x, y, button);
	} else {
		uiWindow.mouseReleased(x, y, button);
	}
}



void Application::dragEvent(ofDragInfo dragInfo) {
	uiWindow.handleFileDragAndDrop(dragInfo);
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
