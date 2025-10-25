// Classe s'occupant du design du UI ( buttons, menu etc )

#include "uiWindow.h"

void UIWindow::setup() {
	//image menu
	imageMenuPanel.setup("Image Menu");
	imageMenuPanel.add(importImageButton.setup("Import Image"));
	imageMenuPanel.add(clearButton.setup("Clear Image"));
	importImageButton.addListener(this, &UIWindow::onImportImagePressed);
	clearButton.addListener(this, &UIWindow::onClearImagePressed);

	// Import 3D Model Button in Image Menu
	imageMenuPanel.add(import3DModelButton.setup("Import 3D Model"));
	imageMenuPanel.add(clear3DModelButton.setup("Clear 3D Models"));
	import3DModelButton.addListener(this, &UIWindow::onImport3DModelPressed);
	clear3DModelButton.addListener(this, &UIWindow::onClear3DModelPressed);


	//draw menu
	drawMenuPanel.setup("Draw Menu");
	drawMenuPanel.add(drawPointButton.setup("Draw a point"));
	drawMenuPanel.add(drawLineButton.setup("Draw a line"));
	drawMenuPanel.add(drawTriangleButton.setup("Draw a triangle"));
	drawMenuPanel.add(drawSquareButton.setup("Draw a square"));
	drawMenuPanel.add(drawRectangleButton.setup("Draw a rectangle"));
	drawMenuPanel.add(drawCircleButton.setup("Draw a circle"));
	drawMenuPanel.add(saveShapeButton.setup("save the shape"));
	drawMenuPanel.add(deleteShapeButton.setup("delete the shape"));
	drawMenuPanel.add(selectionButton.setup("select or interact"));

	drawPointButton.addListener(this, &UIWindow::onDrawAPointPressed);
	drawLineButton.addListener(this, &UIWindow::onDrawALinePressed);
	drawTriangleButton.addListener(this, &UIWindow::onDrawATrianglePressed);
	drawSquareButton.addListener(this, &UIWindow::onDrawASquarePressed);
	drawRectangleButton.addListener(this, &UIWindow::onDrawARectanglePressed);
	drawCircleButton.addListener(this, &UIWindow::onDrawACirclePressed);
	saveShapeButton.addListener(this, &UIWindow::onSaveShapePressed);
	deleteShapeButton.addListener(this, &UIWindow::onDeleteShapePressed);
	selectionButton.addListener(this, &UIWindow::onSelectionPressed);

	// --- Drawing parameters ---
	drawParamsPanel.setup("Drawing Parameters");
	drawParamsPanel.add(lineWidth.set("Line Width", 2.0, 1.0, 10.0));
	drawParamsPanel.add(strokeColor.set("Stroke Color", ofColor(0, 0, 0)));
	drawParamsPanel.add(fillColor.set("Fill Color", ofColor(255, 0, 0)));
	drawParamsPanel.add(backgroundColor.set("Background", ofColor(180, 200, 220)));
	drawParamsPanel.add(useHSB.set("HSB Mode", false));

	drawParamsPanel.add(hue.set("Hue", 128, 0, 255));
	drawParamsPanel.add(saturation.set("Saturation", 255, 0, 255));
	drawParamsPanel.add(brightness.set("Brightness", 255, 0, 255));

	// Transformation parameters
	transformPanel.setup("Transformations");
	transformPanel.add(translateX.set("Translate X", 0.0, -2000, 2000));
	transformPanel.add(translateY.set("Translate Y", 0.0, -2000, 2000));
	transformPanel.add(rotation.set("Rotation", 0.0, -720, 720));
	transformPanel.add(scaleFactor.set("Scale", 1.0, 0.1, 5.0));


}

void UIWindow::update() {
	// No special logic yet
}

void UIWindow::draw() {
	//drawing area auto update
	drawingArea.set(0, menuBarHeight, ofGetWidth(), ofGetHeight() - menuBarHeight);

	//menus form or shape ( a rectangle )
	ofSetColor(50, 50, 50);
	ofDrawRectangle(0, 0, ofGetWidth(), menuBarHeight);

	//panels here so it is responsive with the height and width
	//image panel 
	float sideMenuWidth = ofGetWidth() / 6;

	imageMenuPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	imageMenuPanel.setSize(sideMenuWidth, ofGetHeight()-menuBarHeight);
	//draw panel 
	drawMenuPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	drawMenuPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
	prochainY = menuBarHeight;


	for (auto & tab : { imageTab, drawTab, view3DTab }) {
		ofSetColor(tab.active ? 100 : 150); 
		ofDrawRectangle(tab.bounds);

		ofSetColor(255);
		ofDrawBitmapString(tab.label, tab.bounds.x + 10, tab.bounds.y + 20);
	}
	if (showImageMenu) {
		imageMenuPanel.draw();
	}
	if (showDrawMenu) {
		drawMenuPanel.draw();
	}
	//drawing settings panel
	// Drawing parameter panel (à gauche)
	if (showDrawMenu) {
		float panelWidth = ofGetWidth() / 6;
		drawParamsPanel.setPosition(10, prochainY);
		drawParamsPanel.setSize(panelWidth - 20, 400);
		drawParamsPanel.draw();
		prochainY += drawParamsPanel.getHeight() + 10;
	}
	
	// transformation panel
	if (selectShape) {
		float panelWidth = ofGetWidth() / 6;
		transformPanel.setPosition(10, prochainY);
		transformPanel.setSize(panelWidth - 20, 180);
		float windowWidth = drawingArea.getWidth();
		float windowHeight = drawingArea.getHeight();
		translateX.setMin(-windowWidth / 2);
		translateX.setMax(windowWidth / 2);
		translateY.setMin(-windowHeight / 2);
		translateY.setMax(windowHeight / 2);
		transformPanel.draw();
		prochainY = menuBarHeight + 10;
	}
	imageManager.draw();
}

//Menu toggles
void UIWindow::onImageTabPressed() {
	showImageMenu = !showImageMenu;
}

void UIWindow::onDrawTabPressed() {
	showDrawMenu = !showDrawMenu;
}
void UIWindow::onView3DTabPressed() {
	showView3D = !showView3D;
	view3DRequested = true;
}

//menu actions
//image
void UIWindow::onImportImagePressed() {
	imageManager.import();
}

void UIWindow::handleFileDragAndDrop(ofDragInfo dragInfo) {
	if (!dragInfo.files.empty()) {
		imageManager.loadFromDrag(dragInfo);
	} else {
		std::cout << "Empty drag" << std::endl;
	}
}

void UIWindow::mousePressed(int x, int y, int button) {
	if (imageTab.bounds.inside(x, y)) {
		showImageMenu = !showImageMenu;
		showDrawMenu = false;
		drawTab.active = false;
		view3DTab.active = false;
		showView3D = false;
		currentShape = "none";
		imageTab.active = true;

	} else if (drawTab.bounds.inside(x, y)) {
		showDrawMenu = !showDrawMenu;
		showImageMenu = false;
		imageTab.active = false;
		view3DTab.active = false;
		showView3D = false;
		drawTab.active = true;

	} else if (view3DTab.bounds.inside(x, y)) {
		showView3D = !showView3D;
		showImageMenu = false;
		showDrawMenu = false;
		drawTab.active = false;
		imageTab.active = false;
		currentShape = "none";
		view3DTab.active = true;
	}
}

//draw
void UIWindow::onDrawAPointPressed() {
	currentShape = "point";
	selectShape = false;
}
void UIWindow::onDrawALinePressed() {
	currentShape = "line";
	selectShape = false;
}
void UIWindow::onDrawATrianglePressed() {
	currentShape = "triangle";
	selectShape = false;
}
void UIWindow::onDrawASquarePressed() {
	currentShape = "square";
	selectShape = false;
}
void UIWindow::onDrawARectanglePressed() {
	currentShape = "rectangle";
	selectShape = false;
}
void UIWindow::onDrawACirclePressed() {
	currentShape = "circle";
	selectShape = false;
}
void UIWindow::onSaveShapePressed() {
	saveShape = true;
}
void UIWindow::onDeleteShapePressed() {
	deleteShape = true;
}

void UIWindow::clearRequests() {
	saveShape = false;
	deleteShape = false;
	view3DRequested = false;
}

void UIWindow::onSelectionPressed() {
	selectShape = true;
	currentShape = "none";
}


//general
void UIWindow::onClearImagePressed() {
	imageManager.clear();
}

void UIWindow::mouseReleased(int x, int y, int button) {
	if (currentShape != "none" &&  showDrawMenu ) {
		cout << "you went over the zone allowed to draw";
	}
}

// 3D IMPORT 

void UIWindow::onImport3DModelPressed() {
	import3DModelRequested = true;
}

void UIWindow::onClear3DModelPressed() {
	clear3DModelRequested = true;
}



