////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.cpp
/// @author equipe INF2990 
/// @date 2016-03-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Debug.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn Debug::Debug()
///
/// Constructeur d'un objet Debug.
///
/// @param: Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Debug::Debug()
{
	chargerParametresDebug();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::chargerParametresDebug()
///
/// Methode permettant le chargement des parametres de debug.
///
/// @param: Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::chargerParametresDebug()
{
	char* nomFichierConfig = "données/configuration.xml";
	// // Vérification de l'existance du ficher, Si le fichier n'existe pas, on le crée.
	if (!utilitaire::fichierExiste(nomFichierConfig)) {
		std::cout << "le fichier configuration.xml n'est pas accessible" << std::endl;
	}
	// si le fichier existe on le lit
	else
	{
		tinyxml2::XMLDocument document;

		// Lire à partir du fichier de configuration
		document.LoadFile(nomFichierConfig);

		// Tenter d'obtenir le noeud 'Configuration'
		const tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
		// verifier qu'il existe bien un balise configuration et commencer a boucler sur ses enfants 
		if (elementConfiguration != nullptr)
		{
			int compteur = 0;

			// ici on la balise controle
			const tinyxml2::XMLElement* elementXMLCourantLecture_ = elementConfiguration->FirstChildElement();
			// ici on la balise debougage
			elementXMLCourantLecture_ = elementXMLCourantLecture_->NextSiblingElement();

			for (const tinyxml2::XMLElement* elementXMLBoucleFOR_ = elementXMLCourantLecture_->FirstChildElement();
				elementXMLBoucleFOR_ != NULL;
				elementXMLBoucleFOR_ = elementXMLBoucleFOR_->NextSiblingElement())
			{
				compteur++;

		/*
		<console valeur="oui" changement-comportement="oui" activation-desactivation-eclairage="oui" />
		<alteration-effets-visuels valeur="oui" identification-zones-capteurs="oui" />
		*/
				// noeud console 
				if (strcmp(elementXMLBoucleFOR_->Value(), "console") == 0)
				{
					// std::cout << "if 1" << std::endl;
					const char* valeur = elementXMLBoucleFOR_->ToElement()->Attribute("valeur");

					if (strcmp(valeur, "oui") == 0)
					{
						sortieConsole_ = true;
					}
					else
					{
						sortieConsole_ = false;
					}
					
					valeur = elementXMLBoucleFOR_->ToElement()->Attribute("changement-comportement");
					if (strcmp(valeur, "oui") == 0)
						changementComportement_ = true;
					else
						changementComportement_ = false;

					valeur = elementXMLBoucleFOR_->ToElement()->Attribute("activation-desactivation-eclairage");
					if (strcmp(valeur, "oui") == 0)
						etatEclairage_ = true;
					else
						etatEclairage_ = false;
				}
				// neoud alteration-effets-visuels
				if (strcmp(elementXMLBoucleFOR_->Value(), "alteration-effets-visuels") == 0)
				{
					//std::cout << "if 2" << std::endl;
					const char* valeur = elementXMLBoucleFOR_->ToElement()->Attribute("valeur");
					if (strcmp(valeur, "oui") == 0)
						sortieAlterationEffetsVisuel_ = true;
					else
						sortieAlterationEffetsVisuel_ = false;

					valeur = elementXMLBoucleFOR_->ToElement()->Attribute("identification-zones-capteurs");
					if (strcmp(valeur, "oui") == 0)
						afficherDetectionCapteurs_ = true;
					else 
						afficherDetectionCapteurs_ = false;
				}
			}		
		}
	}
	/*std::cout << "sortieConsole => " << sortieConsole_ << std::endl;
	std::cout << "chargementComportement => " << changementComportement_ << std::endl;
	std::cout << "etatEclairage => " << etatEclairage_ << std::endl;
	std::cout << "sortieAlterationEffetVisuel => "<< sortieAlterationEffetsVisuel_ << std::endl;
	std::cout << "afficherCapteurs => " << afficherDetectionCapteurs_ << std::endl;*/
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool Debug::getSortieConsole()
///
/// Methode retournant la valeur de l'attribut sortieConsole_
///
/// @param: Aucun.
///
/// @return La valeur de sortieConsole_.
///
////////////////////////////////////////////////////////////////////////
bool Debug::getSortieConsole()
{
	return sortieConsole_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool Debug::getChangementComportement()
///
/// Methode retournant la valeur de l'attribut changementComportement_;
///
/// @param: Aucun.
///
/// @return La valeur de changementComportement_.
///
////////////////////////////////////////////////////////////////////////
bool Debug::getChangementComportement()
{
	return changementComportement_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool Debug::getEtatEclairage()
///
/// Methode retournant la valeur de l'attribut etatEclairage_;
///
/// @param: Aucun.
///
/// @return La valeur de etatEclairage_.
///
////////////////////////////////////////////////////////////////////////
bool Debug::getEtatEclairage()
{
	return etatEclairage_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool Debug::getSortieAlterationEffetsVisuel()
///
/// Methode retournant la valeur de l'attribut sortieAlterationEffetsVisuel_;
///
/// @param: Aucun.
///
/// @return La valeur de sortieAlterationEffetsVisuel_.
///
////////////////////////////////////////////////////////////////////////
bool Debug::getSortieAlterationEffetsVisuel()
{
	return sortieAlterationEffetsVisuel_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool Debug::getAfficherDetectionCapteurs()
///
/// Methode retournant la valeur de l'attribut afficherDetectionCapteurs_;
///
/// @param: Aucun.
///
/// @return La valeur de afficherDetectionCapteurs_.
///
////////////////////////////////////////////////////////////////////////
bool Debug::getAfficherDetectionCapteurs()
{
	return afficherDetectionCapteurs_;
}