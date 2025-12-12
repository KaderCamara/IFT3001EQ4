#include "lightingPanel.h"

LightingPanel::LightingPanel() { }
LightingPanel::~LightingPanel() { }

void LightingPanel::setup() {
	lightingPanel.setup("Lighting & Environment");
	lightingPanel.setBorderColor(ofColor(0, 0));
	lightingPanel.setBackgroundColor(ofColor(0, 0, 0, 0));
	// Collapsible dropdown
	lightingPanel.enableHeader();
	lightingPanel.minimize();

	lblTitle.setup("-- Global Settings --", "");
	toggleEnvironmentMap.setup("Use Environment Map", true);
	toggleHDRI.setup("HDRI Background", true);
	toggleShadows.setup("Cast Shadows", true);
	toggleAmbientOcclusion.setup("Ambient Occlusion", true);
	toggleBloom.setup("Bloom", false);

	lblClassic.setup("-- Illumination Classique --", "");
	toggleLambert.setup("Lambert", true);
	toggleGouraud.setup("Gouraud", true);
	togglePhong.setup("Phong", true);
	toggleBlinnPhong.setup("Blinn-Phong", true);
	materialCount.setup("Materials", 2, 0, 8);
	togglePointType.setup("Point lights", true);
	toggleDirectionalType.setup("Directional lights", true);
	toggleSpotType.setup("Spot lights", true);
	toggleAreaType.setup("Area lights", false);

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

	lblModern.setup("-- Illumination Moderne --", "");
	togglePBR.setup("PBR shading", true);
	metallicity.setup("Metallic", 0.5f, 0.0f, 1.0f);
	roughness.setup("Roughness", 0.4f, 0.0f, 1.0f);
	toggleMicrofacets.setup("Microfacets", true);
	toggleEnvLighting.setup("Env. lighting", true);
	ior.setup("IOR", 1.45f, 1.0f, 3.0f);

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

	lightingPanel.add(&lblClassic);
	lightingPanel.add(&toggleLambert);
	lightingPanel.add(&toggleGouraud);
	lightingPanel.add(&togglePhong);
	lightingPanel.add(&toggleBlinnPhong);
	lightingPanel.add(&materialCount);
	lightingPanel.add(&togglePointType);
	lightingPanel.add(&toggleDirectionalType);
	lightingPanel.add(&toggleSpotType);
	lightingPanel.add(&toggleAreaType);

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

	lightingPanel.add(&lblModern);
	lightingPanel.add(&togglePBR);
	lightingPanel.add(&metallicity);
	lightingPanel.add(&roughness);
	lightingPanel.add(&toggleMicrofacets);
	lightingPanel.add(&toggleEnvLighting);
	lightingPanel.add(&ior);

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

std::vector<ofLight> LightingPanel::getActiveLights() {
	std::vector<ofLight> lights;

	// Lumière du soleil
	if (toggleSunLight) {
		ofLight sun;
		sun.setDirectional();
		sun.setOrientation(ofVec3f(sunElevation, sunAzimuth, 0));
		sun.setDiffuseColor(ofColor::white * sunIntensity);
		lights.push_back(sun);
	}

	// Point lights
	if (togglePointLight) {
		ofLight pt;
		pt.setPointLight();
		pt.setDiffuseColor(ofColor::white * pointIntensity);
		lights.push_back(pt);
	}

	// Spot lights
	if (toggleSpotLight) {
		ofLight spot;
		spot.setSpotlight();
		spot.setDiffuseColor(ofColor::white * spotIntensity);
		spot.setSpotlightCutOff(spotAngle);
		lights.push_back(spot);
	}

	return lights;
}
