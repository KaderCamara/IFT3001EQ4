// LightingManager.cpp
#include "lightingManager.h"

LightingManager::LightingManager() {
	initializeDefaultMaterials();
	initializeDefaultLights();
}

void LightingManager::setup() {
	ofLogNotice("LightingManager") << "Lighting manager initialized with "
								   << materials.size() << " materials and "
								   << lights.size() << " lights";
}

void LightingManager::initializeDefaultMaterials() {
	materials.clear();

	// Material 0: BRIGHT WHITE (for debugging) ✅ ADDED
	Material white;
	white.name = "White";
	white.ambient = ofColor(100, 100, 100);
	white.diffuse = ofColor(200, 200, 200); // ✅ Bright diffuse
	white.specular = ofColor(255, 255, 255);
	white.shininess = 32.0f;
	white.metallic = 0.0f;
	white.roughness = 0.5f;
	materials.push_back(white);

	// Material 1: Plastic (shiny)
	Material plastic;
	plastic.name = "Plastic";
	plastic.ambient = ofColor(50, 50, 50);
	plastic.diffuse = ofColor(200, 200, 200);
	plastic.specular = ofColor(255, 255, 255);
	plastic.shininess = 64.0f;
	plastic.metallic = 0.0f;
	plastic.roughness = 0.3f;
	materials.push_back(plastic);

	// Material 2: Metal (gold-like)
	Material metal;
	metal.name = "Gold";
	metal.ambient = ofColor(100, 85, 30);
	metal.diffuse = ofColor(255, 215, 0);
	metal.specular = ofColor(255, 255, 200);
	metal.shininess = 128.0f;
	metal.metallic = 1.0f;
	metal.roughness = 0.2f;
	materials.push_back(metal);

	// Material 3: Rubber (matte)
	Material rubber;
	rubber.name = "Rubber";
	rubber.ambient = ofColor(30, 30, 30);
	rubber.diffuse = ofColor(150, 150, 150);
	rubber.specular = ofColor(50, 50, 50);
	rubber.shininess = 8.0f;
	rubber.metallic = 0.0f;
	rubber.roughness = 0.8f;
	materials.push_back(rubber);

	// Material 4: Jade (semi-shiny, colored)
	Material jade;
	jade.name = "Jade";
	jade.ambient = ofColor(30, 60, 50);
	jade.diffuse = ofColor(84, 204, 153);
	jade.specular = ofColor(127, 255, 212);
	jade.shininess = 32.0f;
	jade.metallic = 0.1f;
	jade.roughness = 0.4f;
	materials.push_back(jade);

	ofLogNotice("LightingManager") << "Initialized " << materials.size() << " materials";
}

void LightingManager::initializeDefaultLights() {
	lights.clear();

	// Light 1: Ambient light - VERY BRIGHT for testing
	Light ambient;
	ambient.type = Light::Type::AMBIENT;
	ambient.enabled = true;
	ambient.color = ofColor(255, 255, 255); // ✅ FULL WHITE
	ambient.intensity = 0.5f; // ✅ 50% intensity
	lights.push_back(ambient);
	// Expected: globalAmbient RGB(127,127,127)

	// Light 2: Directional light (sun)
	Light directional;
	directional.type = Light::Type::DIRECTIONAL;
	directional.enabled = true;
	directional.color = ofColor(255, 250, 240);
	directional.intensity = 1.0f;
	directional.direction = ofVec3f(0.3f, -1.0f, 0.5f).normalize();
	lights.push_back(directional);

	// Light 3: Point light
	Light point;
	point.type = Light::Type::POINT;
	point.enabled = true;
	point.color = ofColor(255, 200, 150);
	point.intensity = 1.5f;
	point.position = ofVec3f(300, 200, 200);
	point.constantAttenuation = 1.0f;
	point.linearAttenuation = 0.09f;
	point.quadraticAttenuation = 0.032f;
	lights.push_back(point);

	// Light 4: Spot light
	Light spot;
	spot.type = Light::Type::SPOT;
	spot.enabled = true;
	spot.color = ofColor(200, 220, 255);
	spot.intensity = 2.0f;
	spot.position = ofVec3f(0, 400, 0);
	spot.direction = ofVec3f(0, -1, 0);
	spot.spotCutoff = 30.0f;
	spot.spotExponent = 2.0f;
	spot.constantAttenuation = 1.0f;
	spot.linearAttenuation = 0.09f;
	spot.quadraticAttenuation = 0.032f;
	lights.push_back(spot);

	ofLogNotice("LightingManager") << "Initialized " << lights.size() << " lights (ambient at FULL brightness for testing)";
}

void LightingManager::processLightingData(LightingData & data) const {
	// Set materials if not already set
	if (data.availableMaterials.empty()) {
		data.availableMaterials = materials;
	}

	// Set lights if not already set
	if (data.lights.empty()) {
		data.lights = lights;
	}

	// Process each light's direction if needed
	for (auto & light : data.lights) {
		if (light.type == Light::Type::DIRECTIONAL || light.type == Light::Type::SPOT) {
			light.direction.normalize();
		}
	}
}

ofVec3f LightingManager::calculateDirectionFromAngles(float azimuth, float elevation) const {
	float azimuthRad = ofDegToRad(azimuth);
	float elevationRad = ofDegToRad(elevation);

	float x = cos(elevationRad) * sin(azimuthRad);
	float y = sin(elevationRad);
	float z = cos(elevationRad) * cos(azimuthRad);

	return ofVec3f(x, y, z).normalize();
}
