// src/ui/panels/curvesPanel.h
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class CurvesPanel {
public:
	CurvesPanel() = default;
	~CurvesPanel() = default;

	void setup();
	void draw(float x, float y, float width);
	void clearRequests();

	bool isPlacePointsMode() const { return placePointsMode; }
	bool isGenerateCurveRequested() const { return generateCurveRequested; }
	bool isClearCurvesRequested() const { return clearCurvesRequested; }
	bool isUndoPointRequested() const { return undoPointRequested; }
	bool isClearPointsRequested() const { return clearPointsRequested; }
	void setPlacePointsMode(bool mode) { placePointsMode = mode; }

private:
	ofxPanel curvesPanel;
	ofxButton placePointsButton;
	ofxButton generateBezierCurveButton;
	ofxButton clearCurvesButton;
	ofxButton undoPointButton;
	ofxButton clearPointsButton;

	bool placePointsMode = false;
	bool generateCurveRequested = false;
	bool clearCurvesRequested = false;
	bool undoPointRequested = false;
	bool clearPointsRequested = false;

	void onPlacePointsPressed();
	void onGenerateCurvePressed();
	void onClearCurvesPressed();
	void onUndoPointPressed();
	void onClearPointsPressed();
};
