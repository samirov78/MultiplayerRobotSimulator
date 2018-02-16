///////////////////////////////////////////////////////////////////////////////
/// @file Balayage180Degres.h
/// @author Equipe 11
/// @date 2016-02-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "ComportementAbstait.h"
//class NoeudRobot;

///////////////////////////////////////////////////////////////////////////
/// @class Defaut
/// @brief Classe qui implemente le comportement concret soit le comportement
/// Balayage180Degres. Application du patron etat.
/// 
/// @author Equipe 11
/// @date 2016-02-25
///////////////////////////////////////////////////////////////////////////

class Balayage180Degres : public ComportementAbstrait
{
public:
	/// Constructeur par d�faut.
	Balayage180Degres(NoeudRobot * contexte);
	/// Destructeur.
	~Balayage180Degres();
	/// Effectuer un comportement.
	void executerComportement();
private:
	///Le robot en question.
	NoeudRobot * contexte_;

};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////