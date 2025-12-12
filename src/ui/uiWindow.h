// uiWindow.h
// Classe orchestratrice de l'interface utilisateur
// Gre les onglets et dlgue aux panels spcialiss
#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "panels/DrawingPanel.h"
#include "panels/ImagePanel.h"
#include "panels/InfoPanel.h"
#include "panels/View3DPanel.h"
#include <vector>

	/**
 * @class UIWindow
 * @brief Orchestrateur principal de l'interface utilisateur
 *
 * Responsabilits :
 * - Grer les onglets (Image, 2D Edition, 3D Edition)
 * - Dlguer aux panels spcialiss
 * - Grer la zone de dessin
 * - Afficher les messages de statut
 * - Grer le drag & drop de fichiers
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
	// ========== ACCESSEURS GNRAUX ==========
	ofRectangle getDrawingArea() const { return drawingArea; }
	ofRectangle getDrawDrawingArea() const { return drawDrawingArea; }
	ofRectangle getCurvesDrawingArea() const { return curvesDrawingArea; }

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

	// ========== VIEW3D PANEL ==========
	bool isImport3DModelRequested() const { return view3DPanel.isImport3DModelRequested(); }
	bool isClear3DModelRequested() const { return view3DPanel.isClear3DModelRequested(); }
	bool is3DviewRequested() const { return view3DActive; }
	bool is2DviewRequested() const { return !view3DActive && !isQuadViewRequested(); }
	bool isQuadViewRequested() const { return view3DPanel.isQuadViewRequested(); }
	bool isShowBoundingBoxEnabled() const { return view3DPanel.isShowBoundingBoxToggled(); }
	bool isWireframeEnabled() const { return view3DPanel.isShowWireframeToggled(); }
	bool isGridEnabled() const { return view3DPanel.isGridEnabled(); }
	bool isAxesEnabled() const { return view3DPanel.isAxesEnabled(); }
	bool isNormalsEnabled() const { return view3DPanel.isNormalsEnabled(); }
	bool isLightingEnabled() const { return view3DPanel.isLightingEnabled(); }
	float getLightingIntensity() const { return view3DPanel.getLightIntensity(); }
	ofColor getLightingColor() const { return view3DPanel.getLightColor(); }

	bool is3DTabActive() const { return view3DActive; }

	// ========== CURVES (INTEGRATED IN DRAWING) ==========
	bool isPlacePointsMode() const { return drawingPanel.isPlacePointsMode(); }
	bool isGenerateCurveRequested() const { return drawingPanel.isGenerateCurveRequested(); }
	bool isClearCurvesRequested() const { return drawingPanel.isClearCurvesRequested(); }
	bool isUndoPointRequested() const { return drawingPanel.isUndoPointRequested(); }
	bool isClearPointsRequested() const { return drawingPanel.isClearPointsRequested(); }

	bool isDrawModeActive() const { return current2DMode == TwoDMode::Draw; }
	bool isCurvesModeActive() const { return current2DMode == TwoDMode::CurvesTools; }

	void clearGenerateCurveRequest() { drawingPanel.clearRequests(); }
	void clearClearCurvesRequest() { drawingPanel.clearRequests(); }
	void clearUndoPointRequest() { drawingPanel.clearRequests(); }
	void clearClearPointsRequest() { drawingPanel.clearRequests(); }

	// ========== CONTRLE DES REQUTES ==========
	void clearRequests();

	// Status message public pour compatibilit
	std::string statusMessage;
	CameraManager cameraManager;

	void disablePlacePointsMode() { drawingPanel.setPlacePointsMode(false); }

private:
	// ========== PANELS ==========
	DrawingPanel drawingPanel;
	ImagePanel imagePanel;
	View3DPanel view3DPanel;
	InfoPanel infoPanel;

	enum class TwoDMode {
		Draw,
		CurvesTools
	};

	TwoDMode current2DMode = TwoDMode::Draw;

	// Dropdown option for 2D mode
	struct DropdownOption {
		std::string label;
		TwoDMode mode;
		ofRectangle bounds;
	};

	std::vector<DropdownOption> drawDropdownOptions;
	bool drawDropdownOpen = false;

	// ========== ONGLETS ==========
	struct TabButton {
		std::string label;
		ofRectangle bounds;
		bool hovered = false;
		bool active = false;
	};

	TabButton imageTab = { "Image", ofRectangle(0, 0, 100, 50) };
	TabButton drawTab = { "2D EDITION", ofRectangle(100, 0, 140, 50) };
	TabButton view3DTab = { "3D EDITION", ofRectangle(240, 0, 140, 50) };

	// ========== ZONES UI ==========
	ofRectangle drawingArea;
	ofRectangle statusBox;
	ofRectangle drawDrawingArea;
	ofRectangle curvesDrawingArea;
	float menuBarHeight = 50;

	// ========== TAT GLOBAL ==========
	bool view3DActive = false;

	// ========== MTHODES PRIVES ==========
	void drawTabs();
	void drawDrawDropdown();
	// Draw dropdown options on top of sidebars (overlay)
	void drawDrawDropdownOverlay();
	void drawStatusBox();
	void handleTabClick(int x, int y);
	bool handleDrawDropdownClick(int x, int y);
	void updateDropdownOptionBounds();
	std::string getCurrent2DModeLabel() const;
	void activateImageTab();
	void activateDrawTab();
	void activateView3DTab();
};
