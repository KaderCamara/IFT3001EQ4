// IFT3100A25_BonjourMonde/renderer.h
// Classe responsable du rendu de l'application.  dessins etc
#pragma once
#include "ofMain.h"
#include "../objects/shapeManager.h"
#include "sceneGraph.h"
#include "cameraManager.h"

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

  //mini-controller
  void save();
  void deleteShape();
  void selectingModeOn();
  void selectingModeOff();
  void view3DMode();
  void view2DMode();

private:
  ofTrueTypeFont font;
  ofRectangle drawingArea;
  std::string currentShape = "none";
  bool drawing = false;
  bool selecting = false;
  ShapeManager shapeManager;
  CameraManager cameraManager;
  SceneGraph sceneGraph;
  ofPoint startPoint, endPoint;
  bool shapeSelected = false;
  int shapeSelectedIndex = -1;
  bool view3D = false;
  bool view2D = true;
  float camDistance = 600.0f;
};
