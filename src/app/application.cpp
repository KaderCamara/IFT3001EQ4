// IFT3100A25_BonjourMonde/application.cpp
// Classe principale de l'application.
//notre controller basically

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
}

void Application::draw()
{
  renderer.setDrawingArea(uiWindow.getDrawingArea());
  renderer.draw();
  uiWindow.draw();
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
