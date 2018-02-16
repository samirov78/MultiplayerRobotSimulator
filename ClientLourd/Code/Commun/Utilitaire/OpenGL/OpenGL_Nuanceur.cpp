///////////////////////////////////////////////////////////////////////////////
/// @file OpenGL_Nuanceur.cpp
///
/// @author Martin Paradis
/// @date 2014-08-28
///
/// @addtogroup opengl OpenGL
/// @{
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include "OpenGL_Nuanceur.h"
#include "OpenGL_Debug.h"
#include "Utilitaire.h"

namespace opengl{

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Nuanceur::Nuanceur(Nuanceur&& shader)
	///
	/// Constructeur par transfert ("move") en utilisant l'assignation par
	/// transfert
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	Nuanceur::Nuanceur(Nuanceur&& shader)
	{
		*this = std::move(shader);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Nuanceur& Nuanceur::operator=(Nuanceur&& shader)
	///
	/// Transf�re la propri�t� du nuanceur re�u en param�tre et s'assure
	/// que ce dernier ne lib�rera pas son identifiant opengl lors de sa 
	/// destruction.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	Nuanceur& Nuanceur::operator=(Nuanceur&& shader)
	{
		/// Lib�rer l'identifiant courant, si n�cessaire
		relacher();

		/// r�cup�rer les donn�es de l'autre nuanceur
		handle_ = shader.handle_;
		shader.handle_ = NUANCEUR_INVALIDE;
		type_ = shader.type_;
		flags = shader.flags;
		nom_ = std::move(shader.nom_);
		source_ = std::move(shader.source_);
		shader.relacher();

		return *this;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Nuanceur::~Nuanceur()
	///
	/// Destructeur, ne fait que rel�cher l'identifiant OpenGL et remettre
	/// les donn�es � leur valeur initiale.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	Nuanceur::~Nuanceur()
	{
		relacher();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Nuanceur::relacher()
	///
	/// Rel�che l'identifiant OpenGL et remet les donn�es � leur valeur initiale.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Nuanceur::relacher()
	{
		/// Si l'identifiant est valide, on le lib�re
		if (handle_ != NUANCEUR_INVALIDE)
		{
			glDeleteShader(handle_);
			handle_ = NUANCEUR_INVALIDE;
		}
		nom_.clear();
		source_.clear();
		type_ = Type::NUANCEUR_INVALIDE;
		flags = Drapeau{};
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Nuanceur::initialiser(Type shader_type, Nuanceur::Path code_filename)
	///
	/// Cr�e un identifiant OpenGL, charge et compile le code source sur la
	/// carte graphique.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Nuanceur::initialiser(Type shader_type, Nuanceur::Path code_filename)
	{
		/// relacher l'idenfiant
		if (handle_ != NUANCEUR_INVALIDE)
			relacher();

		/// Recr�er l'identifiant
		creer(shader_type);
		/// Charger le code source le compiler
		chargerSource(code_filename);
		compiler();
		/// Si la compilation r�ussie, on conserve le nom du fichier
		if (flags.estCompile)
		{
			nom_ = Path{ code_filename }.filename().string();
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Nuanceur::creer(Type shader_type)
	///
	/// Cr�e un identifiant OpenGL, selon le type de nuanceur souhait�.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Nuanceur::creer(Type shader_type)
	{
		handle_ = glCreateShader(static_cast<GLenum>(shader_type));

		/// Conserver le type de nuanceur si la cr�ation a r�ussie
		flags.estInitialise = (handle_ != NUANCEUR_INVALIDE);
		if (flags.estInitialise)
		{
			type_ = shader_type;
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Nuanceur::chargerSource(Nuanceur::Path code_filename)
	///
	/// Charge le code source sur la carte graphique.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Nuanceur::chargerSource(Nuanceur::Path code_filename)
	{
		/// Inutile de charger le code source si le nuanceur n'est pas cr��
		if (!flags.estInitialise)
		{
			return;
		}

		/// Ouvrir le fichier
		std::ifstream file(code_filename);
		if (file.fail())
		{
			flags.sourceEstCharge = false;
			return;
		}

		/// Lire le fichier
		std::stringstream shader_code_stream;
		shader_code_stream << file.rdbuf();
		file.close();

		/// Conserver une copie et charger sur la carte graphique
		source_ = shader_code_stream.str();
		const GLchar *shader_source{ source_.c_str() };
		const GLint shader_length{ static_cast<GLint>(source_.size()) };
		glShaderSource(handle_, 1, &shader_source, &shader_length);

		flags.sourceEstCharge = true;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Nuanceur::compiler()
	///
	/// Compile le code source sur la carte graphique.
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	void Nuanceur::compiler()
	{
		/// Ne pas compiler si le code source n'est pas charg�
		if (!flags.sourceEstCharge)
		{
			return;
		}

		/// Compiler le nuanceur.
		glCompileShader(handle_);

		/// V�rifier la compilation
		GLint result{ 0 };
		glGetShaderiv(handle_, GL_COMPILE_STATUS, &result);
		flags.estCompile = (result == GL_TRUE);

		if (!flags.estCompile)
		{
			char logBuf[1024];
			int len;
			glGetShaderInfoLog(handle_, sizeof(logBuf), &len, logBuf);
			utilitaire::afficherErreur("Il n'a pas �t� possible de compiler le nuanceur : " + nom_ + "\n" + logBuf);
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn std::string Nuanceur::serialiser() const
	///
	/// Permet d'obtenir une chaine de caract�re repr�sentant l'�tat du 
	/// nuanceur.
	///
	/// @return La chaine de caract�re repr�sentant l'�tat du nuanceur.
	///
	////////////////////////////////////////////////////////////////////////
	std::string Nuanceur::serialiser() const
	{
		std::stringstream shader;
		shader
			<< "Nuanceur" << '\n'
			<< "Identifiant : " << '\n'
			<< '\t';

		flags.estInitialise ? shader << handle_ : shader << "Non initialise.";

		shader
			<< '\n'
			<< "Code source charge :" << '\n'
			<< '\t';
		flags.sourceEstCharge ? shader << "Oui" : shader << "Non";

		shader
			<< '\n'
			<< "Source Compilee :" << '\n'
			<< '\t';
		flags.estCompile ? shader << "Oui" : shader << "Non";

		shader << '\n';
		return shader.str();
	}


	namespace debug{
		////////////////////////////////////////////////////////////////////////
		///
		/// @fn void afficherDebugInfo(const Nuanceur& nuanceur)
		///
		/// Permet d'afficher une chaine de caract�re repr�sentant l'�tat du 
		/// nuanceur.
		///
		/// @return Aucune.
		///
		////////////////////////////////////////////////////////////////////////
		void afficherDebugInfo(const Nuanceur& nuanceur)
		{
			std::cout << nuanceur.serialiser();

			/// Afficher le probl�me, s'il y en a un.
			std::cout << ObtenirProgrammeLog(nuanceur.obtenirHandle());
		}
	}
}

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
