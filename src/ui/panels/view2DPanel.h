// src/ui/panels/view2DPanel.h
#pragma once

#include "DrawingPanel.h"
#include "curvesPanel.h"
#include "ofMain.h"
#include "ofxGui.h"

class View2DPanel {
public:
	View2DPanel() = default;
	~View2DPanel() = default;

	void setup();
	void draw(float sideMenuWidth, float menuBarHeight);
	void clearRequests();
	void reset();

	// Accesseurs
	bool isVisible() const { return isActive; }
	void show() { isActive = true; }
	void hide() { isActive = false; }

	// Mode actuel
	bool isDrawModeActive() const { return activeSection == Section::Draw; }
	bool isCurvesModeActive() const { return activeSection == Section::Curves; }

	// Accesseurs DrawingPanel
	std::string getCurrentShape() const { return drawingPanel.getCurrentShape(); }
	bool isSaveShapeRequested() const { return drawingPanel.isSaveShapeRequested(); }
	bool isDeleteShapeRequested() const { return drawingPanel.isDeleteShapeRequested(); }
	bool isSelectShapeRequested() const { return drawingPanel.isSelectionMode(); }
	float getLineWidth() const { return drawingPanel.getLineWidth(); }
	ofColor getStrokeColor() const { return drawingPanel.getStrokeColor(); }
	ofColor getFillColor() const { return drawingPanel.getFillColor(); }
	ofColor getBackgroundColor() const { return drawingPanel.getBackgroundColor(); }
	float getTranslateX() const { return drawingPanel.getTranslateX(); }
	float getTranslateY() const { return drawingPanel.getTranslateY(); }
	float getRotation() const { return drawingPanel.getRotation(); }
	float getScale() const { return drawingPanel.getScale(); }

	// Accesseurs CurvesPanel
	bool isPlacePointsMode() const { return curvesPanel.isPlacePointsMode(); }
	bool isGenerateCurveRequested() const { return curvesPanel.isGenerateCurveRequested(); }
	bool isClearCurvesRequested() const { return curvesPanel.isClearCurvesRequested(); }
	bool isUndoPointRequested() const { return curvesPanel.isUndoPointRequested(); }
	bool isClearPointsRequested() const { return curvesPanel.isClearPointsRequested(); }
	void disablePlacePointsMode() { curvesPanel.setPlacePointsMode(false); }
	void clearGenerateCurveRequest() { curvesPanel.clearRequests(); }
	void clearClearCurvesRequest() { curvesPanel.clearRequests(); }
	void clearUndoPointRequest() { curvesPanel.clearRequests(); }
	void clearClearPointsRequest() { curvesPanel.clearRequests(); }

private:
	enum class Section {
		Draw,
		Curves
	};

	enum class Mode {
		Navigation,
		Draw,
		Curves
	};

	bool isActive = false;
	Section activeSection = Section::Draw;
	Mode currentMode = Mode::Navigation;

	ofxPanel navigationPanel;
	ofxButton drawButton;
	ofxButton curvesButton;

	DrawingPanel drawingPanel;
	CurvesPanel curvesPanel;

	void onDrawButton();
	void onCurvesButton();
	void onSectionButtonPressed(Section section);
};
