///////////////////////////////////////////////////////////////////////////////
/// @file Modele3D.h
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 2.0
/// @note Classe bas�e sur celle d�velopp�e par Julien Gascon-Samson.
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __RENDERING_MODELE3D_H__
#define __RENDERING_MODELE3D_H__

#include <vector>
#include <map>
#include <string>
#include <filesystem>	/// std::tr2::sys::path
#include "Noeud.h"
#include "Utilitaire.h"

struct aiScene;			/// D�claration avanc�e de Assimp

namespace modele{
	
	///////////////////////////////////////////////////////////////////////////
	/// @class Modele3D
	/// @brief Classe qui encapsule un mod�le 3d de la librairie 'assimp'. Cette
	/// classe permet de charger un mod�le 3d d'un fichier export� par un outil 
	/// (en utilisant ladite librairie). La classe ne permet pas, dans sa forme
	/// actuelle, de modifier le mod�le par la suite.  Un point d'extension
	/// pourrait �tre de pouvoir animer le mod�le en modifiant les matrices de
	/// transformation des noeuds contenant les meshes.
	///
	/// @note Le rendu du mod�le 3d est une responsabilit� externe � la classe,
	/// puisqu'OpenGL offre plusieurs m�thodes de chargement des donn�es sur la
	/// carte graphique et de dessin.
	///
	///
	/// @author Martin Paradis
	/// @date 2014-08-16
	///////////////////////////////////////////////////////////////////////////
	class Modele3D{
	public:
		using Path = std::tr2::sys::path;
		
		Modele3D() = default;
		/// Construction par transfert ("move")
		Modele3D(Modele3D && modele);
		/// Assignation par transfert ("move")
		Modele3D& operator=(Modele3D && modele);

		/// Pas de copie, car les identifiants de texture seraient dupliqu�s
		/// et rel�ch�s sur la destruction
		Modele3D(Modele3D const&) = delete;
		/// Pas d'assignation, car les identifiants de texture seraient dupliqu�s
		/// et rel�ch�s sur la destruction
		Modele3D& operator=(Modele3D const&) = delete;
		
		/// Destructeur
		~Modele3D();

		/// Charger le mod�le 3d � partir d'un fichier
		void charger(Path nomFichier);
		
		/// Permet de v�rifier si la texture existe pour ce mod�le
		inline bool possedeTexture(std::string const& nomTexture) const;

		/// Pour permettre aux mat�riau de r�cup�rer l'identifiant opengl de la texture
		inline unsigned int obtenirTextureHandle(std::string const& nomTexture) const;

		/// M�thode d'obtention de l'arbre contenant les meshes
		inline Noeud const& obtenirNoeudRacine() const;
		
		/// M�thode d'obtention du chemin du fichier charg�
		inline Path const& obtenirCheminFichier() const;

	private:
		/// Permet de charger les textures du mod�le vers en m�moire gpu
		void chargerTexturesExternes (aiScene const* scene);	/// � partir d'un fichier externe (jpg, bmp, png, etc.)
		void chargerTexturesIntegrees(aiScene const* scene);	/// Contenues directement dans le fichier du mod�le
		/// Permet de lib�rer les textures du mod�le de la m�moire de la carte graphique
		void libererTextures();

		/// Identificateurs des textures OpenGL
		std::vector<unsigned int> identificateursTextures_;

		/// Map des textures, pour associer chaque nom de texture � un identificateur GLuint
		std::map<std::string, unsigned int*> mapTextures_;

		/// Arbre des meshes
		Noeud racine_;

		/// Chemin du fichier
		Path cheminFichier_;
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Noeud const& Modele3D::obtenirNoeudRacine() const
	///
	/// Cette fonction retourne le noeud racine de l'arbre contenant les
	/// meshes du mod�le 3D.
	///
	/// @return Le noeud racine (const).
	///
	////////////////////////////////////////////////////////////////////////
	inline Noeud const& Modele3D::obtenirNoeudRacine() const
	{
		return racine_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Modele3D::possedeTexture(std::string const& nomTexture) const
	///
	/// Cette fonction permet de v�rifier si la texture existe pour ce mod�le
	/// 
	///
	/// @param[in] nomTexture : le nom de la texture
	///
	/// @return vrai si la texture est utilis�e par le mod�le, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Modele3D::possedeTexture(std::string const& nomTexture) const
	{
		return mapTextures_.end() != mapTextures_.find(nomTexture);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline unsigned int Modele3D::obtenirTextureHandle(std::string const& nomTexture) const
	///
	/// Cette fonction permet de r�cup�rer l'identifiant opengl de la texture.
	/// 
	///
	/// @param[in] nomTexture : le nom de la texture
	///
	/// @return Le handle vers la texture.
	///
	////////////////////////////////////////////////////////////////////////
	inline unsigned int Modele3D::obtenirTextureHandle(std::string const& nomTexture) const
	{
		if (possedeTexture(nomTexture))
			return *mapTextures_.at(nomTexture);

		utilitaire::afficherErreur("Impossible de r�cup�rer le handle de la texture : \"" + nomTexture + "\".");
		return 0;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Modele3D::Path const& Modele3D::obtenirCheminFichier() const
	///
	/// Cette fonction permet de r�cup�rer le chemin du fichier charg�.
	/// 
	///
	/// @return Le chemin du fichier charg�.
	///
	////////////////////////////////////////////////////////////////////////
	inline Modele3D::Path const& Modele3D::obtenirCheminFichier() const
	{
		return cheminFichier_;
	}

} /// fin de rendering

#endif /// __RENDERING_MODELE3D_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////