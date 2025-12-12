#include "Model3DImportManager.h"
#include <algorithm>
#include <cctype>

// ========== IMPORT ==========

std::vector<Shape> Model3DImportManager::import3DModelWithDialog() {
	ofFileDialogResult result = ofSystemLoadDialog(
		"Select a 3D model (.obj, .ply, .stl, .fbx)",
		false);

	if (!result.bSuccess) {
		ofLogNotice("Model3DImportManager") << "Import cancelled by user";
		return std::vector<Shape>(); // Retourne vide
	}

	return import3DModel(result.getPath());
}

std::vector<Shape> Model3DImportManager::import3DModel(const std::string & filePath) {
	std::vector<Shape> importedShapes;

	// Validation du format
	std::string extension = ofFilePath::getFileExt(filePath);
	std::string normalizedExt = normalizeExtension(extension);

	if (!isValidFormat(normalizedExt)) {
		ofLogError("Model3DImportManager")
			<< "Unsupported format: ." << extension
			<< " (supported: obj, ply, stl, fbx)";
		return importedShapes;
	}

	// Chargement avec Assimp
	ofxAssimpModelLoader loader;
	if (!loader.loadModel(filePath)) {
		ofLogError("Model3DImportManager")
			<< "Failed to load model: " << filePath;
		return importedShapes;
	}

	// Conversion de chaque mesh en Shape
	int numMeshes = loader.getMeshCount();
	ofLogNotice("Model3DImportManager")
		<< "Successfully loaded " << numMeshes << " mesh(es) from " << filePath;

	for (int i = 0; i < numMeshes; i++) {
		ofMesh mesh = loader.getMesh(i);
		Shape shape = convertMeshToShape(mesh);
		importedShapes.push_back(shape);
	}

	return importedShapes;
}

// ========== GESTION ==========

std::vector<Shape> Model3DImportManager::removeAll3DModels(const std::vector<Shape> & shapes) {
	std::vector<Shape> filteredShapes;

	// Copie uniquement les shapes NON-3D
	std::copy_if(
		shapes.begin(),
		shapes.end(),
		std::back_inserter(filteredShapes),
		[](const Shape & s) { return !s.is3D; });

	int removed = shapes.size() - filteredShapes.size();
	ofLogNotice("Model3DImportManager")
		<< "Removed " << removed << " 3D model(s) from scene";

	return filteredShapes;
}

// ========== VALIDATION ==========

bool Model3DImportManager::isValidFormat(const std::string & extension) const {
	std::string normalized = normalizeExtension(extension);

	return std::find(
			   supportedFormats.begin(),
			   supportedFormats.end(),
			   normalized)
		!= supportedFormats.end();
}

std::vector<std::string> Model3DImportManager::getSupportedFormats() const {
	return supportedFormats;
}

// ========== PRIVATE ==========

Shape Model3DImportManager::convertMeshToShape(const ofMesh & mesh) {
	Shape shape;
	shape.type = "3DModel";
	shape.is3D = true;
	shape.mesh3D = mesh;

	// Paramètres par défaut
	shape.color = ofColor(200, 200, 200); // Gris clair
	shape.scale = 1.0f;
	shape.rotation = 0.0f;
	shape.translation.set(0, 0);

	return shape;
}

std::string Model3DImportManager::normalizeExtension(const std::string & ext) const {
	std::string normalized = ext;

	// Supprimer le point initial si présent
	if (!normalized.empty() && normalized[0] == '.') {
		normalized = normalized.substr(1);
	}

	// Convertir en minuscules
	std::transform(
		normalized.begin(),
		normalized.end(),
		normalized.begin(),
		[](unsigned char c) { return std::tolower(c); });

	return normalized;
}
