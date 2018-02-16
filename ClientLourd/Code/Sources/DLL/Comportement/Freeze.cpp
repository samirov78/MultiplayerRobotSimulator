///////////////////////////////////////////////////////////////////////////////
/// @file Freeze.cpp
/// @author Equipe 11
/// @date 2016-02-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "ComportementTypes.h"
#include "../Arbre/Noeuds/NoeudRobot.h"




////////////////////////////////////////////////////////////////////////
///
/// @fn Defaut::Defaut(NoeudRobot * contexte)
///
/// Constructeur du comportement defaut.
///
/// @param[in] contexte : Le robot en question.
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
Freeze::Freeze(NoeudRobot * contexte) :contexte_(contexte)
{
	contexte_->resetTempsAttente();

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Defaut::executerComportement()
///
/// Exécute un comportement concret 
///
/// @param[in] Aucun
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void Freeze::executerComportement()
{
	contexte_->arreterMoteurs();
	if (FacadeModele::obtenirInstance()->obtenirAffichageDebougage() && contexte_->obtenirDebug()->getSortieConsole() && contexte_->obtenirDebug()->getChangementComportement())
	{
		std::cout << FacadeModele::obtenirInstance()->timestamps() << " - " << "Fin de " << FacadeModele::obtenirInstance()->etatToString(SUIVI_LIGNE) << " - " << FacadeModele::obtenirInstance()->etatToString(contexte_->getProfil()->getSuivantSuiviLigne()) << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////