// Classe s'occupant du design du UI ( buttons, menu etc )

#include "uiWindow.h"

void UIWindow::setup() {
	//image menu
	imageMenuPanel.setup("Image Menu");
	imageMenuPanel.add(importImageButton.setup("Import Image"));
	imageMenuPanel.add(clearButton.setup("Clear Image"));
	importImageButton.addListener(this, &UIWindow::onImportImagePressed);
	clearButton.addListener(this, &UIWindow::onClearImagePressed);

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

	//interface box
	statusBox.set(10, menuBarHeight + 10, 250, 40);
}

void UIWindow::update() {
	if (statusTimer > 0) {
		statusTimer -= ofGetLastFrameTime();
		if (statusTimer <= 0) {
			statusMessage = "";
		}
	}
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
	imageManager.draw();
	if (!statusMessage.empty()) {
		ofSetColor(0, 0, 0, 180);
		ofDrawRectangle(statusBox);

		ofSetColor(255);
		ofDrawBitmapString(statusMessage, statusBox.x + 10, statusBox.y + 25);
	}
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
}

//menu actions
//image
void UIWindow::onImportImagePressed() {
	imageManager.import();
	statusMessage = "Image imported successfully";
}

void UIWindow::handleFileDragAndDrop(ofDragInfo dragInfo) {
	if (!dragInfo.files.empty()) {
		imageManager.loadFromDrag(dragInfo);
		statusMessage = "Image loaded from drag & drop";
	} else {
		statusMessage = "No file detected in drag & drop";
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
	statusMessage = "Drawing mode: Point";
}
void UIWindow::onDrawALinePressed() {
	currentShape = "line";
	selectShape = false;
	statusMessage = "Drawing mode: Line";
}
void UIWindow::onDrawATrianglePressed() {
	currentShape = "triangle";
	selectShape = false;
	statusMessage = "Drawing mode: Triangle";
}
void UIWindow::onDrawASquarePressed() {
	currentShape = "square";
	selectShape = false;
	statusMessage = "Drawing mode: Square";
}
void UIWindow::onDrawARectanglePressed() {
	currentShape = "rectangle";
	selectShape = false;
	statusMessage = "Drawing mode: Rectangle";
}
void UIWindow::onDrawACirclePressed() {
	currentShape = "circle";
	selectShape = false;
	statusMessage = "Drawing mode: Circle";
}
void UIWindow::onSaveShapePressed() {
	saveShape = true;
	statusMessage = "Shape saved";
}
void UIWindow::onDeleteShapePressed() {
	deleteShape = true;
	statusMessage = "Shape deleted";
}

void UIWindow::clearRequests() {
	saveShape = false;
	deleteShape = false;
}

void UIWindow::onSelectionPressed() {
	selectShape = true;
	currentShape = "none";
	statusMessage = "Selection mode activated";
}


//general
void UIWindow::onClearImagePressed() {
	imageManager.clear();
	statusMessage = "Image cleared";
}

void UIWindow::mouseReleased(int x, int y, int button) {
	if (currentShape != "none" &&  showDrawMenu ) {
		cout << "you went over the zone allowed to draw";
	}
}



