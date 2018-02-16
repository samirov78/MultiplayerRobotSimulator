///////////////////////////////////////////////////////////////////////////////
/// @file EvitementParDroite.h
/// @author Equipe 11
/// @date 2016-02-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

// #include "EvitementParDroite.h"

#include "ComportementTypes.h"
#include "../Arbre/Noeuds/NoeudRobot.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn EvitementParGauche::EvitementParDroite(NoeudRobot * contexte)
///
/// Constructeur
///
/// @param[in] context : classe representant robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
EvitementParDroite::EvitementParDroite(NoeudRobot * contexte) :contexte_(contexte)
{
	contexte_->setDoitSuivre(false);
	contexte_->setangleRotationInitial(contexte_->obtenirRotationRelative()[0]);
	contexte_->resetTempsAttente();
	contexte_->setTempsDebut(time(0));
}



////////////////////////////////////////////////////////////////////////
///
/// @fn EvitementParDroite::~EvitementParDroite()
///
///  @param[in] aucun 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
EvitementParDroite::~EvitementParDroite()
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EvitementParDroite::executerComportement()
///
/// Exécute un comportement concret 
///
/// @param[in] Aucun
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void EvitementParDroite::executerComportement()
{

//if (contexte_->getRoueDroite()->getDirection() == FORWARD)
//	{
//		contexte_->actionnerMoteurs(1, 1, REVERSE);
//	}
//	else 
	if (contexte_->obstacleDetecte())
	{
		contexte_->changerComportementsObstacles();
	}

	if ((difftime(time(0), contexte_->getTempsDebut()))
		< contexte_->getProfil()->getDureeEvitementDroite()/1000)
	{
		contexte_->actionnerMoteurs(1, 1, REVERSE);
	}
	else if ((std::abs(contexte_->getAngleRotationInitial() - contexte_->obtenirRotationRelative()[0])
		< contexte_->getProfil()->getAnglePivoterDroite()))
	{

		contexte_->actionnerMoteurs(1.0, 0.0, FORWARD);
		contexte_->setAffichageDebogageCapteurDangerDroit(true);
		contexte_->setAffichageDebogageCapteurDangerMilieu(true);
		contexte_->setAffichageDebogageCapteurDangerGauche(true);
		contexte_->setAffichageDebogageCapteurSecuritaireDroit(true);
		contexte_->setAffichageDebogageCapteurSecuritaireMilieu(true);
		contexte_->setAffichageDebogageCapteurSecuritaireGauche(true);
	}
	else if (!contexte_->getDoitAttendre())
	{
		contexte_->stopperMoteurs();
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(contexte_->getProfil()->getSuivantEvitDroite()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && contexte_->obtenirDebug()->getSortieConsole() && contexte_->obtenirDebug()->getChangementComportement())
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Fin de " << FacadeModele::obtenirInstance()->etatToString(EVITER_DROITE) << " - " << FacadeModele::obtenirInstance()->etatToString(contexte_->getProfil()->getSuivantEvitDroite()) << std::endl;
				contexte_->setEtat(contexte_->getProfil()->getSuivantEvitDroite());
				contexte_->setAffichageDebogageCapteurDangerDroit(true);
				contexte_->setAffichageDebogageCapteurDangerMilieu(true);
				contexte_->setAffichageDebogageCapteurDangerGauche(true);
				contexte_->setAffichageDebogageCapteurSecuritaireDroit(true);
				contexte_->setAffichageDebogageCapteurSecuritaireMilieu(true);
				contexte_->setAffichageDebogageCapteurSecuritaireGauche(true);
				contexte_->setAffichageDebogageSuiviLigne(true);
			}
			delete ptr;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

