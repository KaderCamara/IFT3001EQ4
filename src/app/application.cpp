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
  renderer.draw();
  uiWindow.draw();
}

void Application::mousePressed(int x, int y, int button) {
	uiWindow.mousePressed(x, y, button);
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
