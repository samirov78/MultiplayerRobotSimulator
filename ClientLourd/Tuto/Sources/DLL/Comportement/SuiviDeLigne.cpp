///////////////////////////////////////////////////////////////////////////////
/// @file SuiviDeLigne.h
/// @author Equipe 11
/// @date 2016-02-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


#include "ComportementTypes.h"
#include "../Arbre/Noeuds/NoeudRobot.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn void SuiviDeLigne::executerComportement()
///
/// Exécute un comportement concret 
///
/// @param[in] Aucun
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void SuiviDeLigne::executerComportement()
{

	int nombreSenseursActifs = contexte_->obtenirNombreSenseursActifs();
	bool droite = contexte_->estdetecteSenseursDeLigneDroite();
	bool extDroite = contexte_->estDetecteSenseurDeLigneExtremeDroite();
	bool centre = contexte_->estDetecteSenseurDeLigneCentral();
	bool gauche = contexte_->estDetecteSenseurDeLigneGauche();
	bool extGauche = contexte_->estDetecteSenseurDeLigneExtremeGauche();


	// Aucun suiveur activé

	if (!contexte_->mettreAjourDetectionsenseurs())
	{
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(contexte_->getProfil()->getSuivantSuiviLigne()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && contexte_->obtenirDebug()->getSortieConsole() && contexte_->obtenirDebug()->getChangementComportement())
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Fin de " << FacadeModele::obtenirInstance()->etatToString(SUIVI_LIGNE) << " - " << FacadeModele::obtenirInstance()->etatToString(contexte_->getProfil()->getSuivantSuiviLigne()) << std::endl;
				contexte_->setEtat(contexte_->getProfil()->getSuivantSuiviLigne());
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
	
	else if ((gauche || extGauche) && !centre)
	{
		contexte_->actionnerMoteurs(0.1, 1, FORWARD);
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(ETATS::SL_DEVIATION_GAUCHE));
			contexte_->setAffichageDebogageCapteurDangerDroit(true);
			contexte_->setAffichageDebogageCapteurDangerMilieu(true);
			contexte_->setAffichageDebogageCapteurDangerGauche(true);
			contexte_->setAffichageDebogageCapteurSecuritaireDroit(true);
			contexte_->setAffichageDebogageCapteurSecuritaireMilieu(true);
			contexte_->setAffichageDebogageCapteurSecuritaireGauche(true);
			delete ptr;
		}
	}

	else if ((droite || extDroite) && !centre)
	{
		contexte_->actionnerMoteurs(1, 0.1, FORWARD);	
		
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(ETATS::SL_DEVIATION_DROITE));
			contexte_->setAffichageDebogageCapteurDangerDroit(true);
			contexte_->setAffichageDebogageCapteurDangerMilieu(true);
			contexte_->setAffichageDebogageCapteurDangerGauche(true);
			contexte_->setAffichageDebogageCapteurSecuritaireDroit(true);
			contexte_->setAffichageDebogageCapteurSecuritaireMilieu(true);
			contexte_->setAffichageDebogageCapteurSecuritaireGauche(true);
			delete ptr;
		}

	}

	else if (extGauche && !centre)
	{
		contexte_->actionnerMoteurs(0.1, 1, FORWARD);	//0.2
		//contexte_->definirComportement(contexte_->lesComportements_[ETATS::SL_DEVIATION_GAUCHE]);
	}
	else if (extDroite && !centre)
	{
		contexte_->actionnerMoteurs(1, 0.1, FORWARD);	//0.2
		//contexte_->definirComportement(contexte_->lesComportements_[ETATS::SL_DEVIATION_DROITE]);
	}

	else if (extGauche && centre)
	{
		contexte_->actionnerMoteurs(0.1, 1, FORWARD);
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(ETATS::SL_DEVIATION_GAUCHE));
			contexte_->setAffichageDebogageCapteurDangerDroit(true);
			contexte_->setAffichageDebogageCapteurDangerMilieu(true);
			contexte_->setAffichageDebogageCapteurDangerGauche(true);
			contexte_->setAffichageDebogageCapteurSecuritaireDroit(true);
			contexte_->setAffichageDebogageCapteurSecuritaireMilieu(true);
			contexte_->setAffichageDebogageCapteurSecuritaireGauche(true);
			delete ptr;
		}
	}
	else if (extDroite && centre)
	{
		contexte_->actionnerMoteurs(1, 0.1, FORWARD);
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(ETATS::SL_DEVIATION_DROITE));
			contexte_->setAffichageDebogageCapteurDangerDroit(true);
			contexte_->setAffichageDebogageCapteurDangerMilieu(true);
			contexte_->setAffichageDebogageCapteurDangerGauche(true);
			contexte_->setAffichageDebogageCapteurSecuritaireDroit(true);
			contexte_->setAffichageDebogageCapteurSecuritaireMilieu(true);
			contexte_->setAffichageDebogageCapteurSecuritaireGauche(true);
			delete ptr;
		}
	}
	else if (centre)
	{
		contexte_->actionnerMoteurs(1, 1, FORWARD);
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(ETATS::ETAT_AVANCER));
			contexte_->setAffichageDebogageCapteurDangerDroit(true);
			contexte_->setAffichageDebogageCapteurDangerMilieu(true);
			contexte_->setAffichageDebogageCapteurDangerGauche(true);
			contexte_->setAffichageDebogageCapteurSecuritaireDroit(true);
			contexte_->setAffichageDebogageCapteurSecuritaireMilieu(true);
			contexte_->setAffichageDebogageCapteurSecuritaireGauche(true);
			delete ptr;
		}
		
	}

	
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


