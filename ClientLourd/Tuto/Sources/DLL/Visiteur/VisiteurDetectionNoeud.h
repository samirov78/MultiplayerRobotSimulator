////////////////////////////////////////////////
/// @file   VisiteurDetectionNoeud.h
/// @author INF2990 Eq.11
/// @date   2016-03-21
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#pragma once

#include "VisiteurAbstrait.h"
#include "NoeudRobot.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 
#include <iostream>
#include "AideCollision.h"
#include "SegmentDroite2D.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDetectionNoeud
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud afin de determiner
///		   s'il y a une collision ou non avec les capteurs de distances.
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////

class VisiteurDetectionNoeud : public VisiteurAbstrait
{
public:

	//Constucteur 
	VisiteurDetectionNoeud(NoeudAbstrait* robot) : leRobot_(robot) {};

	///Destructeur 
	~VisiteurDetectionNoeud(){};

	///Algorithme de visite pour NoeudPoteau
	virtual void visiter(NoeudPoteau& noeud);
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMur& noeud);
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudFleche& noeud);
	///Algorithme de visite pour un NoeudSegment
	virtual void visiter(NoeudSegment& noeud);
	///Algorithme de visite pour NoeudLigne
	virtual void visiter(NoeudLigne& noeud);
private:
	///Fonction permettant de calculer les quatres coins d'un mur.
	void calculerCoinMur(glm::dvec2 pointInitial, glm::dvec2 pointFinal, glm::dvec2& p1, glm::dvec2& p2, glm::dvec2& p3, glm::dvec2& p4, const double& theta);
	///Fonction permettant de mettre a jour les attributs representant les point des capteurs a jours.
	void updatePositionPointCapteurs();
	NoeudAbstrait* leRobot_;
	glm::dvec2 p1CapteurDangerDroit;
	glm::dvec2 p2CapteurDangerDroit;
	glm::dvec2 p3CapteurDangerDroit;
	glm::dvec2 p4CapteurDangerDroit;
	glm::dvec2 p2CapteurSecuritaireDroit;
	glm::dvec2 p3CapteurSecuritaireDroit;

	//Donnee du capteur milieu
	glm::dvec2 p1CapteurDangerMilieu;
	glm::dvec2 p2CapteurDangerMilieu;
	glm::dvec2 p3CapteurDangerMilieu;
	glm::dvec2 p4CapteurDangerMilieu;
	glm::dvec2 p2CapteurSecuritaireMilieu;
	glm::dvec2 p3CapteurSecuritaireMilieu;

	//Donnee du capteur gauche
	glm::dvec2 p1CapteurDangerGauche;
	glm::dvec2 p2CapteurDangerGauche;
	glm::dvec2 p3CapteurDangerGauche;
	glm::dvec2 p4CapteurDangerGauche;
	glm::dvec2 p2CapteurSecuritaireGauche;
	glm::dvec2 p3CapteurSecuritaireGauche;
};