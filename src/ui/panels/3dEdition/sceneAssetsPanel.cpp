#include "sceneAssetsPanel.h"

void SceneAssetsPanel::setup() {
	panel.setup("Scene & Assets");
	panel.enableHeader();
	panel.minimize();

	viewportTitle.setup("Viewport", "");
	panel.add(&viewportTitle);
	panel.add(import3DButton.setup("Import 3D Models"));
	panel.add(clear3DButton.setup("Clear 3D Models"));
	panel.add(toggleGrid.setup("Show grid", true));
	panel.add(toggleAxes.setup("Show axes", true));
	panel.add(toggleWireframe.setup("Wireframe", false));
	panel.add(toggleBoundingBoxes.setup("Bounding boxes", false));
	panel.add(toggleNormals.setup("Show normals", false));

	lightingTitle.setup("Lighting", "");
	panel.add(&lightingTitle);
	panel.add(toggleLighting.setup("Enable lighting", false));
	panel.add(lightIntensity.setup("Light intensity", 1.0f, 0.0f, 3.0f));
	panel.add(lightColor.setup("Light color", ofColor::white, ofColor(0), ofColor(255)));

	import3DButton.addListener(this, &SceneAssetsPanel::onImport3D);
	clear3DButton.addListener(this, &SceneAssetsPanel::onClear3D);
	toggleLighting.addListener(this, &SceneAssetsPanel::onLightingToggle);
}

void SceneAssetsPanel::draw(float x, float y, float width) {
	if (!visible) return;

	panel.setPosition(x, y);
	panel.setSize(width, panel.getHeight());
	// NOTE: ofxGui version in this project does not provide setEnabled/setVisible on widgets.
	// We avoid calling those methods to remain compatible. The controls remain in the panel,
	// but their functional effect (lighting enabled/disabled) is handled elsewhere using
	// the toggle state accessed via accessors in the header.
	panel.draw();
}

void SceneAssetsPanel::clearRequests() {
	import3DRequested = false;
	clear3DRequested = false;
}

void SceneAssetsPanel::onImport3D() {
	import3DRequested = true;
	ofLogNotice("SceneAssetsPanel") << "Import 3D models requested";
}

void SceneAssetsPanel::onClear3D() {
	clear3DRequested = true;
	ofLogNotice("SceneAssetsPanel") << "Clear 3D models requested";
}

void SceneAssetsPanel::onLightingToggle(bool & value) {
	// keep intensity enabled in draw() if needed
	(void)value;
}
