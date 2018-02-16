///////////////////////////////////////////////////////////////////////////////
/// @file Mesh.h
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __RENDERING_MESH_H__
#define __RENDERING_MESH_H__

#include <vector>

#include "Materiau.h"

struct aiScene;		/// D�clarations avanc�es de Assimp
struct aiMesh;		//

namespace modele{

	///////////////////////////////////////////////////////////////////////////
	/// @class Mesh
	/// @brief Classe qui encapsule les donn�es g�om�triques d'un mod�le 3D, 
	///		   donc les vertices, les normales, les coordonn�es de texture, les
	///		   couleurs des vertices et les faces.
	///
	/// @author Martin Paradis
	/// @date 2014-08-16
	///////////////////////////////////////////////////////////////////////////
	class Mesh{
	public:
		/// Alias de type
		template <typename T> using Conteneur = std::vector<T>;
		using Vertex	= glm::vec3;
		using Normale	= glm::vec3;
		using TexCoord	= glm::vec2;
		using Couleur	= glm::vec4;
		using Face		= glm::ivec3;

		Mesh() = default;
		/// Constructeur � partir d'un mesh et d'une sc�ne assimp
		Mesh(aiScene const* scene, aiMesh const* mesh);
		
		/// M�thode pour obtenir les vertex du mesh	
		inline Conteneur<Vertex>   const& obtenirSommets()   const;

		/// M�thode pour obtenir les normales du mesh	
		inline Conteneur<Normale>  const& obtenirNormales()  const;

		/// M�thode pour obtenir les coordonn�es de texture du mesh	
		inline Conteneur<TexCoord> const& obtenirTexCoords() const;

		/// M�thode pour obtenir les couleurs des sommets du mesh	
		inline Conteneur<Couleur>  const& obtenirCouleurs()  const;

		/// M�thode pour obtenir le materiau du mesh	
		inline Materiau			   const& obtenirMateriau()	 const;

		/// M�thode pour obtenir les couleurs des sommets du mesh	
		inline Conteneur<Face>	   const& obtenirFaces()     const;

		/// M�thode pour obtenir le nom du noeud (souvent une chaine vide)
		inline std::string		   const& obtenirNom()		 const;

		/// V�rifier si le mesh contient des sommets
		inline bool possedeSommets() const;
		/// V�rifier si le mesh contient des normales
		inline bool possedeNormales() const;
		/// V�rifier si le mesh contient des coordonn�es de texture
		inline bool possedeTexCoords() const;
		/// V�rifier si le mesh contient des couleurs de vertex
		inline bool possedeCouleurs() const;
		/// V�rifier si le mesh contient des faces
		inline bool possedeFaces() const;

	private:
		/// Permet d'allouer la m�moire n�cessaire pour contenir le mesh
		void reserverMemoire(aiMesh const* mesh);

		/// Les sommets du mod�les
		Conteneur<Vertex> vertices_;
		/// Les normales
		Conteneur<Normale> normales_;
		/// Les coordonn�es de texture
		Conteneur<TexCoord> texcoords_;
		/// Les couleurs des sommets
		Conteneur<Couleur> couleurs_;
		/// Le mat�riau associ� au mesh
		Materiau materiau_;
		/// Indexes dans les diff�rents tampons
		Conteneur<Face> faces_;
		/// Le nom
		std::string nom_;
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::Vertex> const& Mesh::obtenirSommets() const
	///
	/// Cette fonction retourne les sommets dont est compos� le mesh.
	///
	/// @return les sommets (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::Vertex> const& Mesh::obtenirSommets() const
	{
		return vertices_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::Normale> const& Mesh::obtenirNormales() const
	///
	/// Cette fonction retourne les normales contenues dans le mesh.
	///
	/// @return les normales (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::Normale> const& Mesh::obtenirNormales() const
	{
		return normales_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::TexCoord> const& Mesh::obtenirTexCoords() const
	///
	/// Cette fonction retourne les coordonn�es de texture dont est compos� le mesh.
	///
	/// @return les coordonn�es de textures (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::TexCoord> const& Mesh::obtenirTexCoords() const
	{
		return texcoords_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::Couleur> const& Mesh::obtenirCouleurs() const
	///
	/// Cette fonction retourne les couleurs dont est compos� le mesh.
	///
	/// @return les couleurs (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::Couleur> const& Mesh::obtenirCouleurs() const
	{
		return couleurs_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Materiau const& Mesh::obtenirMateriau() const
	///
	/// Cette fonction retourne le mat�riau dont est compos� le mesh.
	///
	/// @return le materiau (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Materiau const& Mesh::obtenirMateriau() const
	{
		return materiau_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Mesh::Conteneur<Mesh::Face> const& Mesh::obtenirFaces() const
	///
	/// Cette fonction retourne les index des faces dont est compos� le mesh.
	/// Les faces sont suppos�es toujours �tre des triangles.
	///
	/// @return les faces (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Mesh::Conteneur<Mesh::Face> const& Mesh::obtenirFaces() const
	{
		return faces_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline std::string const& Mesh::obtenirNom() const
	///
	/// Cette fonction retourne le nom du mesh courant.  Le nom des meshes
	/// est tr�s souvent vide (cela d�pend du type de fichier utilis�).
	///
	/// @return Le nom du mesh (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline std::string const& Mesh::obtenirNom() const
	{
		return nom_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeSommets() const
	///
	/// Cette fonction indique si le mesh contient des sommets.
	///
	/// @return vrai si le mesh poss�de des sommets, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeSommets() const
	{
		return !vertices_.empty();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeNormales() const
	///
	/// Cette fonction indique si le mesh contient des normales.
	///
	/// @return vrai si le mesh poss�de des normales, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeNormales() const
	{
		return !normales_.empty();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeTexCoords() const
	///
	/// Cette fonction indique si le mesh contient des coordonn�es de texture.
	///
	/// @return vrai si le mesh poss�de des coordonn�es de texture, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeTexCoords() const
	{
		return !texcoords_.empty();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeCouleurs() const
	///
	/// Cette fonction indique si le mesh contient des couleurs de sommets.
	///
	/// @return vrai si le mesh poss�de des couleurs de sommets, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeCouleurs() const
	{
		return !couleurs_.empty();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Mesh::possedeFaces() const
	///
	/// Cette fonction indique si le mesh contient des faces.
	///
	/// @return vrai si le mesh poss�de des faces, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Mesh::possedeFaces() const
	{
		return !faces_.empty();
	}

} /// fin de rendering

#endif /// __RENDERING_MESH_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////