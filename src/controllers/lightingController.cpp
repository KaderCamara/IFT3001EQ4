// LightingController.cpp
#include "lightingController.h"

void LightingController::setup() {
	lightingManager.setup();
	ofLogNotice("LightingController") << "Lighting controller initialized";
}

LightingData LightingController::prepareLightingData(const LightingPanel & panel) {
	LightingData data;

	// Extract basic settings from panel
	data = extractFromPanel(panel);

	// Process data using lighting manager (sets default materials and lights)
	lightingManager.processLightingData(data);

	// ========== DETERMINE SHADING MODEL ==========
	// Priority order based on what's toggled on
	if (panel.isPBREnabled()) {
		data.currentModel = LightingData::ShadingModel::PBR;
	} else if (panel.isBlinnPhongEnabled()) {
		data.currentModel = LightingData::ShadingModel::BLINN_PHONG;
	} else if (panel.isPhongEnabled()) {
		data.currentModel = LightingData::ShadingModel::PHONG;
	} else if (panel.isGouraudEnabled()) {
		data.currentModel = LightingData::ShadingModel::GOURAUD;
	} else if (panel.isLambertEnabled()) {
		data.currentModel = LightingData::ShadingModel::LAMBERT;
	} else {
		// Default to FLAT if nothing is enabled (no lighting calculation)
		data.currentModel = LightingData::ShadingModel::FLAT;
	}

	// ========== SET MATERIAL INDEX ==========
	// Clamp material count to available materials
	int matCount = panel.getMaterialCount();
	if (!data.availableMaterials.empty()) {
		data.currentMaterialIndex = matCount % data.availableMaterials.size();
	} else {
		data.currentMaterialIndex = 0;
	}

	// ========== UPDATE LIGHTS BASED ON PANEL ==========
	updateLightsFromPanel(data, panel);

	// ========== PROCESS AMBIENT LIGHTS INTO globalAmbient ==========
	processAmbientLights(data);

	return data;
}

LightingData LightingController::extractFromPanel(const LightingPanel & panel) const {
	LightingData data;

	// Color/Tone
	data.exposure = panel.getExposure();
	data.temperature = panel.getTemperature();
	data.contrast = panel.getContrast();

	// Advanced settings
	data.useEnvironmentMap = panel.isEnvironmentMapEnabled();
	data.useHDRI = panel.isHDRIEnabled();
	data.castShadows = panel.isShadowsEnabled();
	data.useAmbientOcclusion = panel.isAmbientOcclusionEnabled();
	data.useBloom = panel.isBloomEnabled();

	return data;
}

void LightingController::updateLightsFromPanel(LightingData & data, const LightingPanel & panel) const {
	// Make sure we have lights from the manager
	if (data.lights.empty()) {
		ofLogWarning("LightingController") << "No lights available to update";
		return;
	}

	// Update light intensities and enabled states based on panel
	// Assuming default light order from LightingManager:
	// [0] = Ambient
	// [1] = Directional (Sun)
	// [2] = Point
	// [3] = Spot

	// ========== UPDATE AMBIENT LIGHT (index 0) ==========
	if (data.lights.size() > 0 && data.lights[0].type == Light::Type::AMBIENT) {
		data.lights[0].enabled = true; // Always enabled
		data.lights[0].intensity = 0.3f; // Keep default or make configurable
	}

	// ========== UPDATE DIRECTIONAL/SUN LIGHT (index 1) ==========
	if (data.lights.size() > 1 && data.lights[1].type == Light::Type::DIRECTIONAL) {
		data.lights[1].enabled = panel.isSunLightEnabled();
		data.lights[1].intensity = panel.getSunIntensity();

		// Calculate direction from azimuth and elevation
		float azimuth = panel.getSunAzimuth();
		float elevation = panel.getSunElevation();
		data.lights[1].direction = lightingManager.calculateDirectionFromAngles(azimuth, elevation);
		data.lights[1].direction.normalize(); // Ensure normalized
	}

	// ========== UPDATE POINT LIGHT (index 2) ==========
	if (data.lights.size() > 2 && data.lights[2].type == Light::Type::POINT) {
		data.lights[2].enabled = panel.isPointLightEnabled();
		data.lights[2].intensity = panel.getPointIntensity();
		// Position stays as set by LightingManager (or could be made configurable)
	}

	// ========== UPDATE SPOT LIGHT (index 3) ==========
	if (data.lights.size() > 3 && data.lights[3].type == Light::Type::SPOT) {
		data.lights[3].enabled = panel.isSpotLightEnabled();
		data.lights[3].intensity = panel.getSpotIntensity();
		data.lights[3].spotCutoff = panel.getSpotAngle();
		data.lights[3].direction.normalize(); // Ensure normalized
		// Position stays as set by LightingManager (or could be made configurable)
	}

	ofLogNotice("LightingController") << "Updated lights from panel";
}

void LightingController::processAmbientLights(LightingData & data) const {
	// Separate ambient lights from regular lights
	// Ambient lights contribute to globalAmbient, not passed as lights to shader
	std::vector<Light> regularLights;
	ofColor globalAmbient(0, 0, 0);

	for (const auto & light : data.lights) {
		if (light.type == Light::Type::AMBIENT && light.enabled) {
			// Accumulate ambient light into globalAmbient
			ofColor ambientContribution = light.color;
			ambientContribution *= light.intensity;
			globalAmbient.r = std::min(255, globalAmbient.r + ambientContribution.r);
			globalAmbient.g = std::min(255, globalAmbient.g + ambientContribution.g);
			globalAmbient.b = std::min(255, globalAmbient.b + ambientContribution.b);
		} else if (light.enabled) {
			// Only pass non-ambient, enabled lights to shader
			regularLights.push_back(light);
		}
	}

	// Update data
	data.globalAmbient = globalAmbient;
	data.lights = regularLights;

	ofLogNotice("LightingController") << "Processed lights: "
									  << data.lights.size() << " regular, globalAmbient RGB("
									  << (int)data.globalAmbient.r << ","
									  << (int)data.globalAmbient.g << ","
									  << (int)data.globalAmbient.b << ")";
}
