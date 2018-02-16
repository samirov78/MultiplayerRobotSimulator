///////////////////////////////////////////////////////////////////////////////
/// @file balayage180etape2.cpp
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
/// @fn Balayage180Degres::balayage180etape2(NoeudRobot * contexte)
///
/// Constructeur
///
/// @param[in] context : classe representant robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
balayage180etape2::balayage180etape2(NoeudRobot * contexte) :contexte_(contexte)
{
	contexte_->setangleRotationInitial(contexte_->obtenirRotationRelative()[0]);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn balayage180etape2::~balayage180etape2()
///
///  @param[in] aucun 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
balayage180etape2::~balayage180etape2()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void balayage180etape2::executerComportement()
///
/// Exécute un comportement concret 
///
/// @param[in] Aucun
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void balayage180etape2::executerComportement()
{
	if ((std::abs(contexte_->getAngleRotationInitial() - contexte_->obtenirRotationRelative()[0]) < 180))
	{
		contexte_->actionnerMoteurs(0.8, 0.0, FORWARD);
	}
	else
	{
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(ETATS::BALAYAGE_180ETAPE3));
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