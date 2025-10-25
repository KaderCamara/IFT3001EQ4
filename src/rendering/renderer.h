// IFT3100A25_BonjourMonde/renderer.h
// Classe responsable du rendu de l'application.  dessins etc
#pragma once
#include "ofMain.h"
#include "../objects/shapeManager.h"
#include "sceneGraph.h"
#include "ofxAssimpModelLoader.h"
#include <algorithm>
#include "cameraManager.h"
#include "../objects/shapeManager3D.h"


class Renderer
{
public:
  void setup();
  void draw();
  
  void setDrawingArea(const ofRectangle & area) { drawingArea = area; };
  void setCurrentShape(const std::string & shape) { currentShape = shape; }
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void keyPressed(int key);
  void draw3D();
  void setShowBoundingBox(bool state) { showBoundingBox = state; }

  // MODIFICATIONS JORDAN
  void view2DMode();
  bool is3DView() const { return view3D; }
  void applyDrawingParameters(float lineW, const ofColor & stroke, const ofColor & fill, const ofColor & bg, bool useHSB, float hue, float saturation, float brightness);
  void updateShapeManagerParams(float lineW, ofColor stroke, ofColor fill);
  void applyTransformationToSelectedShape(float tx, float ty, float rot, float scale);
  void import3DModel();
  void clear3DModels();

  //mini-controller
  void save();
  void deleteShape();
  void selectingModeOn();
  void selectingModeOff();
  void view3DMode();
  void viewQuadMode();

private:
  ofTrueTypeFont font;
  ofRectangle drawingArea;
  ofRectangle getMeshBoundingBox(const ofMesh & mesh);
  std::string currentShape = "none";
  bool drawing = false;
  bool selecting = false;
  ShapeManager shapeManager;
  CameraManager cameraManager;
  SceneGraph sceneGraph;
  ofPoint startPoint, endPoint;
  bool shapeSelected = false;
  bool showBoundingBox = false;
  int shapeSelectedIndex = -1;
  bool view3D = false;
  bool view2D = true;
  bool viewQuad = false;
  void drawQuadView();
  float camDistance = 600.0f;
  // --- Parameters from UI ---
  float currentLineWidth = 2.0f;
  ofColor currentStrokeColor = ofColor::black;
  ofColor currentFillColor = ofColor::white;
  ofColor currentBgColor = ofColor::white;
  bool useHSBmode = false;

  // 3D IMPORT
  bool modelImported = false;
};
