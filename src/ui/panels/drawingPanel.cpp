// DrawingPanel.cpp
// Implémentation du panel de dessin
#include "DrawingPanel.h"

DrawingPanel::DrawingPanel() {
}

void DrawingPanel::setup() {
	// Setup du menu principal de dessin
	drawMenuPanel.setup("2D EDITION");
	drawMenuPanel.add(drawPointButton.setup("Draw a point"));
	drawMenuPanel.add(drawLineButton.setup("Draw a line"));
	drawMenuPanel.add(drawTriangleButton.setup("Draw a triangle | 3D view"));
	drawMenuPanel.add(drawSquareButton.setup("Draw a square | 3D view"));
	drawMenuPanel.add(drawRectangleButton.setup("Draw a rectangle | 3D view"));
	drawMenuPanel.add(drawCircleButton.setup("Draw a circle | 3D view"));
	drawMenuPanel.add(saveShapeButton.setup("Save shape"));
	drawMenuPanel.add(selectionButton.setup("Select/Interact"));
	drawMenuPanel.add(exportSequenceButton.setup("Export Sequence"));
	drawMenuPanel.add(exportImageButton.setup("Export Image"));

	// Listeners
	drawPointButton.addListener(this, &DrawingPanel::onDrawPointPressed);
	drawLineButton.addListener(this, &DrawingPanel::onDrawLinePressed);
	drawTriangleButton.addListener(this, &DrawingPanel::onDrawTrianglePressed);
	drawSquareButton.addListener(this, &DrawingPanel::onDrawSquarePressed);
	drawRectangleButton.addListener(this, &DrawingPanel::onDrawRectanglePressed);
	drawCircleButton.addListener(this, &DrawingPanel::onDrawCirclePressed);
	saveShapeButton.addListener(this, &DrawingPanel::onSaveShapePressed);
	selectionButton.addListener(this, &DrawingPanel::onSelectionPressed);
	exportSequenceButton.addListener(this, &DrawingPanel::onExportSequencePressed);
	exportImageButton.addListener(this, &DrawingPanel::onExportImagePressed);

	// Panel de suppression
	deletePanel.setup("Delete");
	deletePanel.add(deleteShapeButton.setup("Delete the shape"));
	deleteShapeButton.addListener(this, &DrawingPanel::onDeleteShapePressed);

	// Panel courbes intégré
	curvesPanel.setup("Curve Tools");
	curvesPanel.add(placePointsButton.setup("Place Points"));
	curvesPanel.add(generateBezierCurveButton.setup("Generate Bezier curve"));
	curvesPanel.add(clearCurvesButton.setup("Clear Curves"));
	curvesPanel.add(undoPointButton.setup("Undo point"));
	curvesPanel.add(clearPointsButton.setup("Clear points"));

	placePointsButton.addListener(this, &DrawingPanel::onPlacePointsPressed);
	generateBezierCurveButton.addListener(this, &DrawingPanel::onGenerateCurvePressed);
	clearCurvesButton.addListener(this, &DrawingPanel::onClearCurvesPressed);
	undoPointButton.addListener(this, &DrawingPanel::onUndoPointPressed);
	clearPointsButton.addListener(this, &DrawingPanel::onClearPointsPressed);

	// Setup des panels dédiés
	drawingParamsPanel.setup();
	transformPanel.setup();
}

void DrawingPanel::update() {
	// Logique d'update si nécessaire (export séquence, etc.)
}

void DrawingPanel::draw(float sideMenuWidth, float menuBarHeight) {
	if (!isActive) return;

	// Positionner et dessiner le menu principal
	drawMenuPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	drawMenuPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
	drawMenuPanel.draw();

	// Panel de courbes placé sous le menu principal
	float curvesY = menuBarHeight + drawMenuPanel.getHeight();
	curvesPanel.setPosition(ofGetWidth() - sideMenuWidth, curvesY);
	curvesPanel.setSize(sideMenuWidth, curvesPanel.getHeight());
	curvesPanel.draw();

	// Panel de suppression (si en mode sélection)
	if (selectionMode) {
		deletePanel.setPosition(ofGetWidth() - sideMenuWidth, curvesY + curvesPanel.getHeight());
		deletePanel.draw();
	}

	// Paramètres de dessin (à gauche)
	float panelWidth = ofGetWidth() / 6;
	float prochainY = menuBarHeight;

	drawingParamsPanel.draw(10, prochainY, panelWidth - 20);
	prochainY += 200 + 10; // Hauteur du panel + marge

	// Panel de transformation (si en mode sélection)
	if (selectionMode) {
		float windowWidth = ofGetWidth();
		float windowHeight = ofGetHeight() - menuBarHeight;
		transformPanel.show();
		transformPanel.draw(10, prochainY, panelWidth - 20, windowWidth, windowHeight);
	} else {
		transformPanel.hide();
	}
}

void DrawingPanel::reset() {
	// Réinitialiser l'état du panel lors du changement d'onglet
	currentShape = "none";
	selectionMode = false;
	saveShapeRequested = false;
	deleteShapeRequested = false;
	placePointsMode = false;
	generateCurveRequested = false;
	clearCurvesRequested = false;
	undoPointRequested = false;
	clearPointsRequested = false;

	ofLogNotice("DrawingPanel") << "Panel reset - ready for new interaction";
}

void DrawingPanel::clearRequests() {
	saveShapeRequested = false;
	deleteShapeRequested = false;
	generateCurveRequested = false;
	clearCurvesRequested = false;
	undoPointRequested = false;
	clearPointsRequested = false;
}

// ========== CALLBACKS ==========

void DrawingPanel::onDrawPointPressed() {
	currentShape = "point";
	selectionMode = false;
}

void DrawingPanel::onDrawLinePressed() {
	currentShape = "line";
	selectionMode = false;
}

void DrawingPanel::onDrawTrianglePressed() {
	currentShape = "triangle";
	selectionMode = false;
}

void DrawingPanel::onDrawSquarePressed() {
	currentShape = "square";
	selectionMode = false;
}

void DrawingPanel::onDrawRectanglePressed() {
	currentShape = "rectangle";
	selectionMode = false;
}

void DrawingPanel::onDrawCirclePressed() {
	currentShape = "circle";
	selectionMode = false;
}

void DrawingPanel::onSaveShapePressed() {
	saveShapeRequested = true;
}

void DrawingPanel::onDeleteShapePressed() {
	if (!selectionMode) return;
	deleteShapeRequested = true;
}

void DrawingPanel::onSelectionPressed() {
	selectionMode = true;
	currentShape = "none";
}

void DrawingPanel::onExportSequencePressed() {
	// TODO: Implémenter export séquence
	ofLogNotice("DrawingPanel") << "Export sequence requested";
}

void DrawingPanel::onExportImagePressed() {
	// TODO: Implémenter export image
	ofLogNotice("DrawingPanel") << "Export image requested";
}

void DrawingPanel::onPlacePointsPressed() {
	placePointsMode = !placePointsMode;
	ofLogNotice("DrawingPanel") << "Place points mode: " << (placePointsMode ? "ON" : "OFF");
}

void DrawingPanel::onGenerateCurvePressed() {
	generateCurveRequested = true;
	ofLogNotice("DrawingPanel") << "Generate Bezier curve requested";
}

void DrawingPanel::onClearCurvesPressed() {
	clearCurvesRequested = true;
	ofLogNotice("DrawingPanel") << "Clear curves requested";
}

void DrawingPanel::onUndoPointPressed() {
	undoPointRequested = true;
	ofLogNotice("DrawingPanel") << "Undo point requested";
}

void DrawingPanel::onClearPointsPressed() {
	clearPointsRequested = true;
	ofLogNotice("DrawingPanel") << "Clear points requested";
}
