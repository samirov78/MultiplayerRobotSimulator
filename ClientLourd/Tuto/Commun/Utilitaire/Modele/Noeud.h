///////////////////////////////////////////////////////////////////////////////
/// @file Noeud.h
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __RENDERING_NOEUD_H__
#define __RENDERING_NOEUD_H__

#include <vector>
#include <string>
#include "glm/mat4x4.hpp"

#include "Mesh.h"

struct aiScene;		/// D�clarations avanc�es de Assimp
struct aiNode;		//

namespace modele{

	///////////////////////////////////////////////////////////////////////////
	/// @class Noeud
	/// @brief Classe qui encapsule un arbre compos� de meshes et de matrices
	///		   de transformations.
	///
	/// @author Martin Paradis
	/// @date 2014-08-16
	///////////////////////////////////////////////////////////////////////////
	class Noeud{
	public:
		template <typename T> using Conteneur = std::vector<T>;

		Noeud() = default;
		/// Constructeur � partir d'une sc�ne et d'un noeud assimp
		Noeud(aiScene const* scene, aiNode const* noeud);
		/// Constructeur par transfert ("Move")
		Noeud(Noeud && noeud);
		/// Assignation par transfert ("move")
		Noeud& operator=(Noeud && noeud);

		/// Constructeur par copie non-n�cessaire dans le contexte
		Noeud(Noeud const&) = delete;
		/// Assignation par copie non-n�cessaire dans le contexte
		Noeud& operator=(Noeud const&) = delete;

		~Noeud() = default;

		/// M�thodes pour obtenir les meshes associ�s au noeud
		inline Conteneur<Mesh>  const& obtenirMeshes() const;

		/// M�thodes pour obtenir les noeuds enfants
		inline Conteneur<Noeud> const& obtenirEnfants()	const;

		/// M�thodes pour obtenir la transformation associ�e au noeud
		inline glm::mat4x4		const& obtenirTransformation() const;

		/// M�thodes pour obtenir le nom du noeud (souvent une chaine vide)
		inline std::string		const& obtenirNom()	const;
		
	private:
		/// Contient les meshes (donn�es g�om�triques d'un mod�le 3D)
		Conteneur<Mesh> meshes_;
		/// Contient les noeuds enfants du noeud courant
		Conteneur<Noeud> enfants_;
		/// La matrice de transformation du noeud courant
		glm::mat4x4 transform_;
		/// Le noeud associ� au noeud courant
		std::string nom_;
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Noeud::Conteneur<Mesh> const& Noeud::obtenirMeshes() const
	///
	/// Cette fonction retourne les meshes associ�s au noeud courant (ne 
	/// contient donc pas les meshes des noeuds enfants.
	///
	/// @return Le conteneur des meshes (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Noeud::Conteneur<Mesh> const& Noeud::obtenirMeshes() const
	{
		return meshes_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Noeud::Conteneur<Noeud> const& Noeud::obtenirEnfants() const
	///
	/// Cette fonction retourne les noeuds enfants du noeud courant;
	///
	/// @return Le conteneur des enfants (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Noeud::Conteneur<Noeud> const& Noeud::obtenirEnfants() const
	{
		return enfants_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline glm::mat4x4 const& Noeud::obtenirTransformation() const
	///
	/// Cette fonction retourne la transformation du noeud courant;
	///
	/// @return La matrice de transformation (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline glm::mat4x4 const& Noeud::obtenirTransformation() const
	{
		return transform_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline std::string const& Noeud::obtenirNom() const
	///
	/// Cette fonction retourne le nom du noeud courant.  Le nom des noeuds
	/// est tr�s souvent vide (cela d�pend du type de fichier utilis�).
	///
	/// @return Le nom du noeud (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline std::string const& Noeud::obtenirNom() const
	{
		return nom_;
	}

} /// fin de rendering

#endif /// __RENDERING_NOEUD_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////