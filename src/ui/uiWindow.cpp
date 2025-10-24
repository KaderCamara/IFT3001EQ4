// Classe s'occupant du design du UI ( buttons, menu etc )

#include "uiWindow.h"

extern bool g_showBoundingBox;
extern bool g_showWireframe; 

bool g_showWireframe = false;

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
	drawMenuPanel.add(selectionButton.setup("select or interact"));
	drawMenuPanel.add(exportSequenceButton.setup("Export Sequence"));
	drawMenuPanel.add(exportImageButton.setup("Export Image"));

	// view3D menu
	view3DPanel.setup("3D View Menu");
	view3DPanel.add(showBoundingBoxButton.setup("Show Bounding Boxes"));
	showBoundingBoxButton.addListener(this, &UIWindow::onShowBoundingBoxPressed);

	view3DPanel.add(wireframeButton.setup("Wireframe Mode"));
	wireframeButton.addListener(this, &UIWindow::onWireframePressed);

	// delete panel
	deletePanel.setup("Delete");
	deletePanel.add(deleteShapeButton.setup("delete the shape"));

	deleteShapeButton.addListener(this, &UIWindow::onDeleteShapePressed);
	drawPointButton.addListener(this, &UIWindow::onDrawAPointPressed);
	drawLineButton.addListener(this, &UIWindow::onDrawALinePressed);
	drawTriangleButton.addListener(this, &UIWindow::onDrawATrianglePressed);
	drawSquareButton.addListener(this, &UIWindow::onDrawASquarePressed);
	drawRectangleButton.addListener(this, &UIWindow::onDrawARectanglePressed);
	drawCircleButton.addListener(this, &UIWindow::onDrawACirclePressed);
	saveShapeButton.addListener(this, &UIWindow::onSaveShapePressed);
	selectionButton.addListener(this, &UIWindow::onSelectionPressed);
	exportSequenceButton.addListener(this, &UIWindow::onExportSequencePressed);
	exportImageButton.addListener(this, &UIWindow::onExportImagePressed);

	//interface box
	statusBox.set(10, menuBarHeight + 10, 250, 40);

	//export
	exportFbo.allocate(ofGetWidth(), ofGetHeight() - menuBarHeight, GL_RGBA);
}

void UIWindow::update() {
	if (exportSequence) {
		exportTimer += ofGetLastFrameTime();
		if (exportTimer >= exportInterval) {
			exportCurrentFrame();
			exportTimer = 0;
			if (exportFrameCount >= maxFrames) {
				exportSequence = false;
				statusMessage = "Export finished (" + ofToString(maxFrames) + " frames)";
			}
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

		if (selectShape) {
			float sideMenuWidth = ofGetWidth() / 6;
			deletePanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight + drawMenuPanel.getHeight());
			deletePanel.draw();
		}
	}

	imageManager.draw();
	if (!statusMessage.empty()) {
		ofSetColor(0, 0, 0, 180);
		ofDrawRectangle(statusBox);

		ofSetColor(255);
		ofDrawBitmapString(statusMessage, statusBox.x + 10, statusBox.y + 25);
	}

	if (showView3D) {
		float sideMenuWidth = ofGetWidth() / 6;
		view3DPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
		view3DPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
		view3DPanel.draw();
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
		selectShape = false;

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
		selectShape = false;
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
	if (!selectShape) return;

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


void UIWindow::onExportSequencePressed() {
	exportSequence = !exportSequence;
	if (exportSequence) {
		ofFileDialogResult result = ofSystemLoadDialog("Select folder to save frames", true);
		if (result.bSuccess) {
			exportFolder = result.getPath() + "/sequence_" + ofGetTimestampString("%Y%m%d_%H%M%S");
			ofDirectory dir;
			dir.createDirectory(exportFolder, false, true);
			exportFrameCount = 0;
			exportTimer = 0;
			statusMessage = "Export sequence started in " + exportFolder;
		} else {
			exportSequence = false;
			statusMessage = "Export cancelled";
		}
	} else {
		statusMessage = "Export stopped";
	}
}


void UIWindow::onExportImagePressed() {
	exportScene();
	statusMessage = "Scene exported";
	statusTimer = 2.0f;
}

void UIWindow::exportScene() {
	ofFileDialogResult result = ofSystemLoadDialog("Select folder to save image", true);
	if (!result.bSuccess) return;
	exportFolder = result.getPath();

	ofDirectory dir;
	dir.createDirectory(exportFolder, false, true);

	std::string filename = exportFolder + "/frame_" + ofToString(exportFrameCount, 4, '0') + "_" + ofGetTimestampString("%Y%m%d_%H%M%S") + ".png";

	if (exportFbo.getWidth() != drawingArea.getWidth() || exportFbo.getHeight() != drawingArea.getHeight()) {
		exportFbo.allocate(drawingArea.getWidth(), drawingArea.getHeight(), GL_RGBA);
	}

	exportFbo.begin();
	ofClear(255, 255, 255, 0);
	ofPushMatrix();
	ofTranslate(-drawingArea.x, -drawingArea.y);
	imageManager.draw();
	sceneGraph.draw();
	ofPopMatrix();
	exportFbo.end();

	ofPixels pixels;
	exportFbo.readToPixels(pixels);
	ofImage img;
	img.setFromPixels(pixels);
	img.save(filename);

	statusMessage = "Scene exported to " + filename;
	statusTimer = 2.0f;
}

void UIWindow::exportCurrentFrame() {
	if (exportFbo.getWidth() != drawingArea.getWidth() || exportFbo.getHeight() != drawingArea.getHeight()) {
		exportFbo.allocate(drawingArea.getWidth(), drawingArea.getHeight(), GL_RGBA);
	}

	exportFbo.begin();
	ofClear(255, 255, 255, 0);
	ofPushMatrix();
	ofTranslate(-drawingArea.x, -drawingArea.y);
	imageManager.draw();
	sceneGraph.draw();
	ofPopMatrix();
	exportFbo.end();

	std::string filename = exportFolder + "/frame_" + ofToString(exportFrameCount, 4, '0') + ".png";
	ofPixels pixels;
	exportFbo.readToPixels(pixels);
	ofImage img;
	img.setFromPixels(pixels);
	img.save(filename);

	exportFrameCount++;
	statusMessage = "Exporting frame " + ofToString(exportFrameCount);
}

void UIWindow::onShowBoundingBoxPressed() {
	showBoundingBox = !showBoundingBox;
	g_showBoundingBox = showBoundingBox;
	statusMessage = showBoundingBox ? "Bounding boxes ON" : "Bounding boxes OFF";
}

void UIWindow::onWireframePressed() {
	g_showWireframe = !g_showWireframe;
	statusMessage = g_showWireframe ? "Wireframe ON" : "Wireframe OFF";
}
