///////////////////////////////////////////////////////////////////////////////
/// @file DeviationVersDroite.h
/// @author Equipe 11
/// @date 2016-02-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

//#include "DeviationVersDroite.h"

#include "ComportementTypes.h"
#include "../Arbre/Noeuds/NoeudRobot.h"



////////////////////////////////////////////////////////////////////////
///
/// @fn SL_DeviationVersDroite::SL_DeviationVersDroite(NoeudRobot * contexte)
///
/// Constructeur
///
/// @param[in] contexte : classe representant le robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
SL_DeviationVersDroite::SL_DeviationVersDroite(NoeudRobot * contexte) :contexte_(contexte)
{
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void DeviationVersDroite::executerComportement()
///
/// Exécute un comportement concret 
///
/// @param[in] Aucun
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void SL_DeviationVersDroite::executerComportement()

{
	
	if (contexte_->obstacleDetecte())
	{
		contexte_->changerComportementsObstacles();
	}

	if (!contexte_->estDetecteSenseurDeLigneCentral())
	{
		contexte_->actionnerMoteurs(1, 0.1, FORWARD);
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

