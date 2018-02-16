///////////////////////////////////////////////////////////////////////////////
/// @file OpenGL_Nuanceur.h
///
/// @author Martin Paradis
/// @date 2014-08-28
///
/// @addtogroup opengl OpenGL
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __OPENGL_NUANCEUR_H__
#define __OPENGL_NUANCEUR_H__

#include <filesystem>
#include <string>

#include "gl\glew.h"

namespace opengl{
	////////////////////////////////////////////////////////////////////////////////
	///
	/// @class OpenGL::Nuanceur
	/// @brief Encapsule un nuanceur OpenGL pour les types suivants :
	///				- Vertex shader
	///				- Fragment shader
	///
	/// @author Martin Paradis
	/// @date 2014-08-28
	////////////////////////////////////////////////////////////////////////////////
	class Nuanceur {
	public:
		using Path = std::tr2::sys::path;

		/// Types de nuanceur
		enum class Type : int {
			NUANCEUR_INVALIDE = 0,
			NUANCEUR_VERTEX = GL_VERTEX_SHADER,
			NUANCEUR_FRAGMENT = GL_FRAGMENT_SHADER
		};

		Nuanceur() = default;
		/// Constructeur par transfert ("move") pour �viter de rel�cher le nuanceur
		/// sur la destruction
		Nuanceur(Nuanceur&& nuanceur);
		/// Copie par transfert ("move") pour �viter de rel�cher le nuanceur
		/// sur la destruction
		Nuanceur& operator=(Nuanceur&& nuanceur);

		Nuanceur(Nuanceur const&) = delete;
		Nuanceur& operator=(Nuanceur const&) = delete;

		/// Destructeur
		~Nuanceur();

		/// obtient un identifiant opengl et compile le nuanceur contenu dans le
		/// fichier pass� en param�tre
		void initialiser(Type typeNuanceur, Path fichierSource);

		/// R�cup�rer le nom
		inline const std::string  obtenirNom()    const;
		/// R�cup�rer le texte du nuanceur
		inline const std::string& obtenirSource() const;
		/// R�cup�rer le type du nuanceur
		inline const Type		  obtenirType()   const;
		/// R�cup�rer l'identifiant opengl du nuanceur
		inline		 GLuint		  obtenirHandle() const;

		/// V�rifie qu'un identifiant opengl a �t� assign�
		inline bool estInitialise()	  const;
		/// V�rifie si le code source du nuanceur est charg�
		inline bool sourceEstCharge() const;
		/// V�rifie que le code source a �t� compil�
		inline bool estCompile()      const;

		/// R�cup�rer une chaine de caract�re repr�sentant l'�tat du nuanceur
		std::string serialiser() const;

	private:
		/// Identifiant invalide d'un nuanceur
		static const GLint NUANCEUR_INVALIDE{ 0 };

		/// identifiant opengl
		GLuint		handle_{ 0 };
		/// Type du nuanceur
		Type		type_{ Type::NUANCEUR_INVALIDE };
		/// Nom du nuanceur (obtenu � partir du nom du fichier)
		std::string nom_;
		/// Code source du nuanceur
		std::string source_;
		/// Drapeaux de l'�tat du nuanceur
		struct Drapeau{
			bool estInitialise{ false };
			bool sourceEstCharge{ false };
			bool estCompile{ false };
		} flags;

		/// Permet de cr�er un identifiant opengl
		void creer(Type typeNuanceur);
		/// Permet de charger le code source sur la carte graphique
		void chargerSource(Path fichierSource);
		/// Permet de compiler le code source sur la carte graphique
		void compiler();
		/// Permet de rel�cher l'identifiant opengl
		void relacher();
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const std::string Nuanceur::obtenirNom() const
	///
	/// Cette fonction retourne le nom du nuanceur, obtenu � partir du nom
	/// de fichier contenant le code source.
	///
	/// @return Le nom du nuanceur.
	///
	////////////////////////////////////////////////////////////////////////
	inline const std::string Nuanceur::obtenirNom() const
	{
		return nom_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const Nuanceur::Type Nuanceur::obtenirType() const
	///
	/// Cette fonction retourne le type du nuanceur, soit un nuanceur de 
	/// sommets ou un nuanceur de fragments.
	///
	/// @return Le type du nuanceur.
	///
	////////////////////////////////////////////////////////////////////////
	inline const Nuanceur::Type Nuanceur::obtenirType() const
	{
		return type_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline GLuint Nuanceur::obtenirHandle() const
	///
	/// Cette fonction retourne l'identifiant opengl du nuanceur.
	///
	/// @return L'identifiant opengl du nuanceur.
	///
	////////////////////////////////////////////////////////////////////////
	inline GLuint Nuanceur::obtenirHandle() const
	{
		return handle_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const std::string& Nuanceur::obtenirSource() const
	///
	/// Cette fonction retourne la chaine de caract�res contenant le code 
	/// source du nuanceur.
	///
	/// @return Le code source du nuanceur.
	///
	////////////////////////////////////////////////////////////////////////
	inline const std::string& Nuanceur::obtenirSource() const
	{
		return source_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Nuanceur::estInitialise() const
	///
	/// Cette fonction permet de savoir si un identifiant opengl a �t�
	/// g�n�r� pour le pr�sent nuanceur.
	///
	/// @return Vrai si un identifiant existe, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Nuanceur::estInitialise() const
	{
		return flags.estInitialise;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Nuanceur::sourceEstCharge() const
	///
	/// Cette fonction permet de savoir si le code source du nuanceur a �t�
	/// charg� sur la carte graphique.
	///
	/// @return Vrai si le code source a �t� charg�, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Nuanceur::sourceEstCharge() const
	{
		return flags.sourceEstCharge;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Nuanceur::estCompile() const
	///
	/// Cette fonction permet de savoir si le code source du nuanceur a �t�
	/// compil�.
	///
	/// @return Vrai si le code source a �t� compil�, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Nuanceur::estCompile() const
	{
		return flags.estCompile;
	}


	namespace debug{
		/// Affiche les info de d�bug
		void afficherDebugInfo(const Nuanceur& nuanceur);
	}
}
#endif // __OPENGL_NUANCEUR_H__

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
