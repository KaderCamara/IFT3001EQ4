#pragma once
// Classe s'occupant du design du UI ( buttons, menu etc )

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "../image/imageManager.h"
#include "rendering/sceneGraph.h"

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


private:

	struct TabButton {
		string label;
		ofRectangle bounds;
		bool hovered = false;
		bool active = false;
	};

	//drawing area
	ofRectangle drawingArea;

	//panels of the menu choices
	ofxPanel imageMenuPanel;
	ofxPanel drawMenuPanel;

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

	//view3D
	void onView3DTabPressed();
	bool showView3D = false;

	//general
	ofTrueTypeFont font;
	ImageManager imageManager;
	//float SideMenuwidth = 200;
	float menuBarHeight = 50;
	float buttonsWidth = 100;
	float buttonsWidthMargin = 10;

	//tabs
	TabButton imageTab = { "Image", ofRectangle(0, 0, 100, 50) };
	TabButton drawTab = { "Draw", ofRectangle(100, 0, 100, 50) };
	TabButton view3DTab = { "3D view", ofRectangle(200, 0, 100, 50) };

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
};
