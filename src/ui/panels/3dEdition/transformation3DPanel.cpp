#include "transformation3DPanel.h"

void Transformation3DPanel::setup() {
	transformPanel.setup("Scene & Transformations");
	transformPanel.setBorderColor(ofColor(0, 0));
	transformPanel.setBackgroundColor(ofColor(0, 0, 0, 0));
	// Collapsible dropdown
	transformPanel.enableHeader();
	transformPanel.minimize();

	lblSceneGraph.setup("-- Scene Graph --", "");
	toggleSceneGraph.setup("Enable hierarchy", true);
	toggleMultipleSelection.setup("Multiple selection", true);
	toggleParenting.setup("Allow parenting", true);

	lblTransforms.setup("-- Transformations --", "");
	toggleTranslate.setup("Translate", true);
	toggleRotate.setup("Rotate", true);
	toggleScale.setup("Scale", true);
	toggleGizmo.setup("Transform gizmo", true);

	lblHistory.setup("-- Historique --", "");
	btnUndo.setup("Undo");
	btnRedo.setup("Redo");

	lblSnapping.setup("-- Snapping --", "");
	toggleSnapping.setup("Enable snapping", false);
	snapTranslation.setup("Position snap", 0.5f, 0.0f, 10.0f);
	snapRotation.setup("Rotation snap", 15.0f, 0.0f, 90.0f);
	snapScale.setup("Scale snap", 0.1f, 0.0f, 5.0f);

	transformPanel.add(&lblSceneGraph);
	transformPanel.add(&toggleSceneGraph);
	transformPanel.add(&toggleMultipleSelection);
	transformPanel.add(&toggleParenting);

	transformPanel.add(&lblTransforms);
	transformPanel.add(&toggleTranslate);
	transformPanel.add(&toggleRotate);
	transformPanel.add(&toggleScale);
	transformPanel.add(&toggleGizmo);

	transformPanel.add(&lblHistory);
	transformPanel.add(&btnUndo);
	transformPanel.add(&btnRedo);

	transformPanel.add(&lblSnapping);
	transformPanel.add(&toggleSnapping);
	transformPanel.add(&snapTranslation);
	transformPanel.add(&snapRotation);
	transformPanel.add(&snapScale);
}

void Transformation3DPanel::setPosition(float x, float y) {
	enforcedX = x;
	enforcedY = y;
	transformPanel.setPosition(enforcedX, enforcedY);
}

void Transformation3DPanel::setWidth(float w) {
	enforcedWidth = w;
	transformPanel.setWidthElements(enforcedWidth);
}

float Transformation3DPanel::getHeight() {
	return transformPanel.getHeight();
}

void Transformation3DPanel::draw() {
	transformPanel.setPosition(enforcedX, enforcedY);
	transformPanel.setWidthElements(enforcedWidth);

	if (visible) transformPanel.draw();
}
