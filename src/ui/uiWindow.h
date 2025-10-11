#pragma once
// Classe s'occupant du design du UI ( buttons, menu etc )

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "../image/imageManager.h"

class UIWindow  {
public:

	void setup();
	void draw();
	void update();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);


private:

	// menu elements
	ofxButton imageTabButton;
	ofxButton editTabButton;

	//image tab elements
	ofxPanel imageMenuPanel;
	ofxButton importImageButton;
	ofxButton clearButton;
	bool showImageMenu = false;

	//general
	ofTrueTypeFont font;
	ImageManager imageManager;
	float ImageMenuwidth = 200;
	float menuBarHeight = 50;
	float buttonsWidth = 100;
	float buttonsWidthMargin = 10;

	void onImportImagePressed();
	void onClearImagePressed();
	void onImageTabPressed();
	void onEditTabPressed();
};

struct TabButton {
	string label;
	ofRectangle bounds;
	bool hovered = false;
	bool active = false;
};
