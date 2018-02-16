///////////////////////////////////////////////////////////////////////////////
/// @file Mesh.cpp
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup rendering Rendering
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Mesh.h"
#include "scene.h"			// Structure de donn�es de sortie "assimp"

namespace modele{

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn Mesh::Mesh(aiScene const* scene, aiMesh const* mesh)
	///
	/// Construit un mesh � partir d'une sc�ne et d'un mesh Assimp
	///
	/// @param[in] scene : la sc�ne contenant le mod�le
	/// @param[in] mesh  : le mesh � importer
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	Mesh::Mesh(aiScene const* scene, aiMesh const* mesh)
	{
		if (scene == nullptr || mesh == nullptr)
			return;

		/// Le mesh contient les informations sur le nombre de donn�es � importer,
		/// on r�serve donc la m�moire pour �viter la r�allocation.
		reserverMemoire(mesh);

		/// Pour tous les sommets
		for (unsigned int vertex_index{ 0 }; vertex_index < mesh->mNumVertices; ++vertex_index)
		{
			/// Positions
			if (mesh->HasPositions())
			{
				const aiVector3D* vertex{ &(mesh->mVertices[vertex_index]) };
				vertices_.emplace_back(vertex->x, vertex->y, vertex->z);
			}

			/// Normales
			if (mesh->HasNormals())
			{
				const aiVector3D* normal{ &(mesh->mNormals[vertex_index]) };
				normales_.emplace_back(normal->x, normal->y, normal->z);
			}

			/// Une seule texture 2D est support�e
			if (mesh->HasTextureCoords(0))
			{
				const aiVector3D* texcoord{ &(mesh->mTextureCoords[0][vertex_index]) };
				texcoords_.emplace_back(texcoord->x, texcoord->y);
			}

			/// Une seule couleur par vertex est support�e
			if (mesh->HasVertexColors(0))
			{
				const aiColor4D* couleur{ &(mesh->mColors[0][vertex_index]) };
				couleurs_.emplace_back(couleur->r, couleur->g, couleur->b, couleur->a);
			}
		}

		/// Pour chaque face
		for (size_t face_index{ 0 }; face_index < mesh->mNumFaces; ++face_index)
		{
			const aiFace* face{ &(mesh->mFaces[face_index]) };
			/// R�cup�rer les indices de face
			for (size_t index{ 0 }; index < face->mNumIndices; index += 3)
				faces_.emplace_back(face->mIndices[index], face->mIndices[index + 1], face->mIndices[index + 2]);
		}

		/// Assigner le materiau
		materiau_ = Materiau{ scene->mMaterials[mesh->mMaterialIndex] };
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Mesh::reserverMemoire(aiMesh const* mesh)
	///
	/// Permet de r�server la m�moire des conteneurs pour �viter la r�allocation
	/// de la m�moire.
	///
	/// @param[in] mesh  : le mesh assimp
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Mesh::reserverMemoire(aiMesh const* mesh)
	{
		/// Positions (toujours pr�sentes)
		if (mesh->HasPositions())
		{
			vertices_.reserve(mesh->mNumVertices);
		}

		/// Normales
		if (mesh->HasNormals())
		{
			normales_.reserve(mesh->mNumVertices);
		}

		/// Une seule texture est support�e
		if (mesh->HasTextureCoords(0))
		{
			texcoords_.reserve(mesh->mNumVertices);
		}

		/// Une seule couleur par vertex est support�e
		if (mesh->HasVertexColors(0))
		{
			couleurs_.reserve(mesh->mNumVertices);
		}

		/// Faces (toujours pr�sentes)
		if (mesh->HasFaces())
		{
			faces_.reserve(mesh->mNumFaces);
		}
	}

} /// fin de rendering

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////