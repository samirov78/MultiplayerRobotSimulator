///////////////////////////////////////////////////////////////////////////////
/// @file OpenGL_Programme.cpp
///
/// @author Martin Paradis
/// @date 2014-08-28
///
/// @addtogroup opengl OpenGL
/// @{
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <algorithm>

#include "OpenGL_Programme.h"
#include "OpenGL_Nuanceur.h"
#include "OpenGL_Debug.h"

namespace opengl{

	GLuint Programme::programmeActif{ PROGRAMME_INVALIDE };

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Programme::Programme(Programme&& programme)
	///
	/// Constructeur par transfert ("move") en utilisant l'assignation par
	/// transfert
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	Programme::Programme(Programme&& programme)
	{
		*this = std::move(programme);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Programme& Programme::operator=(Programme&& programme)
	///
	/// Transf�re la propri�t� du programme re�u en param�tre et s'assure
	/// que ce dernier ne lib�rera pas son identifiant opengl lors de sa 
	/// destruction.
	///
	/// @return Le pr�sent programme
	///
	////////////////////////////////////////////////////////////////////////
	Programme& Programme::operator=(Programme&& programme)
	{
		/// Lib�rer l'identifiant courant, si n�cessaire
		relacher();

		/// r�cup�rer les donn�es de l'autre programme
		handle_ = programme.handle_;
		programme.handle_ = PROGRAMME_INVALIDE;
		mapUniforme = std::move(programme.mapUniforme);
		nuanceursAttaches = std::move(programme.nuanceursAttaches);
		flags = programme.flags;
		nom_ = std::move(programme.nom_);
		programme.relacher();

		return *this;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Programme::~Programme()
	///
	/// Destructeur, ne fait que rel�cher l'identifiant OpenGL et remettre
	/// les donn�es � leur valeur initiale.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	Programme::~Programme()
	{
		relacher();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::relacher()
	///
	/// Rel�che l'identifiant OpenGL et remet les donn�es � leur valeur initiale.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::relacher()
	{
		if (handle_ != PROGRAMME_INVALIDE)
		{
			glDeleteProgram(handle_);
		}
		handle_ = PROGRAMME_INVALIDE;
		mapUniforme.clear();
		nuanceursAttaches.clear();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::initialiser()
	///
	/// Cr�e un identifiant OpenGL pour le programme.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::initialiser()
	{
		/// Make sure resource is not left unused
		relacher();
		handle_ = glCreateProgram();
		flags.estInitialise = (handle_ != PROGRAMME_INVALIDE);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::attacherNuanceur(const opengl::Nuanceur& shader)
	///
	/// Attache un nuanceur au programme.
	///
	/// @param[in] nuanceur : le nuanceur � attacher au programme
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::attacherNuanceur(const opengl::Nuanceur& nuanceur)
	{
		/// Attacher le nuanceur si le programme a �t� cr�� et si le 
		/// nuanceur n'est pas d�j� attach�
		if (flags.estInitialise &&
			std::find(std::begin(nuanceursAttaches), std::end(nuanceursAttaches), nuanceur.obtenirNom()) == nuanceursAttaches.end())
		{
			glAttachShader(handle_, nuanceur.obtenirHandle());
			nuanceursAttaches.push_back(nuanceur.obtenirNom());
			/// N�cessite d'�tre lier � nouveau
			flags.estLie = false;
			flags.estValide = false;
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::detacherNuanceur(const opengl::Nuanceur& shader)
	///
	/// Detache un nuanceur au programme.
	///
	/// @param[in] nuanceur : le nuanceur � d�tacher au programme
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::detacherNuanceur(const opengl::Nuanceur& shader)
	{
		/// D�tacher seulement si le nuanceur est attach�
		if (std::find(std::begin(nuanceursAttaches), std::end(nuanceursAttaches), shader.obtenirNom()) != nuanceursAttaches.end())
		{
			nuanceursAttaches.erase(std::remove(std::begin(nuanceursAttaches), std::end(nuanceursAttaches), shader.obtenirNom()), std::end(nuanceursAttaches));
			glDetachShader(handle_, shader.obtenirHandle());
			/// N�cessite d'�tre lier � nouveau
			flags.estLie = false;
			flags.estValide = false;
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::lier()
	///
	/// Permet de lier le programme.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::lier()
	{
		/// Ne pas lier le programme sans n�c�ssit�
		if (flags.estLie || !flags.estInitialise)
			return;

		/// La location des uniformes ne sont plus valides, on les flush
		mapUniforme.clear();

		glLinkProgram(handle_);

		/// V�rifier le status de la liaison
		GLint LinkStatus{ 0 };
		glGetProgramiv(handle_, GL_LINK_STATUS, &LinkStatus);
		flags.estLie = (LinkStatus == GL_TRUE);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::valider()
	///
	/// Permet de valider le programme.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::valider()
	{
		/// Ne pas valider sans n�c�ssit�
		if (flags.estValide || !flags.estLie)
			return;

		glValidateProgram(handle_);

		/// V�rifier le status de la validit�
		GLint validationStatus{ 0 };
		glGetProgramiv(handle_, GL_VALIDATE_STATUS, &validationStatus);
		flags.estValide = (validationStatus == GL_TRUE);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::Start(Programme& programme)
	///
	/// Permet de commencer l'utilisation d'un programme.
	///
	/// @param[in] : programme : le programme � utiliser.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::Start(Programme & programme)
	{
		/// Ne pas repartir le m�me programme
		if (programmeActif == programme.handle_ && programme.flags.estValide)
			return;

		/// Lier et valider le programme
		programme.lier();
		programme.valider();
		/// Ne pas partir un programme invalide
		programmeActif = programme.flags.estValide ? programme.handle_ : PROGRAMME_INVALIDE;
		glUseProgram(programmeActif);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Programme::Stop(Programme& programme)
	///
	/// Permet de cesser l'utilisation d'un programme.
	///
	/// @param[in] : programme : le programme � cesser.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Programme::Stop(Programme const& programme)
	{
		/// Ne pas cesser l'utilisation d'un programme s'il n'est pas utilis�
		if (programmeActif != programme.handle_)
			return;

		programmeActif = PROGRAMME_INVALIDE;
		glUseProgram(programmeActif);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool Programme::recupererLocationUniforme(std::string attribute_name)
	///
	/// Permet de r�cup�rer la location d'un uniforme dans les nuanceurs.
	///
	/// @param[in] : attribute_name : le nom de l'uniforme.
	///
	/// @return Vrai si la location a �t� r�cup�r�e, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	bool Programme::recupererLocationUniforme(std::string attribute_name)
	{
		/// Si la location n'est pas d�j� trouv�e
		bool reponse = true;
		if (mapUniforme.find(attribute_name) == mapUniforme.end())
		{
			/// L'obtenir
			GLint uniform{ glGetUniformLocation(handle_, attribute_name.c_str()) };
			if (uniform == -1)
			{
				/// La location de l'uniforme n'a pu �tre trouv�e
				reponse = false;
			}
			else
			{	/// Conserver la location de l'uniforme
				mapUniforme[attribute_name] = uniform;
			}
		}
		return reponse;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn std::string Programme::serialiser() const
	///
	/// Permet d'obtenir une chaine de caract�re repr�sentant l'�tat du 
	/// programme.
	///
	/// @return La chaine de caract�re repr�sentant l'�tat du programme.
	///
	////////////////////////////////////////////////////////////////////////
	std::string Programme::serialiser() const
	{
		std::stringstream programme;
		programme
			<< '\n'
			<< "Programme : " << '\n'
			<< '\t' << nom_ << '\n'
			<< "handle : " << '\n'
			<< '\t';

		flags.estInitialise ? programme << handle_ : programme << "Non-initialise";
		programme << '\n';

		programme
			<< "Nuanceurs attaches : " << '\n';
		if (!nuanceursAttaches.empty())
		{
			for (std::string const& shader_name : nuanceursAttaches)
			{
				programme << '\t' << shader_name << '\n';
			}
		}
		else
		{
			programme << '\t' << "Aucun" << '\n';
		}

		programme << "uniforme map :" << '\n';
		if (!mapUniforme.empty())
		{
			for (auto const& elem : mapUniforme)
			{
				programme << '\t' << "{ " << "uniforme location: " << elem.second << ", nom : " << elem.first << " }" << '\n';
			}
		}
		else
		{
			programme << '\t' << "Aucun" << '\n';
		}

		programme << "Validite : " << '\n';
		if (flags.estValide)
		{
			programme << '\t' << "valide.";
		}
		else
		{
			programme << '\t' << (flags.estLie ? "invalide." : flags.estInitialise ? "non-lie." : "non-initialise.");
		}

		programme << '\n';
		return programme.str();
	}

	namespace debug{
		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void afficherDebugInfo(const Programme& programme)
		///
		/// Permet d'afficher une chaine de caract�re repr�sentant l'�tat du 
		/// programme.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void afficherDebugInfo(const Programme& programme)
		{
			std::cout << programme.serialiser();
			std::cout << ObtenirProgrammeLog(programme.obtenirHandle());
		}
	}
}

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
