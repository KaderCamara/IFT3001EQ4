// LightingController.h
// Controller for lighting system (CONTROLLER)
#pragma once
#include "../objects/lightingManager.h"
#include "../rendering/renderData.h"
#include "../ui/panels/3dEdition/lightingPanel.h"
#include "ofMain.h"

/**
 * @class LightingController
 * @brief Controller for lighting system (CONTROLLER)
 * 
 * Responsibilities:
 * - Read values from LightingPanel (UI)
 * - Coordinate with LightingManager (MODEL)
 * - Prepare LightingData for rendering
 * - NO rendering logic
 */
class LightingController {
public:
	LightingController() = default;
	~LightingController() = default;

	void setup();

	/**
     * @brief Prepare lighting data from UI panel
     * @param panel Reference to the lighting UI panel
     * @return Complete lighting data ready for rendering
     */
	LightingData prepareLightingData(const LightingPanel & panel);

	/**
     * @brief Get reference to lighting manager
     */
	LightingManager & getLightingManager() { return lightingManager; }

private:
	LightingManager lightingManager;

	/**
     * @brief Extract lighting parameters from UI panel
     */
	LightingData extractFromPanel(const LightingPanel & panel) const;
	void updateLightsFromPanel(LightingData & data, const LightingPanel & panel) const;
	void processAmbientLights(LightingData & data) const;
};
