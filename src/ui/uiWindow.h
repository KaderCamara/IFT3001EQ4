#pragma once
// Classe s'occupant du design du UI ( buttons, menu etc )

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "../image/imageManager.h"
#include "rendering/sceneGraph.h"
#include "rendering/renderer.h"

class UIWindow  {
public:

	void setup();
	void draw();
	void update();
	void handleFileDragAndDrop(ofDragInfo dragInfo);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	ofRectangle getDrawingArea() const { return drawingArea; }
	std::string getCurrentShape() const { return currentShape; }
	bool isSelectShapeRequested() const { return selectShape; }
	bool isSaveShapeRequested() const { return saveShape; }
	bool isDeleteShapeRequested() const { return deleteShape; }
	bool is3DviewRequested() const { return showView3D; }
	bool is2DviewRequested() const { return showDrawMenu; }
	bool isQuadViewRequested() const { return showQuadView; }
	void clearRequests();
	bool view3DRequested = false;
	float getLineWidth() const { return lineWidth; }
	ofColor getStrokeColor() const { return strokeColor; }
	ofColor getFillColor() const { return fillColor; }
	ofColor getBackgroundColor() const { return backgroundColor; }
	bool isHSBMode() const { return useHSB; }
	float getHue() const { return hue; }
	float getSaturation() const { return saturation; }
	float getBrightness() const { return brightness; }

	// Transformation getters
	float getTranslateX() const { return translateX; }
	float getTranslateY() const { return translateY; }
	float getRotation() const { return rotation; }
	float getScale() const { return scaleFactor; }

	// 3D IMPORT

	bool isImport3DModelRequested() const { return import3DModelRequested; }
	void clearImport3DModelRequest() { import3DModelRequested = false; }
	void onImport3DModelPressed();
	bool isClear3DModelRequested() const { return clear3DModelRequested; }
	void clearClear3DModelRequest() { clear3DModelRequested = false; }
	void onClear3DModelPressed();
	bool showBoundingBox = false;
	bool showWireframe = false; 
	bool getShowBoundingBox() const { return showBoundingBox; }
	bool getShowWireframe() const { return showWireframe; }


private:

	struct TabButton {
		string label;
		ofRectangle bounds;
		bool hovered = false;
		bool active = false;
	};

	CameraManager cameraManager;

	//drawing area
	ofRectangle drawingArea;

	//panels of the menu choices
	ofxPanel imageMenuPanel;
	ofxPanel drawMenuPanel;
	ofxPanel view3DMenuPanel;
	ofxPanel deletePanel;
	ofxPanel view3DPanel;

	//image tab elements
	ofxButton importImageButton;
	ofxButton clearButton;
	bool showImageMenu = false;
	void onImportImagePressed();
	void onClearImagePressed();
	void onImageTabPressed();

	//draw tab elements
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
	ofxButton showBoundingBoxButton;
	ofxButton wireframeButton;
	std::string currentShape = "none";
	bool showDrawMenu = false;
	bool saveShape = false;
	bool deleteShape = false;
	bool selectShape = false;
	void onDrawAPointPressed();
	void onDrawALinePressed();
	void onDrawATrianglePressed();
	void onDrawASquarePressed();
	void onDrawARectanglePressed();
	void onDrawACirclePressed();
	void onDrawTabPressed();
	void onDeleteShapePressed();
	void onSaveShapePressed();
	void onSelectionPressed();
	void onShowBoundingBoxPressed();
	void onWireframePressed();


	//view3D
	void onView3DTabPressed();
	bool showView3D = false;
	bool show3DMenu = false; 
	//view quad
	bool showQuadView = false;
	ofxButton quadViewButton;
	ofxLabel cameraTitle;
	ofxLabel cameraInstructions1;
	ofxLabel cameraInstructions2;
	void onQuadViewButtonPressed();

	//general
	ofTrueTypeFont font;
	ImageManager imageManager;
	SceneGraph sceneGraph;
	//float SideMenuwidth = 200;
	float menuBarHeight = 50;
	float buttonsWidth = 100;
	float buttonsWidthMargin = 10;

	//tabs
	TabButton imageTab = { "Image", ofRectangle(0, 0, 100, 50) };
	TabButton drawTab = { "Draw", ofRectangle(100, 0, 100, 50) };
	TabButton view3DTab = { "3D view", ofRectangle(200, 0, 100, 50) };

	// status box
	float statusTimer = 0.0f;
	std::string statusMessage;
	ofRectangle statusBox;

	// Export
	ofFbo exportFbo;
	std::string exportFolder = "export";
	bool exportSequence = false;
	int exportFrameCount = 0;
	int maxFrames = 100;
	float exportInterval = 0.5f;
	float exportTimer = 0.0f;

	void onExportSequencePressed();
	void exportCurrentFrame();
	void onExportImagePressed();
	void exportScene();
	// --- Drawing parameters panel ---
	ofxPanel drawParamsPanel;
	ofParameter<float> lineWidth;
	ofParameter<ofColor> strokeColor;
	ofParameter<ofColor> fillColor;
	ofParameter<ofColor> backgroundColor;
	ofParameter<bool> useHSB;
	ofParameter<float> hue;
	ofParameter<float> saturation;
	ofParameter<float> brightness;

	// Transformation attributes
	ofxPanel transformPanel;
	ofParameter<float> translateX, translateY;
	ofParameter<float> rotation;
	ofParameter<float> scaleFactor;

	// Bouton d'importation 3D
	ofxButton import3DModelButton;
	bool import3DModelRequested = false;
	ofxButton clear3DModelButton;
	bool clear3DModelRequested = false;
	//
	float prochainY = 0.0f;
	// vidual feedback
	ofColor feedbackColor = ofColor::white;
	float feedbackAlpha = 255.0f;
	bool feedbackFlash = false;
	float feedbackTimer = 0.0f;
	float feedbackFlashDuration = 0.5f;
	
};
