// src/ui/uiWindow.h - MODIFICATIONS
#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "panels/DrawingPanel.h"
#include "panels/ImagePanel.h"
#include "panels/InfoPanel.h"
#include "panels/View2DPanel.h"
#include "panels/View3DPanel.h"

class UIWindow {
public:
	UIWindow() = default;
	~UIWindow() = default;

	void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void handleFileDragAndDrop(ofDragInfo dragInfo);

	ofRectangle getDrawingArea() const { return drawingArea; }
	ofRectangle getDrawDrawingArea() const { return drawDrawingArea; }
	ofRectangle getCurvesDrawingArea() const { return curvesDrawingArea; }

	// DRAWING PANEL (via View2DPanel)
	std::string getCurrentShape() const { return view2DPanel.getCurrentShape(); }
	bool isSaveShapeRequested() const { return view2DPanel.isSaveShapeRequested(); }
	bool isDeleteShapeRequested() const { return view2DPanel.isDeleteShapeRequested(); }
	bool isSelectShapeRequested() const { return view2DPanel.isSelectShapeRequested(); }
	float getLineWidth() const { return view2DPanel.getLineWidth(); }
	ofColor getStrokeColor() const { return view2DPanel.getStrokeColor(); }
	ofColor getFillColor() const { return view2DPanel.getFillColor(); }

	// Transform accessors required by Application
	float getTranslateX() const { return view2DPanel.getTranslateX(); }
	float getTranslateY() const { return view2DPanel.getTranslateY(); }
	float getRotation() const { return view2DPanel.getRotation(); }
	float getScale() const { return view2DPanel.getScale(); }

	// Return background color depending on active tab: Image has its own default background
	ofColor getBackgroundColor() const {
		if (imageTab.active) {
			// Image mode uses a neutral darker background to better show images
			return ofColor(20, 20, 20);
		}
		// Default to the 2D view background when 2D view is active
		if (view2DPanel.isVisible()) {
			return view2DPanel.getBackgroundColor();
		}
		// Fallback background
		return ofColor(180, 200, 220);
	}

	// Expose active tab states
	bool isImageTabActive() const { return imageTab.active; }

	// IMAGE PANEL
	bool isImportImageRequested() const { return imagePanel.isImportImageRequested(); }
	bool isClearImageRequested() const { return imagePanel.isClearImageRequested(); }

	// VIEW3D PANEL
	bool isImport3DModelRequested() const { return view3DPanel.isImport3DModelRequested(); }
	bool isClear3DModelRequested() const { return view3DPanel.isClear3DModelRequested(); }
	bool is3DviewRequested() const { return view3DActive; }
	bool is2DviewRequested() const { return view2DActive; }
	bool isQuadViewRequested() const { return view3DPanel.isQuadViewRequested(); }
	bool isShowBoundingBoxEnabled() const { return view3DPanel.isShowBoundingBoxToggled(); }
	bool isWireframeEnabled() const { return view3DPanel.isShowWireframeToggled(); }
	bool isGridEnabled() const { return view3DPanel.isGridEnabled(); }
	bool isAxesEnabled() const { return view3DPanel.isAxesEnabled(); }
	bool isNormalsEnabled() const { return view3DPanel.isNormalsEnabled(); }
	bool isLightingEnabled() const { return view3DPanel.isLightingEnabled(); }
	float getLightingIntensity() const { return view3DPanel.getLightIntensity(); }
	ofColor getLightingColor() const { return view3DPanel.getLightColor(); }
	bool is3DTabActive() const { return view3DActive; }

	// CURVES (via View2DPanel)
	bool isPlacePointsMode() const { return view2DPanel.isPlacePointsMode(); }
	bool isGenerateCurveRequested() const { return view2DPanel.isGenerateCurveRequested(); }
	bool isClearCurvesRequested() const { return view2DPanel.isClearCurvesRequested(); }
	bool isUndoPointRequested() const { return view2DPanel.isUndoPointRequested(); }
	bool isClearPointsRequested() const { return view2DPanel.isClearPointsRequested(); }
	bool isDrawModeActive() const { return view2DPanel.isDrawModeActive(); }
	bool isCurvesModeActive() const { return view2DPanel.isCurvesModeActive(); }
	void disablePlacePointsMode() { view2DPanel.disablePlacePointsMode(); }
	void clearGenerateCurveRequest() { view2DPanel.clearGenerateCurveRequest(); }
	void clearClearCurvesRequest() { view2DPanel.clearClearCurvesRequest(); }
	void clearUndoPointRequest() { view2DPanel.clearUndoPointRequest(); }
	void clearClearPointsRequest() { view2DPanel.clearClearPointsRequest(); }

	void clearRequests();

	std::string statusMessage;

	bool isPlayAnimationRequested() const { return view2DPanel.isPlayAnimationRequested(); }
	bool isStopAnimationRequested() const { return view2DPanel.isStopAnimationRequested(); }
	void clearPlayAnimationRequest() { view2DPanel.clearRequests(); }
	void clearStopAnimationRequest() { view2DPanel.clearRequests(); }

private:
	ImagePanel imagePanel;
	View2DPanel view2DPanel;
	View3DPanel view3DPanel;
	InfoPanel infoPanel;

	struct TabButton {
		std::string label;
		ofRectangle bounds;
		bool active = false;
	};

	TabButton imageTab = { "Image", ofRectangle(0, 0, 100, 50) };
	TabButton draw2DTab = { "2D EDITION", ofRectangle(100, 0, 140, 50) };
	TabButton view3DTab = { "3D EDITION", ofRectangle(240, 0, 140, 50) };

	ofRectangle drawingArea;
	ofRectangle statusBox;
	ofRectangle drawDrawingArea;
	ofRectangle curvesDrawingArea;
	float menuBarHeight = 50;

	bool view2DActive = false;
	bool view3DActive = false;

	void drawTabs();
	void drawStatusBox();
	void handleTabClick(int x, int y);
	void activateImageTab();
	void activateDraw2DTab();
	void activateView3DTab();
};
