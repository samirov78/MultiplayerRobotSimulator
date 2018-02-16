///////////////////////////////////////////////////////////////////////////////
/// @file Defaut.h
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
Defaut::Defaut(NoeudRobot * contexte) :contexte_(contexte)
{
	contexte_->setDoitSuivre(true);
	contexte_->resetTempsAttente();
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Defaut::executerComportement()
///
/// Ex�cute un comportement concret 
///
/// @param[in] Aucun
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void Defaut::executerComportement()
{
	contexte_->actionnerMoteurs(0.7, 0.7, FORWARD);	//0.5
	
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////