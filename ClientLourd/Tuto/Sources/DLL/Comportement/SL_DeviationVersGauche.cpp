///////////////////////////////////////////////////////////////////////////////
/// @file DeviationVersGauche.h
/// @author Equipe 11
/// @date 2016-02-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

// #include "DeviationVersGauche.h"

#include "ComportementTypes.h"
#include "../Arbre/Noeuds/NoeudRobot.h"




////////////////////////////////////////////////////////////////////////
///
/// @fn DeviationVersGauche::DeviationVersGauche(NoeudRobot * contexte)
///
/// Constructeur
///
/// @param[in] contexte : classe representant le robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
SL_DeviationVersGauche::SL_DeviationVersGauche(NoeudRobot * contexte) :contexte_(contexte)
{
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void DeviationVersGauche::executerComportement()
///
/// Exécute un comportement concret 
///
/// @param[in] Aucun
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void SL_DeviationVersGauche::executerComportement()
{
	
	if (contexte_->obstacleDetecte())
	{
		contexte_->changerComportementsObstacles();
	}

	if (!contexte_->estDetecteSenseurDeLigneCentral())
	{
		contexte_->actionnerMoteurs(0.1, 1, FORWARD);
	}
	else
	{
		
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(ETATS::SUIVI_LIGNE));
			contexte_->setAffichageDebogageCapteurDangerDroit(true);
			contexte_->setAffichageDebogageCapteurDangerMilieu(true);
			contexte_->setAffichageDebogageCapteurDangerGauche(true);
			contexte_->setAffichageDebogageCapteurSecuritaireDroit(true);
			contexte_->setAffichageDebogageCapteurSecuritaireMilieu(true);
			contexte_->setAffichageDebogageCapteurSecuritaireGauche(true);
			contexte_->setAffichageDebogageSuiviLigne(true);
			delete ptr;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

