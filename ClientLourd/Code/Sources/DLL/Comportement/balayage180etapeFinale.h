///////////////////////////////////////////////////////////////////////////////
/// @file balayage180etapeFinale.h
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
/// balayage180 etape Finale
/// 
/// @author Equipe 11
/// @date 2016-02-25
///////////////////////////////////////////////////////////////////////////

class balayage180etapeFinale : public ComportementAbstrait
{
public:
	/// Constructeur par d�faut.
	balayage180etapeFinale(NoeudRobot * contexte);
	/// Destructeur.
	~balayage180etapeFinale();
	/// Effectuer un comportement.
	void executerComportement();
private:
	///Le robot en question.
	NoeudRobot * contexte_;

};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////