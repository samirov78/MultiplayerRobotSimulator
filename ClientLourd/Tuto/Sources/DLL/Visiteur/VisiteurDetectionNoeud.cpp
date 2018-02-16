////////////////////////////////////////////////
/// @file   VisiteurDetectionNoeud.cpp
/// @author INF2990 Eq.11
/// @date   2016-03-21
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "VisiteurDetectionNoeud.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionNoeud::visiter(NoeudPoteau& noeud)
///
/// Cette methode permet d'appliquer l'algorithme detection d'un noeud poteau.
/// 
/// @param[in] noeud : le noeud poteau en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionNoeud::visiter(NoeudPoteau& noeud)
{
	if (noeud.estAffiche())
	{
		double rayon = noeud.obtenirRedimensionnementRelative().x;
		glm::dvec2 position = glm::dvec2(noeud.obtenirPositionRelative());

		updatePositionPointCapteurs();

		aidecollision::DetailsCollision detailP1P2DangerDroit;
		aidecollision::DetailsCollision detailP2P3DangerDroit;
		aidecollision::DetailsCollision detailP3P4DangerDroit;
		aidecollision::DetailsCollision detailP2P2SecuritaireDroit;
		aidecollision::DetailsCollision detailP2P3SecuritaireDroit;
		aidecollision::DetailsCollision detailP3P3SecuritaireDroit;
		aidecollision::DetailsCollision detailP1P2DangerMilieu;
		aidecollision::DetailsCollision detailP2P3DangerMilieu;
		aidecollision::DetailsCollision detailP3P4DangerMilieu;
		aidecollision::DetailsCollision detailP2P2SecuritaireMilieu;
		aidecollision::DetailsCollision detailP2P3SecuritaireMilieu;
		aidecollision::DetailsCollision detailP3P3SecuritaireMilieu;
		aidecollision::DetailsCollision detailP1P2DangerGauche;
		aidecollision::DetailsCollision detailP2P3DangerGauche;
		aidecollision::DetailsCollision detailP3P4DangerGauche;
		aidecollision::DetailsCollision detailP2P2SecuritaireGauche;
		aidecollision::DetailsCollision detailP2P3SecuritaireGauche;
		aidecollision::DetailsCollision detailP3P3SecuritaireGauche;

		if (leRobot_->obtenirProfil()->capteurDroitActif_)
		{
			///Detection capteur droit zone danger
			detailP1P2DangerDroit = aidecollision::calculerCollisionSegment(p1CapteurDangerDroit, p2CapteurDangerDroit, position, rayon);
			detailP2P3DangerDroit = aidecollision::calculerCollisionSegment(p2CapteurDangerDroit, p3CapteurDangerDroit, position, rayon);
			detailP3P4DangerDroit = aidecollision::calculerCollisionSegment(p3CapteurDangerDroit, p4CapteurDangerDroit, position, rayon);

			///Detection capteur droit zone securitaire
			detailP2P2SecuritaireDroit = aidecollision::calculerCollisionSegment(p2CapteurDangerDroit, p2CapteurSecuritaireDroit, position, rayon);
			detailP2P3SecuritaireDroit = aidecollision::calculerCollisionSegment(p2CapteurSecuritaireDroit, p3CapteurSecuritaireDroit, position, rayon);
			detailP3P3SecuritaireDroit = aidecollision::calculerCollisionSegment(p3CapteurSecuritaireDroit, p3CapteurDangerDroit, position, rayon);
			///Verification s'il y a collision au niveau de la zone de danger du capteur droit.
			if (detailP1P2DangerDroit.type != aidecollision::COLLISION_AUCUNE || detailP2P3DangerDroit.type != aidecollision::COLLISION_AUCUNE || detailP3P4DangerDroit.type != aidecollision::COLLISION_AUCUNE)
			{
				leRobot_->setDetectionDangerDroit(true);
			}
			///Verification s'il y a collision au niveau de la zone securitaire du capteur droit.
			else if (detailP2P2SecuritaireDroit.type != aidecollision::COLLISION_AUCUNE || detailP2P3SecuritaireDroit.type != aidecollision::COLLISION_AUCUNE || detailP3P3SecuritaireDroit.type != aidecollision::COLLISION_AUCUNE || detailP2P3DangerDroit.type != aidecollision::COLLISION_AUCUNE)
			{
				leRobot_->setDetectionSecuritaireDroit(true);
			}

		}

		if (leRobot_->obtenirProfil()->capteurMilieuActif_)
		{
			///Detection capteur milieu zone danger
			detailP1P2DangerMilieu = aidecollision::calculerCollisionSegment(p1CapteurDangerMilieu, p2CapteurDangerMilieu, position, rayon);
			detailP2P3DangerMilieu = aidecollision::calculerCollisionSegment(p2CapteurDangerMilieu, p3CapteurDangerMilieu, position, rayon);
			detailP3P4DangerMilieu = aidecollision::calculerCollisionSegment(p3CapteurDangerMilieu, p4CapteurDangerMilieu, position, rayon);

			///Detection capteur milieu zone securitaire
			detailP2P2SecuritaireMilieu = aidecollision::calculerCollisionSegment(p2CapteurDangerMilieu, p2CapteurSecuritaireMilieu, position, rayon);
			detailP2P3SecuritaireMilieu = aidecollision::calculerCollisionSegment(p2CapteurSecuritaireMilieu, p3CapteurSecuritaireMilieu, position, rayon);
			detailP3P3SecuritaireMilieu = aidecollision::calculerCollisionSegment(p3CapteurSecuritaireMilieu, p3CapteurDangerMilieu, position, rayon);
			//std::cout << "if etat actif capteur milieu" << std::endl;
			///Verification s'il y a collision au niveau de la zone de danger du capteur milieu.
			if (detailP1P2DangerMilieu.type != aidecollision::COLLISION_AUCUNE || detailP2P3DangerMilieu.type != aidecollision::COLLISION_AUCUNE || detailP3P4DangerMilieu.type != aidecollision::COLLISION_AUCUNE)
			{
				leRobot_->setDetectionDangerMilieu(true);
			}
			///Verification s'il y a collision au niveau de la zone securitaire du capteur milieu.
			else if (detailP2P2SecuritaireMilieu.type != aidecollision::COLLISION_AUCUNE || detailP2P3SecuritaireMilieu.type != aidecollision::COLLISION_AUCUNE || detailP3P3SecuritaireMilieu.type != aidecollision::COLLISION_AUCUNE || detailP2P3DangerMilieu.type != aidecollision::COLLISION_AUCUNE)
			{
				leRobot_->setDetectionSecuritaireMilieu(true);
			}

		}

		if (leRobot_->obtenirProfil()->capteurGaucheActif_)
		{

			///Detection capteur gauche zone danger
			detailP1P2DangerGauche = aidecollision::calculerCollisionSegment(p1CapteurDangerGauche, p2CapteurDangerGauche, position, rayon);
			detailP2P3DangerGauche = aidecollision::calculerCollisionSegment(p2CapteurDangerGauche, p3CapteurDangerGauche, position, rayon);
			detailP3P4DangerGauche = aidecollision::calculerCollisionSegment(p3CapteurDangerGauche, p4CapteurDangerGauche, position, rayon);

			///Detection capteur gauche zone securitaire
			detailP2P2SecuritaireGauche = aidecollision::calculerCollisionSegment(p2CapteurDangerGauche, p2CapteurSecuritaireGauche, position, rayon);
			detailP2P3SecuritaireGauche = aidecollision::calculerCollisionSegment(p2CapteurSecuritaireGauche, p3CapteurSecuritaireGauche, position, rayon);
			detailP3P3SecuritaireGauche = aidecollision::calculerCollisionSegment(p3CapteurSecuritaireGauche, p3CapteurDangerGauche, position, rayon);
			//std::cout << "if etat actif capteur gauche" << std::endl;
			///Verification s'il y a collision au niveau de la zone de danger du capteur gauche.
			if (detailP1P2DangerGauche.type != aidecollision::COLLISION_AUCUNE || detailP2P3DangerGauche.type != aidecollision::COLLISION_AUCUNE || detailP3P4DangerGauche.type != aidecollision::COLLISION_AUCUNE)
			{
				leRobot_->setDetectionDangerGauche(true);
			}

			///Verification s'il y a collision au niveau de la zone securitaire du capteur gauche.
			else if (detailP2P2SecuritaireGauche.type != aidecollision::COLLISION_AUCUNE || detailP2P3SecuritaireGauche.type != aidecollision::COLLISION_AUCUNE || detailP3P3SecuritaireGauche.type != aidecollision::COLLISION_AUCUNE || detailP2P3DangerGauche.type != aidecollision::COLLISION_AUCUNE)
			{
				leRobot_->setDetectionSecuritaireGauche(true);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionNoeud::visiter(NoeudMur& noeud)
///
/// Cette methode permet d'appliquer l'algorithme detection d'un noeud mur.
/// 
/// @param[in] noeud : le noeud mur en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void VisiteurDetectionNoeud::visiter(NoeudMur& noeud)
{
	if (noeud.estAffiche())
	{
		bool etatActifCapteurDroit = leRobot_->obtenirProfil()->capteurDroitActif_;
		bool etatActifCapteurMilieu = leRobot_->obtenirProfil()->capteurMilieuActif_;
		bool etatActifCapteurGauche = leRobot_->obtenirProfil()->capteurGaucheActif_;

		//Donnee du capteur droit.

		updatePositionPointCapteurs();

		//Verification des collisions sur un objet de type mur.
		//Segment zone danger droit.
		math::SegmentDroite2D segP1P2DangerDroit(p1CapteurDangerDroit, p2CapteurDangerDroit);
		math::SegmentDroite2D segP2P3DangerDroit(p2CapteurDangerDroit, p3CapteurDangerDroit);
		math::SegmentDroite2D segP3P4DangerDroit(p3CapteurDangerDroit, p4CapteurDangerDroit);
		//segment zone securitaire droit
		math::SegmentDroite2D segP2P2SecuritaireDroit(p2CapteurSecuritaireDroit, p2CapteurDangerDroit);
		math::SegmentDroite2D segP2P3SecuritaireDroit(p2CapteurSecuritaireDroit, p3CapteurSecuritaireDroit);
		math::SegmentDroite2D segP3P3SecuritaireDroit(p3CapteurSecuritaireDroit, p3CapteurDangerDroit);
		//segment zone danger milieu
		math::SegmentDroite2D segP1P2DangerMilieu(p1CapteurDangerMilieu, p2CapteurDangerMilieu);
		math::SegmentDroite2D segP2P3DangerMilieu(p2CapteurDangerMilieu, p3CapteurDangerMilieu);
		math::SegmentDroite2D segP3P4DangerMilieu(p3CapteurDangerMilieu, p4CapteurDangerMilieu);
		//segment zone securitaire milieu
		math::SegmentDroite2D segP2P2SecuritaireMilieu(p2CapteurSecuritaireMilieu, p2CapteurDangerMilieu);
		math::SegmentDroite2D segP2P3SecuritaireMilieu(p2CapteurSecuritaireMilieu, p3CapteurSecuritaireMilieu);
		math::SegmentDroite2D segP3P3SecuritaireMilieu(p3CapteurSecuritaireMilieu, p3CapteurDangerMilieu);
		//segment zone danger gauche
		math::SegmentDroite2D segP1P2DangerGauche(p1CapteurDangerGauche, p2CapteurDangerGauche);
		math::SegmentDroite2D segP2P3DangerGauche(p2CapteurDangerGauche, p3CapteurDangerGauche);
		math::SegmentDroite2D segP3P4DangerGauche(p3CapteurDangerGauche, p4CapteurDangerGauche);
		//segment zone securitaire gauche
		math::SegmentDroite2D segP2P2SecuritaireGauche(p2CapteurSecuritaireGauche, p2CapteurDangerGauche);
		math::SegmentDroite2D segP2P3SecuritaireGauche(p2CapteurSecuritaireGauche, p3CapteurSecuritaireGauche);
		math::SegmentDroite2D segP3P3SecuritaireGauche(p3CapteurSecuritaireGauche, p3CapteurDangerGauche);

		glm::dvec2 pointDepartMur = glm::dvec2(noeud.getPointDepart());
		glm::dvec2 pointFinMur = glm::dvec2(noeud.getPointFin());
		double rotationMur = noeud.obtenirRotationRelative()[0];
		glm::dvec2 coin1Mur;
		glm::dvec2 coin2Mur;
		glm::dvec2 coin3Mur;
		glm::dvec2 coin4Mur;
		//std::cout << rotationMur << std::endl;
		calculerCoinMur(pointDepartMur, pointFinMur, coin1Mur, coin2Mur, coin3Mur, coin4Mur, rotationMur);
		/*std::cout << "pointDepartMur x :" << pointDepartMur.x << "\t y: " << pointDepartMur.y << std::endl;
		std::cout << "pointFinMur x :" << pointFinMur.x << "\t y: " << pointFinMur.y << std::endl;*/
		//std::cout << "pointDepartMur x :" << pointDepartMur.x << "\t y: " << pointDepartMur.y << std::endl;
		if (leRobot_->obtenirProfil()->capteurDroitActif_)
		{
			///Verification s'il y a collision au niveau de la zone de danger du capteur droit.
			if (segP1P2DangerDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP1P2DangerDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP1P2DangerDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP1P2DangerDroit.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP2P3DangerDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P3DangerDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P3DangerDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P3DangerDroit.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP3P4DangerDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP3P4DangerDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP3P4DangerDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP3P4DangerDroit.intersectionAvecSegment(coin4Mur, coin1Mur))
			{
				leRobot_->setDetectionDangerDroit(true);
			}
			///Verification s'il y a collision au niveau de la zone securitaire du capteur droit
			else if (segP2P2SecuritaireDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P2SecuritaireDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P2SecuritaireDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P2SecuritaireDroit.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP2P3SecuritaireDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P3SecuritaireDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P3SecuritaireDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P3SecuritaireDroit.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP3P3SecuritaireDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP3P3SecuritaireDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP3P3SecuritaireDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP3P3SecuritaireDroit.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP2P3DangerDroit.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P3DangerDroit.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P3DangerDroit.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P3DangerDroit.intersectionAvecSegment(coin4Mur, coin1Mur))
			{
				leRobot_->setDetectionSecuritaireDroit(true);
			}
		}
		if (leRobot_->obtenirProfil()->capteurMilieuActif_)
		{
			///Detection capteur milieu zone danger
			if (segP1P2DangerMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP1P2DangerMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP1P2DangerMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP1P2DangerMilieu.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP2P3DangerMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P3DangerMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P3DangerMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P3DangerMilieu.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP3P4DangerMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP3P4DangerMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP3P4DangerMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP3P4DangerMilieu.intersectionAvecSegment(coin4Mur, coin1Mur))
			{
				leRobot_->setDetectionDangerMilieu(true);

			}
			///Verification s'il y a collision au niveau de la zone securitaire du capteur milieu.
			else if (segP2P2SecuritaireMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P2SecuritaireMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P2SecuritaireMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P2SecuritaireMilieu.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP2P3SecuritaireMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P3SecuritaireMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P3SecuritaireMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P3SecuritaireMilieu.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP2P3DangerMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P3DangerMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P3DangerMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P3DangerMilieu.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP3P3SecuritaireMilieu.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP3P3SecuritaireMilieu.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP3P3SecuritaireMilieu.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP3P3SecuritaireMilieu.intersectionAvecSegment(coin4Mur, coin1Mur))
			{
				leRobot_->setDetectionSecuritaireMilieu(true);
			}
		}

		if (leRobot_->obtenirProfil()->capteurGaucheActif_)
		{
			///Detection capteur gauche zone danger
			if (segP1P2DangerGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP1P2DangerGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP1P2DangerGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP1P2DangerGauche.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP2P3DangerGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P3DangerGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P3DangerGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P3DangerGauche.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP3P4DangerGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP3P4DangerGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP3P4DangerGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP3P4DangerGauche.intersectionAvecSegment(coin4Mur, coin1Mur))
			{
				leRobot_->setDetectionDangerGauche(true);
			}
			///Verification s'il y a collision au niveau de la zone securitaire du capteur gauche.
			else if (segP2P2SecuritaireGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P2SecuritaireGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P2SecuritaireGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P2SecuritaireGauche.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP2P3SecuritaireGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P3SecuritaireGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P3SecuritaireGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P3SecuritaireGauche.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP2P3DangerGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP2P3DangerGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP2P3DangerGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP2P3DangerGauche.intersectionAvecSegment(coin4Mur, coin1Mur) ||

				segP3P3SecuritaireGauche.intersectionAvecSegment(coin1Mur, coin2Mur) ||
				segP3P3SecuritaireGauche.intersectionAvecSegment(coin2Mur, coin3Mur) ||
				segP3P3SecuritaireGauche.intersectionAvecSegment(coin3Mur, coin4Mur) ||
				segP3P3SecuritaireGauche.intersectionAvecSegment(coin4Mur, coin1Mur))
			{
				leRobot_->setDetectionSecuritaireGauche(true);
			}
		}
	}
}
void VisiteurDetectionNoeud::visiter(NoeudFleche& noeud)
{

}
void VisiteurDetectionNoeud::visiter(NoeudSegment& noeud)
{

}
void VisiteurDetectionNoeud::visiter(NoeudLigne& noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionNoeud::calculerCoinMur(glm::dvec2 pointInitial, glm::dvec2 pointFinal, glm::dvec2& p1, glm::dvec2& p2, glm::dvec2& p3, glm::dvec2& p4, const double& theta)
///
/// Cette methode permet de calculer les coins d'un noeud mur.
/// 
/// @param[in] pointInitial : La position de clic initial lors de l'ajout d'un noeud mur.
///
/// @param[in] pointFinal : La position de clic final lors du depot d'un noeud mur.
///
/// @param[in, out] p1 : L'equivalent du point inferieur droit d'un rectangle.
///
/// @param[in, out] p2 : L'equivalent du point superieur droit d'un rectangle.
///
/// @param[in, out] p3 : L'equivalent du point superieur gauche d'un rectangle.
///
/// @param[in, out] p4 : L'equivalent du point inferieur gauche d'un rectangle.
///
/// @param[in] theta : L'angle de rotation relatif du mur par rapport a la table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void VisiteurDetectionNoeud::calculerCoinMur(glm::dvec2 pointInitial, glm::dvec2 pointFinal, glm::dvec2& p1, glm::dvec2& p2, glm::dvec2& p3, glm::dvec2& p4, const double& theta)
{
	double largeurMur = 0.25;
	p1.x = pointInitial.x + (largeurMur / 2.0) * cos(utilitaire::DEG_TO_RAD(90.0 - theta));
	p1.y = pointInitial.y - (largeurMur / 2.0) * sin(utilitaire::DEG_TO_RAD(90.0 - theta));

	p2.x = pointFinal.x + (largeurMur / 2.0) * cos(utilitaire::DEG_TO_RAD(90.0 - theta));
	p2.y = pointFinal.y - (largeurMur / 2.0) * sin(utilitaire::DEG_TO_RAD(90.0 - theta));

	p3.x = pointFinal.x - (largeurMur / 2.0) * cos(utilitaire::DEG_TO_RAD(90.0 - theta));
	p3.y = pointFinal.y + (largeurMur / 2.0) * sin(utilitaire::DEG_TO_RAD(90.0 - theta));

	p4.x = pointInitial.x - (largeurMur / 2.0) * cos(utilitaire::DEG_TO_RAD(90.0 - theta));
	p4.y = pointInitial.y + (largeurMur / 2.0) * sin(utilitaire::DEG_TO_RAD(90.0 - theta));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionNoeud::calculerCoinMur(glm::dvec2 pointInitial, glm::dvec2 pointFinal, glm::dvec2& p1, glm::dvec2& p2, glm::dvec2& p3, glm::dvec2& p4, const double& theta)
///
/// Cette methode permet de mettre a jour les differents attributs representant
/// les points des capteurs de distance.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDetectionNoeud::updatePositionPointCapteurs()
{
	p1CapteurDangerDroit = leRobot_->obtenirP1CapteurDangerDroit();
	p2CapteurDangerDroit = leRobot_->obtenirP2CapteurDangerDroit();
	p3CapteurDangerDroit = leRobot_->obtenirP3CapteurDangerDroit();
	p4CapteurDangerDroit = leRobot_->obtenirP4CapteurDangerDroit();
	p2CapteurSecuritaireDroit = leRobot_->obtenirP2CapteurSecuritaireDroit();
	p3CapteurSecuritaireDroit = leRobot_->obtenirP3CapteurSecuritaireDroit();

	//Donnee du capteur milieu
	p1CapteurDangerMilieu = leRobot_->obtenirP1CapteurDangerMilieu();
	p2CapteurDangerMilieu = leRobot_->obtenirP2CapteurDangerMilieu();
	p3CapteurDangerMilieu = leRobot_->obtenirP3CapteurDangerMilieu();
	p4CapteurDangerMilieu = leRobot_->obtenirP4CapteurDangerMilieu();
	p2CapteurSecuritaireMilieu = leRobot_->obtenirP2CapteurSecuritaireMilieu();
	p3CapteurSecuritaireMilieu = leRobot_->obtenirP3CapteurSecuritaireMilieu();

	//Donnee du capteur gauche
	p1CapteurDangerGauche = leRobot_->obtenirP1CapteurDangerGauche();
	p2CapteurDangerGauche = leRobot_->obtenirP2CapteurDangerGauche();
	p3CapteurDangerGauche = leRobot_->obtenirP3CapteurDangerGauche();
	p4CapteurDangerGauche = leRobot_->obtenirP4CapteurDangerGauche();
	p2CapteurSecuritaireGauche = leRobot_->obtenirP2CapteurSecuritaireGauche();
	p3CapteurSecuritaireGauche = leRobot_->obtenirP3CapteurSecuritaireGauche();
}