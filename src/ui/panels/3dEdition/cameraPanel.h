#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>
#include <functional>
#include <string>

// Panneau de gestion des caméras 3D
class CameraPanel {
public:
    CameraPanel();
    ~CameraPanel();

    // Initialisation et rendu
    void setup();
    void update();
    void draw();

    // Positionnement / taille (pour fixer le panneau dans la colonne latérale)
    void setPosition(float x, float y);
    void setWidth(float w);

    // Gestion des caméras
    void setCameraNames(const std::vector<std::string>& names);
    void setActiveCameraIndex(int idx);
    int getActiveCameraIndex() const;

    // Affichage / contrôle du panneau
    void show();
    void hide();
    void toggle();
    bool isVisible() const;

    // Callbacks que l'application doit connecter
    std::function<void()> onAddCamera = nullptr;
    std::function<void(int)> onDeleteCamera = nullptr; // index
    std::function<void(int)> onActiveCameraChanged = nullptr;
    std::function<void()> onFocusSelection = nullptr;
    std::function<void()> onResetCamera = nullptr;
    std::function<void()> onProjectionChanged = nullptr;

private:
    // GUI root
    ofxPanel cameraPanel;

    // Top: active camera + add / delete
    ofxLabel lblActiveCamera; // affiche "Active Camera: Name"
    ofParameter<std::string> activeCameraName; // used by ofxLabel
    ofxButton btnPrevCamera;
    ofxButton btnNextCamera;
    ofxButton btnAddCamera;
    ofxButton btnDeleteCamera;

    // Projection controls
    ofxLabel lblProjection;
    ofxToggle togglePerspective;
    ofxFloatSlider fovSlider;
    ofxToggle toggleOrthographic;
    ofxFloatSlider orthoScaleSlider;

    // Clipping planes
    ofxFloatSlider nearPlaneSlider;
    ofxFloatSlider farPlaneSlider;

    // Transform (position + rotation)
    ofxLabel lblTransform;
    ofxFloatSlider posX, posY, posZ;
    ofxFloatSlider rotPitch, rotYaw, rotRoll;

    // Navigation
    ofxLabel lblNavigation;
    ofxToggle toggleOrbitMode;
    ofxFloatSlider mouseSensitivitySlider;
    ofxFloatSlider zoomSpeedSlider;

    // Display toggles
    ofxLabel lblDisplay;
    ofxToggle toggleGrid;
    ofxToggle toggleAxes;
    ofxToggle toggleWireframe;
    ofxToggle toggleBoundingBoxes;

    // Shortcuts
    ofxButton btnFocusSelection;
    ofxButton btnResetCamera;

    // Internal state
    std::vector<std::string> cameraNames;
    ofParameter<int> activeCameraIndex{"ActiveCameraIndex", 0, 0, 100};
    bool visible = true;

    // Stored layout to enforce fixed placement
    float enforcedX = 0.f;
    float enforcedY = 0.f;
    float enforcedWidth = 200.f;

    // Listeners / handlers internes
    void attachListeners();
    void detachListeners();

    void onBtnAddCamera();
    void onBtnDeleteCamera();
    void onBtnPrevCamera();
    void onBtnNextCamera();
    void onActiveCameraIndexChanged(int & newIndex);
    void onTogglePerspectiveChanged(bool & val);
    void onToggleOrthoChanged(bool & val);
    void onBtnFocusSelection();
    void onBtnResetCamera();

    std::string getActiveCameraLabel() const;
    void refreshActiveCameraLabel();
};
