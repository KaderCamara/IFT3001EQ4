// src/ui/uiWindow.cpp - MODIFICATIONS
#include "uiWindow.h"

void UIWindow::setup() {
	imagePanel.setup();
	view2DPanel.setup();
	view3DPanel.setup();
	infoPanel.setup();

	activateImageTab();
	statusBox.set(10, menuBarHeight + 10, 250, 40);
	ofLogNotice("UIWindow") << "UI Window setup complete";
}

void UIWindow::update() {
	infoPanel.update(
		(imageTab.active ? "Image" : (draw2DTab.active ? "2D" : "3D")),
		view3DActive && !view3DPanel.isQuadViewRequested(),
		view3DPanel.isQuadViewRequested(),
		drawingArea,
		statusMessage);
}

void UIWindow::draw() {
	float sideMenuWidth = ofGetWidth() / 6;
	float leftPanelWidth = sideMenuWidth;
	float rightPanelWidth = 0.0f;

	bool leftActive = (view2DActive && view2DPanel.isVisible()) || (view3DActive && view3DPanel.isVisible());
	bool rightActive = leftActive;
	if (rightActive) rightPanelWidth = sideMenuWidth;

	float bottomInset = infoPanel.getHeight();

	ofRectangle baseArea;
	if (view3DActive) {
		float left = leftPanelWidth;
		float right = sideMenuWidth;
		float w = ofGetWidth() - left - right;
		if (w < 0) w = ofGetWidth();
		baseArea.set(left, menuBarHeight, w, ofGetHeight() - menuBarHeight - bottomInset);
	} else if (leftActive || rightActive) {
		float left = leftActive ? leftPanelWidth : 0.0f;
		float right = rightActive ? rightPanelWidth : 0.0f;
		float w = ofGetWidth() - left - right;
		if (w < 0) w = ofGetWidth();
		baseArea.set(left, menuBarHeight, w, ofGetHeight() - menuBarHeight - bottomInset);
	} else {
		baseArea.set(0, menuBarHeight, ofGetWidth(), ofGetHeight() - menuBarHeight - bottomInset);
	}

	drawDrawingArea = baseArea;
	curvesDrawingArea = baseArea;
	drawingArea = view3DActive ? baseArea
							   : (view2DPanel.isDrawModeActive() ? drawDrawingArea : curvesDrawingArea);

	ofPushStyle();
	ofSetColor(50, 50, 50);
	ofDrawRectangle(0, 0, ofGetWidth(), menuBarHeight);
	ofPopStyle();

	drawTabs();

	if (leftActive) {
		ofPushStyle();
		ofSetColor(30, 30, 35, 180);
		ofFill();
		ofDrawRectangle(0, menuBarHeight, leftPanelWidth, ofGetHeight() - menuBarHeight - bottomInset);
		ofNoFill();
		ofSetColor(180, 200, 255);
		ofSetLineWidth(2);
		ofDrawRectangle(0, menuBarHeight, leftPanelWidth, ofGetHeight() - menuBarHeight - bottomInset);
		ofPopStyle();
	}

	if (rightActive) {
		float rx = ofGetWidth() - rightPanelWidth;
		ofPushStyle();
		ofSetColor(30, 30, 35, 180);
		ofFill();
		ofDrawRectangle(rx, menuBarHeight, rightPanelWidth, ofGetHeight() - menuBarHeight - bottomInset);
		ofNoFill();
		ofSetColor(180, 200, 255);
		ofSetLineWidth(2);
		ofDrawRectangle(rx, menuBarHeight, rightPanelWidth, ofGetHeight() - menuBarHeight - bottomInset);
		ofPopStyle();
	}

	if (view2DActive && view2DPanel.isVisible()) {
		const ofRectangle & activeArea = view2DPanel.isDrawModeActive() ? drawDrawingArea : curvesDrawingArea;
		ofPushStyle();
		ofNoFill();
		ofSetColor(180, 200, 255);
		ofSetLineWidth(3);
		ofDrawRectangle(activeArea.x + 2, activeArea.y + 2, activeArea.width - 4, activeArea.height - 4);
		ofSetColor(200);
		std::string label = view2DPanel.isDrawModeActive() ? "DRAW CANVAS" : "CURVES CANVAS";
		ofDrawBitmapString(label, activeArea.x + 10, activeArea.y + 20);
		ofPopStyle();
	}

	if (view3DActive && view3DPanel.isVisible()) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(180, 200, 255);
		ofSetLineWidth(3);
		ofDrawRectangle(drawingArea.x + 2, drawingArea.y + 2, drawingArea.width - 4, drawingArea.height - 4);
		ofSetColor(200);
		ofDrawBitmapString("3D VIEW", drawingArea.x + 10, drawingArea.y + 20);
		ofPopStyle();
	}

	imagePanel.draw(sideMenuWidth, menuBarHeight);
	view2DPanel.draw(sideMenuWidth, menuBarHeight);
	view3DPanel.draw(sideMenuWidth, menuBarHeight);
	infoPanel.draw(menuBarHeight);
	drawStatusBox();
}

void UIWindow::drawTabs() {
	auto drawTabButton = [](TabButton & tab) {
		ofPushStyle();
		ofSetColor(tab.active ? 100 : 150);
		ofDrawRectangle(tab.bounds);
		ofSetColor(255);
		ofDrawBitmapString(tab.label, tab.bounds.x + 10, tab.bounds.y + 30);
		ofPopStyle();
	};

	drawTabButton(imageTab);
	drawTabButton(draw2DTab);
	drawTabButton(view3DTab);
}

void UIWindow::drawStatusBox() {
	if (!statusMessage.empty()) {
		ofPushStyle();
		ofSetColor(0, 0, 0, 180);
		ofDrawRectangle(statusBox);
		ofSetColor(255);
		ofDrawBitmapString(statusMessage, statusBox.x + 10, statusBox.y + 25);
		ofPopStyle();
	}
}

void UIWindow::mousePressed(int x, int y, int button) {
	handleTabClick(x, y);
}

void UIWindow::mouseReleased(int x, int y, int button) { }

void UIWindow::handleFileDragAndDrop(ofDragInfo dragInfo) {
	if (dragInfo.files.empty()) return;
	statusMessage = "File loaded via drag & drop";
}

void UIWindow::handleTabClick(int x, int y) {
	if (imageTab.bounds.inside(x, y)) {
		activateImageTab();
	} else if (draw2DTab.bounds.inside(x, y)) {
		activateDraw2DTab();
	} else if (view3DTab.bounds.inside(x, y)) {
		activateView3DTab();
	}
}

void UIWindow::activateImageTab() {
	imageTab.active = true;
	draw2DTab.active = false;
	view3DTab.active = false;
	imagePanel.show();
	view2DPanel.hide();
	view3DPanel.hide();
	view2DActive = false;
	view3DActive = false;
	ofLogNotice("UIWindow") << "Image tab activated";
}

void UIWindow::activateDraw2DTab() {
	imageTab.active = false;
	draw2DTab.active = true;
	view3DTab.active = false;
	imagePanel.hide();
	view2DPanel.show();
	view3DPanel.hide();
	view2DActive = true;
	view3DActive = false;
	ofLogNotice("UIWindow") << "2D Edition tab activated";
}

void UIWindow::activateView3DTab() {
	imageTab.active = false;
	draw2DTab.active = false;
	view3DTab.active = true;
	imagePanel.hide();
	view2DPanel.hide();
	view3DPanel.show();
	view2DActive = false;
	view3DActive = true;
	ofLogNotice("UIWindow") << "3D Edition tab activated";
}

void UIWindow::clearRequests() {
	imagePanel.clearRequests();
	view2DPanel.clearRequests();
	view3DPanel.clearRequests();
}
