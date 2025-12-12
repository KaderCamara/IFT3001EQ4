// TransformPanel.h
// Panel responsable des transformations (translation, rotation, scale)
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class TransformPanel
 * @brief Panel UI pour les transformations de formes
 * 
 * Responsabilités :
 * - Translation X/Y
 * - Rotation
 * - Scale (mise à l'échelle)
 */
class TransformPanel {
public:
	TransformPanel();
	~TransformPanel() = default;

	void setup();
	void draw(float x, float y, float width, float windowWidth, float windowHeight);

	// Accesseurs des paramètres
	float getTranslateX() const { return translateX; }
	float getTranslateY() const { return translateY; }
	float getRotation() const { return rotation; }
	float getScale() const { return scaleFactor; }

	// Contrôle du panel
	void show() { isVisible = true; }
	void hide() { isVisible = false; }
	bool isActive() const { return isVisible; }

private:
	bool isVisible = false; // Visible uniquement en mode sélection

	// Panel ofxGui
	ofxPanel panel;

	// Paramètres de transformation
	ofParameter<float> translateX, translateY;
	ofParameter<float> rotation;
	ofParameter<float> scaleFactor;
};
