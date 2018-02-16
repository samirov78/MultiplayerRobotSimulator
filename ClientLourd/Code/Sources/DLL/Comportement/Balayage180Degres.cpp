///////////////////////////////////////////////////////////////////////////////
/// @file Balayage180Degres.cpp
/// @author Equipe 11
/// @date 2016-02-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

//#include "Defaut.h"

#include "ComportementTypes.h"
#include "../Arbre/Noeuds/NoeudRobot.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn Balayage180Degres::Balayage180Degres(NoeudRobot * contexte)
///
/// Constructeur
///
/// @param[in] context : classe representant robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Balayage180Degres::Balayage180Degres(NoeudRobot * contexte) :contexte_(contexte)
{
	contexte_->stopperMoteurs();
	contexte_->setDoitSuivre(true);
	contexte_->setangleRotationInitial(contexte_->obtenirRotationRelative()[0]);
	contexte_->resetTempsAttente();
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Balayage180Degres::~Balayage180Degres()
///
///  @param[in] aucun 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Balayage180Degres::~Balayage180Degres()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Balayage180Degres::executerComportement()
///
/// Exécute un comportement concret 
///
/// @param[in] Aucun
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void Balayage180Degres::executerComportement()
{
	if ((std::abs(contexte_->getAngleRotationInitial() - contexte_->obtenirRotationRelative()[0]) < 90))
	{
		contexte_->actionnerMoteurs(0.0, 0.8, FORWARD);
	}
	else
	{
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(ETATS::BALAYAGE_180ETAPE2));
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