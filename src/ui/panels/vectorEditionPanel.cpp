#include "vectorEditionPanel.h"

void VectorEditionPanel::setup() {
	vectorPanel.setup("Vector tools & cursors");
	vectorPanel.setBorderColor(ofColor(0, 0));
	vectorPanel.setBackgroundColor(ofColor(0, 0, 0, 0));
	vectorPanel.enableHeader();
	vectorPanel.minimize();

	lblCursor.setup("-- Curseur --", "");
	toggleDynamicCursor.setup("Dynamic cursor", true);
	toggleCursorFeedback.setup("Feedback visuel", true);

	lblDrawingTools.setup("-- Outils --", "");
	lineThickness.setup("Line thickness", 2.0f, 0.1f, 20.0f);
	outlineOpacity.setup("Outline opacity", 1.0f, 0.0f, 1.0f);
	fillOpacity.setup("Fill opacity", 1.0f, 0.0f, 1.0f);

	lblPrimitives.setup("-- Primitives --", "");
	toggleVectorPoint.setup("Point", true);
	toggleVectorLine.setup("Line", true);
	toggleVectorCurve.setup("Curve", true);
	toggleVectorPolygon.setup("Polygon", true);

	lblTransforms.setup("-- Transformations --", "");
	toggleTranslate.setup("Translate", true);
	toggleRotate.setup("Rotate", true);
	toggleScale.setup("Scale", true);
	toggleShear.setup("Shear", false);

	lblForms.setup("-- Formes --", "");
	toggleTextShape.setup("Text", false);
	toggleIconShape.setup("Icone", false);
	toggleGroupedEditing.setup("Group editing", true);

	vectorPanel.add(&lblCursor);
	vectorPanel.add(&toggleDynamicCursor);
	vectorPanel.add(&toggleCursorFeedback);

	vectorPanel.add(&lblDrawingTools);
	vectorPanel.add(&lineThickness);
	vectorPanel.add(&outlineOpacity);
	vectorPanel.add(&fillOpacity);

	vectorPanel.add(&lblPrimitives);
	vectorPanel.add(&toggleVectorPoint);
	vectorPanel.add(&toggleVectorLine);
	vectorPanel.add(&toggleVectorCurve);
	vectorPanel.add(&toggleVectorPolygon);

	vectorPanel.add(&lblTransforms);
	vectorPanel.add(&toggleTranslate);
	vectorPanel.add(&toggleRotate);
	vectorPanel.add(&toggleScale);
	vectorPanel.add(&toggleShear);

	vectorPanel.add(&lblForms);
	vectorPanel.add(&toggleTextShape);
	vectorPanel.add(&toggleIconShape);
	vectorPanel.add(&toggleGroupedEditing);
}

void VectorEditionPanel::setPosition(float x, float y) {
	enforcedX = x;
	enforcedY = y;
	vectorPanel.setPosition(enforcedX, enforcedY);
}

void VectorEditionPanel::setWidth(float w) {
	enforcedWidth = w;
	vectorPanel.setWidthElements(enforcedWidth);
}

float VectorEditionPanel::getHeight() {
	return vectorPanel.getHeight();
}

void VectorEditionPanel::draw() {
	vectorPanel.setPosition(enforcedX, enforcedY);
	vectorPanel.setWidthElements(enforcedWidth);

	if (visible) vectorPanel.draw();
}
