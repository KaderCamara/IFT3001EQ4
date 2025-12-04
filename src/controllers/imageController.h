// imageController.h
// Contrôleur responsable de la logique métier des images
#pragma once

#include "../image/imageManager.h"
#include "ofMain.h"

/**
 * @class ImageController
 * @brief Contrôleur gérant la logique métier des images (CONTROLLER - MVC)
 * 
 * Responsabilités :
 * - Gestion de l'import/export d'images
 * - Validation des fichiers
 * - Coordination avec ImageManager (MODEL)
 * - Logique de drag & drop
 * - AUCUN rendu (délégué à ImageRenderer)
 */
class ImageController {
public:
	ImageController() = default;
	~ImageController() = default;

	void setup();

	// ========== OPÉRATIONS SUR LES IMAGES ==========

	/**
	 * @brief Importe une image via dialog système
	 * @return true si succès
	 */
	bool importImage();

	/**
	 * @brief Charge une image depuis un chemin
	 * @param path Chemin du fichier
	 * @return true si succès
	 */
	bool loadImage(const std::string & path);

	/**
	 * @brief Charge une image depuis un événement drag & drop
	 * @param dragInfo Informations du drag & drop
	 * @return true si succès
	 */
	bool loadFromDragAndDrop(ofDragInfo dragInfo);

	/**
	 * @brief Efface l'image actuelle
	 */
	void clearImage();

	// ========== ACCESSEURS ==========

	/**
	 * @brief Vérifie si une image est chargée
	 */
	bool hasImage() const { return imageManager.isImageLoaded(); }

	/**
	 * @brief Récupère l'image actuelle (pour le renderer)
	 */
	const ofImage & getImage() const { return imageManager.getImage(); }

	/**
	 * @brief Récupère le manager (pour accès avancé)
	 */
	ImageManager & getImageManager() { return imageManager; }
	const ImageManager & getImageManager() const { return imageManager; }

private:
	// Manager (MODEL)
	ImageManager imageManager;

	// ========== VALIDATION ==========

	/**
	 * @brief Valide qu'un fichier est une image supportée
	 * @param path Chemin du fichier
	 * @return true si format valide
	 */
	bool isValidImageFormat(const std::string & path) const;

	/**
	 * @brief Extrait l'extension d'un fichier
	 */
	std::string getFileExtension(const std::string & path) const;
};
