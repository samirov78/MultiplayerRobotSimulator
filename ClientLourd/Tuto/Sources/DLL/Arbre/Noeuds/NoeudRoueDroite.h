///////////////////////////////////////////////////////////////////////////
/// @file NoeudRoueDroite.h
/// @author INF2990 Eq.11
/// @date 2016-02-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDROUEDROITE_H__
#define __ARBRE_NOEUDS_NOEUDROUEDROITE_H__


#include "NoeudRoue.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudRoueDroite
/// @brief Classe qui représente un noeud roue droite.
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class NoeudRoueDroite : public NoeudRoue
{
public:
	/// Constructeur du noeud poteau
	NoeudRoueDroite(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRoueDroite();

	/// Affiche le noeud poteau
	virtual void afficherConcret(const bool& attribuerCouleur) const;
	/// Effectue l'animation du noeud poteau
	virtual void animer(float dt);
	
	/// appliquer l'algorithme du visiteur sur le noeud courant 
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
};


#endif // __ARBRE_NOEUDS_NOEUDROUEDROITE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
