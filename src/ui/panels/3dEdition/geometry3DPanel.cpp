#include "geometry3DPanel.h"

void Geometry3DPanel::setup() {
	geometryPanel.setup("Geometry & Bounding");
	geometryPanel.setBorderColor(ofColor(0, 0));
	geometryPanel.setBackgroundColor(ofColor(0, 0, 0, 0));
	// Collapsible dropdown
	geometryPanel.enableHeader();
	geometryPanel.minimize();

	lblBounds.setup("-- Boites --", "");
	toggleBoundingBox.setup("Show bounding boxes", true);

	lblPrimitives.setup("-- Primitives --", "");
	togglePrimitiveSetA.setup("Generated primitives (set A)", true);
	togglePrimitiveSetB.setup("Generated primitives (set B)", true);

	lblModels.setup("-- Modeles 3D --", "");
	toggleModelTypeA.setup("Type A", true);
	toggleModelTypeB.setup("Type B", true);
	toggleModelTypeC.setup("Type C", true);
	variantCount.setup("Variants", 2, 0, 6);

	lblLod.setup("-- LOD & Variantes --", "");
	lodLevel.setup("LOD Level", 1, 0, 5);
	toggleSimplifiedViewport.setup("Use simplified view", false);

	geometryPanel.add(&lblBounds);
	geometryPanel.add(&toggleBoundingBox);

	geometryPanel.add(&lblPrimitives);
	geometryPanel.add(&togglePrimitiveSetA);
	geometryPanel.add(&togglePrimitiveSetB);

	geometryPanel.add(&lblModels);
	geometryPanel.add(&toggleModelTypeA);
	geometryPanel.add(&toggleModelTypeB);
	geometryPanel.add(&toggleModelTypeC);
	geometryPanel.add(&variantCount);

	geometryPanel.add(&lblLod);
	geometryPanel.add(&lodLevel);
	geometryPanel.add(&toggleSimplifiedViewport);
}

void Geometry3DPanel::setPosition(float x, float y) {
	enforcedX = x;
	enforcedY = y;
	geometryPanel.setPosition(enforcedX, enforcedY);
}

void Geometry3DPanel::setWidth(float w) {
	enforcedWidth = w;
	geometryPanel.setWidthElements(enforcedWidth);
}

float Geometry3DPanel::getHeight() {
	return geometryPanel.getHeight();
}

void Geometry3DPanel::draw() {
	geometryPanel.setPosition(enforcedX, enforcedY);
	geometryPanel.setWidthElements(enforcedWidth);

	if (visible) geometryPanel.draw();
}
