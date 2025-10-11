// Classe s'occupant du design du UI ( buttons, menu etc )

#include "uiWindow.h"

TabButton imageTab = { "Image", ofRectangle(0, 0, 100, 50) };
TabButton editTab = { "Edit", ofRectangle(100, 0, 100, 50) };

void UIWindow::setup() {
	//image menu
	imageMenuPanel.setup("Image Menu");
	imageMenuPanel.add(importImageButton.setup("Import Image"));
	imageMenuPanel.add(clearButton.setup("Clear Image"));

	importImageButton.addListener(this, &UIWindow::onImportImagePressed);
	clearButton.addListener(this, &UIWindow::onClearImagePressed);
}

void UIWindow::update() {
	// No special logic yet
}

void UIWindow::draw() {
	//menu rectangle
	ofSetColor(50, 50, 50);
	ofDrawRectangle(0, 0, ofGetWidth(), menuBarHeight);

	//image panel here so it is responsive with the height and width
	imageMenuPanel.setPosition(ofGetWidth() - ImageMenuwidth, menuBarHeight);
	imageMenuPanel.setSize(ImageMenuwidth, ofGetHeight());

	for (auto & tab : { imageTab, editTab }) {
		ofSetColor(tab.active ? 100 : 150); 
		ofDrawRectangle(tab.bounds);

		ofSetColor(255);
		ofDrawBitmapString(tab.label, tab.bounds.x + 10, tab.bounds.y + 20);
	}
	if (showImageMenu) {
		imageMenuPanel.draw();
	}
	imageManager.draw();
}

void UIWindow::onImageTabPressed() {
	showImageMenu = !showImageMenu;
}

void UIWindow::onImportImagePressed() {
	imageManager.import();
}

void UIWindow::mousePressed(int x, int y, int button) {
	if (imageTab.bounds.inside(x, y)) {
		showImageMenu = !showImageMenu;
		imageTab.active = true;
		editTab.active = false;
	} else if (editTab.bounds.inside(x, y)) {
		showImageMenu = false;
		editTab.active = true;
		imageTab.active = false;
	}
}

void UIWindow::mouseReleased(int x, int y, int button) {
}

void UIWindow::onClearImagePressed() {
	imageManager.clear();
}
//exemple pour futurs éléments du menu
void UIWindow::onEditTabPressed() {
}
