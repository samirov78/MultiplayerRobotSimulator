///////////////////////////////////////////////////////////////////////////////
/// @file balayage180etapeFinale.cpp
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
/// @fn balayage180etapeFinale::balayage180etapeFinale(NoeudRobot * contexte)
///
/// Constructeur
///
/// @param[in] context : classe representant robot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
balayage180etapeFinale::balayage180etapeFinale(NoeudRobot * contexte) :contexte_(contexte)
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
balayage180etapeFinale::~balayage180etapeFinale()
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
void balayage180etapeFinale::executerComportement()
{
	if ((std::abs(contexte_->getAngleRotationInitial() - contexte_->obtenirRotationRelative()[0]) < 90))
	{
		contexte_->actionnerMoteurs(0.0, 0.8, FORWARD);
	}
	else if ((std::abs(contexte_->getAngleRotationInitial() - contexte_->obtenirRotationRelative()[0]) < 5))
	{
		contexte_->actionnerMoteurs(0.0, 0.8, FORWARD);
	}
	else if (!contexte_->getDoitAttendre())
	{
		if (contexte_->getComportementCourant() != nullptr)
		{
			ComportementAbstrait * ptr = contexte_->getComportementCourant();
			contexte_->definirComportement(contexte_->getComportement(contexte_->getProfil()->getSuivantBalayage()));
			if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && contexte_->obtenirDebug()->getSortieConsole() && contexte_->obtenirDebug()->getChangementComportement())
			{
				std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Fin de " << FacadeModele::obtenirInstance()->etatToString(BALAYAGE_180ETAPE1) << " - " << FacadeModele::obtenirInstance()->etatToString(contexte_->getProfil()->getSuivantBalayage()) << std::endl;
				contexte_->setEtat(contexte_->getProfil()->getSuivantBalayage());
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