///////////////////////////////////////////////////////////////////////////
/// @file Profil.h
/// @author equipe INF2990-11
/// @date 2016-03-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#pragma once

#include "tinyxml2.h"
#include "utilitaire.h"
#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class Profil
/// @brief Classe qui représente le profil a adopter par le robot 
///
/// @author equipe INF2990-11
/// @date 2016-03-11
///////////////////////////////////////////////////////////////////////////
///Differents etat de comportement.
enum ETATS
{
	DEFAUT = 0,
	DEVIATION_DROITE,
	DEVIATION_GAUCHE,
	EVITER_DROITE,
	EVITER_GAUCHE,
	SUIVI_LIGNE,
	SL_DEVIATION_DROITE,
	SL_DEVIATION_GAUCHE,
	BALAYAGE_180ETAPE1,
	BALAYAGE_180ETAPE2,
	BALAYAGE_180ETAPE3,
	ETAT_AVANCER,
	ETAT_FREEZE
	
};
///Elements xml present dans le profil.
class ElementXML
{
public:
	const char* PROFILS = "profils";
	const char* PROFIL = "profil";
	const char* NOM = "nom";
	const char* ACTIF = "actif";

	const char* SUIVANT_SUIVI_LIGNE = "suivant-suivi-ligne";
	const char* SUIVANT_BALAYAGE = "suivant-balayage";

	const char* SUIVANT_DEVIATION_DROITE = "suivant-deviation-droite";
	const char* ANGLE_DEVIATION_DROITE = "angle-deviation-droite";

	const char* SUIVANT_DEVIATION_GAUCHE = "suivant-deviation-gauche";
	const char* ANGLE_DEVIATION_GHAUCHE = "angle-deviation-gauche";

	const char* SUIVANT_EVITER_DROITE = "suivant-eviter-droite";
	const char* ANGLE_PIVOTEMENT_DROITE = "angle-pivotement-droite";
	const char* DUREE_RECUL_DROITE = "duree-recul-droite";

	const char* SUIVANT_EVITER_GAUCHE = "suivant-eviter-gauche";
	const char* ANGLE_PIVOTEMENT_GAUCHE = "angle-pivotement-gauche";
	const char* DUREE_RECUL_GAUCHE = "duree-recul-gauche";

	const char* SUIVANT_DANGER_GAUCHE = "suivant-danger-gauche";
	const char* SUIVANT_SECURITAIRE_GAUCHE = "suivant-securitaire-gauche";
	const char* LONGUEUR_DANGER_GHAUCHE = "longueur-danger-gauche";
	const char* LONGUEUR_SECURITAIRE_GHAUCHE = "longueur-securitaire-gauche";

	const char* SUIVANT_DANGER_MILIEU = "suivant-danger-milieu";
	const char* SUIVANT_SECURITAIRE_MILIEU = "suivant-securitaire-milieu";
	const char* LONGUEUR_DANGER_MILIEU = "longueur-danger-milieu";
	const char* LONGUEUR_SECURITAIRE_MILIEU = "longueur-securitaire-milieu";

	const char* SUIVANT_DANGER_DROITE = "suivant-danger-droite";
	const char* SUIVANT_SECURITAIRE_DROITE = "suivant-securitaire-droite";
	const char* LONGUEUR_DANGER_DROITE = "longueur-danger-droite";
	const char* LONGUEUR_SECURITAIRE_DROITE = "longueur-securitaire-droite";

	const char* CAPTEUR_GAUCHE = "capteur-gauche";
	const char* CAPTEUR_DROIT = "capteur-droit";
	const char* CAPTEUR_MILIEU = "capteur-milieu";
	const char* SUIVEUR_LIGNE = "suiveur-ligne";
};

class Profil
{
public:

	/// Constructeur du noeud robot.
	Profil();
	/// Destructeur.
	~Profil() = default;
	// permet de charger le bon profil
	void chargerProfil(char* nomProfil);

	/// quelques setteurs a completer s'il le faut 
	double getAngleDeviationDroite() { return _angleDeviationDroite; };
	double getAngleDeviationGauche() { return _angleDeviationGauche; };
	ETATS getSuivantDevGauche() { return _suivantDeviationGauche; };
	ETATS getSuivantDevDroite() { return _suivantDeviationDroite; }
	double getDureeEvitementGauche(){ return _dureeReculGauche; };
	double getDureeEvitementDroite(){ return _dureeReculDroite; };
	ETATS getSuivantEvitGauche() { return _suivantEviterGauche; };
	ETATS getSuivantEvitDroite() { return _suivantEviterDroite; };
	ETATS getSuivantSuiviLigne() { return _suivantSuiviLigne; };
	ETATS getSuivantBalayage() { return _suivantBalayage; };
	double getAnglePivoterDroite() { return _anglePivotementDroite; };
	double getAnglePivoterGauche() { return _anglePivotementGauche; };

	///les getters pour les comportements a executer apres detection par les capteurs
	ETATS getSuivantDangerG() { return _suivantDangerCapteurG; };
	ETATS getSuivantDangerM() { return _suivantDangerCapteurM; };
	ETATS getSuivantDangerD() { return _suivantDangerCapteurD; };
	ETATS getSuivantSecureG() { return _suivantSecuritaireCapteurG; };
	ETATS getSuivantSecureD() { return _suivantSecuritaireCapteurD; };
	ETATS getSuivantSecureM() { return _suivantSecuritaireCapteurM; };
	///Differentes longueurs des capteurs de distance.
	double longueurDangerCapteurDroit_;
	double longueurSecuritaireCapteurDroit_;
	double longueurDangerCapteurMilieu_;
	double longueurSecuritaireCapteurMilieu_;
	double longueurDangerCapteurGauche_;
	double longueurSecuritaireCapteurGauche_;
	///Booleen representant l'etat actif ou non d'un capteur.
	bool capteurDroitActif_;
	bool capteurMilieuActif_;
	bool capteurGaucheActif_;
	///Methode permettant l'obtention de l'etat actif ou non du suiveur de ligne.
	bool getSuiveurActif(){ return _suiveurLigneActif; };
	//std::string getProfilActif(){ return _profilActif; };
	std::string _profilActif;
private:

	// permet de convertit une valeur d'etat d'un element XML en chaine de caractere vers un etat enum ETATS
	ETATS convertirEtatXML(std::string etat);
	
	// permet de convertit l'etat d'activation en chaine de caractere vers un etat d'activation boolean
	bool convertirActivation(std::string etat);
	///Nom du profil actif.
	//std::string _profilActif;
	///Differents etats suivants.
	ETATS _suivantSuiviLigne;
	ETATS _suivantBalayage;
	ETATS _suivantDeviationDroite;
	ETATS _suivantDeviationGauche;
	ETATS _suivantEviterDroite;
	ETATS _suivantEviterGauche;
	ETATS _suivantDangerCapteurG;
	ETATS _suivantSecuritaireCapteurG;
	ETATS _suivantDangerCapteurM;
	ETATS _suivantSecuritaireCapteurM;
	ETATS _suivantDangerCapteurD;
	ETATS _suivantSecuritaireCapteurD;
	///Donnees de configuration de certains etats.
	double _angleDeviationDroite;
	double _angleDeviationGauche;
	double _anglePivotementDroite;
	double _dureeReculDroite;
	double _anglePivotementGauche;
	double _dureeReculGauche;
	///Booleen representant si le suiveur de ligne est actif ou non.
	bool _suiveurLigneActif;
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
