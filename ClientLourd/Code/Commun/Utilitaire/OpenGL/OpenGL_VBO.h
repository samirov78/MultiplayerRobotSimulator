///////////////////////////////////////////////////////////////////////////////
/// @file ModeleStorage_VBO.h
/// @author Martin Paradis
/// @date 2015-08-28
/// @version 1.0
///
/// @addtogroup opengl
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __VBO_H__
#define __VBO_H__

#include "GL/glew.h"

#include <iostream>
#include <vector>
#include <type_traits>

namespace modele{
	class  Modele3D;
	class  Noeud;
	struct Materiau;
}

namespace opengl{
	///////////////////////////////////////////////////////////////////////////
	/// @class VBO
	/// @brief Classe permettant le dessin d'un mod�le 3D par VBO.
	///
	/// @note Pr�condition : prends pour acquis que le pointeur vers le mod�le
	/// 3D reste valide durant toute la dur�e de vie du storage.  Le mod�le est
	/// consid�r� "constant", c'est-�-dire que ses meshes ne sont pas modifi�s
	/// et qu'il n'est pas rel�ch� lors de l'appel au dessin.
	/// Une modification � la g�om�trie du mod�le n�cessite de lib�rer le VBO 
	/// et le recr�er.
	///
	/// @author Martin Paradis
	/// @date 2015-08-28
	///////////////////////////////////////////////////////////////////////////
	class VBO {
	public:
		VBO() = default;
		/// Constructeur � partir d'un mod�le 3D
		VBO(modele::Modele3D const* modele);

		/// Destructeur
		virtual ~VBO();

		/// Permet de charger les donn�es/commandes sur la carte graphique
		virtual void charger();
		/// Permet d'effectuer le dessin du mod�le 3D
		virtual void dessiner(bool estSelectionne, bool attribCouleur, GLubyte couleurObjet[], GLubyte couleurSelection[]) const;
		/// Permet de rel�cher les donn�es/commandes sur la crate graphique
		virtual void liberer();

	private:
		/// M�thode "helper" pour passer les donn�es du mesh vers la carte graphique
		template <typename T>
		inline void enregistrerTampon(T const& data);

		/// Assigne le mat�riau/texture courante d'un mesh.
		void appliquerMateriau(modele::Materiau const& materiau) const;
		/// Cr�ation r�cursive des VBO
		void creerVBO(modele::Noeud const& noeud);
		/// Dessin r�cursif
		void dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex, bool estSelectionne, bool attribCouleur, 
						GLubyte couleurObjet[], GLubyte couleurSelection[]) const;

		/// Permet de v�rifier si l'identifiant est valide
		inline bool identifiantEstValide() const;

		/// Mod�le � dessiner
		modele::Modele3D const* modele_{ nullptr };
		/// Les identifiants OpenGL.
		std::vector<unsigned int> handles_;
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn template <typename T> inline void VBO::enregistrerTampon(T const& data)
	///
	/// Permet de charger les donn�es d'un mod�le (vertex, normales, texCoord, etc.)
	/// en m�moire de la carte graphique et de conserver un handle vers les donn�es.
	///
	/// @param[in] data : le vecteur contenant les donn�es.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	template <typename T>
	inline void VBO::enregistrerTampon(T const& data)
	{
		/// Le type contenu dans le std::vecteur (glm::vec3, glm::ivec3, etc.)
		using type = T::value_type;
		/// Le type contenu dans le glm::vec (float, int, etc.)
		using subType = type::value_type;
		/// Le tampon � envoyer � la carte graphique
		std::vector<subType> tampon;
		/// R�cup�rer la dimension du glm::vec
		int size = type{}.length();
		tampon.reserve(data.size() * size);

		/// Cr�er un tampon s�quentiel.
		for (auto const& subData : data)
		{
			for (int i = 0; i < subData.length(); ++i)
			{
				tampon.push_back(subData[i]);
			}
		}

		/// On assume que les entiers sont utilis�s pour les indices.
		auto bufferType = std::is_same<subType, int>::value ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER;

		/// Transf�rer le tampon cr��.
		unsigned int tamponSommet;
		glGenBuffers(1, &tamponSommet);
		glBindBuffer(bufferType, tamponSommet);
		glBufferData(bufferType, tampon.size() * sizeof(subType), data.data(), GL_STATIC_DRAW);
		/// Conserver le handle.
		handles_.push_back(tamponSommet);
	}
}
#endif /// __VBO_H__