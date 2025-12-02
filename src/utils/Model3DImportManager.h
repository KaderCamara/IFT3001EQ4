#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include <string>
#include <vector>
# include "../objects/shape.h"

// Forward declaration pour éviter dépendance circulaire
struct Shape;

/**
 * @class Model3DImportManager
 * @brief Gestionnaire responsable de l'import et de la gestion des modèles 3D
 * 
 * Responsabilités (MODEL - MVC) :
 * - Importer des fichiers 3D (.obj, .ply, .stl, .fbx)
 * - Valider les formats supportés
 * - Convertir les meshes en objets Shape
 * - Filtrer/supprimer les modèles 3D de la scène
 */
class Model3DImportManager {
public:
	// ========== IMPORT ==========

	/**
     * @brief Importe un modèle 3D depuis un chemin de fichier
     * @param filePath Chemin absolu du fichier 3D
     * @return Vector de shapes créés (vide si échec)
     */
	std::vector<Shape> import3DModel(const std::string & filePath);

	/**
     * @brief Ouvre une dialog système pour sélectionner un fichier 3D
     * @return Vector de shapes créés (vide si annulé ou échec)
     */
	std::vector<Shape> import3DModelWithDialog();

	// ========== GESTION ==========

	/**
     * @brief Filtre et retourne tous les shapes NON-3D d'une collection
     * @param shapes Collection de shapes à filtrer
     * @return Nouveau vector sans les modèles 3D
     */
	std::vector<Shape> removeAll3DModels(const std::vector<Shape> & shapes);

	// ========== VALIDATION ==========

	/**
     * @brief Vérifie si une extension de fichier est supportée
     * @param extension Extension sans le point (ex: "obj", "fbx")
     * @return true si le format est supporté
     */
	bool isValidFormat(const std::string & extension) const;

	/**
     * @brief Retourne la liste des extensions supportées
     * @return Vector des formats supportés (minuscules)
     */
	std::vector<std::string> getSupportedFormats() const;

private:
	// Formats supportés par Assimp
	const std::vector<std::string> supportedFormats = { "obj", "ply", "stl", "fbx" };

	/**
     * @brief Convertit un mesh Assimp en objet Shape
     * @param mesh Mesh OpenFrameworks
     * @return Shape configuré pour affichage 3D
     */
	Shape convertMeshToShape(const ofMesh & mesh);

	/**
     * @brief Normalise une extension (minuscules, sans point)
     * @param ext Extension brute
     * @return Extension normalisée
     */
	std::string normalizeExtension(const std::string & ext) const;
};
