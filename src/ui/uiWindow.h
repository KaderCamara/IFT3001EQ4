// uiWindow.h
// Classe orchestratrice de l'interface utilisateur
// Gère les onglets et délègue aux panels spécialisés
#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "panels/CurvesPanel.h"
#include "panels/DrawingPanel.h"
#include "panels/ImagePanel.h"
#include "panels/View3DPanel.h"
#include "panels/3dEdition/CameraPanel.h"

/**
 * @class UIWindow
 * @brief Orchestrateur principal de l'interface utilisateur
 * 
 * Responsabilités :
 * - Gérer les onglets (Image, Draw, 3D View, Curves)
 * - Déléguer aux panels spécialisés
 * - Gérer la zone de dessin
 * - Afficher les messages de statut
 * - Gérer le drag & drop de fichiers
 */
class UIWindow {
public:
	UIWindow() = default;
	~UIWindow() = default;

	void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void handleFileDragAndDrop(ofDragInfo dragInfo);

	public:
	// ========== ACCESSEURS GÉNÉRAUX ==========
	ofRectangle getDrawingArea() const { return drawingArea; }

	// ========== DRAWING PANEL ==========
	std::string getCurrentShape() const { return drawingPanel.getCurrentShape(); }
	bool isSaveShapeRequested() const { return drawingPanel.isSaveShapeRequested(); }
	bool isDeleteShapeRequested() const { return drawingPanel.isDeleteShapeRequested(); }
	bool isSelectShapeRequested() const { return drawingPanel.isSelectionMode(); }

	float getLineWidth() const { return drawingPanel.getLineWidth(); }
	ofColor getStrokeColor() const { return drawingPanel.getStrokeColor(); }
	ofColor getFillColor() const { return drawingPanel.getFillColor(); }
	ofColor getBackgroundColor() const { return drawingPanel.getBackgroundColor(); }
	bool isHSBMode() const { return drawingPanel.isHSBMode(); }
	float getHue() const { return drawingPanel.getHue(); }
	float getSaturation() const { return drawingPanel.getSaturation(); }
	float getBrightness() const { return drawingPanel.getBrightness(); }

	float getTranslateX() const { return drawingPanel.getTranslateX(); }
	float getTranslateY() const { return drawingPanel.getTranslateY(); }
	float getRotation() const { return drawingPanel.getRotation(); }
	float getScale() const { return drawingPanel.getScale(); }

	// ========== IMAGE PANEL ==========
	bool isImportImageRequested() const { return imagePanel.isImportImageRequested(); }
	bool isClearImageRequested() const { return imagePanel.isClearImageRequested(); }
	bool isImport3DModelRequested() const { return imagePanel.isImport3DModelRequested(); }
	bool isClear3DModelRequested() const { return imagePanel.isClear3DModelRequested(); }
	void clearImport3DModelRequest() { imagePanel.clearRequests(); }
	void clearClear3DModelRequest() { imagePanel.clearRequests(); }

	// ========== VIEW3D PANEL ==========
	bool is3DviewRequested() const { return view3DActive; }
	bool is2DviewRequested() const { return !view3DActive && !isQuadViewRequested(); }
	bool isQuadViewRequested() const { return view3DPanel.isQuadViewRequested(); }
	bool isShowBoundingBoxEnabled() const { return view3DPanel.isShowBoundingBoxToggled(); } 
	bool isWireframeEnabled() const { return view3DPanel.isShowWireframeToggled(); }

	// ========== CURVES PANEL ==========
	bool isPlacePointsMode() const { return curvesPanel.isPlacePointsMode(); }
	bool isGenerateCurveRequested() const { return curvesPanel.isGenerateCurveRequested(); }
	bool isClearCurvesRequested() const { return curvesPanel.isClearCurvesRequested(); }
	bool isUndoPointRequested() const { return curvesPanel.isUndoPointRequested(); }
	bool isClearPointsRequested() const { return curvesPanel.isClearPointsRequested(); }
	bool getPlacePointsModeState() const { return curvesPanel.isPlacePointsMode(); }

	void clearGenerateCurveRequest() { curvesPanel.clearRequests(); }
	void clearClearCurvesRequest() { curvesPanel.clearRequests(); }
	void clearUndoPointRequest() { curvesPanel.clearRequests(); }
	void clearClearPointsRequest() { curvesPanel.clearRequests(); }

	// ========== CONTRÔLE DES REQUÊTES ==========
	void clearRequests();

	// Status message public pour compatibilité
	std::string statusMessage;

	// Place points mode public pour compatibilité (sera supprimé après refacto complète)
	bool placePointsMode = false;

private:
	// ========== PANELS ==========
	DrawingPanel drawingPanel;
	ImagePanel imagePanel;
	View3DPanel view3DPanel;
	CurvesPanel curvesPanel;
	CameraPanel cameraPanel;

	// ========== ONGLETS ==========
	struct TabButton {
		std::string label;
		ofRectangle bounds;
		bool hovered = false;
		bool active = false;
	};

	TabButton imageTab = { "Image", ofRectangle(0, 0, 100, 50) };
	TabButton drawTab = { "Draw", ofRectangle(100, 0, 100, 50) };
	TabButton view3DTab = { "3D view", ofRectangle(200, 0, 100, 50) };
	TabButton curvesTab = { "Curves", ofRectangle(300, 0, 100, 50) };

	// ========== ZONES UI ==========
	ofRectangle drawingArea;
	ofRectangle statusBox;
	float menuBarHeight = 50;

	// ========== ÉTAT GLOBAL ==========
	bool view3DActive = false;

	// ========== MÉTHODES PRIVÉES ==========
	void drawTabs();
	void drawStatusBox();
	void handleTabClick(int x, int y);
	void activateImageTab();
	void activateDrawTab();
	void activateView3DTab();
	void activateCurvesTab();
};
