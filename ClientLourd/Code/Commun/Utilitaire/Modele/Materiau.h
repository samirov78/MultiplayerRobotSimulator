///////////////////////////////////////////////////////////////////////////////
/// @file Materiau.h
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __RENDERING_MATERIAU_H__
#define __RENDERING_MATERIAU_H__

#include <vector>
#include <string>

#include "glm/glm.hpp"

struct aiMaterial;

namespace modele{

	///////////////////////////////////////////////////////////////////////////
	/// @struct Materiau
	/// @brief Structure comprennant les divers composants d'un mat�riau.
	///
	/// @author Martin Paradis
	/// @date 2014-08-16
	///////////////////////////////////////////////////////////////////////////
	struct Materiau{
	public:
		/// Alias de type
		using VecType = glm::vec3;
		
		Materiau() = default;
		/// Constructeur � partir d'un mat�riau assimp
		Materiau(aiMaterial const* material);

		/// Nom du mat�riau
		std::string nom_;
		/// Composante diffuse
		VecType diffuse_;
		/// Composante sp�culaire
		VecType speculaire_;
		/// Composante ambiante
		VecType ambiant_;
		/// Composante d'�mission
		VecType emission_;
		/// Composante de transparence
		VecType transparence_;
		/// Composante d'opacit�
		float opacite_					{ 0.0f };
		/// Composante de brillance
		float shininess_				{ 1.0f };
		/// Composante de force de brillance
		float shininessStrength_		{ 1.0f };
		/// Nom de la texture associ�e
		std::string nomTexture_;
		/// Mode de rendu (wireframe)
		bool filDeFer_					{ false };
		/// mode de culling (two-side)
		bool afficherDeuxCotes_			{ false };
	};
} /// fin de rendering

#endif /// __RENDERING_MATERIAU_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////