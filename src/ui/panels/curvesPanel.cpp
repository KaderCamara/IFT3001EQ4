// CurvesPanel.cpp
// Implémentation du panel de courbes de Bézier
#include "CurvesPanel.h"

CurvesPanel::CurvesPanel() {
}

void CurvesPanel::setup() {
	// Setup du menu courbes
	curvesPanel.setup("Curves Menu");
	curvesPanel.enableHeader();
	curvesPanel.minimize();
	curvesPanel.add(placePointsButton.setup("Place Points"));
	curvesPanel.add(generateBezierCurveButton.setup("Generate Bezier curve"));
	curvesPanel.add(clearCurvesButton.setup("Clear Curves"));
	curvesPanel.add(undoPointButton.setup("Undo point"));
	curvesPanel.add(clearPointsButton.setup("Clear points"));

	// Listeners
	placePointsButton.addListener(this, &CurvesPanel::onPlacePointsPressed);
	generateBezierCurveButton.addListener(this, &CurvesPanel::onGenerateCurvePressed);
	clearCurvesButton.addListener(this, &CurvesPanel::onClearCurvesPressed);
	undoPointButton.addListener(this, &CurvesPanel::onUndoPointPressed);
	clearPointsButton.addListener(this, &CurvesPanel::onClearPointsPressed);
}

void CurvesPanel::draw(float sideMenuWidth, float menuBarHeight) {
	if (!isActive) return;

	// Positionner et dessiner le panel
	curvesPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	curvesPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
	curvesPanel.draw();
}

void CurvesPanel::clearRequests() {
	generateCurveRequested = false;
	clearCurvesRequested = false;
	undoPointRequested = false;
	clearPointsRequested = false;
}

void CurvesPanel::reset() {
	// Réinitialiser l'état du panel lors du changement d'onglet
	placePointsMode = false;
	generateCurveRequested = false;
	clearCurvesRequested = false;
	undoPointRequested = false;
	clearPointsRequested = false;
	ofLogNotice("CurvesPanel") << "Panel reset - ready for new interaction";
}
// ========== CALLBACKS ==========

void CurvesPanel::onPlacePointsPressed() {
	placePointsMode = !placePointsMode;
	ofLogNotice("CurvesPanel") << "Place points mode: " << (placePointsMode ? "ON" : "OFF");
}

void CurvesPanel::onGenerateCurvePressed() {
	generateCurveRequested = true;
	ofLogNotice("CurvesPanel") << "Generate Bezier curve requested";
}

void CurvesPanel::onClearCurvesPressed() {
	clearCurvesRequested = true;
	ofLogNotice("CurvesPanel") << "Clear curves requested";
}

void CurvesPanel::onUndoPointPressed() {
	undoPointRequested = true;
	ofLogNotice("CurvesPanel") << "Undo point requested";
}

void CurvesPanel::onClearPointsPressed() {
	clearPointsRequested = true;
	ofLogNotice("CurvesPanel") << "Clear points requested";
}
