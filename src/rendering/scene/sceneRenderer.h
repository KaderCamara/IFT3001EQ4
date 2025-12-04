// SceneRenderer.h
// Orchestrateur de rendu de la scène (2D, 3D, Quad)

#pragma once

#include "../../app/sceneController.h"
#include "../curves/CurvesRenderer.h"
#include "ofMain.h"
#include "../shapes/Shape2DRenderer.h"
#include "../shapes/Shape3DRenderer.h"
#include "../../app/curvesController.h"

class SceneRenderer {
public:
	SceneRenderer() = default;
	~SceneRenderer() = default;

	void setSceneController(SceneController * controller) { sceneController = controller; }
	void setCurvesRenderer(CurvesRenderer * curves) { curvesRenderer = curves; }
	void setDrawingArea(const ofRectangle & area) { drawingArea = area; }
	void setLineWidth(float w) { currentLineWidth = w; }

	void draw2D();
	void draw3D();
	void drawQuadView();
	void set3DDisplayOptions(bool showBoundingBox, bool showWireframe);
	void setCurvesController(CurvesController * controller) { curvesController = controller; }; 

private:
	SceneController * sceneController = nullptr;
	CurvesRenderer * curvesRenderer = nullptr;
	CurvesController * curvesController = nullptr;

	Shape2DRenderer shape2DRenderer;
	Shape3DRenderer shape3DRenderer;

	ofRectangle drawingArea;
	float currentLineWidth = 2.0f;

	void drawQuadViewCamera(int cameraIndex, int x, int y, int width, int height, const std::string & label);
	void drawQuadViewSeparators();
};
