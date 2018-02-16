///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurScaleSelection.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurScaleSelection.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScaleSelection::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de redimensionnement à un 
/// objet sélectionné de la classe NoeudPoteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScaleSelection::visiter(NoeudPoteau& noeud)
{
	if (noeud.estSelectionne())
	{
		glm::dvec3 dimentionement = noeud.obtenirScaleInitialeEnTraitement();
		noeud.assignerRedimensionnementRelative(glm::dvec3(scale_ * dimentionement[0], scale_ * dimentionement[1], 1));
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScaleSelection::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de redimensionnement à un 
/// objet sélectionné de la classe NoeudMur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScaleSelection::visiter(NoeudMur& noeud)
{
	if (noeud.estSelectionne() /*&& (scale_ >= 0.01)*/)
	{
		/*if (scale_ >= 0.1){*/
			// a enlever et appliquer un simple redimensionnement
			 noeud.changerScale(scale_);

			 /*
			 glm::dvec3 dimensionement = noeud.obtenirRedimensionnementRelative();
			 double ancienneLongueur = dimensionement[0];
			 noeud.assignerRedimensionnementRelative(glm::dvec3(scale_ * dimensionement[0], dimensionement[1], 1));
			 glm::dvec3 pointDepart =noeud.getPointDepart();
			 glm::dvec3 pointFin = noeud.getPointFin();
			 glm::dvec3 position = noeud.obtenirPositionRelative();
			 double nouvelleLongueur = noeud.obtenirRedimensionnementRelative()[0];
			 glm::dvec3 pointDepart_ = position - ((pointFin - pointDepart) / ancienneLongueur) * (nouvelleLongueur / 2);
			 glm::dvec3 pointFin_ = position + ((pointFin - pointDepart) / ancienneLongueur) * (nouvelleLongueur / 2);
			 noeud.setPoints(pointDepart_, pointFin_);

			 */

		//}
	}	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScaleSelection::visiter(NoeudTable& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de redimensionnement à un 
/// objet sélectionné de la classe NoeudTable.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScaleSelection::visiter(NoeudTable& noeud)
{	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScaleSelection::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme de redimensionnement à un 
/// objet sélectionné de la classe NoeudFleche.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScaleSelection::visiter(NoeudFleche& noeud)
{
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
