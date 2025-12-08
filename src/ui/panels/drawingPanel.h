// DrawingPanel.h
// Panel responsable de la gestion du dessin de formes 2D/3D
#pragma once

#include "DrawingParametersPanel.h"
#include "TransformPanel.h"
#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class DrawingPanel
 * @brief Panel UI pour le dessin de formes primitives
 *
 * Responsabilités :
 * - Boutons de sélection de formes (point, ligne, triangle, carré, rectangle, cercle)
 * - Mode sélection/interaction
 * - Sauvegarde et suppression de formes
 * - Export d'images et séquences
 * - Délègue les paramètres de dessin à DrawingParametersPanel
 * - Délègue les transformations à TransformPanel
 */
class DrawingPanel {
public:
	DrawingPanel();
	~DrawingPanel() = default;

	void setup();
	void update();
	void draw(float sideMenuWidth, float menuBarHeight);

	// Accesseurs d'état
	std::string getCurrentShape() const { return currentShape; }
	bool isVisible() const { return isActive; }
	bool isSaveShapeRequested() const { return saveShapeRequested; }
	bool isDeleteShapeRequested() const { return deleteShapeRequested; }
	bool isSelectionMode() const { return selectionMode; }
	bool isPlacePointsMode() const { return placePointsMode; }
	bool isGenerateCurveRequested() const { return generateCurveRequested; }
	bool isClearCurvesRequested() const { return clearCurvesRequested; }
	bool isUndoPointRequested() const { return undoPointRequested; }
	bool isClearPointsRequested() const { return clearPointsRequested; }

	// Paramètres de dessin (délégués au DrawingParametersPanel)
	float getLineWidth() const { return drawingParamsPanel.getLineWidth(); }
	ofColor getStrokeColor() const { return drawingParamsPanel.getStrokeColor(); }
	ofColor getFillColor() const { return drawingParamsPanel.getFillColor(); }
	ofColor getBackgroundColor() const { return drawingParamsPanel.getBackgroundColor(); }
	bool isHSBMode() const { return drawingParamsPanel.isHSBMode(); }
	float getHue() const { return drawingParamsPanel.getHue(); }
	float getSaturation() const { return drawingParamsPanel.getSaturation(); }
	float getBrightness() const { return drawingParamsPanel.getBrightness(); }

	// Paramètres de transformation (délégués au TransformPanel)
	float getTranslateX() const { return transformPanel.getTranslateX(); }
	float getTranslateY() const { return transformPanel.getTranslateY(); }
	float getRotation() const { return transformPanel.getRotation(); }
	float getScale() const { return transformPanel.getScale(); }

	// Contrôle du panel
	void show() { isActive = true; }
	void hide() {
		isActive = false;
		reset();
	} // Réinitialise lors du masquage
	void toggle() { isActive = !isActive; }

	// Réinitialisation de l'état
	void reset();

	// Clear des requêtes
	void clearRequests();

	// Contrôle du mode courbes
	void setPlacePointsMode(bool mode) { placePointsMode = mode; }

private:
	// État du panel
	bool isActive = false;
	std::string currentShape = "none";
	bool saveShapeRequested = false;
	bool deleteShapeRequested = false;
	bool selectionMode = false;
	bool placePointsMode = false;
	bool generateCurveRequested = false;
	bool clearCurvesRequested = false;
	bool undoPointRequested = false;
	bool clearPointsRequested = false;

	// Panels dédiés (composition)
	DrawingParametersPanel drawingParamsPanel;
	TransformPanel transformPanel;

	// Panels ofxGui
	ofxPanel drawMenuPanel;
	ofxPanel deletePanel;
	ofxPanel curvesPanel;

	// Boutons de dessin
	ofxButton drawPointButton;
	ofxButton drawLineButton;
	ofxButton drawTriangleButton;
	ofxButton drawSquareButton;
	ofxButton drawRectangleButton;
	ofxButton drawCircleButton;
	ofxButton saveShapeButton;
	ofxButton deleteShapeButton;
	ofxButton selectionButton;
	ofxButton exportSequenceButton;
	ofxButton exportImageButton;
	ofxButton placePointsButton;
	ofxButton generateBezierCurveButton;
	ofxButton clearCurvesButton;
	ofxButton undoPointButton;
	ofxButton clearPointsButton;

	// Export
	bool exportSequenceActive = false;
	int exportFrameCount = 0;
	std::string exportFolder = "export";

	// Callbacks
	void onDrawPointPressed();
	void onDrawLinePressed();
	void onDrawTrianglePressed();
	void onDrawSquarePressed();
	void onDrawRectanglePressed();
	void onDrawCirclePressed();
	void onSaveShapePressed();
	void onDeleteShapePressed();
	void onSelectionPressed();
	void onExportSequencePressed();
	void onExportImagePressed();
	void onPlacePointsPressed();
	void onGenerateCurvePressed();
	void onClearCurvesPressed();
	void onUndoPointPressed();
	void onClearPointsPressed();
};
