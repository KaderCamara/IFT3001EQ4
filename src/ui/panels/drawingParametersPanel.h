// DrawingParametersPanel.h
// Panel responsable des paramètres de dessin (couleurs, lignes, HSB)
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/**
 * @class DrawingParametersPanel
 * @brief Panel UI pour les paramètres de dessin
 * 
 * Responsabilités :
 * - Gestion de l'épaisseur de ligne
 * - Couleurs (stroke, fill, background)
 * - Mode HSB (Hue, Saturation, Brightness)
 */
class DrawingParametersPanel {
public:
	DrawingParametersPanel();
	~DrawingParametersPanel() = default;

	void setup();
	void draw(float x, float y, float width);

	// Accesseurs des paramètres
	float getLineWidth() const { return lineWidth; }
	ofColor getStrokeColor() const { return strokeColor; }
	ofColor getFillColor() const { return fillColor; }
	ofColor getBackgroundColor() const { return backgroundColor; }
	bool isHSBMode() const { return useHSB; }
	float getHue() const { return hue; }
	float getSaturation() const { return saturation; }
	float getBrightness() const { return brightness; }

	// Contrôle du panel
	void show() { isVisible = true; }
	void hide() { isVisible = false; }
	bool isActive() const { return isVisible; }

private:
	bool isVisible = true; // Toujours visible quand le panel parent est actif

	// Panel ofxGui
	ofxPanel panel;

	// Paramètres de dessin
	ofParameter<float> lineWidth;
	ofParameter<ofColor> strokeColor;
	ofParameter<ofColor> fillColor;
	ofParameter<ofColor> backgroundColor;
	ofParameter<bool> useHSB;
	ofParameter<float> hue;
	ofParameter<float> saturation;
	ofParameter<float> brightness;
};
