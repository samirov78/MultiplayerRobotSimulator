///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotateSelection.cpp
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "visiteurSelectElastique.h"
#include "VisiteurAnnulerRotationSelection.h"
#include <iostream>
#include "FacadeModele.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotateSelection::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme rotation sur un objet
/// poteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAnnulerRotationSelection::visiter(NoeudPoteau& noeud)
{
	if (noeud.estSelectionne() && noeud.estSelectionnable())
	{
		noeud.assignerPositionRelative(noeud.obtenirPositionInitialeEnTraitement());
		noeud.assignerRotationRelative(noeud.getRotationRelativeAvantraitement());
		
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotateSelection::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme rotation sur un objet
/// mur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAnnulerRotationSelection::visiter(NoeudMur& noeud)
{
	if (noeud.estSelectionne() && noeud.estSelectionnable())
	{
		noeud.assignerPositionRelative(noeud.obtenirPositionInitialeEnTraitement());
		noeud.assignerRotationRelative(noeud.getRotationRelativeAvantraitement());
		noeud.setPoints(noeud.getPointDepartInitialEnTraitement(), noeud.getPointFinInitialEnTraitement());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotateSelection::visiter(NoeudFleche& noeud)
///
/// Cette methode permet d'appliquer l'algorithme rotation sur un objet
/// fleche.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAnnulerRotationSelection::visiter(NoeudFleche& noeud)
{
	if (noeud.estSelectionne() && noeud.estSelectionnable())
	{
		noeud.assignerPositionRelative(noeud.obtenirPositionInitialeEnTraitement());
		noeud.assignerRotationRelative(noeud.getRotationRelativeAvantraitement());

	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotateSelection::visiter(NoeudSegment& noeud)
///
/// Cette methode permet d'appliquer l'algorithme rotation sur un objet
/// segment.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAnnulerRotationSelection::visiter(NoeudSegment& noeud)
{
	if (noeud.estSelectionne() && noeud.estSelectionnable())
	{
		noeud.assignerPositionRelative(noeud.obtenirPositionInitialeEnTraitement());
		noeud.assignerRotationRelative(noeud.getRotationRelativeAvantraitement());
		noeud.setPoints(noeud.getPointDepartInitialEnTraitement(), noeud.getPointFinInitialEnTraitement());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotateSelection::visiter(NoeudLigne& noeud)
///
/// Cette methode permet d'appliquer l'algorithme rotation sur un objet
/// ligne.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAnnulerRotationSelection::visiter(NoeudLigne& noeud)
{

}
