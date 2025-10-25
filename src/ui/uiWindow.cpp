// Classe s'occupant du design du UI ( buttons, menu etc )

#include "uiWindow.h"

extern bool g_showBoundingBox;
extern bool g_showWireframe;


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
	drawMenuPanel.add(drawTriangleButton.setup("Draw a triangle | 3D view"));
	drawMenuPanel.add(drawSquareButton.setup("Draw a square | 3D view"));
	drawMenuPanel.add(drawRectangleButton.setup("Draw a rectangle | 3D view"));
	drawMenuPanel.add(drawCircleButton.setup("Draw a circle | 3D view"));
	drawMenuPanel.add(saveShapeButton.setup("Save shape"));
	drawMenuPanel.add(selectionButton.setup("Select/Interact"));
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

    drawPointButton.addListener(this, &UIWindow::onDrawAPointPressed);
	drawLineButton.addListener(this, &UIWindow::onDrawALinePressed);
	drawTriangleButton.addListener(this, &UIWindow::onDrawATrianglePressed);
	drawSquareButton.addListener(this, &UIWindow::onDrawASquarePressed);
	drawRectangleButton.addListener(this, &UIWindow::onDrawARectanglePressed);
	drawCircleButton.addListener(this, &UIWindow::onDrawACirclePressed);
	saveShapeButton.addListener(this, &UIWindow::onSaveShapePressed);
	selectionButton.addListener(this, &UIWindow::onSelectionPressed);
	deleteShapeButton.addListener(this, &UIWindow::onDeleteShapePressed);
	exportSequenceButton.addListener(this, &UIWindow::onExportSequencePressed);
	exportImageButton.addListener(this, &UIWindow::onExportImagePressed);

	//3d view Menu
	view3DPanel.setup("3D View Menu");
	view3DPanel.add(showBoundingBoxButton.setup("Show Bounding Boxes"));
	showBoundingBoxButton.addListener(this, &UIWindow::onShowBoundingBoxPressed);

	view3DPanel.add(wireframeButton.setup("Wireframe Mode"));
	wireframeButton.addListener(this, &UIWindow::onWireframePressed);

	view3DPanel.add(cameraTitle.setup("Camera Controls", ""));
	view3DPanel.add(cameraInstructions1.setup("1:Top 2:Front 3:Side", ""));
	view3DPanel.add(cameraInstructions2.setup("4:Bottom 5:Free (drag)", ""));
	view3DPanel.add(quadViewButton.setup("4 Cameras View"));
	quadViewButton.addListener(this, &UIWindow::onQuadViewButtonPressed);

	//interface box
	statusBox.set(10, menuBarHeight + 10, 250, 40);

	//export
	exportFbo.allocate(ofGetWidth(), ofGetHeight() - menuBarHeight, GL_RGBA);

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
	imageMenuPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
	//draw panel
	drawMenuPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	drawMenuPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
	//3d panel
	view3DMenuPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
	view3DMenuPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
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

		if (selectShape) {
			float sideMenuWidth = ofGetWidth() / 6;
			deletePanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight + drawMenuPanel.getHeight());
			deletePanel.draw();
		}
	}
	if (show3DMenu) {
		float sideMenuWidth = ofGetWidth() / 6;
		view3DPanel.setPosition(ofGetWidth() - sideMenuWidth, menuBarHeight);
		view3DPanel.setSize(sideMenuWidth, ofGetHeight() - menuBarHeight);
		view3DPanel.draw();
	}
	}
	//drawing settings panel
	// Drawing parameter panel (a gauche)
	if (showDrawMenu) {
		float panelWidth = ofGetWidth() / 6;
		drawParamsPanel.setPosition(10, prochainY);
		drawParamsPanel.setSize(panelWidth - 20, 200);
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
	show3DMenu = !show3DMenu;
	view3DRequested = true;
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
		show3DMenu = false;
		showQuadView = false;
		currentShape = "none";
		imageTab.active = true;
		selectShape = false;

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
	view3DRequested = false;
}

void UIWindow::onSelectionPressed() {
	selectShape = true;
	currentShape = "none";
	statusMessage = "Selection mode activated";
}

//3d
void UIWindow::onQuadViewButtonPressed() {
	showQuadView = true;
}

//general
void UIWindow::onClearImagePressed() {
	imageManager.clear();
	statusMessage = "Image cleared";
}

void UIWindow::mouseReleased(int x, int y, int button) {
	if (currentShape != "none" && showDrawMenu) {
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

// 3D IMPORT 

void UIWindow::onImport3DModelPressed() {
	import3DModelRequested = true;
}

void UIWindow::onClear3DModelPressed() {
	clear3DModelRequested = true;
}

void UIWindow::onWireframePressed() {
	g_showWireframe = !g_showWireframe;
	statusMessage = g_showWireframe ? "Wireframe ON" : "Wireframe OFF";
}

void UIWindow::onShowBoundingBoxPressed() {
	g_showBoundingBox = !g_showBoundingBox;
	statusMessage = g_showBoundingBox ? "Bounding boxes ON" : "Bounding boxes OFF";
}

