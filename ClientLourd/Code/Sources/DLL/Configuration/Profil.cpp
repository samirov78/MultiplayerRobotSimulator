////////////////////////////////////////////////////////////////////////////////////
/// @file Profil.cpp
/// @author INF2990 Eq.11
/// @date 2016-03-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Profil.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn Profil::Profil()
///
/// Constructeur d'un objet Profil.
///
/// @param : Aucun.
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
Profil::Profil()
{
	char* nomFichier = "données/profils.xml";
	ElementXML elementXML;

	if (!utilitaire::fichierExiste(nomFichier)) {
		std::cout << "le fichier profils.xml n'est pas accessible" << std::endl;
	}
	else
	{
		tinyxml2::XMLDocument document;

		// Lire à partir du fichier de profils
		document.LoadFile(nomFichier);

		// obtenir le premier noeud 'profils'
		const tinyxml2::XMLElement* elementProfils = document.FirstChildElement();

		if (elementProfils != nullptr)
		{
			char* profilActif = (char*)elementProfils->Attribute("actif");
			chargerProfil(profilActif);
			_profilActif = profilActif;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ETATS Profil::convertirEtatXML(std::string etat)
///
/// Methode permettant de convertir ce qui est ecrit dans le fichier xml
/// en Etat.
///
/// @param[in] etat: chaine de caractere representant les etats de comportement.
///
/// @return Un enum representant l'etat du robot.
///
////////////////////////////////////////////////////////////////////////
ETATS Profil::convertirEtatXML(std::string etat)
{
	if (etat.compare("suivi-ligne") == 0)
		return SUIVI_LIGNE;
	if (etat.compare("balayage") == 0)
		return BALAYAGE_180ETAPE1;
	if (etat.compare("deviation-droite") == 0)
		return DEVIATION_DROITE;
	if (etat.compare("deviation-gauche") == 0)
		return DEVIATION_GAUCHE;
	if (etat.compare("eviter-droite") == 0)
		return EVITER_DROITE;
	if (etat.compare("eviter-gauche") == 0)
		return EVITER_GAUCHE;
	return DEFAUT;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Profil::convertirActivation(std::string etat)
///
/// Methode permettant de convertir les options activer en XML.
///
/// @param[in] etat: chaine de caractere representant les etats actif ou inactif.
///
/// @return Vrai si actif, faux sinon.
///
////////////////////////////////////////////////////////////////////////
bool Profil::convertirActivation(std::string etat)
{
	if (&etat == nullptr)
	{
		return true;
	}
	if (etat.compare("actif") == 0)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Profil::chargerProfil(char* nomProfil)
///
/// Methode permettant de charger un profil.
///
/// @param[in] nomProfil: chaine de caractere representant le nom du profil.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void Profil::chargerProfil(char* nomProfil)
{
	char* nomFichier = "données/profils.xml";
	ElementXML elementXML;

	// // Vérification de l'existance du ficher
	if (!utilitaire::fichierExiste(nomFichier)) {
		std::cout << "le fichier profils.xml n'est pas accessible" << std::endl;
	}
	// si le fichier existe on le lit
	else
	{
		tinyxml2::XMLDocument document;

		// Lire à partir du fichier profils
		document.LoadFile(nomFichier);

		// Tenter d'obtenir le noeud 'profils'
		const tinyxml2::XMLElement* elementProfils{ document.FirstChildElement("profils") };
		// verifier qu'il existe bien un balise profils et commencer a boucler sur ses enfants 
		if (elementProfils != nullptr)
		{
			for (const tinyxml2::XMLElement* elementXMLCourantLecture_ = elementProfils->FirstChildElement();
				elementXMLCourantLecture_ != NULL;
				elementXMLCourantLecture_ = elementXMLCourantLecture_->NextSiblingElement())
			{
				const char* typeNoeud;
				typeNoeud = elementXMLCourantLecture_->Value();
				
				const char* nomProfilLu = elementXMLCourantLecture_->ToElement()->Attribute("nom");
				_profilActif = nomProfilLu;

				if (strcmp(nomProfilLu, nomProfil) == 0 )
				{
					_suivantSuiviLigne = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_SUIVI_LIGNE));
					//std::cout << "Suivant suivi ligne : " << _suivantSuiviLigne << std::endl;
					
					_suivantBalayage = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_BALAYAGE));
					//std::cout << "Suivant balayage : " << _suivantBalayage << std::endl;

					_suivantDeviationDroite = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_DEVIATION_DROITE));
					//std::cout << "Suivant Devitaion Droite : " << _suivantDeviationDroite << std::endl;

					_angleDeviationDroite = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.ANGLE_DEVIATION_DROITE));
					//std::cout << "angle Devitaion Droite : " << _angleDeviationDroite << std::endl;

					_suivantDeviationGauche = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_DEVIATION_GAUCHE));
					//std::cout << "Suivant Devitaion Gauche : " << _suivantDeviationGauche << std::endl;

					_angleDeviationGauche = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.ANGLE_DEVIATION_GHAUCHE));
					//std::cout << "angle Devitaion gauche : " << _angleDeviationGauche << std::endl;

					_suivantEviterDroite = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_EVITER_DROITE));
					//std::cout << "Suivant eviter droite : " << _suivantEviterDroite << std::endl;

					_anglePivotementDroite = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.ANGLE_PIVOTEMENT_DROITE));
					//std::cout << "Angle Pivotement Droite : " << _anglePivotementDroite << std::endl;

					_dureeReculDroite = std::stoi(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.DUREE_RECUL_DROITE));
					//std::cout << "Duree Recul Droite : " << _dureeReculDroite << std::endl;

					_suivantEviterGauche = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_EVITER_GAUCHE));
					//std::cout << "Suivant Eviter Gauche : " << _suivantEviterGauche << std::endl;

					_anglePivotementGauche = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.ANGLE_PIVOTEMENT_GAUCHE));
					//std::cout << "Angle Pivotement Gauche : " << _anglePivotementGauche << std::endl;

					_dureeReculGauche = std::stoi(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.DUREE_RECUL_GAUCHE));
					//std::cout << "Duree Recul Gauche : " << _dureeReculGauche << std::endl;

					_suivantDangerCapteurG = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_DANGER_GAUCHE));
					//std::cout << "_suivantDangerCapteurG : " << _suivantDangerCapteurG << std::endl;

					_suivantSecuritaireCapteurG = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_SECURITAIRE_GAUCHE));
					//std::cout << "_suivantSecuritaireCapteurG : " << _suivantSecuritaireCapteurG << std::endl;

					longueurDangerCapteurGauche_ = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.LONGUEUR_DANGER_GHAUCHE));
					//std::cout << "longueurDangerCapteurGauche_ : " << longueurDangerCapteurGauche_ << std::endl;

					longueurSecuritaireCapteurGauche_ = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.LONGUEUR_SECURITAIRE_GHAUCHE));
					//std::cout << "longueurSecuritaireCapteurGauche_ : " << longueurSecuritaireCapteurGauche_ << std::endl;

					_suivantDangerCapteurM = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_DANGER_MILIEU));
					//std::cout << "_suivantDangerCapteurM : " << _suivantDangerCapteurM << std::endl;

					_suivantSecuritaireCapteurM = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_SECURITAIRE_MILIEU));
					//std::cout << "_suivantSecuritaireCapteurM : " << _suivantSecuritaireCapteurM << std::endl;

					longueurDangerCapteurMilieu_ = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.LONGUEUR_DANGER_MILIEU));
					//std::cout << "longueurDangerCapteurMilieu_ : " << longueurDangerCapteurMilieu_ << std::endl;

					longueurSecuritaireCapteurMilieu_ = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.LONGUEUR_SECURITAIRE_MILIEU));
					//std::cout << "longueurSecuritaireCapteurMilieu_ : " << longueurSecuritaireCapteurMilieu_ << std::endl;

					_suivantDangerCapteurD = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_DANGER_DROITE));
					//std::cout << "Suivant Danger Capteur D : " << _suivantDangerCapteurD << std::endl;

					_suivantSecuritaireCapteurD = convertirEtatXML(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVANT_SECURITAIRE_DROITE));
					//std::cout << "Suivant Danger Capteur G : " << _suivantDangerCapteurG << std::endl;

					longueurDangerCapteurDroit_ = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.LONGUEUR_DANGER_DROITE));
					//std::cout << "longueurDangerCapteurDroit_ : " << longueurDangerCapteurDroit_ << std::endl;

					longueurSecuritaireCapteurDroit_ = std::stod(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.LONGUEUR_SECURITAIRE_DROITE));
					//std::cout << "longueurSecuritaireCapteurDroit_ : " << longueurSecuritaireCapteurDroit_ << std::endl;

					capteurGaucheActif_ = convertirActivation(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.CAPTEUR_GAUCHE));
					//std::cout << "capteurGaucheActif_ : " << capteurGaucheActif_ << std::endl;

					capteurDroitActif_ = convertirActivation(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.CAPTEUR_DROIT));
					//std::cout << "capteurDroitActif_ : " << capteurDroitActif_ << std::endl;

					capteurMilieuActif_ = convertirActivation(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.CAPTEUR_MILIEU));
					//std::cout << "capteurMilieuActif_ : " << capteurMilieuActif_ << std::endl;

					_suiveurLigneActif = convertirActivation(elementXMLCourantLecture_->ToElement()->Attribute(elementXML.SUIVEUR_LIGNE));
					//std::cout << "Suiveur Ligne Actif : " << _suiveurLigneActif << std::endl;

					return;
				}
			}
		}
	}
}