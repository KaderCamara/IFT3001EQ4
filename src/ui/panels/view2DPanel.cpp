// src/ui/panels/view2DPanel.cpp
#include "view2DPanel.h"

void View2DPanel::setup() {
	navigationPanel.setup("2D Sections");
	navigationPanel.enableHeader();
	navigationPanel.minimize();
	navigationPanel.add(drawButton.setup("Draw"));
	navigationPanel.add(curvesButton.setup("Curves"));

	drawButton.addListener(this, &View2DPanel::onDrawButton);
	curvesButton.addListener(this, &View2DPanel::onCurvesButton);

	drawingPanel.setup();
	curvesPanel.setup();
}

void View2DPanel::draw(float sideMenuWidth, float menuBarHeight) {
	if (!isActive) return;

	float panelX = ofGetWidth() - sideMenuWidth;
	float currentY = menuBarHeight;

	// Toujours afficher le navigationPanel (2D Sections) en haut
	navigationPanel.setPosition(panelX, currentY);
	navigationPanel.setSize(sideMenuWidth, navigationPanel.getHeight());
	navigationPanel.draw();
	currentY += navigationPanel.getHeight() + 10.0f;

	// Afficher le panel actif en dessous
	switch (currentMode) {
	case Mode::Draw:
		drawingPanel.draw(panelX, currentY, sideMenuWidth);
		break;
	case Mode::Curves:
		curvesPanel.draw(panelX, currentY, sideMenuWidth);
		break;
	default:
		break;
	}
}

void View2DPanel::clearRequests() {
	drawingPanel.clearRequests();
	curvesPanel.clearRequests();
}

void View2DPanel::reset() {
	currentMode = Mode::Navigation;
	activeSection = Section::Draw;
	drawingPanel.clearRequests();
	curvesPanel.clearRequests();
	ofLogNotice("View2DPanel") << "Panel reset";
}

void View2DPanel::onDrawButton() {
	currentMode = Mode::Draw;
}

void View2DPanel::onCurvesButton() {
	currentMode = Mode::Curves;
}

void View2DPanel::onSectionButtonPressed(Section section) {
	activeSection = section;
	// Ne plus appeler drawingPanel.show()/hide() ici, on laisse le navigationPanel toujours visible
}
