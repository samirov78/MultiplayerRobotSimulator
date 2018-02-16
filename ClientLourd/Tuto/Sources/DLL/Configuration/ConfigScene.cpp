////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.cpp
/// @author Jean-Fran�ois P�russe
/// @date 2007-01-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigScene.h"
#include <iostream>


SINGLETON_DECLARATION_CPP(ConfigScene);

/// Nombre de calculs par image.
int ConfigScene::CALCULS_PAR_IMAGE{ 50 };


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::creerDOM ( TiXmlNode& node ) const
///
/// Cette fonction �crit les valeurs de la configuration dans un �l�ment XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::creerDOM ( tinyxml2::XMLDocument& document ) const
{
	// Cr�er le noeud 'configuration'
	tinyxml2::XMLElement* elementConfiguration{ document.NewElement("configuration") };
	
	// Cr�er le noeud scene et d�finir ses attributs
	tinyxml2::XMLElement* elementScene{ document.NewElement("CScene") };
	elementScene->SetAttribute("CALCULS_PAR_IMAGE", ConfigScene::CALCULS_PAR_IMAGE);
	
	// Adjoindre le noeud 'elementScene'
	elementConfiguration->LinkEndChild(elementScene);

	// Adjoindre le noeud 'configuration' au noeud principal
	// (Rappel : pas besoin de lib�rer la m�moire de elementConfiguration
	// puisque toutes les fonctions Link... le font pour nous)
	document.LinkEndChild(elementConfiguration);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::lireDOM( const TiXmlNode& node )
///
/// Cette fonction lit les valeurs de la configuration � partir d'un �l�ment
/// XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::lireDOM( const tinyxml2::XMLDocument& document )
{ /*
	int elementApresScene = 0;

	std::cout << "lireDOM en cours  " << std::endl;

	// Tenter d'obtenir le noeud 'Configuration'
	const tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
	if (elementConfiguration != nullptr) {
		// Tenter d'obtenir l'�l�ment CScene, puis l'attribut CALCULS_PAR_IMAGE
		std::cout << "le noeud configuration existe" << std::endl;
		const tinyxml2::XMLElement* elementScene{ elementConfiguration->FirstChildElement("CScene") };
		if (elementScene != nullptr) {
			std::cout << "le noeud scene existe" << std::endl;
			if (elementScene->QueryIntAttribute("CALCULS_PAR_IMAGE", &ConfigScene::CALCULS_PAR_IMAGE) != tinyxml2::XML_SUCCESS){
				std::cerr << "Erreur : CALCULS_PAR_IMAGE : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
			}
			
			// ajoute par Mehdi
			// http://stackoverflow.com/questions/15606842/getting-the-child-elements-in-tinyxml2

			// premier element apres l'element scene
			elementXMLCourantLecture_ = elementScene->FirstChildElement(); 

			while (elementXMLCourantLecture_ != NULL){
			// traitement du noeud courant et appel a l'usine du noeud en quesiton 

				// test 
				double x, y = 0;
				elementXMLCourantLecture_->QueryDoubleAttribute("Pos_x", &x);
				elementXMLCourantLecture_->QueryDoubleAttribute("Pos_y", &y);

				elementApresScene++;
				elementXMLCourantLecture_ = elementXMLCourantLecture_->FirstChildElement();
			}

			std::cout << "nombre elements = " << elementApresScene << std::endl;
		}
	}
	*/
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
