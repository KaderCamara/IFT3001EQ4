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
	}
	if (!uiWindow.isSelectShapeRequested()) {
		renderer.selectingModeOff();
	}
	if (uiWindow.is3DviewRequested()) {
		renderer.view3DMode();
	}
	if (uiWindow.is2DviewRequested()) {
		renderer.view2DMode();
	}
	if (uiWindow.isQuadViewRequested()) {
		renderer.viewQuadMode();
	}

	uiWindow.clearRequests();
}

void Application::draw()
{
  renderer.setDrawingArea(uiWindow.getDrawingArea());
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
