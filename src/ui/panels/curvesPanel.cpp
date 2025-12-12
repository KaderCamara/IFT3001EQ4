// src/ui/panels/curvesPanel.cpp
#include "curvesPanel.h"

void CurvesPanel::setup() {
	curvesPanel.setup("Curve Tools");
	curvesPanel.enableHeader();
	curvesPanel.minimize();
	curvesPanel.add(placePointsButton.setup("Place Points"));
	curvesPanel.add(generateBezierCurveButton.setup("Generate Bezier curve"));
	curvesPanel.add(clearCurvesButton.setup("Clear Curves"));
	curvesPanel.add(undoPointButton.setup("Undo point"));
	curvesPanel.add(clearPointsButton.setup("Clear points"));

	curvesPanel.add(playAnimationButton.setup("Play Animation"));
	curvesPanel.add(stopAnimationButton.setup("Stop Animation"));

	placePointsButton.addListener(this, &CurvesPanel::onPlacePointsPressed);
	generateBezierCurveButton.addListener(this, &CurvesPanel::onGenerateCurvePressed);
	clearCurvesButton.addListener(this, &CurvesPanel::onClearCurvesPressed);
	undoPointButton.addListener(this, &CurvesPanel::onUndoPointPressed);
	clearPointsButton.addListener(this, &CurvesPanel::onClearPointsPressed);

	playAnimationButton.addListener(this, &CurvesPanel::onPlayAnimation);
	stopAnimationButton.addListener(this, &CurvesPanel::onStopAnimation);
}

void CurvesPanel::draw(float x, float y, float width) {
    curvesPanel.setPosition(x, y);
    curvesPanel.setSize(width, curvesPanel.getHeight());
    curvesPanel.draw();
}

void CurvesPanel::clearRequests() {
	generateCurveRequested = false;
	clearCurvesRequested = false;
	undoPointRequested = false;
	clearPointsRequested = false;

	playAnimationRequested = false;
	stopAnimationRequested = false;
}

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

void CurvesPanel::onPlayAnimation() {
	playAnimationRequested = true;
	ofLogNotice("CurvesPanel") << "Play animation requested";
}

void CurvesPanel::onStopAnimation() {
	stopAnimationRequested = true;
	ofLogNotice("CurvesPanel") << "Stop animation requested";
}
