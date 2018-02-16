///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"

#include <map>
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui repr�sente l'arbre de rendu sp�cifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilis�s par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par d�faut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu � son �tat initial.
   void initialiser();

	/// La cha�ne repr�sentant le type des araign�es.
   static const std::string NOM_ARAIGNEE;
	/// La cha�ne repr�sentant le type des cones-cubes.
   static const std::string NOM_CONECUBE;
   /// La cha�ne repr�sentant le type du robot.
   static const std::string NOM_ROBOT;
   /// La cha�ne repr�sentant le type de la table.
   static const std::string NOM_TABLE;
   /// La cha�ne repr�sentant le type de la fl�che de d�part.
   static const std::string NOM_FLECHE;
   /// La cha�ne repr�sentant le type du poteau.
   static const std::string NOM_POTEAU;
   /// La cha�ne repr�sentant le type du mur.
   static const std::string NOM_MUR;
   /// La cha�ne repr�sentant le type de la ligne.
   static const std::string NOM_LIGNE;
   /// La cha�ne repr�sentant le type du segment de ligne.
   static const std::string NOM_SEGMENT;
   /// La cha�ne repr�sentant le type de la roue gauche du robot.
   static const std::string NOM_ROUE_GAUCHE;
   /// La cha�ne repr�sentant le type de la roue droite du robot.
   static const std::string NOM_ROUE_DROITE;

   // permet de verifier 
   bool chargerFichierXMl_{ false };
};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
