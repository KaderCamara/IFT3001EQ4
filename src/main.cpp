// IFT3100A25_3DApp/main.cpp
// Basé sur un exemple d'un programme minimaliste.
// point d'entrée de l'application

#include "ofMain.h"
#include "application.h"

int main()
{
  // paramètres du contexte de rendu OpenGL
  ofGLFWWindowSettings windowSettings;

  // option de redimentionnement de la fenêtre d'affichage
  windowSettings.resizable = true;

  // sélection de la version de OpenGL
  windowSettings.setGLVersion(3, 3);

  // création de la fenêtre
  ofCreateWindow(windowSettings);

  // démarrer l'exécution de l'application
  ofRunApp(new Application());
}
