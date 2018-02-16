////////////////////////////////////////////////
/// @file   visiteurSelectObjet.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEURSELECTIONOBJET_H
#define VISITEURSELECTIONOBJET_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelectObjet
/// @brief Classe qui impl�mentante le visiteur concr�t permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud afin de
///		   permettre la selection par clic.
///
///		   Les visiteurs concr�ts pourront faire diff�rents tra�tements en 
///		   fonction du type de noeud visit�, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
#include <iostream>
class VisiteurSelectObjet : public VisiteurAbstrait
{
public:

	///Constucteur 
	VisiteurSelectObjet(glm::dvec3 & point, bool selectionUnique, GLubyte couleurPixel[], const bool& initialiserVisite)
	{
		type_ = VISITEUR_DEFAULT;
		point_ = point;
		selectionunique_ = selectionUnique;
		selectionexiste_ = false;
		for (unsigned int i = 0; i < 3; i++)
			couleurObjet_[i] = couleurPixel[i];
		initialiserVisite_ = initialiserVisite;
	};

	///Destructeur 
	~VisiteurSelectObjet(){};

	///Algorithme de visite pour NoeudPoteau
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudTable
	virtual void visiter(NoeudTable& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudFleche& noeud);
	///Algorithme de visite pour NoeudSegment
	virtual void visiter(NoeudSegment& noeud);
	///Algorithme de visite pour NoeudLigne
	virtual void visiter(NoeudLigne& noeud);

	///Methode permettant le retour de la selectionexiste
	bool obtenirselectionExiste() { return selectionexiste_; };


private:
	///Point de selection.
	glm::dvec3 point_;
	///Booleen representant une selection unique ou non.
	bool selectionunique_;
	///Booleen representant si une selection existe ou non.
	bool selectionexiste_;

	GLubyte couleurObjet_[3];

	bool initialiserVisite_;
};

#endif
//VISITEURSELECTIONOBJET_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


