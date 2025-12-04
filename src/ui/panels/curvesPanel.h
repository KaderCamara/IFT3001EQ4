// CurvesPanel.h
// Panel responsable de la gestion des courbes de Bézier
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class CurvesPanel
 * @brief Panel UI pour la gestion des courbes de Bézier
 * 
 * Responsabilités :
 * - Placer des points de contrôle
 * - Générer des courbes de Bézier
 * - Undo/Clear des points
 * - Clear des courbes
 */
class CurvesPanel {
public:
	CurvesPanel();
	~CurvesPanel() = default;

	void setup();
	void draw(float sideMenuWidth, float menuBarHeight);

	// Accesseurs d'état
	bool isVisible() const { return isActive; }
	bool isPlacePointsMode() const { return placePointsMode; }
	bool isGenerateCurveRequested() const { return generateCurveRequested; }
	bool isClearCurvesRequested() const { return clearCurvesRequested; }
	bool isUndoPointRequested() const { return undoPointRequested; }
	bool isClearPointsRequested() const { return clearPointsRequested; }

	// Contrôle du panel
	void show() { isActive = true; }
	void hide() { isActive = false; }
	void toggle() { isActive = !isActive; }

	// Contrôle du mode placement de points
	void setPlacePointsMode(bool mode) { placePointsMode = mode; }

	// Reset state
	void reset();

	// Clear des requêtes
	void clearRequests();

private:
	// État du panel
	bool isActive = false;
	bool placePointsMode = false;
	bool generateCurveRequested = false;
	bool clearCurvesRequested = false;
	bool undoPointRequested = false;
	bool clearPointsRequested = false;

	// Panel ofxGui
	ofxPanel curvesPanel;

	// Boutons
	ofxButton placePointsButton;
	ofxButton generateBezierCurveButton;
	ofxButton clearCurvesButton;
	ofxButton undoPointButton;
	ofxButton clearPointsButton;

	// Callbacks
	void onPlacePointsPressed();
	void onGenerateCurvePressed();
	void onClearCurvesPressed();
	void onUndoPointPressed();
	void onClearPointsPressed();
};
