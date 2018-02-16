////////////////////////////////////////////////
/// @file   VisiteurVerifierCollision.h
/// @author INF2990 Eq.11
/// @date   2016-03-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#ifndef	VISITEURVERIFIERCOLLISION_H
#define VISITEURVERIFIERCOLLISION_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <iostream>
#include "NoeudRobot.h"
#include "AideCollision.h"



///////////////////////////////////////////////////////////////////////////
/// @class VisiteurVerifierCollision
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   de vérifier la collision entre le robot et les objets poteaux et murs.
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-03-15
///////////////////////////////////////////////////////////////////////////

class VisiteurVerifierCollision : public VisiteurAbstrait
{
public:

	///Constucteur 

	VisiteurVerifierCollision()	{/* ptrLeRobot_ = (NoeudRobot*)FacadeModele::obtenirInstance()->obtenirRobot();*/}
	
	///Destructeur 
	~VisiteurVerifierCollision(){};

	const double VisiteurVerifierCollision::LARGEUR_MUR{ 0.25 };
	const double VisiteurVerifierCollision::DISTA_ROBOT{ 0.3 };
	///Algorithme de visite pour NoeudPoteau.
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur.
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudTable.
	virtual void visiter(NoeudTable& noeud);
	///Algorithme de visite pour NoeudFleche.
	virtual void visiter(NoeudFleche& noeud);
	///Algorithme de visite pour NoeudSegment.
	virtual void visiter(NoeudSegment& noeud);
	///Algorithme de visite pour NoeudLigne.
	virtual void visiter(NoeudLigne& noeud);
	virtual void visiter(NoeudRobot& noeud);

	///Calcule la distance entre un point et une droite.
	double calculerDistancePointDroite(glm::dvec2 pointDroite1, glm::dvec2 pointDroite2, glm::dvec2 point);
	///Pointeur vers le robot.
	NoeudRobot* ptrLeRobot_{ nullptr };
	///Type de collision.
	TypeCollision type_{ AUCUNE };
	///Objet en collision.
	ObjetCollision objet_{ AUCUN };
	///Detail d'une collision.
	aidecollision::DetailsCollision detailCollision_;
	///Angle de reflexion.
	double angleReflexion_{ 0.0 };
};

#endif

// VISITEURVERIFIERCOLLISION_H