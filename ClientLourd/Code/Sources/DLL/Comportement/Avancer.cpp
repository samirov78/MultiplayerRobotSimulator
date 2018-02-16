///////////////////////////////////////////////////////////////////////////////
/// @Avancer.cpp
/// @author Equipe 11
/// @date 2016-03-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


#include "ComportementTypes.h"
#include "../Arbre/Noeuds/NoeudRobot.h"




////////////////////////////////////////////////////////////////////////
///
/// @fn void Avancer::executerComportement()
///
/// Exécute un comportement concret 
///
/// @param[in] Aucun
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void Avancer::executerComportement()
{
	
	if (contexte_->obstacleDetecte())
	{
		contexte_->changerComportementsObstacles();
	}

	contexte_->actionnerMoteurs(1, 1, FORWARD);

	// Aucun suiveur activé
	if (!contexte_->mettreAjourDetectionsenseurs())
	{
		ETATS etatsuivant = contexte_->getProfil()->getSuivantSuiviLigne();
		if (etatsuivant == ETATS::SUIVI_LIGNE)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(new Freeze(contexte_));
			delete ptr;
		}
		else
		{

			if (contexte_->getComportementCourant() != nullptr)
			{
				ComportementAbstrait * ptr = contexte_->getComportementCourant();
				contexte_->definirComportement(contexte_->getComportement(contexte_->getProfil()->getSuivantSuiviLigne()));
				if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && contexte_->obtenirDebug()->getSortieConsole() && contexte_->obtenirDebug()->getChangementComportement())
				{
					std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Fin de " << FacadeModele::obtenirInstance()->etatToString(SUIVI_LIGNE) << " - " << FacadeModele::obtenirInstance()->etatToString(contexte_->getProfil()->getSuivantSuiviLigne()) << std::endl;
					contexte_->setEtat(contexte_->getProfil()->getSuivantSuiviLigne());
					contexte_->setAffichageDebogageSuiviLigne(true);
					contexte_->setAffichageDebogageCapteurDangerDroit(true);
					contexte_->setAffichageDebogageCapteurDangerMilieu(true);
					contexte_->setAffichageDebogageCapteurDangerGauche(true);
					contexte_->setAffichageDebogageCapteurSecuritaireDroit(true);
					contexte_->setAffichageDebogageCapteurSecuritaireMilieu(true);
					contexte_->setAffichageDebogageCapteurSecuritaireGauche(true);
				}
				delete ptr;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

