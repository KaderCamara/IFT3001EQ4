// Classe s'occupant du design du UI ( buttons, menu etc )

#include "uiWindow.h"

void UIWindow::setup() {
	//drawing area
	drawingArea.set(0, menuBarHeight, ofGetWidth(), ofGetHeight() - menuBarHeight);

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

	drawPointButton.addListener(this, &UIWindow::onDrawAPointPressed);
	drawLineButton.addListener(this, &UIWindow::onDrawALinePressed);
	drawTriangleButton.addListener(this, &UIWindow::onDrawATrianglePressed);
	drawSquareButton.addListener(this, &UIWindow::onDrawASquarePressed);
	drawRectangleButton.addListener(this, &UIWindow::onDrawARectanglePressed);
	drawCircleButton.addListener(this, &UIWindow::onDrawACirclePressed);
	
}

void UIWindow::update() {
	// No special logic yet
}

void UIWindow::draw() {
	//drawing area auto update
	drawingArea.set(0, menuBarHeight, ofGetWidth(), ofGetHeight() - menuBarHeight);

	//menu rectangle
	ofSetColor(50, 50, 50);
	ofDrawRectangle(0, 0, ofGetWidth(), menuBarHeight);

	//image panel here so it is responsive with the height and width
	imageMenuPanel.setPosition(ofGetWidth() - SideMenuwidth, menuBarHeight);
	imageMenuPanel.setSize(SideMenuwidth, ofGetHeight());

	//image panel here so it is responsive with the height and width
	drawMenuPanel.setPosition(ofGetWidth() - SideMenuwidth, menuBarHeight);
	drawMenuPanel.setSize(SideMenuwidth, ofGetHeight());

	for (auto & tab : { imageTab, drawTab }) {
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
}

//Menu toggles
void UIWindow::onImageTabPressed() {
	showImageMenu = !showImageMenu;
}

void UIWindow::onDrawTabPressed() {
	showDrawMenu = !showDrawMenu;
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
		imageTab.active = true;
		drawTab.active = false;
		currentShape = "none";
	} else if (drawTab.bounds.inside(x, y)) {
		showDrawMenu = !showDrawMenu;
		showImageMenu = false;
		drawTab.active = true;
		imageTab.active = false;
	}
}

//draw
void UIWindow::onDrawAPointPressed() {currentShape = "point";}
void UIWindow::onDrawALinePressed() { currentShape = "line"; }
void UIWindow::onDrawATrianglePressed() { currentShape = "triangle"; }
void UIWindow::onDrawASquarePressed() { currentShape = "square"; }
void UIWindow::onDrawARectanglePressed() { currentShape = "rectangle"; }
void UIWindow::onDrawACirclePressed() { currentShape = "circle"; }

//general
void UIWindow::onClearImagePressed() {
	imageManager.clear();
}

void UIWindow::mouseReleased(int x, int y, int button) {
	if (currentShape != "none" &&  showDrawMenu ) {
		cout << "you went over the zone allowed to draw";
	}
}



