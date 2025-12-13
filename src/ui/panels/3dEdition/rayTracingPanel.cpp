#include "rayTracingPanel.h"

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
	return static_cast<ofParameter<bool> &>(
		const_cast<ofxToggle &>(toggleGlobalIllumination).getParameter())
		.get();
}

// Getter const pour le nombre de rebonds
int RayTracingPanel::getBounceCount() const {
	return static_cast<ofParameter<int> &>(
		const_cast<ofxIntSlider &>(bounceCount).getParameter())
		.get();
}
