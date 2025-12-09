#include "sceneHierarchyPanel.h"

SceneHierarchyPanel::SceneHierarchyPanel() {
}

SceneHierarchyPanel::~SceneHierarchyPanel() {
}

void SceneHierarchyPanel::setup() {
	hierarchyPanel.setup("Scene Hierarchy");
	hierarchyPanel.setBorderColor(ofColor(0, 0));
	hierarchyPanel.setBackgroundColor(ofColor(0, 0, 0, 0));

	lblTitle.setup("-- Objects & Layers --", "");
	btnAddEmpty.setup("+ Empty Object");
	btnAddPrimitive.setup("+ Primitive Mesh");
	btnAddLight.setup("+ Light");
	btnDuplicate.setup("Duplicate Selection");
	btnDelete.setup("Delete / Hide");

	lblFilters.setup("-- Filters --", "");
	toggleShowMeshes.setup("Show Meshes", true);
	toggleShowLights.setup("Show Lights", true);
	toggleShowCameras.setup("Show Cameras", true);
	toggleLockSelection.setup("Lock Selection", false);
	toggleSoloSelection.setup("Solo Selected", false);

	lblObjects.setup("-- Scene Graph --", "");
	cameraEntry.set(false);
	meshEntry.set(false);
	lightEntry.set(false);
	helperEntry.set(false);

	lblParenting.setup("-- Helpers --", "");
	toggleSnapToGrid.setup("Snap to Grid", true);
	toggleInheritTransform.setup("Inherit Transform", true);
	toggleShowGizmos.setup("Show Gizmos", true);

	hierarchyPanel.add(&lblTitle);
	hierarchyPanel.add(&btnAddEmpty);
	hierarchyPanel.add(&btnAddPrimitive);
	hierarchyPanel.add(&btnAddLight);
	hierarchyPanel.add(&btnDuplicate);
	hierarchyPanel.add(&btnDelete);

	hierarchyPanel.add(&lblFilters);
	hierarchyPanel.add(&toggleShowMeshes);
	hierarchyPanel.add(&toggleShowLights);
	hierarchyPanel.add(&toggleShowCameras);
	hierarchyPanel.add(&toggleLockSelection);
	hierarchyPanel.add(&toggleSoloSelection);

	hierarchyPanel.add(&lblObjects);
	hierarchyPanel.add(cameraEntry);
	hierarchyPanel.add(meshEntry);
	hierarchyPanel.add(lightEntry);
	hierarchyPanel.add(helperEntry);

	hierarchyPanel.add(&lblParenting);
	hierarchyPanel.add(&toggleSnapToGrid);
	hierarchyPanel.add(&toggleInheritTransform);
	hierarchyPanel.add(&toggleShowGizmos);
}

void SceneHierarchyPanel::setPosition(float x, float y) {
	enforcedX = x;
	enforcedY = y;
	hierarchyPanel.setPosition(enforcedX, enforcedY);
}

void SceneHierarchyPanel::setWidth(float w) {
	enforcedWidth = w;
	hierarchyPanel.setWidthElements(enforcedWidth);
}

float SceneHierarchyPanel::getHeight() {
	return hierarchyPanel.getHeight();
}

void SceneHierarchyPanel::update() {
	// Placeholder pour une logique future (synchroniser avec la scene)
}

void SceneHierarchyPanel::draw() {
	hierarchyPanel.setPosition(enforcedX, enforcedY);
	hierarchyPanel.setWidthElements(enforcedWidth);

	if (visible) hierarchyPanel.draw();
}

void SceneHierarchyPanel::show() { visible = true; }
void SceneHierarchyPanel::hide() { visible = false; }
bool SceneHierarchyPanel::isVisible() const { return visible; }
