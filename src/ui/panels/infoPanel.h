// Barre d'information type déditeur 2D/3D affichée en bas de la fenêtre
#pragma once

#include "ofMain.h"
#include <string>

/**
 * @class InfoPanel
 * @brief Bandeau d'informations affiché en bas de l'interface
 *
 * Responsabilités :
 * - Afficher des informations contextuelles (onglet actif, mode de vue)
 * - Montrer des détails utiles (zone de dessin, FPS, statut)
 * - Dessiner un bandeau d'information cohérent avec un éditeur 2D/3D
 */
class InfoPanel {
public:
	InfoPanel() = default;
	~InfoPanel() = default;

	void setup();
	void update(const std::string & activeTabLabel, bool is3DView, bool isQuadView, const ofRectangle & drawingArea, const std::string & statusMessage);
	void draw(float menuBarHeight);

	float getHeight() const { return panelHeight; }

private:
	// Données affichées
	std::string activeTab;
	std::string viewMode;
	ofRectangle drawingAreaInfo;
	std::string statusText;
	float fps = 0.0f;

	// Dimensions
	float panelHeight = 80.0f;

	// Méthodes utilitaires
	void drawBackground(float yPosition);
	void drawContent(float yPosition);
};
