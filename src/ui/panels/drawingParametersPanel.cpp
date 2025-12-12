// DrawingParametersPanel.cpp
// Implémentation du panel de paramètres de dessin
#include "DrawingParametersPanel.h"

DrawingParametersPanel::DrawingParametersPanel() {
}

void DrawingParametersPanel::setup() {
	panel.setup("Drawing Parameters");
	panel.enableHeader();
	panel.minimize();
	panel.add(lineWidth.set("Line Width", 2.0, 1.0, 10.0));
	panel.add(strokeColor.set("Stroke Color", ofColor(0, 0, 0)));
	panel.add(fillColor.set("Fill Color", ofColor(255, 0, 0)));
	panel.add(backgroundColor.set("Background", ofColor(180, 200, 220)));
	panel.add(useHSB.set("HSB Mode", false));
	panel.add(hue.set("Hue", 128, 0, 255));
	panel.add(saturation.set("Saturation", 255, 0, 255));
	panel.add(brightness.set("Brightness", 255, 0, 255));

	ofLogNotice("DrawingParametersPanel") << "Setup complete";
}

void DrawingParametersPanel::draw(float x, float y, float width) {
	if (!isVisible) return;

	panel.setPosition(x, y);
	panel.setSize(width, 200);
	panel.draw();
}

float DrawingParametersPanel::getHeight() const {
	// ofxGuiGroup::getHeight() already returns header-only height when minimized
	return panel.getHeight();
}
