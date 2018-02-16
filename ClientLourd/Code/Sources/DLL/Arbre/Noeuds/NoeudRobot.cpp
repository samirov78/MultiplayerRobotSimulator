///////////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.cpp
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "NoeudRobot.h"
#include "NoeudRoue.h"
#include "Utilitaire.h"
#include "VisiteurDetectionNoeud.h"
#include "VisiteurVerifierCollision.h"
#include "FacadeModele.h"
#include <time.h>
#include <string>

#include "GL/glew.h"
#include <cmath>
#include <iostream>
#include "Modele3D.h"
#include "OpenGL_VBO.h"


#include "VueOrtho.h"
#include "../../Commun/Utilitaire/Vue/VueOrbite.h"
#include "Camera.h"
#include "Projection.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot::NoeudRobot(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRobot::NoeudRobot(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	
	DerniereDetection_ = time(0);
	derniereIntersection_ = time(0);
	attenteAvantChanger_ = time(0);
	TempsInitial_ = std::chrono::system_clock::now();
	profil_ = new Profil();
	
	debug_ = new Debug();

	lumiereAmbianteActivee_ = true;
	lumiereDirectionnelleActivee_ = true;
	spotsActives_ = true;

	//std::cout << "Constructeur_Robot" << std::endl;

	vuePremierePersonneRobot_ = new vue::VueOrbite
	{
		vue::Camera{
			//				z
			//				|  
			//				| 
			//				|------x
			//				 \
						//			      \
						//			       -y
			glm::dvec3(positionRelative_.x, positionRelative_.y, 200), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0), glm::dvec3(0, 0, 1), false },
			vue::ProjectionPerspective{
				0, 1000, 0, 1000,
				1, 1000, 1, 10000, 1.25,
				-100, 100, -100, 100 }, true
	};
}


// accepter visiteur Robot:
void NoeudRobot::accepterVisiteur(VisiteurAbstrait* visiteur) {
	visiteur->visiter(*this);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot::~NoeudRobot()
///
/// Destructeur du NoeudRobot.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRobot::~NoeudRobot()
{
	if (profil_ != nullptr)
		delete profil_;
	if (debug_ != nullptr)
		delete debug_;
	if (vuePremierePersonneRobot_ != nullptr)
		delete vuePremierePersonneRobot_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherConcret(const bool& attribuerCouleur) const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(attribuerCouleur);

	// Sauvegarde de la matrice.
	glPushMatrix();

	GLubyte couleur[3] = { 0, 0, 0 };
	// Affichage du modèle.
	vbo_->dessiner(estSelectionne(), false, couleur, couleur);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	afficherCapteursDistances();
	//glDisable(GL_BLEND);
	// Restauration de la matrice.
	glPopMatrix();

	vuePremierePersonneRobot_->obtenirCamera().assignerPosition(positionCamera_);
	vuePremierePersonneRobot_->obtenirCamera().assignerPointVise(pointViseCamera_);
	vuePremierePersonneRobot_->obtenirCamera().assignerDirectionHaut(glm::dvec3(0.0, 0.0, 1.0));
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::obtenirSenseurDeLigneExtremeGauche() const
///
/// Cette fonction retourne le senseur de ligne à l'extrême gauche
///
///
///@param[in] Aucun
/// @return glm::dvec3.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 NoeudRobot::obtenirSenseurDeLigneExtremeGauche() const{
	return senseurDeLigneExtremeGauche_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn glm::dvec3 NoeudRobot::obtenirSenseurDeLigneGauche()const
///
/// Cette fonction retourne le senseur de ligne gauche(pas extreme gauche)
///
///
///@param[in] Aucun
/// @return glm::dvec3.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 NoeudRobot::obtenirSenseurDeLigneGauche()const{
	return senseurDeLigneGauche_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::obtenirSenseurDeLigneCentral() const
///
/// Cette fonction retourne le senseur de ligne central
///
///
///@param[in] Aucun
/// @return glm::dvec3.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 NoeudRobot::obtenirSenseurDeLigneCentral() const{
	return senseurDeLigneCentral_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn glm::dvec3 NoeudRobot:: obtenirSenseursDeLigneDroite()const
///
/// Cette fonction retourne le senseur de ligne droite(pas extreme droite)
///
///
///@param[in] Aucun
/// @return glm::dvec3.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 NoeudRobot:: obtenirSenseursDeLigneDroite()const{
	return senseursDeLigneDroite_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::obtenirSenseurDeLigneExtremeDroite() const
///
/// Cette fonction retourne le senseur de ligne extrême droite
///
///
///@param[in] Aucun
/// @return glm::dvec3.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 NoeudRobot::obtenirSenseurDeLigneExtremeDroite() const{
	return senseurDeLigneExtremeDroite_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::actionnerMoteurs(const double& rapportVitesseGauche, const double& rapportVitesseDroit, const Direction& direction)
///
/// Cette fonction permet d'actionner les moteurs des deux roues du robot en mode «FORWARD» ou «REVERSE» dépendemment 
/// de la valeur du paramètre direction en assignant des rapports de vitesses aux deux roues droite et gauche 
///
/// @param[in] rapportVitesseGauche : Le rapport de vitesse de la roue gauche entre 0 et 1, 
/// @param[in] rapportVitesseDroit : Le rapport de vitesse de la roue Droite entre 0 et 1,
/// @param[in] direction : La direction de rotation des roues du robot prend les valeurs «FORWARD» (sens direct) ou «REVERSE» (sens inverse).
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::actionnerMoteurs(const double& rapportVitesseGauche, const double& rapportVitesseDroit, const Direction& direction)
{
	roueDroite_->rapportVitesseReel_ = std::min(1.0, std::max(0.0, rapportVitesseDroit));
	roueGauche_->rapportVitesseReel_ = std::min(1.0, std::max(0.0, rapportVitesseGauche));
	deltaRapportVitesse_ = roueDroite_->rapportVitesseReel_ - roueGauche_->rapportVitesseReel_;
	Direction directionInverse = (direction == FORWARD) ? REVERSE : FORWARD;
	
	if (utilitaire::EGAL_ZERO(deltaRapportVitesse_))
	{
		roueDroite_->setDirection(direction);
		roueGauche_->setDirection(direction);
		roueDroite_->setRapportVitesse(roueDroite_->rapportVitesseReel_);
		roueGauche_->setRapportVitesse(roueGauche_->rapportVitesseReel_);
	}
	else if (utilitaire::EGAL_ZERO(roueDroite_->rapportVitesseReel_))
	{
		roueDroite_->setDirection(directionInverse);
		roueGauche_->setDirection(direction);
		roueDroite_->setRapportVitesse(roueGauche_->rapportVitesseReel_);
		roueGauche_->setRapportVitesse(roueGauche_->rapportVitesseReel_);
	}
	else if (utilitaire::EGAL_ZERO(roueGauche_->rapportVitesseReel_))
	{
		roueDroite_->setDirection(direction);
		roueGauche_->setDirection(directionInverse);
		roueDroite_->setRapportVitesse(roueDroite_->rapportVitesseReel_);
		roueGauche_->setRapportVitesse(roueDroite_->rapportVitesseReel_);
	}
	else
	{
		roueDroite_->setDirection(direction);
		roueGauche_->setDirection(direction);
		roueDroite_->setRapportVitesse(roueDroite_->rapportVitesseReel_);
		roueGauche_->setRapportVitesse(roueGauche_->rapportVitesseReel_);
	}	
	
	roueDroite_->setIncrAcceleration(1.0);
	roueGauche_->setIncrAcceleration(1.0);

	if (modeAutomatique_)
	{
		roueDroite_->setIncrAcceleration(100.0);
		roueGauche_->setIncrAcceleration(100.0);
	}
	else
	{
		if (roueDroite_->oldDirection_ != roueDroite_->getDirection())
		{
			roueDroite_->setVitesse(0.0);
			roueDroite_->setAcceleration(0.0);
		}
		if (roueGauche_->oldDirection_ != roueGauche_->getDirection())
		{
			roueGauche_->setVitesse(0.0);
			roueGauche_->setAcceleration(0.0);
		}
	}
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::stopperMoteurs()
///
/// Cette fonction permet d'arrêter les moteurs des deux roues du robot
///
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::arreterMoteurs()
{
	getRoueDroite()->setRapportVitesse(0.0);
	getRoueGauche()->setRapportVitesse(0.0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAjourParametres(float dt)
///
/// Cette fonction permet de mettre a jours les differents parametres du robot en fonction d'un temps dt.
///
/// @param[in] dt: Une certain variation du temps dt.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAjourParametres(float dt)
{
	double angleReference = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->obtenirRotationRelative()[0] - 90;
	angleCorrection_ = obtenirRotationRelative().x - angleReference;

	if (activerRebond_)
	{
		if (decompteurDeblocage_-- <= 0)
		{
			switch (dernierDeplacement_)
			{
				case AVANCER					: reculer(3 * dt); break;
				case RECULER					: avancer(3 * dt); break;
				case AVANCER_ANGLE_REFLEXION	: reculer(3 * dt); break;
				case RECULER_ANGLE_REFLEXION	: avancer(3 * dt); break;
				default							: break;
			}
			((VisiteurVerifierCollision*)visiteurVerifierCollision_)->type_ = AUCUNE;
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurVerifierCollision_);
			if (((VisiteurVerifierCollision*)visiteurVerifierCollision_)->type_ != AUCUNE)
			{
				activerRebond_ = false;
				decompteurDeblocage_ = DECOMPT_DEBLOCAGE_MAX;
				// Samir
				switch (((VisiteurVerifierCollision*)visiteurVerifierCollision_)->objet_)
				{
					
				case POTEAU:
					jouerSon(1); break;
				case MUR_VISIBLE:
					jouerSon(2) ; break;
				case MUR_INVISIBLE:
					jouerSon(3); break;
				case ROBOT:
					jouerSon(2); break;
				default: break;
				}
			}
		}
	}
	if (!activerRebond_)
	{
		if (!utilitaire::EGAL_ZERO(deltaRapportVitesse_) && utilitaire::EGAL_ZERO(roueGauche_->rapportVitesseReel_))
		{
			incrAngleRotation_ = (RAYON_ROUE / LONG_ESSIEU) * roueDroite_->getAngleRotation();
		}
		else if (!utilitaire::EGAL_ZERO(deltaRapportVitesse_) && utilitaire::EGAL_ZERO(roueDroite_->rapportVitesseReel_))
		{
			incrAngleRotation_ = -(RAYON_ROUE / LONG_ESSIEU) * roueGauche_->getAngleRotation();
		}
		else
		{
			incrAngleRotation_ = (RAYON_ROUE / LONG_ESSIEU) * (roueDroite_->getAngleRotation() - roueGauche_->getAngleRotation());
		}
		if (deltaRapportVitesse_ == 0.9)
		{
			rayonRotation_ = 5.0;
			coefCorrecRayon_ = 0.4 * incrAngleRotation_;
		}
		else if (deltaRapportVitesse_ == -0.9)
		{
			rayonRotation_ = -5.0;
			coefCorrecRayon_ = -0.4 * incrAngleRotation_;
		}
		else if (deltaRapportVitesse_ < 0.0)
		{
			rayonRotation_ = std::max(-100.0, LONG_ESSIEU / (2 * deltaRapportVitesse_));
			coefCorrecRayon_ = -0.9 * incrAngleRotation_;
		}
		else if (deltaRapportVitesse_ > 0.0)
		{
			rayonRotation_ = std::min(100.0, LONG_ESSIEU / (2 * deltaRapportVitesse_));
			coefCorrecRayon_ = 0.9 * incrAngleRotation_;
		}
		angleRotation_ = angleCorrection_ + incrAngleRotation_;
		double angleRotationMax = std::max(roueDroite_->getAngleRotation(), roueGauche_->getAngleRotation());
		forceMoteurs_ = RAYON_ROUE * angleRotationMax * 0.7;
		decompteurDeblocage_ = DECOMPT_DEBLOCAGE_MAX;
	}

	((VisiteurVerifierCollision*)visiteurVerifierCollision_)->type_ = AUCUNE;
	((VisiteurVerifierCollision*)visiteurVerifierCollision_)->objet_ = AUCUN;
	((VisiteurVerifierCollision*)visiteurVerifierCollision_)->angleReflexion_ = 0.0;

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurVerifierCollision_);
	if (((VisiteurVerifierCollision*)visiteurVerifierCollision_)->type_ != AUCUNE)
	{
		activerRebond_ = true;
		coefficientFriction_ = COEFF_FRICTION;
		typeCollision_ = ((VisiteurVerifierCollision*)visiteurVerifierCollision_)->type_;
		objetCollision_ = ((VisiteurVerifierCollision*)visiteurVerifierCollision_)->objet_;
		angleReflexion_ = ((VisiteurVerifierCollision*)visiteurVerifierCollision_)->angleReflexion_;
		// Samir
		switch (objetCollision_)
		{
			case POTEAU : 
				jouerSon(1); break;
			case MUR_VISIBLE: 
				jouerSon(2); break;
			case MUR_INVISIBLE	: 
				jouerSon(3); break;
			default	: break;
		}
	}

	if (activerRebond_ && (coefficientFriction_-- <= 0))
	{
		activerRebond_ = false;
		typeCollision_ = AUCUNE;
		objetCollision_ = AUCUN;
		angleReflexion_ = 0.0;
	}

	estDetecteDangerDroit_ = false;
	estDetecteDangerMilieu_ = false;
	estDetecteDangerGauche_ = false;
	estDetecteSecuritaireDroit_ = false;
	estDetecteSecuritaireMilieu_ = false;
	estDetecteSecuritaireGauche_ = false;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(FacadeModele::obtenirInstance()->visiteurDetectionNoeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::seDeplacer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudRobot::seDeplacer(float dt)
{
	if (activerRebond_)
	{
		if ((typeCollision_ == AVANT_GAUCHE) || (typeCollision_ == AVANT) || (typeCollision_ == AVANT_DROIT))
		{
			if (utilitaire::EGAL_ZERO(angleReflexion_))
			{
				reculer(dt);
				dernierDeplacement_ = RECULER;
			}
			else
			{
				angleCorrection_ += angleReflexion_;
				avancer(dt);
				dernierDeplacement_ = AVANCER_ANGLE_REFLEXION;
			}
		}
		else
		{
			if (utilitaire::EGAL_ZERO(angleReflexion_))
			{
				avancer(dt);
				dernierDeplacement_ = AVANCER;
			}
			else
			{
				angleCorrection_ -= angleReflexion_;
				reculer(dt);
				dernierDeplacement_ = RECULER_ANGLE_REFLEXION;
			}
		}
	}
	else if (utilitaire::EGAL_ZERO(deltaRapportVitesse_))
	{
		if (roueDroite_->getDirection() == FORWARD)
		{
			avancer(dt);
		}
		else
		{
			reculer(dt);
		}
	}
	else if (deltaRapportVitesse_ > 0.0)			
	{
		if (roueDroite_->getDirection() == FORWARD)
		{
			if (!utilitaire::EGAL_ZERO(roueGauche_->rapportVitesseReel_))
			{
				virerAvG(dt);						// Virer avant gauche
			}
			rotationRelative_.x += incrAngleRotation_;
		}
		else
		{
			if (!utilitaire::EGAL_ZERO(roueGauche_->rapportVitesseReel_))
			{
				virerArG(dt);						// Virer arrière gauche
			}
			rotationRelative_.x -= incrAngleRotation_;
		}				
	}
	else
	{
		if (roueGauche_->getDirection() == FORWARD)
		{
			if (!utilitaire::EGAL_ZERO(roueDroite_->rapportVitesseReel_))
			{
				virerAvD(dt);						// Virer avant droite
			}
			rotationRelative_.x += incrAngleRotation_;
		}
		else
		{
			if (!utilitaire::EGAL_ZERO(roueDroite_->rapportVitesseReel_))
			{
				virerArD(dt);						// Virer arrière droite
			}
			rotationRelative_.x -= incrAngleRotation_;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudRobot::animer(float dt)
{
	if (compteurTemps_ < 2)
		compteurTemps_++;
	else
	{
		FacadeModele::obtenirInstance()->mtx.lock();
		mettreAJourSenseurs();
	    
		if (difftime(time(0), attenteAvantChanger_) > 0.1)
		{
			attente_ = false;
		}
		if (modeAutomatique_)
		{
			if (mettreAjourDetectionsenseurs() && doitSuivre_ && !attente_ && getProfil()->getSuiveurActif())
			{
				if (comportementCourant_ != nullptr)
				{
					ComportementAbstrait * ptr = comportementCourant_;
					definirComportement(new SuiviDeLigne(this));
					if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getChangementComportement() && flipFlopSuiviLigne_)
					{
						std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Fin de " 
							<< FacadeModele::obtenirInstance()->etatToString(etatExecuter_) << " - " 
							<< FacadeModele::obtenirInstance()->etatToString(SUIVI_LIGNE) << std::endl;
						setEtat(SUIVI_LIGNE);
						flipFlopSuiviLigne_ = false;
					}
					delete ptr;
				}
			}
			changerComportementsObstacles();
			comportementCourant_->executerComportement();
		}

		for (NoeudAbstrait * enfant : enfants_){
			enfant->animer(dt);
		}
		mettreAjourParametres(dt);
		mettreAjourSon();
		appliquerSonMoteurs();
		seDeplacer(dt);
		mettreAjourBteEnglobante();
		FacadeModele::obtenirInstance()->mtx.unlock();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::avancer(float dt)
///
/// Cette fonction permet de faire avancer le robot en fonction du temps.
///
/// @param[in] dt: Une certaine variation du temps dt.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::avancer(float dt)
{
	positionRelative_.x -= forceMoteurs_ * dt * std::cos(utilitaire::DEG_TO_RAD(angleCorrection_));
	positionRelative_.y -= forceMoteurs_ * dt * std::sin(utilitaire::DEG_TO_RAD(angleCorrection_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::reculer(float dt)
///
/// Cette fonction permet de faire reculer le robot en fonction du temps.
///
/// @param[in] dt: Une certaine variation du temps dt.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::reculer(float dt)
{
	positionRelative_.x += forceMoteurs_ * dt * std::cos(utilitaire::DEG_TO_RAD(angleCorrection_));
	positionRelative_.y += forceMoteurs_ * dt * std::sin(utilitaire::DEG_TO_RAD(angleCorrection_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::virerAvG(float dt)
///
/// Cette fonction permet de faire avancer tout en tournant a gauche
///	le robot en fonction du temps.
///
/// @param[in] dt: Une certaine variation du temps dt.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::virerAvG(float dt)
{
	positionRelative_.x -= coefCorrecRayon_ * rayonRotation_ * dt * std::cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y -= coefCorrecRayon_ * rayonRotation_ * dt * std::sin(utilitaire::DEG_TO_RAD(angleRotation_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::virerAvD(float dt)
///
/// Cette fonction permet de faire avancer tout en tournant a droite
///	le robot en fonction du temps.
///
/// @param[in] dt: Une certaine variation du temps dt.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::virerAvD(float dt)
{
	positionRelative_.x += coefCorrecRayon_ * rayonRotation_ * dt * std::cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y += coefCorrecRayon_ * rayonRotation_ * dt * std::sin(utilitaire::DEG_TO_RAD(angleRotation_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::virerArG(float dt)
///
/// Cette fonction permet de faire reculer tout en tournant a gauche
///	le robot en fonction du temps.
///
/// @param[in] dt: Une certaine variation du temps dt.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::virerArG(float dt)
{
	positionRelative_.x += coefCorrecRayon_ * rayonRotation_ * dt * std::cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y += coefCorrecRayon_ * rayonRotation_ * dt * std::sin(utilitaire::DEG_TO_RAD(angleRotation_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::virerArD(float dt)
///
/// Cette fonction permet de faire reculer tout en tournant a droite
///	le robot en fonction du temps.
///
/// @param[in] dt: Une certaine variation du temps dt.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::virerArD(float dt)
{
	positionRelative_.x -= coefCorrecRayon_ * rayonRotation_ * dt  * std::cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y -= coefCorrecRayon_ * rayonRotation_ * dt  * std::sin(utilitaire::DEG_TO_RAD(angleRotation_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherCapteursDistances() const
///
/// Cette fonction effectue l'affichage des capteurs de distance du robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherCapteursDistances() const
{
	if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && (debug_->getSortieAlterationEffetsVisuel() && debug_->getAfficherDetectionCapteurs()))
	{
		if (profil_->capteurDroitActif_)
		{
			///Affichage de la zone de danger.
			//Je choisi une largeur de 3.0
			glPushMatrix();
			glTranslated(-4.0, -9.9, 0.0); //tatonnement
			glRotated(23.0, 0.0, 0.0, 1.0); //tatonnement
			glBegin(GL_QUADS);
			//point parcouru en sens anti horraire
			glColor4d(0.933, 0.933, 0.0, 0.8);
			//point danger
			glVertex3d(0.0, 0.0, 5.2); //p1 (min)
			glVertex3d(-profil_->longueurDangerCapteurDroit_, 0.0, 5.2); //p2 (max)
			glVertex3d(-profil_->longueurDangerCapteurDroit_, -3.0, 5.2); //p3 (max)
			glVertex3d(0.0, -3.0, 5.2); //p4 (min)
			//point securitaire
			glColor4d(0.0, 1.0, 0.0, 0.8);
			glVertex3d(-profil_->longueurDangerCapteurDroit_, 0.0, 5.2); //p1 (min)
			glVertex3d(-profil_->longueurDangerCapteurDroit_ - profil_->longueurSecuritaireCapteurDroit_, 0.0, 5.2); //p2 (max)
			glVertex3d(-profil_->longueurDangerCapteurDroit_ - profil_->longueurSecuritaireCapteurDroit_, -3.0, 5.2); //p3 (max)
			glVertex3d(-profil_->longueurDangerCapteurDroit_, -3.0, 5.2); //p4 (min)
			glEnd();

			/*
			//test affichage des axes du capteurs droit.
			glColor3d(0.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex3d(0.0, 0.0, 0.0);
			glVertex3d(20.0, 0.0, 0.0);
			glVertex3d(0.0, 0.0, 0.0);
			glVertex3d(0.0, 10.0, 0.0);
			glEnd();*/
			glPopMatrix();
		}

		if (profil_->capteurMilieuActif_)
		{
			///Affichage de la zone de danger.
			//Je choisi une largeur de 3
			glPushMatrix();
			glTranslated(-1.5, -15.5, 0.0); //tatonnement
			glBegin(GL_QUADS);
			//point parcouru en sens anti horraire
			glColor4d(0.933, 0.933, 0.0, 0.8);
			glVertex3d(0.0, 0.0, 5.2); //p1 (min)
			glVertex3d(0.0, -profil_->longueurDangerCapteurMilieu_, 5.2); //p2 (max)
			glVertex3d(3.0, -profil_->longueurDangerCapteurMilieu_, 5.2);  //p3 (max)
			glVertex3d(3.0, 0.0, 5.2); //p4 (min)
			glColor4d(0.0, 1.0, 0.0, 0.8);
			glVertex3d(0.0, -profil_->longueurDangerCapteurMilieu_, 5.2); //p1 (min)
			glVertex3d(0.0, -profil_->longueurDangerCapteurMilieu_ - profil_->longueurSecuritaireCapteurMilieu_, 5.2); //p2 (max)
			glVertex3d(3.0, -profil_->longueurDangerCapteurMilieu_ - profil_->longueurSecuritaireCapteurMilieu_, 5.2);  //p3 (max)
			glVertex3d(3.0, -profil_->longueurDangerCapteurMilieu_, 5.2); //p4 (min)
			glEnd();
			/*
			//test affichage des axes du capteurs milieu.
			glColor3d(0.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex3d(0.0, 0.0, 0.0);
			glVertex3d(20.0, 0.0, 0.0);
			glVertex3d(0.0, 0.0, 0.0);
			glVertex3d(0.0, -10.0, 0.0);
			glEnd();*/
			glPopMatrix();

		}

		if (profil_->capteurGaucheActif_)
		{
			///Affichage de la zone de danger.
			glPushMatrix();
			glTranslated(3.0, -12.5, 0.0); //tatonnement
			glRotated(-23.0, 0.0, 0.0, 1.0); //tatonnement
			glBegin(GL_QUADS);
			//point parcouru en sens anti horraire
			glColor4d(0.933, 0.933, 0.0, 0.8); //jaune
			glVertex3d(0.0, 0.0, 5.2); //p1 (min)
			glVertex3d(profil_->longueurDangerCapteurGauche_, 0.0, 5.2); //p2 (max)
			glVertex3d(profil_->longueurDangerCapteurGauche_, 3.0, 5.2); //p3 (max)
			glVertex3d(0.0, 3.0, 5.2); //p4 (min)
			///Affichage de la zone securitaire
			glColor4d(0.0, 1.0, 0.0, 0.8); //vert
			glVertex3d(profil_->longueurDangerCapteurGauche_, 0.0, 5.2); //p1 (min)
			glVertex3d(profil_->longueurDangerCapteurGauche_ + profil_->longueurSecuritaireCapteurGauche_, 0.0, 5.2); //p2 (max)
			glVertex3d(profil_->longueurDangerCapteurGauche_ + profil_->longueurSecuritaireCapteurGauche_, 3.0, 5.2); //p3 (max)
			glVertex3d(profil_->longueurDangerCapteurGauche_, 3.0, 5.2); //p4 (min)
			glEnd();

			/*
			//test affichage des axes du capteurs milieu.
			glColor3d(0.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex3d(0.0, 0.0, 0.0);
			glVertex3d(20.0, 0.0, 0.0);
			glVertex3d(0.0, 0.0, 0.0);
			glVertex3d(0.0, 10.0, 0.0);
			glEnd();*/
			glPopMatrix();
		}
	}
	mettreAJourPointsCapteurs();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourPointsCapteurs() const
///
/// Cette fonction effectue la mise a jours des points des capteurs de
/// distance a chaque reaffichage de la scene.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAJourPointsCapteurs() const
{
	glm::dvec3  pos = obtenirPositionRelative();
	glm::dvec4 rotationRobot = obtenirRotationRelative();

	p1CapteurDangerDroit_ = coordonneesParRapportAOrigine(glm::dvec2(0.0 * SCALE_ROBOT, 0.0 * SCALE_ROBOT), glm::dvec2(-4.0 * SCALE_ROBOT, -9.9 * SCALE_ROBOT), 23.0);
	p1CapteurDangerDroit_ = coordonneesParRapportAOrigine(p1CapteurDangerDroit_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p2CapteurDangerDroit_ = coordonneesParRapportAOrigine(glm::dvec2(-profil_->longueurDangerCapteurDroit_ * SCALE_ROBOT, 0.0 * SCALE_ROBOT), glm::dvec2(-4.0 * SCALE_ROBOT, -9.9 * SCALE_ROBOT), 23.0);
	p2CapteurDangerDroit_ = coordonneesParRapportAOrigine(p2CapteurDangerDroit_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p3CapteurDangerDroit_ = coordonneesParRapportAOrigine(glm::dvec2(-profil_->longueurDangerCapteurDroit_ * SCALE_ROBOT, -3.0 * SCALE_ROBOT), glm::dvec2(-4.0 * SCALE_ROBOT, -9.9 * SCALE_ROBOT), 23.0);
	p3CapteurDangerDroit_ = coordonneesParRapportAOrigine(p3CapteurDangerDroit_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p4CapteurDangerDroit_ = coordonneesParRapportAOrigine(glm::dvec2(0.0 * SCALE_ROBOT, -3.0 * SCALE_ROBOT), glm::dvec2(-4.0 * SCALE_ROBOT, -9.9 * SCALE_ROBOT), 23.0);
	p4CapteurDangerDroit_ = coordonneesParRapportAOrigine(p4CapteurDangerDroit_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p2CapteurSecuritaireDroit_ = coordonneesParRapportAOrigine(glm::dvec2((-profil_->longueurDangerCapteurDroit_ - profil_->longueurSecuritaireCapteurDroit_) * SCALE_ROBOT, 0.0 * SCALE_ROBOT), glm::dvec2(-4.0 * SCALE_ROBOT, -9.9 * SCALE_ROBOT), 23.0);
	p2CapteurSecuritaireDroit_ = coordonneesParRapportAOrigine(p2CapteurSecuritaireDroit_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p3CapteurSecuritaireDroit_ = coordonneesParRapportAOrigine(glm::dvec2((-profil_->longueurDangerCapteurDroit_ - profil_->longueurSecuritaireCapteurDroit_) * SCALE_ROBOT, -3.0 * SCALE_ROBOT), glm::dvec2(-4.0 * SCALE_ROBOT, -9.9 * SCALE_ROBOT), 23.0);
	p3CapteurSecuritaireDroit_ = coordonneesParRapportAOrigine(p3CapteurSecuritaireDroit_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p1CapteurDangerMilieu_ = coordonneesParRapportAOrigine(glm::dvec2(0.0 * SCALE_ROBOT, 0.0 * SCALE_ROBOT), glm::dvec2(-1.5 * SCALE_ROBOT, -15.5 * SCALE_ROBOT), 0.0);
	p1CapteurDangerMilieu_ = coordonneesParRapportAOrigine(p1CapteurDangerMilieu_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p2CapteurDangerMilieu_ = coordonneesParRapportAOrigine(glm::dvec2(0.0 * SCALE_ROBOT,-profil_->longueurDangerCapteurMilieu_ * SCALE_ROBOT), glm::dvec2(-1.5 * SCALE_ROBOT, -15.5 * SCALE_ROBOT), 0.0);
	p2CapteurDangerMilieu_ = coordonneesParRapportAOrigine(p2CapteurDangerMilieu_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p3CapteurDangerMilieu_ = coordonneesParRapportAOrigine(glm::dvec2(3.0 * SCALE_ROBOT, -profil_->longueurDangerCapteurMilieu_ * SCALE_ROBOT), glm::dvec2(-1.5 * SCALE_ROBOT, -15.5 * SCALE_ROBOT), 0.0);
	p3CapteurDangerMilieu_ = coordonneesParRapportAOrigine(p3CapteurDangerMilieu_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p4CapteurDangerMilieu_ = coordonneesParRapportAOrigine(glm::dvec2(3.0 * SCALE_ROBOT, 0.0 * SCALE_ROBOT), glm::dvec2(-1.5 * SCALE_ROBOT, -15.5 * SCALE_ROBOT), 0.0);
	p4CapteurDangerMilieu_ = coordonneesParRapportAOrigine(p4CapteurDangerMilieu_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p2CapteurSecuritaireMilieu_ = coordonneesParRapportAOrigine(glm::dvec2(0.0 * SCALE_ROBOT, (-profil_->longueurDangerCapteurMilieu_ - profil_->longueurSecuritaireCapteurMilieu_) * SCALE_ROBOT), glm::dvec2(-1.5 * SCALE_ROBOT, -15.5 * SCALE_ROBOT), 0.0);
	p2CapteurSecuritaireMilieu_ = coordonneesParRapportAOrigine(p2CapteurSecuritaireMilieu_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p3CapteurSecuritaireMilieu_ = coordonneesParRapportAOrigine(glm::dvec2(3.0 * SCALE_ROBOT, (-profil_->longueurDangerCapteurMilieu_ - profil_->longueurSecuritaireCapteurMilieu_) * SCALE_ROBOT), glm::dvec2(-1.5 * SCALE_ROBOT, -15.5 * SCALE_ROBOT), 0.0);
	p3CapteurSecuritaireMilieu_ = coordonneesParRapportAOrigine(p3CapteurSecuritaireMilieu_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p1CapteurDangerGauche_ = coordonneesParRapportAOrigine(glm::dvec2(0.0 * SCALE_ROBOT, 0.0 * SCALE_ROBOT), glm::dvec2(3.0 * SCALE_ROBOT, -12.5 * SCALE_ROBOT), -23.0);
	p1CapteurDangerGauche_ = coordonneesParRapportAOrigine(p1CapteurDangerGauche_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p2CapteurDangerGauche_ = coordonneesParRapportAOrigine(glm::dvec2(profil_->longueurDangerCapteurGauche_ * SCALE_ROBOT, 0.0 * SCALE_ROBOT), glm::dvec2( 3.0 * SCALE_ROBOT, -12.5 * SCALE_ROBOT), -23.0);
	p2CapteurDangerGauche_ = coordonneesParRapportAOrigine(p2CapteurDangerGauche_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p3CapteurDangerGauche_ = coordonneesParRapportAOrigine(glm::dvec2(profil_->longueurDangerCapteurGauche_ * SCALE_ROBOT, 3.0 * SCALE_ROBOT), glm::dvec2(3.0 * SCALE_ROBOT, -12.5 * SCALE_ROBOT), -23.0);
	p3CapteurDangerGauche_ = coordonneesParRapportAOrigine(p3CapteurDangerGauche_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p4CapteurDangerGauche_ = coordonneesParRapportAOrigine(glm::dvec2(0.0 * SCALE_ROBOT, 3.0 * SCALE_ROBOT), glm::dvec2(3.0 * SCALE_ROBOT, -12.5 * SCALE_ROBOT), -23.0);
	p4CapteurDangerGauche_ = coordonneesParRapportAOrigine(p4CapteurDangerGauche_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p2CapteurSecuritaireGauche_ = coordonneesParRapportAOrigine(glm::dvec2((profil_->longueurDangerCapteurGauche_ + profil_->longueurSecuritaireCapteurGauche_) * SCALE_ROBOT, 0.0 * SCALE_ROBOT), glm::dvec2(3.0 * SCALE_ROBOT, -12.5 * SCALE_ROBOT), -23.0);
	p2CapteurSecuritaireGauche_ = coordonneesParRapportAOrigine(p2CapteurSecuritaireGauche_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);

	p3CapteurSecuritaireGauche_ = coordonneesParRapportAOrigine(glm::dvec2((profil_->longueurDangerCapteurGauche_ + profil_->longueurSecuritaireCapteurGauche_) * SCALE_ROBOT, 3.0 * SCALE_ROBOT), glm::dvec2(3.0 * SCALE_ROBOT, -12.5 * SCALE_ROBOT), -23.0);
	p3CapteurSecuritaireGauche_ = coordonneesParRapportAOrigine(p3CapteurSecuritaireGauche_, glm::dvec2(pos.x, pos.y), rotationRobot[0]);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourSenseurs()
///
/// Cette fonction met a jour les positions des 5 senseurs du suiveur
/// de ligne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAJourSenseurs()
{

	glm::dvec2 pointExtDroiteAvant = { -2.58379*SCALE_ROBOT, -15.49721*SCALE_ROBOT };
	glm::dvec2 pointExtGaucheAvant = { 2.94637*SCALE_ROBOT, -15.49721*SCALE_ROBOT };
	glm::dvec2 origine = { positionRelative_.x, positionRelative_.y };
	double rotation = rotationRelative_[0];
	glm::dvec2 pointExtGaucheApres, pointExtDroiteApres;
	pointExtGaucheApres = coordonneesParRapportAOrigine(pointExtGaucheAvant, origine, rotation);
	pointExtDroiteApres = coordonneesParRapportAOrigine(pointExtDroiteAvant, origine, rotation);

	senseurDeLigneExtremeDroite_ = glm::dvec3(pointExtDroiteApres.x, pointExtDroiteApres.y, 0);
	senseurDeLigneExtremeGauche_ = glm::dvec3(pointExtGaucheApres.x, pointExtGaucheApres.y, 0);
	senseurDeLigneCentral_ = { (senseurDeLigneExtremeGauche_.x + senseurDeLigneExtremeDroite_.x) / 2, (senseurDeLigneExtremeGauche_.y + senseurDeLigneExtremeDroite_.y) / 2, 0 };

	senseursDeLigneDroite_ = { (senseurDeLigneCentral_.x + senseurDeLigneExtremeDroite_.x) / 2, (senseurDeLigneCentral_.y + senseurDeLigneExtremeDroite_.y) / 2, 0 };
	senseurDeLigneGauche_ = { (senseurDeLigneCentral_.x + senseurDeLigneExtremeGauche_.x) / 2, (senseurDeLigneCentral_.y + senseurDeLigneExtremeGauche_.y) / 2, 0 };

}

//Obtenir le nombre de senseurs actifs
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourSenseurs()
///
/// Cette fonction permet l'obtention du nombre de senseurs actifs.
///
/// @return Un entier representant le nombre de senseurs actifs.
///
////////////////////////////////////////////////////////////////////////
int NoeudRobot::obtenirNombreSenseursActifs()
{
	int count = 0;
	if (senseurDeLigneExtremeDroiteDetecte_)
		count++;
	if (senseurDeLigneExtremeGaucheDetecte_)
		count++;
	if (senseurDeLigneCentralDetecte_)
		count++;
	if (senseursDeLigneDroiteDetecte_)
		count++;
	if (senseurDeLigneGaucheDetecte_)
		count++;
	return count;
}

//mettre a jour la detection des senseurs
//j'ai reutilisé la méthode clickToucheNoeud qui va vérifier pour nous cette fois si un senseur representé par un dvec3 est 
//au dessus d'un segment d'une ligne(les coordonnees du senseur au lieu de ceux du click)
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRobot::mettreAjourDetectionsenseurs()
///
/// Cette fonction met a jour la detection des senseurs.
///
/// @return Vrai si elle detecte une ligne, faux sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudRobot::mettreAjourDetectionsenseurs()
{
	
	bool estTouche = false;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ligneTouchee(senseurDeLigneExtremeGauche_, estTouche);
	senseurDeLigneExtremeGaucheDetecte_ = estTouche;
	//if (senseurDeLigneExtremeGaucheDetecte_)
	//std::cout << "touche ex G" << std::endl;

	estTouche = false;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ligneTouchee(senseurDeLigneGauche_, estTouche);
	senseurDeLigneGaucheDetecte_ = estTouche;
	//if (senseurDeLigneGaucheDetecte_)
	//std::cout << "touche G" << std::endl;

	estTouche = false;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ligneTouchee(senseurDeLigneCentral_, estTouche);
	senseurDeLigneCentralDetecte_ = estTouche;
	//if (senseurDeLigneCentralDetecte_)
	//std::cout << "touche centre" << std::endl;

	estTouche = false;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ligneTouchee(senseursDeLigneDroite_, estTouche);
	senseursDeLigneDroiteDetecte_ = estTouche;
	//if (senseursDeLigneDroiteDetecte_)
	//std::cout << "touche D" << std::endl;

	estTouche = false;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ligneTouchee(senseurDeLigneExtremeDroite_, estTouche);
	senseurDeLigneExtremeDroiteDetecte_ = estTouche;
	//if (senseurDeLigneExtremeDroiteDetecte_)
	//std::cout << "touche ex D" << std::endl;

	return (senseurDeLigneExtremeGaucheDetecte_ || senseurDeLigneGaucheDetecte_ || senseurDeLigneCentralDetecte_
		|| senseursDeLigneDroiteDetecte_ || senseurDeLigneExtremeDroiteDetecte_);


}

////////////////////////////////////////////////////////////////////////
///
/// @fn glm::dvec2 NoeudRobot::coordonneesParRapportAOrigine(glm::dvec2 point, glm::dvec2 positionOrigine, double theta) const
///
/// Cette fonction permet de convertir les coordonnees d'un repere vers
/// celui de la table.
///
/// @param[in] point : La coordonnee x,y du point par rapport au repere.
/// @param[in] positionOrigine : Position de l'origine du repere contenant le point.
/// @param[in] theta : Angle de rotation du repere.
///
/// @return Coordonnees x,y du point par rapport a celui de la table.
///
////////////////////////////////////////////////////////////////////////
glm::dvec2 NoeudRobot::coordonneesParRapportAOrigine(glm::dvec2 point, glm::dvec2 positionOrigine, double theta) const
{
	glm::dvec2 retour;
	retour.x = cos(utilitaire::DEG_TO_RAD(theta)) * point.x - sin(utilitaire::DEG_TO_RAD(theta)) * point.y + positionOrigine.x;
	retour.y = sin(utilitaire::DEG_TO_RAD(theta)) * point.x + cos(utilitaire::DEG_TO_RAD(theta)) * point.y + positionOrigine.y;
	return retour;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAjourBteEnglobante()
///
/// Cette fonction permet de mettre a jours la boite englobante du robot.
///
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAjourBteEnglobante()
{
	/// Centre du robot
	glm::dvec2 centre = glm::dvec2(obtenirPositionRelative().x, obtenirPositionRelative().y);
	/// Angle de rotation du robot
	double angle = obtenirRotationRelative().x;

	glm::dvec2 point1[16] = { glm::dvec2(2.94, -15.50), glm::dvec2(-2.58, -15.50), glm::dvec2(-2.64, -13.25),
		glm::dvec2(-4.40, -11.24), glm::dvec2(-4.52, -9.07), glm::dvec2(-4.52, -3.46), glm::dvec2(-5.71, -2.27),
		glm::dvec2(-5.71, 2.6), glm::dvec2(-3.83, 7.07), glm::dvec2(4.22, 7.07), glm::dvec2(6.21, 2.6),
		glm::dvec2(6.21, -2.27), glm::dvec2(4.91, -3.46), glm::dvec2(4.91, -9.07), glm::dvec2(4.77, -11.24), glm::dvec2(3.03, -13.25) };
	glm::dvec2 point2[16] = { glm::dvec2(-2.58, -15.50), glm::dvec2(-2.64, -13.25), glm::dvec2(-4.40, -11.24), 
		glm::dvec2(-4.52, -9.07), glm::dvec2(-4.52, -3.46), glm::dvec2(-5.71, -2.27), glm::dvec2(-5.71, 2.6), 
		glm::dvec2(-3.83, 7.07), glm::dvec2(4.22, 7.07), glm::dvec2(6.21, 2.6), glm::dvec2(6.21, -2.27), 
		glm::dvec2(4.91, -3.46), glm::dvec2(4.91, -9.07), glm::dvec2(4.77, -11.24), glm::dvec2(3.03, -13.25), glm::dvec2(2.94, -15.50)};
	/// Points d'extremités du segment avant du robot
	for (unsigned int i = 0; i < 16; i++)
	{
		bteEnglobante_->segments[i].point1 = coordonneesParRapportAOrigine(point1[i] * SCALE_ROBOT, centre, angle);
		bteEnglobante_->segments[i].point2 = coordonneesParRapportAOrigine(point2[i] * SCALE_ROBOT, centre, angle);
	}

	pointViseCamera_ = glm::dvec3(coordonneesParRapportAOrigine(glm::dvec2(0.18, -30.0)* SCALE_ROBOT, centre, angle), -10.0);
	positionCamera_ = glm::dvec3(coordonneesParRapportAOrigine(glm::dvec2(0.0, 10.0)* SCALE_ROBOT, centre, angle), -8.0);
	positionSpot_ = glm::dvec3(coordonneesParRapportAOrigine(glm::dvec2(0.0, -4.0)* SCALE_ROBOT, centre, angle), 40.0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherTypeEtObjetCollision(TypeCollision type, ObjetCollision objet)
///
/// Cette fonction permet l'affichage du type et de l'objet collision.
///
/// @param[in] type : Le type de la collision.
///
/// @param[in] objet : L'objet en question (mur ou poteau).
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherTypeEtObjetCollision(TypeCollision type, ObjetCollision objet)
{
	std::string affichage = "Collision Type : ";
	switch (type)
	{
		case AUCUNE: affichage += "AUCUNE"; break;
		case AVANT: affichage += "AVANT"; break;
		case AVANT_DROIT: affichage += "AVANT_DROIT"; break;
		case AVANT_GAUCHE: affichage += "AVANT_GAUCHE"; break;
		case ARRIERE_DROIT: affichage += "ARRIERE_DROIT"; break;
		case ARRIERE_GAUCHE: affichage += "ARRIERE_GAUCHE"; break;
		case ARRIERE: affichage += "ARRIERE"; break;
		default: break;
	}
	affichage += "	&	Objet : ";
	switch (objet)
	{
		case AUCUN: affichage += "AUCUN\n"; break;
		case POTEAU: affichage += "POTEAU\n"; break;
		case MUR_VISIBLE: affichage += "MUR_VISIBLE\n"; break;
		case MUR_INVISIBLE: affichage += "MUR_INVISIBLE\n"; break;
		default: break;
	}
	std::cout << affichage;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::chargerProfil(char* nomProfil)
///
/// Cette fonction permet le chargement du profil d'un robot.
///
/// @param[in] nomProfil : Nom du profil.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::chargerProfil(char* nomProfil)
{
	profil_->chargerProfil(nomProfil);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait *  NoeudRobot::getComportement(ETATS etats)
///
/// Prend un enum représentant un état (provenant du profil coté C#) puis renvoi
/// le comportement associé.
///
/// @param[in] etats l'enum du Profil associé au comportement désiré.
///
/// @return pointeur vers une nouvelle instance du comportement correspondant.
///
////////////////////////////////////////////////////////////////////////
ComportementAbstrait *  NoeudRobot::getComportement(ETATS etat)
{
	switch (etat)
	{
	case ETATS::DEFAUT:
		return new Defaut(this);
	case ETATS::DEVIATION_DROITE:
		return new DeviationVersDroite(this);
	case ETATS::DEVIATION_GAUCHE:
		return new DeviationVersGauche(this);
	case ETATS::ETAT_AVANCER:
		return new Avancer(this);
	case ETATS::EVITER_DROITE:
		return new EvitementParDroite(this);
	case ETATS::EVITER_GAUCHE:
		return new EvitementParGauche(this);
	case ETATS::SL_DEVIATION_DROITE:
		return new SL_DeviationVersDroite(this);
	case ETATS::SL_DEVIATION_GAUCHE:
		return new SL_DeviationVersGauche(this);
	case ETATS::SUIVI_LIGNE:
		return new SuiviDeLigne(this);
	case ETATS::BALAYAGE_180ETAPE1:
		return new Balayage180Degres(this);
	case ETATS::BALAYAGE_180ETAPE2:
		return new balayage180etape2(this);
	case ETATS::BALAYAGE_180ETAPE3:
		return new balayage180etapeFinale(this);
	case ETATS::ETAT_FREEZE:
		return new Freeze(this);
	default:
		return NULL;
	}
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::basculerActivationLumiereAmbiante(std::string log)
///
/// Cette fonction l'activation de la lumiere ambiante.
///
/// @param[in] log : Timestamps du moment de l'activation / desactivation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::basculerActivationLumiereAmbiante(std::string log)
{
	if (lumiereAmbianteActivee_)
	{
		lumiereAmbianteActivee_ = false;
		if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getEtatEclairage())
			std::cout << log << " - Lumiere ambiante fermee" << std::endl;
	}
	else
	{
		lumiereAmbianteActivee_ = true;
		if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getEtatEclairage())
			std::cout << log << " - Lumiere ambiante ouverte" << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::basculerActivationLumiereDirectionnelle(std::string log)
///
/// Cette fonction l'activation de la lumiere directionnelle.
///
/// @param[in] log : Timestamps du moment de l'activation / desactivation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::basculerActivationLumiereDirectionnelle(std::string log)
{
	if (lumiereDirectionnelleActivee_)
	{
		lumiereDirectionnelleActivee_ = false;
		if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getEtatEclairage())
			std::cout << log << " - Lumiere directionnelle fermee" << std::endl;
	}
	else
	{
		lumiereDirectionnelleActivee_ = true;
		if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getEtatEclairage())
			std::cout << log << " - Lumiere directionnelle ouverte" << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::basculerActivationSpots(std::string log)
///
/// Cette fonction l'activation de la lumiere du spot.
///
/// @param[in] log : Timestamps du moment de l'activation / desactivation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::basculerActivationSpots(std::string log)
{
	if (spotsActives_)
	{
		spotsActives_ = false;
		if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getEtatEclairage())
			std::cout << log << " - Lumieres spots fermees" << std::endl;
		
	}
	else
	{
		spotsActives_ = true;
		if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getEtatEclairage())
			std::cout << log << " - Lumieres spots ouvertes" << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::changerComportementsObstacles()
///
/// Cette fonction permet de changer le comportement du robot en fonction
/// de l'obstacle detecte.
///
/// @param: Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::changerComportementsObstacles()
{
	if (estDetecteDangerDroit_)
	{
		if (comportementCourant_ != nullptr)
		{
			ComportementAbstrait * ptr = comportementCourant_;
			definirComportement(getComportement(getProfil()->getSuivantDangerD()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getChangementComportement() && flipFlopCapteurDangerDroit_)
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Capteur de distance droit, zone danger" 
						  << " - "<< FacadeModele::obtenirInstance()->etatToString(profil_->getSuivantDangerD()) << std::endl;
				setEtat(profil_->getSuivantDangerD());
				flipFlopCapteurDangerDroit_ = false;
				flipFlopCapteurSecuritaireDroit_ = true;
				flipFlopCapteurDangerMilieu_ = true;
				flipFlopCapteurDangerGauche_ = true;
				flipFlopCapteurSecuritaireMilieu_ = true;
				flipFlopCapteurSecuritaireGauche_ = true;
			}
			delete ptr;
		}
		return;
	}
	if (estDetecteDangerMilieu_)
	{
		if (comportementCourant_ != nullptr)
		{
			ComportementAbstrait * ptr = comportementCourant_;
			definirComportement(getComportement(getProfil()->getSuivantDangerM()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getChangementComportement() && flipFlopCapteurDangerMilieu_)
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Capteur de distance milieu, zone danger"
					<< " - " << FacadeModele::obtenirInstance()->etatToString(profil_->getSuivantDangerM()) << std::endl;
				setEtat(profil_->getSuivantDangerM());
				flipFlopCapteurDangerMilieu_ = false;
				flipFlopCapteurSecuritaireMilieu_ = true;
				flipFlopCapteurDangerDroit_ = true;
				flipFlopCapteurDangerGauche_ = true;
				flipFlopCapteurSecuritaireDroit_ = true;
				flipFlopCapteurSecuritaireGauche_ = true;
			}
			delete ptr;
		}
		return;
	}
	if (estDetecteDangerGauche_)
	{
		if (comportementCourant_ != nullptr)
		{
			ComportementAbstrait * ptr = comportementCourant_;
			definirComportement(getComportement(getProfil()->getSuivantDangerG()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getChangementComportement() && flipFlopCapteurDangerGauche_)
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Capteur de distance gauche, zone danger"
					<< " - " << FacadeModele::obtenirInstance()->etatToString(profil_->getSuivantDangerG()) << std::endl;
				setEtat(profil_->getSuivantDangerG());
				flipFlopCapteurDangerGauche_ = false;
				flipFlopCapteurSecuritaireGauche_ = true;
				flipFlopCapteurDangerMilieu_ = true;
				flipFlopCapteurDangerDroit_ = true;
				flipFlopCapteurSecuritaireMilieu_ = true;
				flipFlopCapteurSecuritaireDroit_ = true;
			}
			delete ptr;
		}
		return;
	}

	if (estDetecteSecuritaireGauche_)
	{
		if (comportementCourant_ != nullptr)
		{
			ComportementAbstrait * ptr = comportementCourant_;
			definirComportement(getComportement(getProfil()->getSuivantSecureG()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getChangementComportement() && flipFlopCapteurSecuritaireGauche_)
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Capteur de distance gauche, zone securitaire"
					<< " - " << FacadeModele::obtenirInstance()->etatToString(profil_->getSuivantSecureG()) << std::endl;
				setEtat(profil_->getSuivantSecureG());
				flipFlopCapteurSecuritaireGauche_ = false;
				flipFlopCapteurDangerGauche_ = true;
				flipFlopCapteurDangerMilieu_ = true;
				flipFlopCapteurDangerDroit_ = true;
				flipFlopCapteurSecuritaireDroit_ = true;
				flipFlopCapteurSecuritaireMilieu_ = true;
			}
			delete ptr;
		}
		return;
	}

	if (estDetecteSecuritaireMilieu_)
	{
		if (comportementCourant_ != nullptr)
		{
			ComportementAbstrait * ptr = comportementCourant_;
			definirComportement(getComportement(getProfil()->getSuivantSecureM()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getChangementComportement() && flipFlopCapteurSecuritaireMilieu_)
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Capteur de distance milieu, zone securitaire"
					<< " - " << FacadeModele::obtenirInstance()->etatToString(profil_->getSuivantSecureM()) << std::endl;
				setEtat(profil_->getSuivantSecureM());
				flipFlopCapteurSecuritaireMilieu_ = false;
				flipFlopCapteurDangerMilieu_ = true;
				flipFlopCapteurDangerGauche_ = true;
				flipFlopCapteurDangerDroit_ = true;
				flipFlopCapteurSecuritaireDroit_ = true;
				flipFlopCapteurSecuritaireGauche_ = true;
			}
			delete ptr;
		}
		return;
	}

	if (estDetecteSecuritaireDroit_)
	{
		if (comportementCourant_ != nullptr)
		{
			ComportementAbstrait * ptr = comportementCourant_;
			definirComportement(getComportement(getProfil()->getSuivantSecureD()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && debug_->getSortieConsole() && debug_->getChangementComportement() && flipFlopCapteurSecuritaireDroit_)
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Capteur de distance droit, zone securitaire"
					<< " - " << FacadeModele::obtenirInstance()->etatToString(profil_->getSuivantSecureD()) << std::endl;
				setEtat(profil_->getSuivantSecureD());
				flipFlopCapteurSecuritaireDroit_ = false;
				flipFlopCapteurDangerDroit_ = true;
				flipFlopCapteurDangerMilieu_ = true;
				flipFlopCapteurDangerGauche_ = true;
				flipFlopCapteurSecuritaireGauche_ = true;
				flipFlopCapteurSecuritaireMilieu_ = true;
			}
			delete ptr;
		}
		return;
	}


}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::jouerSon(int i)
///
/// Joue le son associe a l'evenement
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::jouerSon(int i)
{
	switch (i)
	{
	case 1:
		// Poteau
		son_->jouer(false);
		break;
	case 2:
		// Mur
		son_->jouer2(false);
		break;
	case 3:
		// Mur Invisible
		son_->jouer3(false);
		break;
	case 4:
		// Mur avancer/reculer
		son_->jouer4(false);
		break;
	case 5:
		// rotation
		son_->jouer5(false);
		break;
	case 7:
		// Deviation
		son_->jouer7(false);
		break;
	case 8:
		//  Mode Manuel 
		son_->jouer8(false);
		break;
	case 9:
		//  Mode Auto
		son_->jouer9(false);
		break;

	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::pauseSon()
///
/// pause le channel associe au son demande
///
/// @param[in] i l'indice de l'effet sonore..
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::pauseSon(int i, bool pause)
{
	{
		switch (i)
		{
		case 4:
			// Avancer/reculer
			son_->setPause(2, pause);
			break;
		case 5:
			// rotation
			son_->setPause(3, pause);
			break;
		case 7 :
			//deviation
			son_->setPause(4, pause);
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::updateSound()
///
/// Update le son (FMOD)
///
/// @param[in] Aucun.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAjourSon()
{
	son_->mettreAjour();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::appliquerSonMoteurs()
///
/// Cette fonction permet d'appliquer un son différent dépendemment
/// du sens et de la vitesse de rotation des moteurs
///
/// @param[in] Aucun.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::appliquerSonMoteurs()
{
	if (comportementCourant_ != nullptr && etatExecuter_ == SUIVI_LIGNE)
	{
		//suivi de ligne
		pauseSon(5, true);
		pauseSon(7, true);
		pauseSon(4,false); 
	}
	else if (utilitaire::EGAL_ZERO(roueDroite_->getRapportVitesse()) && utilitaire::EGAL_ZERO(roueGauche_->getRapportVitesse()))
	{
        //les roues ne tournes pas
		pauseSon(5, true);
		pauseSon(7, true);
		pauseSon(4, true);
	}
	else if (utilitaire::EGAL_ZERO(deltaRapportVitesse_))
	{
		if (roueDroite_->getDirection() == FORWARD)
		{
			// Son avancer
			pauseSon(5, true);
			pauseSon(7, true);
			pauseSon(4, false);
		}
		else
		{
			// Son reculer
			pauseSon(5, true);
			pauseSon(7, true);
			pauseSon(4, false);
		}
	}
	else if (deltaRapportVitesse_ > 0.0)
	{
		if (roueDroite_->getDirection() == FORWARD)
		{
			if (!utilitaire::EGAL_ZERO(roueGauche_->rapportVitesseReel_))
			{
				// Son Virer Avant sens Anti-Horaire	
				pauseSon(4, true);
				pauseSon(5, true);
				pauseSon(7, false);
			}
			else
			{
				// Son pivoter Avant sens Anti-Horaire
				pauseSon(7, true);
				pauseSon(4, true);
				pauseSon(5, false);
				
			}
		}
		else
		{
			if (!utilitaire::EGAL_ZERO(roueGauche_->rapportVitesseReel_))
			{
				// Son Virer Arrière sens Horaire							
			}
			else
			{
				// Son pivoter Arrière sens Horaire
			}
		}
	}
	else
	{
		if (roueGauche_->getDirection() == FORWARD)
		{
			if (!utilitaire::EGAL_ZERO(roueDroite_->rapportVitesseReel_))
			{
				// Son Virer Avant sens Horaire
				pauseSon(4, true);
				pauseSon(5, true);
				pauseSon(7, false);
			}
			else
			{
				// Son pivoter Avant sens Horaire
				pauseSon(7, true);
				pauseSon(4, true);
				pauseSon(5, false);
			}
		}
		else
		{
			if (!utilitaire::EGAL_ZERO(roueDroite_->rapportVitesseReel_))
			{
				// Son Virer Arrière sens Anti-Horaire
			}
			else
			{
				// Son pivoter Arrière sens Anti-Horaire
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
