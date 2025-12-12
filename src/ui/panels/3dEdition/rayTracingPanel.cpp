#include "rayTracingPanel.h"
#include <objects/shape.h>


void RayTracingPanel::setup() {
	rayPanel.setup("Ray Tracing");
	rayPanel.setBorderColor(ofColor(0, 0));
	rayPanel.setBackgroundColor(ofColor(0, 0, 0, 0));
	// Collapsible dropdown
	rayPanel.enableHeader();
	rayPanel.minimize();

	lblCore.setup("-- Coeur --", "");
	toggleIntersection.setup("Intersection tests", true);
	toggleReflection.setup("Reflection", true);
	toggleRefraction.setup("Refraction", true);
	toggleShadows.setup("Shadows", true);

	lblGi.setup("-- Illumination Globale --", "");
	toggleGlobalIllumination.setup("Global illumination", false);
	bounceCount.setup("Light bounces", 1, 0, 5);

	rayPanel.add(&lblCore);
	rayPanel.add(&toggleIntersection);
	rayPanel.add(&toggleReflection);
	rayPanel.add(&toggleRefraction);
	rayPanel.add(&toggleShadows);

	rayPanel.add(&lblGi);
	rayPanel.add(&toggleGlobalIllumination);
	rayPanel.add(&bounceCount);
}

void RayTracingPanel::setPosition(float x, float y) {
	enforcedX = x;
	enforcedY = y;
	rayPanel.setPosition(enforcedX, enforcedY);
}

void RayTracingPanel::setWidth(float w) {
	enforcedWidth = w;
	rayPanel.setWidthElements(enforcedWidth);
}

float RayTracingPanel::getHeight() {
	return rayPanel.getHeight();
}

void RayTracingPanel::draw() {
	rayPanel.setPosition(enforcedX, enforcedY);
	rayPanel.setWidthElements(enforcedWidth);

	if (visible) rayPanel.draw();
}

bool RayTracingPanel::isGlobalIlluminationEnabled() const {
	return static_cast<ofParameter<bool> &>(const_cast<ofxToggle &>(toggleGlobalIllumination).getParameter()).get();
}

int RayTracingPanel::getBounceCount() const {
	return static_cast<ofParameter<int> &>(const_cast<ofxIntSlider &>(bounceCount).getParameter()).get();
}

void RayTracingPanel::renderSceneWithGI(
	const std::vector<Shape> & shapes,
	ofEasyCam & cam,
	const LightingPanel & lighting) {
	// NE PAS refaire cam.begin() ici (c’est déjà fait par View3DPanel)

	ofEnableDepthTest();
	ofEnableLighting();

	// Obtenir les lumières réelles (pointeurs)
	auto & lightPanelNonConst = const_cast<LightingPanel &>(lighting);
	std::vector<ofLight *> lights = lightPanelNonConst.getActiveLights();

	// Activer les lumières
	for (auto * l : lights) {
		if (l) l->enable();
	}

	// --- DRAW 3D ---
	for (const auto & s : shapes) {
		s.mesh3D.drawFaces(); // meilleur shading
	}

	// Désactiver lumières
	for (auto * l : lights) {
		if (l) l->disable();
	}

	ofDisableLighting();
	ofDisableDepthTest();
}
