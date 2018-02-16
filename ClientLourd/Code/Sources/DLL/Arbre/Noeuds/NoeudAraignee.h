///////////////////////////////////////////////////////////////////////////
/// @file NoeudAraignee.h
/// @author Julien Gascon-Samson- modified by Mehdi KADI 2016-01-17 (Patron visiteur ajout�)
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDARAIGNEE_H__
#define __ARBRE_NOEUDS_NOEUDARAIGNEE_H__


#include "NoeudComposite.h"
#include "GL/glew.h"

#include "NoeudAbstrait.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudAraignee
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
/// 
/// @author Julien Gascon-Samson - modified by Mehdi KADI 2016-01-17 (Patron visiteur ajout�)
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudAraignee : public NoeudComposite
{
public:
   /// Constructeur � partir du type du noeud.
   NoeudAraignee(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudAraignee();

   /// Affiche le cube.
   virtual void afficherConcret(const bool& attribuerCouleur) const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );

   // appliquer l'algorithme du visiteur sur le noeud courant 
   void accepterVisiteur(VisiteurAbstrait& visiteur);


private:
   /// Angle dans le sinus de l'oscillation
   float angle_{ 0 };

};


#endif // __ARBRE_NOEUDS_NOEUDARAIGNEE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
