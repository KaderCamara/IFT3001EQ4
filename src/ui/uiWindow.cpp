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
	drawMenuPanel.add(drawTriangleButton.setup("Draw a triangle | view in 3D mode"));
	drawMenuPanel.add(drawSquareButton.setup("Draw a square | view in 3D mode"));
	drawMenuPanel.add(drawRectangleButton.setup("Draw a rectangle | view in 3D mode"));
	drawMenuPanel.add(drawCircleButton.setup("Draw a circle | view in 3D mode"));
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

	//3d view Menu
	view3DMenuPanel.setup("3D View Menu");
	view3DMenuPanel.add(cameraTitle.setup("Camera Controls", ""));
	view3DMenuPanel.add(cameraInstructions1.setup("1:Top 2:Front 3:Side", ""));
	view3DMenuPanel.add(cameraInstructions2.setup("4:Bottom 5:Free (drag)", ""));
	view3DMenuPanel.add(quadViewButton.setup("view with 4 cameras at the same time."));
	quadViewButton.addListener(this, &UIWindow::onQuadViewButtonPressed);
}

void UIWindow::update() {
}

void UIWindow::draw() {
	//drawing area auto update
	drawingArea.set(0, menuBarHeight, ofGetWidth(), ofGetHeight() - menuBarHeight);

	//menus form or shape ( a rectangle )
	ofSetColor(50, 50, 50);
	ofDrawRectangle(0, 0, ofGetWidth(), menuBarHeight);

	//panels here so it is responsive with the height and width, il faut que ca soit auto
	//image panel 
	float sideMenuWidth = ofGetWidth() / 6;
	imageMenuPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	imageMenuPanel.setSize(sideMenuWidth, ofGetHeight()-menuBarHeight);
	//draw panel 
	drawMenuPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	drawMenuPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
	//3d panel
	view3DMenuPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	view3DMenuPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);


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
	if (show3DMenu) {
		view3DMenuPanel.draw();
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
	show3DMenu = !show3DMenu;
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
		show3DMenu = false;
		showQuadView = false;
		currentShape = "none";
		imageTab.active = true;

	} else if (drawTab.bounds.inside(x, y)) {
		showDrawMenu = !showDrawMenu;
		showImageMenu = false;
		imageTab.active = false;
		view3DTab.active = false;
		showView3D = false;
		show3DMenu = false;
		showQuadView = false;
		drawTab.active = true;

	} else if (view3DTab.bounds.inside(x, y)) {
		showView3D = !showView3D;
		show3DMenu = true;
		showImageMenu = false;
		showDrawMenu = false;
		drawTab.active = false;
		imageTab.active = false;
		showQuadView = false;
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
}

void UIWindow::onSelectionPressed() {
	selectShape = true;
	currentShape = "none";
}

//3d
void UIWindow::onQuadViewButtonPressed() {
	showQuadView = true;
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



