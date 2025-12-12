// LightingManager.h
// Model/Service for lighting calculations and logic
#pragma once
#include "../rendering/renderData.h"
#include "ofMain.h"

/**
 * @class LightingManager
 * @brief Service for lighting calculations (MODEL/SERVICE)
 * 
 * Responsibilities:
 * - Calculate sun direction from azimuth/elevation
 * - Calculate light positions relative to scene
 * - Compute lighting equations
 * - Prepare lighting uniforms for shaders
 */
class LightingManager {
public:
	LightingManager();
	~LightingManager() = default;

	void setup();

	/**
     * @brief Initialize default materials (requirement 7.2)
     */
	void initializeDefaultMaterials();

	/**
     * @brief Initialize default lights (requirements 7.3 & 7.4)
     */
	void initializeDefaultLights();

	/**
     * @brief Get the list of available materials
     */
	const std::vector<Material> & getMaterials() const { return materials; }

	/**
     * @brief Get the list of lights
     */
	const std::vector<Light> & getLights() const { return lights; }

	/**
     * @brief Process lighting data and calculate derived values
     */
	void processLightingData(LightingData & data) const;

	/**
     * @brief Calculate light direction from azimuth/elevation
     */
	ofVec3f calculateDirectionFromAngles(float azimuth, float elevation) const;

private:
	// 7.2: At least 4 different materials
	std::vector<Material> materials;

	// 7.3 & 7.4: At least 4 light instances of different types
	std::vector<Light> lights;
};
