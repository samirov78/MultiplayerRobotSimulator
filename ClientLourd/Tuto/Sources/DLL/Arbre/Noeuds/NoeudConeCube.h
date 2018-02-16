///////////////////////////////////////////////////////////////////////////
/// @file NoeudConeCube.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDCONECUBE_H__
#define __ARBRE_NOEUDS_NOEUDCONECUBE_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudConeCube
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudConeCube : public NoeudAbstrait
{
public:
   /// Constructeur � partir du type du noeud.
   NoeudConeCube(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudConeCube();

   /// Affiche le cube.
   virtual void afficherConcret(const bool& attribuerCouleur) const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );


private:
   /// Angle selon l'axe des X.
   float angleX_{ 0.f };
   /// Angle selon l'axe des Y.
   float angleY_{ 0.f };
   /// Angle de rotation.
   float angleRotation_{ 0.f };

};


#endif // __ARBRE_NOEUDS_NOEUDCONECUBE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
