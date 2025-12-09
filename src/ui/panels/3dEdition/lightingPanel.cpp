#include "lightingPanel.h"

LightingPanel::LightingPanel() {
}

LightingPanel::~LightingPanel() {
}

void LightingPanel::setup() {
	lightingPanel.setup("Lighting & Environment");
	lightingPanel.setBorderColor(ofColor(0, 0));
	lightingPanel.setBackgroundColor(ofColor(0, 0, 0, 0));

	lblTitle.setup("-- Global Settings --", "");
	toggleEnvironmentMap.setup("Use Environment Map", true);
	toggleHDRI.setup("HDRI Background", true);
	toggleShadows.setup("Cast Shadows", true);
	toggleAmbientOcclusion.setup("Ambient Occlusion", true);
	toggleBloom.setup("Bloom", false);

	lblSunLight.setup("-- Sun / Directional --", "");
	toggleSunLight.setup("Enable Sun Light", true);
	sunIntensity.setup("Sun Intensity", 1.0f, 0.0f, 5.0f);
	sunAzimuth.setup("Azimuth", 45.0f, -180.0f, 180.0f);
	sunElevation.setup("Elevation", 35.0f, -90.0f, 90.0f);

	lblFillLights.setup("-- Fill Lights --", "");
	togglePointLight.setup("Point Light", true);
	pointIntensity.setup("Point Intensity", 0.7f, 0.0f, 5.0f);
	toggleSpotLight.setup("Spot Light", false);
	spotIntensity.setup("Spot Intensity", 1.2f, 0.0f, 5.0f);
	spotAngle.setup("Spot Angle", 30.0f, 1.0f, 90.0f);

	lblColorControls.setup("-- Color & Tone --", "");
	exposureSlider.setup("Exposure", 1.0f, 0.1f, 4.0f);
	temperatureSlider.setup("White Balance", 0.0f, -1.0f, 1.0f);
	contrastSlider.setup("Contrast", 1.0f, 0.5f, 2.0f);

	lightingPanel.add(&lblTitle);
	lightingPanel.add(&toggleEnvironmentMap);
	lightingPanel.add(&toggleHDRI);
	lightingPanel.add(&toggleShadows);
	lightingPanel.add(&toggleAmbientOcclusion);
	lightingPanel.add(&toggleBloom);

	lightingPanel.add(&lblSunLight);
	lightingPanel.add(&toggleSunLight);
	lightingPanel.add(&sunIntensity);
	lightingPanel.add(&sunAzimuth);
	lightingPanel.add(&sunElevation);

	lightingPanel.add(&lblFillLights);
	lightingPanel.add(&togglePointLight);
	lightingPanel.add(&pointIntensity);
	lightingPanel.add(&toggleSpotLight);
	lightingPanel.add(&spotIntensity);
	lightingPanel.add(&spotAngle);

	lightingPanel.add(&lblColorControls);
	lightingPanel.add(&exposureSlider);
	lightingPanel.add(&temperatureSlider);
	lightingPanel.add(&contrastSlider);
}

void LightingPanel::setPosition(float x, float y) {
	enforcedX = x;
	enforcedY = y;
	lightingPanel.setPosition(enforcedX, enforcedY);
}

void LightingPanel::setWidth(float w) {
	enforcedWidth = w;
	lightingPanel.setWidthElements(enforcedWidth);
}

float LightingPanel::getHeight() {
	return lightingPanel.getHeight();
}

void LightingPanel::update() {
	// Placeholder pour une logique future lie a l'eclairage
}

void LightingPanel::draw() {
	lightingPanel.setPosition(enforcedX, enforcedY);
	lightingPanel.setWidthElements(enforcedWidth);

	if (visible) lightingPanel.draw();
}

void LightingPanel::show() { visible = true; }
void LightingPanel::hide() { visible = false; }
bool LightingPanel::isVisible() const { return visible; }
