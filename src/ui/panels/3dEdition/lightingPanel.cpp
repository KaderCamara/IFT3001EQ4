#include "lightingPanel.h"

LightingPanel::LightingPanel() { }
LightingPanel::~LightingPanel() { }

void LightingPanel::setup() {
	lightingPanel.setup("Lighting & Environment");
	lightingPanel.setBorderColor(ofColor(0, 0));
	lightingPanel.setBackgroundColor(ofColor(0, 0, 0, 0));
	// Collapsible dropdown
	lightingPanel.enableHeader();
	//lightingPanel.minimize();

	//lblTitle.setup("-- Global Settings --", "");
	//toggleEnvironmentMap.setup("Use Environment Map", false); // ✅ DISABLED
	//toggleHDRI.setup("HDRI Background", false); // ✅ DISABLED
	//toggleShadows.setup("Cast Shadows", false); // ✅ DISABLED
	//toggleAmbientOcclusion.setup("Ambient Occlusion", false); // ✅ DISABLED
	//toggleBloom.setup("Bloom", false); // Already disabled

	lblClassic.setup("-- Illumination Classique --", "");
	toggleLambert.setup("Lambert", false); // ✅ DISABLED
	toggleGouraud.setup("Gouraud", false); // ✅ DISABLED
	togglePhong.setup("Phong", false); // ✅ DISABLED - Start with NO shading
	toggleBlinnPhong.setup("Blinn-Phong", false); // ✅ DISABLED
	materialCount.setup("Materials", 0, 0, 8); // ✅ Set to 0
	togglePointType.setup("Point lights", false); // ✅ DISABLED
	toggleDirectionalType.setup("Directional lights", false); // ✅ DISABLED
	toggleSpotType.setup("Spot lights", false); // ✅ DISABLED
	toggleAreaType.setup("Area lights", false); // Already disabled

	lblSunLight.setup("-- Sun / Directional --", "");
	toggleSunLight.setup("Enable Sun Light", true); 
	sunIntensity.setup("Sun Intensity", 1.0f, 0.0f, 5.0f);
	sunAzimuth.setup("Azimuth", 45.0f, -180.0f, 180.0f);
	sunElevation.setup("Elevation", 35.0f, -90.0f, 90.0f);

	lblFillLights.setup("-- Fill Lights --", "");
	togglePointLight.setup("Point Light", false); // ✅ DISABLED
	pointIntensity.setup("Point Intensity", 0.7f, 0.0f, 5.0f);
	toggleSpotLight.setup("Spot Light", false); // Already disabled
	spotIntensity.setup("Spot Intensity", 1.2f, 0.0f, 5.0f);
	spotAngle.setup("Spot Angle", 30.0f, 1.0f, 90.0f);

	lblNonRealistic.setup("-- Non-Realistic Shading --", "");
	toggleFlat.setup("Flat Shading", false);
	toggleCel.setup("Cel/Toon Shading", false);
	toggleGooch.setup("Gooch Shading", false);

	lblModern.setup("-- Illumination Moderne --", "");
	togglePBR.setup("PBR shading", false); // ✅ DISABLED
	metallicity.setup("Metallic", 0.5f, 0.0f, 1.0f);
	roughness.setup("Roughness", 0.4f, 0.0f, 1.0f);
	toggleMicrofacets.setup("Microfacets", false); // ✅ DISABLED
	toggleEnvLighting.setup("Env. lighting", false); // ✅ DISABLED
	ior.setup("IOR", 1.45f, 1.0f, 3.0f);

	lblColorControls.setup("-- Color & Tone --", "");
	exposureSlider.setup("Exposure", 1.0f, 0.1f, 4.0f);
	temperatureSlider.setup("White Balance", 0.0f, -1.0f, 1.0f);
	contrastSlider.setup("Contrast", 1.0f, 0.5f, 2.0f);

	lightingPanel.add(&lblTitle);
	//lightingPanel.add(&toggleEnvironmentMap);
	//lightingPanel.add(&toggleHDRI);
	//lightingPanel.add(&toggleShadows);
	//lightingPanel.add(&toggleAmbientOcclusion);
	//lightingPanel.add(&toggleBloom);

	lightingPanel.add(&lblClassic);
	lightingPanel.add(&toggleLambert);
	lightingPanel.add(&toggleGouraud);
	lightingPanel.add(&togglePhong);
	lightingPanel.add(&toggleBlinnPhong);
	lightingPanel.add(&materialCount);
	//lightingPanel.add(&togglePointType);
	lightingPanel.add(&toggleDirectionalType);
	//lightingPanel.add(&toggleSpotType);
	//lightingPanel.add(&toggleAreaType);

	lightingPanel.add(&lblSunLight);
	lightingPanel.add(&toggleSunLight);
	lightingPanel.add(&sunIntensity);
	lightingPanel.add(&sunAzimuth);
	lightingPanel.add(&sunElevation);

	lightingPanel.add(&lblFillLights);
	//lightingPanel.add(&togglePointLight);
	//lightingPanel.add(&pointIntensity);
	//lightingPanel.add(&toggleSpotLight);
	//lightingPanel.add(&spotIntensity);
	//lightingPanel.add(&spotAngle);

	//lightingPanel.add(&lblModern);
	//lightingPanel.add(&togglePBR);
	//lightingPanel.add(&metallicity);
	//lightingPanel.add(&roughness);
	//lightingPanel.add(&toggleMicrofacets);
	//lightingPanel.add(&toggleEnvLighting);
	//lightingPanel.add(&ior);

	lightingPanel.add(&lblNonRealistic);
	lightingPanel.add(&toggleFlat);
	lightingPanel.add(&toggleCel);
	lightingPanel.add(&toggleGooch);

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
