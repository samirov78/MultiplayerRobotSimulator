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
#include "VisiteurRotateSelection.h"
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
void VisiteurRotateSelection::visiter(NoeudPoteau& noeud)
{
	if (noeud.estSelectionne()&& noeud.estSelectionnable())
	{

		double angleRad = utilitaire::DEG_TO_RAD(rotation_);
		glm::dvec4 angleInitial = noeud.obtenirRotationRelative();
		glm::dvec3 positionInitiale = noeud.obtenirPositionRelative();
		glm::dvec3 position;

		position.x = cos(angleRad) * (positionInitiale.x - centre_.x) - sin(angleRad) * (positionInitiale.y - centre_.y) + centre_.x;
		position.y = sin(angleRad) * (positionInitiale.x - centre_.x) + cos(angleRad) * (positionInitiale.y - centre_.y) + centre_.y;
		position.z = noeud.obtenirPositionRelative().z;
		noeud.assignerPositionRelative(position);
			
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
void VisiteurRotateSelection::visiter(NoeudMur& noeud)
{
	if (noeud.estSelectionne() && noeud.estSelectionnable())
	{

		glm::dvec4 rotationInitiale = noeud.obtenirRotationRelative();
		glm::dvec3 centreInitial = noeud.obtenirPositionRelative();
		glm::dvec3 positionInitialeLigne = noeud.obtenirParent()->obtenirPositionRelative(); // position par defaut de la ligne
		glm::dvec3 scaleInitial = noeud.obtenirRedimensionnementRelative();

		glm::dvec3 pointDebutInitial = noeud.getPointDepart();
		glm::dvec3 pointFinInitial = noeud.getPointFin();
		glm::dvec3 pointDebutFinal, pointFinFinal; // oui cest pas un joli comme nom 
		pointDebutFinal = pointDebutInitial; pointFinFinal = pointFinInitial;

		FacadeModele::obtenirInstance()->rotaterPointAutourDecentre(centre_.x, centre_.y, rotation_, pointDebutFinal);
		FacadeModele::obtenirInstance()->rotaterPointAutourDecentre(centre_.x, centre_.y, rotation_, pointFinFinal);
		double longueurObjet, angleObjet;
		glm::dvec3 centre = FacadeModele::obtenirInstance()->calculerDimensions(longueurObjet, angleObjet, pointDebutFinal, pointFinFinal);

		noeud.assignerPositionRelative(glm::dvec3(centre.x, centre.y, 1.0));
		noeud.assignerRedimensionnementRelative(glm::dvec3(longueurObjet, 1.0, 1.0));
		noeud.assignerRotationRelative(glm::dvec4(angleObjet, 0.0, 0.0, 1.0));
//3		noeud.setPoints(pointDebutFinal, pointFinFinal);

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
void VisiteurRotateSelection::visiter(NoeudFleche& noeud)
{
	if (noeud.estSelectionne() && noeud.estSelectionnable())
	{

		double angleRad = utilitaire::DEG_TO_RAD(rotation_);
		glm::dvec4 angleInitial = noeud.obtenirRotationRelative();
		glm::dvec3 positionInitiale = noeud.obtenirPositionRelative();
		glm::dvec3 position;

		position.x = cos(angleRad) * (positionInitiale.x - centre_.x) - sin(angleRad) * (positionInitiale.y - centre_.y) + centre_.x;
		position.y = sin(angleRad) * (positionInitiale.x - centre_.x) + cos(angleRad) * (positionInitiale.y - centre_.y) + centre_.y;
		position.z = noeud.obtenirPositionRelative().z;
		noeud.assignerPositionRelative(position);
		double nouvelAngle = angleInitial[0] + utilitaire::RAD_TO_DEG(angleRad);
		noeud.assignerRotationRelative(glm::dvec4(nouvelAngle , 0, 0, 1));
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
void VisiteurRotateSelection::visiter(NoeudSegment& noeud)
{
	
	if (noeud.estSelectionne() && noeud.estSelectionnable())
	{
		glm::dvec4 rotationInitiale = noeud.obtenirRotationRelative();
		glm::dvec3 centreInitial = noeud.obtenirPositionRelative();
		glm::dvec3 positionInitialeLigne = noeud.obtenirParent()->obtenirPositionRelative(); // position par defaut de la ligne
		glm::dvec3 scaleInitial = noeud.obtenirRedimensionnementRelative();

		glm::dvec3 pointDebutInitial = noeud.getPointDepart();
		glm::dvec3 pointFinInitial = noeud.getPointFin();
		glm::dvec3 pointDebutFinal, pointFinFinal; // oui cest pas un joli comme nom 
		pointDebutFinal = pointDebutInitial; pointFinFinal = pointFinInitial;

		FacadeModele::obtenirInstance()->rotaterPointAutourDecentre(centre_.x, centre_.y, rotation_, pointDebutFinal);
		FacadeModele::obtenirInstance()->rotaterPointAutourDecentre(centre_.x, centre_.y, rotation_, pointFinFinal);
		double longueurObjet, angleObjet;
		glm::dvec3 centre = FacadeModele::obtenirInstance()->calculerDimensions(longueurObjet, angleObjet, pointDebutFinal, pointFinFinal);

		noeud.assignerPositionRelative(glm::dvec3(centre.x, centre.y, 1.0));
		noeud.assignerRedimensionnementRelative(glm::dvec3(longueurObjet, 1.0, 1.0));
		noeud.assignerRotationRelative(glm::dvec4(angleObjet, 0.0, 0.0, 1.0));
//3		noeud.setPoints(pointDebutFinal, pointFinFinal);
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
void VisiteurRotateSelection::visiter(NoeudLigne& noeud)
{
	
}
