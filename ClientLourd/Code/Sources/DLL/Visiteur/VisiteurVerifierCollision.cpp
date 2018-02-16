///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurVerifierCollision.cpp
/// @author INF2990 Eq.11
/// @date 2016-03-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurVerifierCollision.h"
#include "FacadeModele.h"
#include <iostream>
#include <cmath>

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierCollision::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet de vérifier la collision entre le robot et un
/// objet poteau.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierCollision::visiter(NoeudPoteau& noeud)
{
	double rayon = noeud.obtenirRedimensionnementRelative().x;
	glm::dvec2 position = glm::dvec2(noeud.obtenirPositionRelative());
	detailCollision_.type = aidecollision::COLLISION_AUCUNE;
	for (unsigned int i = 0; i < 16 && (detailCollision_.type == aidecollision::COLLISION_AUCUNE); i++)
	{
		glm::dvec2 point1 = ptrLeRobot_->bteEnglobante_->segments[i].point1;
		glm::dvec2 point2 = ptrLeRobot_->bteEnglobante_->segments[i].point2;
		detailCollision_ = aidecollision::calculerCollisionSegment(point1, point2, position, rayon);
		if (detailCollision_.type != aidecollision::COLLISION_AUCUNE)
		{
			angleReflexion_ = 45.0;
			if (i == 0 && detailCollision_.type == aidecollision::COLLISION_SEGMENT)
			{
				type_ = AVANT;
				angleReflexion_ = 0.0;
			}
			else if ((i == 0 && detailCollision_.type == aidecollision::COLLISION_SEGMENT_DEUXIEMEPOINT) || (i > 0 && i <= 4) ||
				(i == 5 && detailCollision_.type == aidecollision::COLLISION_SEGMENT_PREMIERPOINT))
			{
				type_ = AVANT_DROIT;
			}
			else if ((i == 5 && detailCollision_.type != aidecollision::COLLISION_SEGMENT_PREMIERPOINT) || (i >= 6 && i < 8) ||
				(i == 8 && detailCollision_.type == aidecollision::COLLISION_SEGMENT_PREMIERPOINT))
			{
				type_ = ARRIERE_DROIT;
			}
			else if (i == 8 && detailCollision_.type == aidecollision::COLLISION_SEGMENT)
			{
				type_ = ARRIERE;
				angleReflexion_ = 0.0;
			}
			else if ((i > 8 && i <= 10) || (i == 8 && detailCollision_.type != aidecollision::COLLISION_SEGMENT_PREMIERPOINT) ||
				(i == 11 && detailCollision_.type != aidecollision::COLLISION_SEGMENT_PREMIERPOINT))
			{
				type_ = ARRIERE_GAUCHE;
				angleReflexion_ = -1 * angleReflexion_;
			}
			else
			{
				type_ = AVANT_GAUCHE;
				angleReflexion_ = -1 * angleReflexion_;
			}
			objet_ = POTEAU;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierCollision::visiter(NoeudMur& noeud)
///
/// Cette methode permet de vérifier la collision entre le robot et un
/// objet mur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierCollision::visiter(NoeudMur& noeud)
{
	auto pointMur1 = noeud.getPointDepart();
	auto pointMur2 = noeud.getPointFin();
	int N = int(std::sqrt(pow((pointMur2.x - pointMur1.x), 2.0) + pow((pointMur2.y - pointMur1.y), 2.0)) / (LARGEUR_MUR / 2.0));
	glm::dvec2* point = new glm::dvec2[N+1]; //leak
	point[0] = glm::dvec2(pointMur1);
	for (int i = 1; i < N+1; i++)
	{
		point[i].x = point[i-1].x + (pointMur2.x - pointMur1.x) / N;
		point[i].y = point[i-1].y + (pointMur2.y - pointMur1.y) / N;
	}

	detailCollision_.type = aidecollision::COLLISION_AUCUNE;
	double rayon = LARGEUR_MUR / 2.0;
	for (unsigned int i = 0; i < 16 && (detailCollision_.type == aidecollision::COLLISION_AUCUNE); i++)
	{
		for (int j = 0; j < N + 1 && (detailCollision_.type == aidecollision::COLLISION_AUCUNE); j++)
		{
			auto point1 = ptrLeRobot_->bteEnglobante_->segments[i].point1;
			auto point2 = ptrLeRobot_->bteEnglobante_->segments[i].point2;
			detailCollision_ = aidecollision::calculerCollisionSegment(point1, point2, point[j], rayon);
			if (detailCollision_.type != aidecollision::COLLISION_AUCUNE)
			{
				auto vecteur1 = ptrLeRobot_->bteEnglobante_->segments[0].point2 - ptrLeRobot_->bteEnglobante_->segments[0].point1;
				vecteur1 = vecteur1 / std::sqrt(std::pow(vecteur1.x, 2.0) + std::pow(vecteur1.y, 2.0));
				auto vecteur2 = glm::dvec2(pointMur2 - pointMur1);
				vecteur2 = vecteur2 / std::sqrt(std::pow(vecteur2.x, 2.0) + std::pow(vecteur2.y, 2.0));
				auto theta = utilitaire::RAD_TO_DEG(std::acos(glm::dot(vecteur1, vecteur2)));
				auto alpha = (theta <= 90) ? std::acos(glm::dot(vecteur1, vecteur2)) : (utilitaire::PI - std::acos(glm::dot(vecteur1, vecteur2)));
				angleReflexion_ = utilitaire::RAD_TO_DEG(utilitaire::PI - 2 * alpha);
				if (i == 0 && std::abs(angleReflexion_) < 2.0)
				{
					type_ = AVANT;
				}
				else if ((i == 0 && (calculerDistancePointDroite(glm::dvec2(pointMur1), glm::dvec2(pointMur2), point2) < 2 * calculerDistancePointDroite(glm::dvec2(pointMur1), glm::dvec2(pointMur2), point1))) ||
					(i > 0 && i <= 4))
				{
					type_ = AVANT_DROIT;
				}
				else if ((i >= 5 && i < 8) || (i == 8 && detailCollision_.type != aidecollision::COLLISION_SEGMENT_DEUXIEMEPOINT))
				{
					type_ = ARRIERE_DROIT;
				}
				else if (i == 8 && std::abs(angleReflexion_) < 2.0)
				{
					type_ = ARRIERE;
				}
				else if ((i > 8 && i <= 11) || (i == 8 && detailCollision_.type != aidecollision::COLLISION_SEGMENT_PREMIERPOINT))
				{
					type_ = ARRIERE_GAUCHE;
					angleReflexion_ = -1 * angleReflexion_;
				}
				else
				{
					type_ = AVANT_GAUCHE;
					angleReflexion_ = -1 * angleReflexion_;
				}
				if ((i == 0 || i == 8) && (j <= 2 || j >= N - 2) && (std::abs(utilitaire::RAD_TO_DEG(alpha) >= 50)))
				{
					angleReflexion_ = 0.0;
				}
				if (noeud.estAffiche())
					objet_ = MUR_VISIBLE;
				else
					objet_ = MUR_INVISIBLE;
			}
		}
	}
	delete point;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierCollision::visiter(NoeudTable& noeud)
///
/// Cette methode ne fait rien
/// 
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierCollision::visiter(NoeudTable& noeud)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierCollision::visiter(NoeudLigne& noeud)
///
/// Cette methode ne fait rien
///  
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierCollision::visiter(NoeudLigne& noeud)
{

}

//collision entre les robot:
void VisiteurVerifierCollision::visiter(NoeudRobot & noeud)
{

	if (&noeud != ptrLeRobot_)

	{

		double rayon = DISTA_ROBOT;
		///detailCollision_.type = aidecollision::COLLISION_AUCUNE;
		for (unsigned int i = 0; i < 16 && (detailCollision_.type == aidecollision::COLLISION_AUCUNE); i++)
		{
			for (unsigned int j = 0; j < 16 && (detailCollision_.type == aidecollision::COLLISION_AUCUNE); j++)
			{
				glm::dvec2 RB1point1 = ptrLeRobot_->bteEnglobante_->segments[i].point1;
				glm::dvec2 RB1point2 = ptrLeRobot_->bteEnglobante_->segments[i].point2;
				glm::dvec2 RB2point1 = noeud.bteEnglobante_->segments[j].point1;
				glm::dvec2 RB2point2 = noeud.bteEnglobante_->segments[j].point2;


				aidecollision::DetailsCollision detailCollision_1 = aidecollision::calculerCollisionSegment(RB1point1, RB1point2, RB2point1, rayon);
				aidecollision::DetailsCollision detailCollision_2 = aidecollision::calculerCollisionSegment(RB1point1, RB1point2, RB2point2, rayon);
				aidecollision::DetailsCollision detailCollision_3 = aidecollision::calculerCollisionSegment(RB2point1, RB2point2, RB1point1, rayon);
				aidecollision::DetailsCollision detailCollision_4 = aidecollision::calculerCollisionSegment(RB2point1, RB2point2, RB1point2, rayon);

				if (detailCollision_1.type != aidecollision::COLLISION_AUCUNE ||
					detailCollision_2.type != aidecollision::COLLISION_AUCUNE ||
					detailCollision_3.type != aidecollision::COLLISION_AUCUNE ||
					detailCollision_4.type != aidecollision::COLLISION_AUCUNE)
				{
					if (detailCollision_1.type != aidecollision::COLLISION_AUCUNE)
					{
//head
						detailCollision_.type = detailCollision_1.type;
					}
					else if (detailCollision_2.type != aidecollision::COLLISION_AUCUNE)
					{
						detailCollision_.type = detailCollision_2.type;
					}
					else if (detailCollision_3.type != aidecollision::COLLISION_AUCUNE)
					{
						detailCollision_.type = detailCollision_3.type;
					}
					else if (detailCollision_4.type != aidecollision::COLLISION_AUCUNE)
					{
						detailCollision_.type = detailCollision_4.type;
					}


					auto vecteur1 = ptrLeRobot_->bteEnglobante_->segments[0].point2 - ptrLeRobot_->bteEnglobante_->segments[0].point1;
					vecteur1 = vecteur1 / std::sqrt(std::pow(vecteur1.x, 2.0) + std::pow(vecteur1.y, 2.0));
					auto vecteur2 = glm::dvec2(RB2point2 - RB2point1);
					vecteur2 = vecteur2 / std::sqrt(std::pow(vecteur2.x, 2.0) + std::pow(vecteur2.y, 2.0));
					auto theta = utilitaire::RAD_TO_DEG(std::acos(glm::dot(vecteur1, vecteur2)));
					auto alpha = (theta <= 90) ? std::acos(glm::dot(vecteur1, vecteur2)) : (utilitaire::PI - std::acos(glm::dot(vecteur1, vecteur2)));
					angleReflexion_ = utilitaire::RAD_TO_DEG(utilitaire::PI - 2 * alpha);
					if (i == 0 && std::abs(angleReflexion_) < 2.0)
					{
						type_ = AVANT;
					}
					else if ((i == 0 && (calculerDistancePointDroite(glm::dvec2(RB2point1), glm::dvec2(RB2point2), RB1point2) < 2 * calculerDistancePointDroite(glm::dvec2(RB2point1), glm::dvec2(RB2point2), RB1point1))) ||
						(i > 0 && i <= 4))
					{
						type_ = AVANT_DROIT;
					}
					else if ((i >= 5 && i < 8) || (i == 8 && detailCollision_.type != aidecollision::COLLISION_SEGMENT_DEUXIEMEPOINT))
					{
						type_ = ARRIERE_DROIT;
					}
					else if (i == 8 && std::abs(angleReflexion_) < 2.0)
					{
						type_ = ARRIERE;
					}
					else if ((i > 8 && i <= 11) || (i == 8 && detailCollision_.type != aidecollision::COLLISION_SEGMENT_PREMIERPOINT))
					{
						type_ = ARRIERE_GAUCHE;
						angleReflexion_ = -1 * angleReflexion_;
					}
					else
					{
						type_ = AVANT_GAUCHE;
						angleReflexion_ = -1 * angleReflexion_;
					}
					if ((i == 0 || i == 8) && (j <= 2) && (std::abs(utilitaire::RAD_TO_DEG(alpha) >= 50)))
					{
						angleReflexion_ = 0.0;
					}
					objet_ = ROBOT;
				}
			}
		}
	}
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierCollision::visiter(NoeudSegment& noeud)
///
/// Cette methode ne fait rien
/// 
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierCollision::visiter(NoeudSegment& noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurVerifierCollision::visiter(NoeudFleche& noeud)
///
/// Cette methode ne fait rien
/// 
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerifierCollision::visiter(NoeudFleche& noeud)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double calculerDistancePointDroite(glm::dvec2 pointDroite1, glm::dvec2 pointDroite2, glm::dvec2 point)
///
/// Cette methode permet de calculer la distance d'un point à une droite définie par 2 points
/// 
///
/// @param[in] pointDroite1, pointDroite2 : les 2 points définissant la droite
/// @param[in] point : le point pour lequel on veut calculer la distance par rapport à la droite
///
/// @return la distance entre le point et la droite de type double.
///
////////////////////////////////////////////////////////////////////////
double VisiteurVerifierCollision::calculerDistancePointDroite(glm::dvec2 pointDroite1, glm::dvec2 pointDroite2, glm::dvec2 point)
{
	double distance;
	if (!utilitaire::EGAL_ZERO(pointDroite2.x - pointDroite1.x))
	{
		// Eqt de la droite : Y = a X + b
		double a = (pointDroite2.y - pointDroite1.y) / (pointDroite2.x - pointDroite1.x);
		double b = pointDroite1.y - pointDroite1.x * a;
		distance = std::abs(a * point.x - point.y + b) / std::sqrt(pow(a, 2.0) + 1);
	}
	else
	{
		// Eqt de la droite : X = c
		double c = pointDroite1.x;
		distance = std::abs(point.x - c);
	}
	return distance;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////