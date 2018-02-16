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
DeviationVersGauche::DeviationVersGauche(NoeudRobot * contexte) :contexte_(contexte)
{
	contexte_->setDoitSuivre(false);
	contexte_->setangleRotationInitial(contexte_->obtenirRotationRelative()[0]);
	contexte_->resetTempsAttente();
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
void DeviationVersGauche::executerComportement()
{
	if (contexte_->obstacleDetecte())
	{
		contexte_->changerComportementsObstacles();
	}

	if (std::abs(contexte_->getAngleRotationInitial() - contexte_->obtenirRotationRelative()[0])
		< contexte_->getProfil()->getAngleDeviationGauche())
	{
		contexte_->actionnerMoteurs(0.4, 0.8, FORWARD);	//0.2
	}
	else if (contexte_->getDoitAttendre() == false)
	{
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(contexte_->getProfil()->getSuivantDevGauche()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && contexte_->obtenirDebug()->getSortieConsole() && contexte_->obtenirDebug()->getChangementComportement())
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Fin de " << FacadeModele::obtenirInstance()->etatToString(DEVIATION_GAUCHE) <<  " - " << FacadeModele::obtenirInstance()->etatToString(contexte_->getProfil()->getSuivantDevGauche()) << std::endl;
				contexte_->setEtat(contexte_->getProfil()->getSuivantDevGauche());
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
		
		// Prochain état dicté par le profil
	}
	
	
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

