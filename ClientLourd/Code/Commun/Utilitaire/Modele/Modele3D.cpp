///////////////////////////////////////////////////////////////////////////////
/// @file Modele3D.cpp
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 2.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Modele3D.h"

#include "GL/glew.h"
#include "utilitaire.h"		// Afficher les erreurs dans un message box
#include "aidegl.h"			// Chargement des textures dans la m�moire du gpu

#include "Importer.hpp"		// Interface d'importation "assimp" C++
#include "scene.h"			// Structure de donn�es de sortie "assimp"
#include "postprocess.h"	// Drapaux de post-traitement "assimp"

namespace modele{

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Modele3D::Modele3D(Modele3D && modele)
	///
	/// Constructeur "move".  Utilise l'assignation "move".
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	Modele3D::Modele3D(Modele3D && modele)
	{
		*this = std::move(modele);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Modele3D& Modele3D::operator=(Modele3D && modele)
	///
	/// Assignation par transfert ("move"), ne fait que transf�rer les
	/// donn�es et s'assurer que les textures OpenGL ne seront pas lib�r�es
	/// lors de la destruction du mod�le pass� en param�tre.
	///
	/// @return le mod�le courant.
	///
	////////////////////////////////////////////////////////////////////////
	Modele3D& Modele3D::operator=(Modele3D && modele)
	{
		if (this != &modele)
		{
			identificateursTextures_ = std::move(modele.identificateursTextures_);
			mapTextures_ = std::move(modele.mapTextures_);
			racine_ = std::move(modele.racine_);
			cheminFichier_ = std::move(modele.cheminFichier_);
		}
		return *this;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Modele3D::~Modele3D()
	///
	/// Destructeur. Ne fait que lib�rer les donn�es des textures.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	Modele3D::~Modele3D()
	{
		libererTextures();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Modele3D::charger(Path cheminFichier)
	///
	/// Cette fonction charge un mod�le 3D � partir d'un fichier support�
	/// par la librairie 'assimp'. Les textures OpenGL aff�rentes sont
	/// �galement charg�es.
	///
	/// @param[in] nomFichier : nom du fichier mod�le (normalement .obj
	///	ou .dae)
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Modele3D::charger(Path cheminFichier)
	{
		/// Ne pas charger le m�me fichier inutilement 
		if (cheminFichier_ == cheminFichier)
			return;

		cheminFichier_ = std::move(cheminFichier);

		/// Ne pas conserver les identifiants de texture d'un ancien mod�le
		libererTextures();

		Assimp::Importer importer;

		/// Lors de l'importation, ne pas conserver les lignes et les points.
		importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);

		/// Le flag aiProcess_Triangulate, inclus dans aiProcessPreset_TargetRealtime_Quality,
		/// fera en sorte que les mesh ne comporteront que des triangles.
		const aiScene* scene{ importer.ReadFile(cheminFichier_.string(), aiProcessPreset_TargetRealtime_Quality) };

		if (scene == nullptr) {
			utilitaire::afficherErreur(std::string{ "Impossible de charger l'objet 3d : " } +cheminFichier.filename().string() + std::string{ "." });
			return;
		}

		/// Charger l'ensemble des textures contenues dans le mod�le :
		chargerTexturesExternes(scene);
		chargerTexturesIntegrees(scene);

		/// Chargement des donn�es du mod�le 3D
		racine_ = Noeud{ scene, scene->mRootNode };
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Modele3D::chargerTexturesExternes()
	///
	/// Cette fonction charge les textures OpenGL associ�es au mod�le
	/// 'assimp' pr�alablement charg�, � partir des fichiers de textures.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Modele3D::chargerTexturesExternes(aiScene const* scene)
	{
		// It�rer parmi l'ensemble des mat�riaux
		for (unsigned int i{ 0 }; i < scene->mNumMaterials; i++) {
			aiMaterial* materiau{ scene->mMaterials[i] };

			// POINT D'EXTENSION : il vous serait possible de prendre en charge d'autres types de textures que celle
			// en diffusion (DIFFUSE)...

			// Parcourir l'ensemble des textures pour ce mat�riau et stocker les noms de fichiers
			// Par la suite, nous initialiserons la m�moire de textures OpenGL et proc�derons
			// au chargement des fichiers graphiques.
			int idTexture{ 0 };
			while (true) {

				// Cha�ne UTF-8 (fort possiblement compatible ASCII) qui contient le nom de fichier associ� � la texture
				// On peut l'utiliser comme une cha�ne C standard (char *) sans r�el risque (selon la doc. assimp !)
				aiString cheminTexture{ "" };

				// R�cup�rer le chemin vers la texture...
				aiReturn retour{ materiau->GetTexture(aiTextureType_DIFFUSE, idTexture, &cheminTexture) };
				// V�rifie que la texture est valide...
				if (retour != AI_SUCCESS)
					break;

				// Stocker le nom de texture dans le tableau associatif
				mapTextures_[cheminTexture.data] = NULL;

				idTexture++;
			}
		}
		// Pour chaque texture trouv�e, proc�der au chargement

		// Nombre de textures
		unsigned int nombreTextures{ static_cast<unsigned int>(mapTextures_.size()) };

		// G�n�rer les textures OpenGL
		if (nombreTextures > 0)
		{
			identificateursTextures_ = std::vector<unsigned int>(nombreTextures);
			glGenTextures(nombreTextures, &identificateursTextures_[0]);

			// It�rateur STL
			std::map<std::string, unsigned int*>::iterator itr{ mapTextures_.begin() };

			for (unsigned int j{ 0 }; j < nombreTextures; j++) {
				std::string nomFichier{ itr->first };
				itr->second = &(identificateursTextures_[j]);
				itr++;

				// Charger la texture
				aidegl::glLoadTexture(std::string{ "media/" } +nomFichier, identificateursTextures_[j], false);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Mesh::chargerTexturesIntegrees()
	///
	/// Cette fonction charge les textures OpenGL int�gr�es au fichier du 
	/// mod�le 'assimp' pr�alablement charg�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Modele3D::chargerTexturesIntegrees(aiScene const* scene)
	{
		if (scene->HasTextures()) {
			utilitaire::afficherErreur("Les textures int�gr�es ne sont pas prises en charge pour le moment.");
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Modele3D::libererTextures()
	///
	/// Cette fonction lib�re les textures de la m�moire de la carte graphique
	/// et vide les conteneurs conservant les handles.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Modele3D::libererTextures()
	{
		// Lib�rer les textures
		if (!identificateursTextures_.empty())
		{
			glDeleteTextures(static_cast<GLsizei>(identificateursTextures_.size()), &identificateursTextures_[0]);
			identificateursTextures_.clear();
		}
		if (!mapTextures_.empty())
		{
			mapTextures_.clear();
		}
	}

} /// fin de rendering

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////