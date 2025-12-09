#pragma once

#include "DrawingParametersPanel.h"
#include "TransformPanel.h"
#include "VectorEditionPanel.h"
#include "ofMain.h"
#include "ofxGui.h"
#include <string>

/**
 * @class DrawingPanel
 * @brief UI panel responsible for managing all 2D drawing interactions.
 */
class DrawingPanel {
public:
	DrawingPanel();
	~DrawingPanel() = default;

	void setup();
	void update();
	void draw(float sideMenuWidth, float menuBarHeight);

	// State accessors
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

	// Drawing parameters
	float getLineWidth() const { return drawingParamsPanel.getLineWidth(); }
	ofColor getStrokeColor() const { return drawingParamsPanel.getStrokeColor(); }
	ofColor getFillColor() const { return drawingParamsPanel.getFillColor(); }
	ofColor getBackgroundColor() const { return drawingParamsPanel.getBackgroundColor(); }
	bool isHSBMode() const { return drawingParamsPanel.isHSBMode(); }
	float getHue() const { return drawingParamsPanel.getHue(); }
	float getSaturation() const { return drawingParamsPanel.getSaturation(); }
	float getBrightness() const { return drawingParamsPanel.getBrightness(); }

	// Transformation parameters
	float getTranslateX() const { return transformPanel.getTranslateX(); }
	float getTranslateY() const { return transformPanel.getTranslateY(); }
	float getRotation() const { return transformPanel.getRotation(); }
	float getScale() const { return transformPanel.getScale(); }

	// Panel visibility
	void show() { isActive = true; }
	void hide();
	void toggle() { isActive = !isActive; }

	// State management
	void reset();
	void clearRequests();

	// Curve mode control
	void setPlacePointsMode(bool mode) { placePointsMode = mode; }

private:
	// State flags
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

	// Sub-panels
	DrawingParametersPanel drawingParamsPanel;
	TransformPanel transformPanel;
	VectorEditionPanel vectorEditionPanel;

	// ofxGui panels
	ofxPanel drawMenuPanel;
	ofxPanel deletePanel;
	ofxPanel curvesPanel;

	// Drawing buttons
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

	// Export helpers
	bool exportSequenceActive = false;
	int exportFrameCount = 0;
	std::string exportFolder = "export";

	// Layout helpers
	float leftMargin = 10.0f;
	float verticalSpacing = 10.0f;

	// Internal helpers
	void setCurrentShape(const std::string & shapeName);
	void enableSelectionMode();
	void handleExportSequence();

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
