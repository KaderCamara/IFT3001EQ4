#include "topologyPanel.h"

void TopologyPanel::setup() {
	topologyPanel.setup("Topologie & Courbes");
	topologyPanel.setBorderColor(ofColor(0, 0));
	topologyPanel.setBackgroundColor(ofColor(0, 0, 0, 0));
	// Collapsible dropdown
	topologyPanel.enableHeader();
	topologyPanel.minimize();

	lblTriangulation.setup("-- Triangulation --", "");
	toggleTriangulation.setup("Delaunay/Voronoi", true);
	toggleVoronoi.setup("Voronoi diagram", false);

	lblCurves.setup("-- Courbes --", "");
	toggleBezierCurve.setup("Bezier", true);
	toggleBSplineCurve.setup("B-Spline", true);

	lblSurfaces.setup("-- Surfaces --", "");
	toggleBezierSurface.setup("Bezier surface", true);
	toggleCoonsSurface.setup("Coons patch", false);

	lblDisplacement.setup("-- Relief --", "");
	toggleHeightMap.setup("Height map", true);
	toggleNormalMap.setup("Normal map", true);

	lblAnimation.setup("-- Animation --", "");
	toggleAnimationCurve.setup("Animation curve", true);
	animationSamples.setup("Samples", 10, 2, 64);

	topologyPanel.add(&lblTriangulation);
	topologyPanel.add(&toggleTriangulation);
	topologyPanel.add(&toggleVoronoi);

	topologyPanel.add(&lblCurves);
	topologyPanel.add(&toggleBezierCurve);
	topologyPanel.add(&toggleBSplineCurve);

	topologyPanel.add(&lblSurfaces);
	topologyPanel.add(&toggleBezierSurface);
	topologyPanel.add(&toggleCoonsSurface);

	topologyPanel.add(&lblDisplacement);
	topologyPanel.add(&toggleHeightMap);
	topologyPanel.add(&toggleNormalMap);

	topologyPanel.add(&lblAnimation);
	topologyPanel.add(&toggleAnimationCurve);
	topologyPanel.add(&animationSamples);
}

void TopologyPanel::setPosition(float x, float y) {
	enforcedX = x;
	enforcedY = y;
	topologyPanel.setPosition(enforcedX, enforcedY);
}

void TopologyPanel::setWidth(float w) {
	enforcedWidth = w;
	topologyPanel.setWidthElements(enforcedWidth);
}

float TopologyPanel::getHeight() {
	return topologyPanel.getHeight();
}

void TopologyPanel::draw() {
	topologyPanel.setPosition(enforcedX, enforcedY);
	topologyPanel.setWidthElements(enforcedWidth);

	if (visible) topologyPanel.draw();
}
