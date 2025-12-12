// imageController.cpp
// Implémentation du contrôleur d'images
#include "imageController.h"

void ImageController::setup() {
	ofLogNotice("ImageController") << "Setup complete";
}

// ========== OPÉRATIONS SUR LES IMAGES ==========

bool ImageController::importImage() {
	// Ouvrir une dialog pour sélectionner une image
	ofFileDialogResult result = ofSystemLoadDialog("Select an image to import (png, jpg, jpeg)");

	if (!result.bSuccess) {
		ofLogNotice("ImageController") << "Import cancelled by user";
		return false;
	}

	return loadImage(result.getPath());
}

bool ImageController::loadImage(const std::string & path) {
	// Valider le format
	if (!isValidImageFormat(path)) {
		ofLogError("ImageController") << "Invalid image format: " << path;
		return false;
	}

	// Charger via le manager
	bool success = imageManager.loadFromPath(path);

	if (success) {
		ofLogNotice("ImageController") << "Image loaded successfully: " << path;
		return true;
	} else {
		ofLogError("ImageController") << "Failed to load image: " << path;
		return false;
	}
}

bool ImageController::loadFromDragAndDrop(ofDragInfo dragInfo) {
	// Vérifier qu'il y a des fichiers
	if (dragInfo.files.empty()) {
		ofLogWarning("ImageController") << "No files in drag & drop event";
		return false;
	}

	// Prendre le premier fichier
	std::string path = dragInfo.files[0].string();

	// Valider le format
	if (!isValidImageFormat(path)) {
		ofLogError("ImageController") << "Invalid image format dropped: " << path;
		return false;
	}

	// Charger via le manager
	imageManager.loadFromDrag(dragInfo);

	if (imageManager.isImageLoaded()) {
		ofLogNotice("ImageController") << "Image loaded from drag & drop: " << path;
		return true;
	} else {
		ofLogError("ImageController") << "Failed to load image from drag & drop";
		return false;
	}
}

void ImageController::clearImage() {
	imageManager.clear();
	ofLogNotice("ImageController") << "Image cleared";
}

// ========== VALIDATION ==========

bool ImageController::isValidImageFormat(const std::string & path) const {
	std::string ext = getFileExtension(path);

	// Formats supportés par ofImage
	return (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "gif" || ext == "bmp" || ext == "tif" || ext == "tiff");
}

std::string ImageController::getFileExtension(const std::string & path) const {
	// Extraire l'extension
	size_t dotPos = path.find_last_of('.');
	if (dotPos == std::string::npos) {
		return "";
	}

	std::string ext = path.substr(dotPos + 1);

	// Convertir en minuscules
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	return ext;
}

