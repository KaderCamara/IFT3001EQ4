// IFT3100A25_BonjourMonde/application.h
// Classe principale de l'application.
//notre controller basically

#pragma once

#include "ofMain.h"
#include "../rendering/renderer.h"
#include "../ui/uiWindow.h"

class Application : public ofBaseApp
{
public:

  Renderer renderer;

  UIWindow uiWindow;

  void setup();

  void draw();

  void update();

  void mousePressed(int x, int y, int button);

  void mouseReleased(int x, int y, int button);

  void dragEvent(ofDragInfo dragInfo);

  void exit();
};
