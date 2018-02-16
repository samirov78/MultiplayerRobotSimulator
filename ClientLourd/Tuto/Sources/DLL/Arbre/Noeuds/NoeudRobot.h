///////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.h
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#pragma once

#include "NoeudComposite.h"
#include "GL/glew.h"
#include "VisiteurAbstrait.h"
#include <memory>
#include "FacadeModele.h"
#include "../../Comportement/ComportementTypes.h"
#include "../../Configuration/Profil.h"
#include "../../Configuration/Debug.h"
#include <time.h>
#include <chrono>
#include "son.h"

namespace vue {
	class Vue;
}

/// Type de collisions possibles avec le robot
enum TypeCollision {
	AUCUNE = 0,
	AVANT,
	AVANT_DROIT,
	AVANT_GAUCHE,
	ARRIERE_DROIT,
	ARRIERE_GAUCHE,
	ARRIERE
};

/// Objet en collision possible avec le robot
enum ObjetCollision {
	AUCUN = 0,
	POTEAU,
	MUR_VISIBLE,
	MUR_INVISIBLE
};
///Les differents etat de deplacement du robot.
enum EtatDeplacement{
	AVANCER = 0,
	RECULER,
	AVANCER_ANGLE_REFLEXION,
	RECULER_ANGLE_REFLEXION
};
///Coefficient de friction du robot.
const int COEFF_FRICTION = 2;
///Decompte deblocage max du robot.
const int DECOMPT_DEBLOCAGE_MAX = 3;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudRobot
/// @brief Classe qui représente le robot du premier projet intégrateur.
///
/// @author Martin Paradis
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudRobot : public NoeudComposite
{
public:
	///Constructeur defaut.
	NoeudRobot();
	///destructeur.
	~NoeudRobot();
	/// Constructeur du noeud robot.
	NoeudRobot(const std::string& typeNoeud);

	/// Affiche le robot.
	virtual void afficherConcret(const bool& attribuerCouleur) const;

	//animer
	void animer(float dt);
	//virtual bool estDansLaTable();

	/// Mouvements du robot
	void avancer(float dt);
	void reculer(float dt);
	void virerAvG(float dt);
	void virerAvD(float dt);
	void virerArG(float dt);
	void virerArD(float dt);
	void seDeplacer(float dt);

	/// Accesseurs du suiveur de ligne de cytron
	glm::dvec3 obtenirSenseurDeLigneExtremeGauche()const;
	glm::dvec3 obtenirSenseurDeLigneGauche()const;
	glm::dvec3 obtenirSenseurDeLigneCentral()const;
	glm::dvec3 obtenirSenseursDeLigneDroite()const;
	glm::dvec3 obtenirSenseurDeLigneExtremeDroite()const;

	//mettre a jour les positions des 5 senseurs
	void mettreAJourSenseurs();
	//mettre a jour la detection des senseurs
	bool mettreAjourDetectionsenseurs();
	//Obtenir le nombre de senseurs actifs
	int obtenirNombreSenseursActifs();

	/// Détecteur des senseurs du suiveur de ligne
	bool verifierSenseurs();
	bool estDetecteSenseurDeLigneExtremeGauche()const { return senseurDeLigneExtremeGaucheDetecte_; };
	bool estDetecteSenseurDeLigneGauche()const { return senseurDeLigneGaucheDetecte_; };
	bool estDetecteSenseurDeLigneCentral()const { return senseurDeLigneCentralDetecte_; };
	bool estdetecteSenseursDeLigneDroite()const{ return senseursDeLigneDroiteDetecte_; };
	bool estDetecteSenseurDeLigneExtremeDroite()const{ return senseurDeLigneExtremeDroiteDetecte_; };

	/// changer l'etat d'un senseur
	void assignerSenseurDeLigneExtremeGauche(bool senseur){ senseurDeLigneExtremeGaucheDetecte_ = senseur; };
	void assignerSenseurDeLigneGauche(bool senseur){ senseurDeLigneGaucheDetecte_ = senseur; };
	void assignerSenseurDeLigneCentral(bool senseur){ senseurDeLigneCentralDetecte_ = senseur; };
	void assignerSenseurDeLigneDroite(bool senseur){ senseursDeLigneDroiteDetecte_ = senseur; };
	void assignerSenseurDeLigneExtremeDroite(bool senseur){ senseurDeLigneExtremeDroiteDetecte_ = senseur; };

	/// Vitesse du robot
	float obtenirVitesseMaximale() const;
	float obtenirVitesse() const;
	void reglerVitesse();
	/// Affichage des capteurs de distance
	void afficherCapteursDistances() const;
	/// Setters / getteurs capteurs distances
	///Scrutation capteurs
	void mettreAJourPointsCapteurs() const;

	virtual NoeudAbstrait* getRoueDroite(){ return roueDroite_; };
	virtual NoeudAbstrait* getRoueGauche(){ return roueGauche_; };
	virtual void setRoueDroite(NoeudAbstrait* noeudRoue){ roueDroite_ = noeudRoue; };
	virtual void setRoueGauche(NoeudAbstrait* noeudRoue){ roueGauche_ = noeudRoue; };
	virtual void actionnerMoteurs(const double& rapportVitesseGauche, const double& rapportVitesseDroit, const Direction& direction);
	virtual void arreterMoteurs();

	glm::dvec2 coordonneesParRapportAOrigine(glm::dvec2 point, glm::dvec2 positionOrigine, double theta) const;
	///Getters des points des capteurs
	virtual glm::dvec2 obtenirP2CapteurSecuritaireDroit() { return p2CapteurSecuritaireDroit_; };
	virtual glm::dvec2 obtenirP2CapteurSecuritaireMilieu() { return p2CapteurSecuritaireMilieu_; };
	virtual glm::dvec2 obtenirP2CapteurSecuritaireGauche() { return p2CapteurSecuritaireGauche_; };
	virtual glm::dvec2 obtenirP2CapteurDangerDroit() { return p2CapteurDangerDroit_; };
	virtual glm::dvec2 obtenirP2CapteurDangerMilieu() { return p2CapteurDangerMilieu_; };
	virtual glm::dvec2 obtenirP2CapteurDangerGauche() { return p2CapteurDangerGauche_; };
	virtual glm::dvec2 obtenirP1CapteurDangerDroit() { return p1CapteurDangerDroit_; };
	virtual glm::dvec2 obtenirP1CapteurDangerMilieu() { return p1CapteurDangerMilieu_; };
	virtual glm::dvec2 obtenirP1CapteurDangerGauche() { return p1CapteurDangerGauche_; };
	virtual glm::dvec2 obtenirP3CapteurSecuritaireDroit() { return p3CapteurSecuritaireDroit_; };
	virtual glm::dvec2 obtenirP3CapteurSecuritaireMilieu() { return p3CapteurSecuritaireMilieu_; };
	virtual glm::dvec2 obtenirP3CapteurSecuritaireGauche() { return p3CapteurSecuritaireGauche_; };
	virtual glm::dvec2 obtenirP3CapteurDangerDroit() { return p3CapteurDangerDroit_; };
	virtual glm::dvec2 obtenirP3CapteurDangerMilieu() { return p3CapteurDangerMilieu_; };
	virtual glm::dvec2 obtenirP3CapteurDangerGauche() { return p3CapteurDangerGauche_; };
	virtual glm::dvec2 obtenirP4CapteurDangerDroit() { return p4CapteurDangerDroit_; };
	virtual glm::dvec2 obtenirP4CapteurDangerMilieu() { return p4CapteurDangerMilieu_; };
	virtual glm::dvec2 obtenirP4CapteurDangerGauche() { return p4CapteurDangerGauche_; };
	///Setters des attributs de detection des capteurs.
	virtual void setDetectionSecuritaireDroit(const bool& detection) { estDetecteSecuritaireDroit_ = detection; };
	virtual void setDetectionSecuritaireMilieu(const bool& detection) { estDetecteSecuritaireMilieu_ = detection; };
	virtual void setDetectionSecuritaireGauche(const bool& detection) { estDetecteSecuritaireGauche_ = detection; };
	virtual void setDetectionDangerDroit(const bool& detection) { estDetecteDangerDroit_ = detection;};
	virtual void setDetectionDangerMilieu(const bool& detection) { estDetecteDangerMilieu_ = detection; };
	virtual void setDetectionDangerGauche(const bool& detection) { estDetecteDangerGauche_ = detection; };
	///Getters des etats de detection des zones securitaire et danger des differents capteurs.
	virtual bool getEtatCapteurSecuritaireDroit(){ return estDetecteSecuritaireDroit_; };
	virtual bool getEtatCapteurDangerDroit(){ return estDetecteDangerDroit_; };
	virtual bool getEtatCapteurSecuritaireMilieu() { return estDetecteSecuritaireMilieu_; }
	virtual bool getEtatCapteurDangerMilieu() { return estDetecteDangerMilieu_; };
	virtual bool getEtatCapteurSecuritaireGauche() { return estDetecteSecuritaireGauche_; }
	virtual bool getEtatCapteurDangerGauche() { return estDetecteDangerGauche_; };

	///Permet l'affichage du type de collision et de l'objet en collision.
	void afficherTypeEtObjetCollision(TypeCollision type, ObjetCollision objet);
	///Met a jours les parametres du robot en tenant compte d'un certain dt.
	void mettreAjourParametres(float dt);
	///Met a jours la boite englobante du robot.
	void mettreAjourBteEnglobante();
	///Boite englobante du robot.
	utilitaire::BteEnglobanteRobot* bteEnglobante_{nullptr};
	///Visiteur verifiant les collisions du robot.
	VisiteurAbstrait* visiteurVerifierCollision_{nullptr};
	//comportements du robot
	void definirComportement(ComportementAbstrait * comportement) { comportementCourant_ = comportement; };
	void interpreterComportement() { comportementCourant_->executerComportement(); };
	///Type de collision du robot.
	TypeCollision typeCollision_;
	///Objet avec lequel le robot est en collision.
	ObjetCollision objetCollision_;

	/// permet de charger le bon profil et de mettre a jour le profil courant 
	void chargerProfil(char* nomProfil);
	///Methode permettant le retour du profil.
	Profil * getProfil(){ return profil_; };
	///Methode permettant l'assignation de l'angle de rotation initial du robot.
	void setangleRotationInitial(double angle){ angleRotationInitial_ = angle; };
	///Methode permettant l'obtention de l'angle de rotation initial du robot.
	double getAngleRotationInitial(){ return angleRotationInitial_; };
	///Methode permettant l'assignation d'un booleen suivi de ligne ou non au robot.
	void setDoitSuivre(bool doit){ doitSuivre_ = doit; };
	///Methode permettant l'obtention d'un booleen represent si le robot doit suivre ou non la ligne.
	bool getDoitSuivre(){ return doitSuivre_; };
	///Reinitialise le temps d'attente du robot.
	void resetTempsAttente() { attenteAvantChanger_ = time(0); }

	/// Temps initial de l'etat d'evitement
	time_t getTempsDebut() { return tempsDebut_; };
	///Methode permettant l'assignation du temps initial.
	void setTempsDebut(time_t time) { tempsDebut_ = time; };
	///Methode permettant l'obtention de l'etat d'attente du robot.
	bool getDoitAttendre() { return attente_; };
	///Methode permettant l'obtention du comportement du robot.
	ComportementAbstrait * getComportement(ETATS etat);
	///Mode automatique du robot.
	bool modeAutomatique_{ false };
	///Methode permettant l'obtention du profil de debugage.
	virtual Debug* obtenirDebug(){ return debug_; };
	///Methodes permettant l'activation des differents mode de lumiere.
	void basculerActivationLumiereAmbiante(std::string log);
	void basculerActivationLumiereDirectionnelle(std::string log);
	void basculerActivationSpots(std::string log);
	///Methode permettant l'activation de l'affichage console de debugage ou non.
	void basculerActivationDebougage();
	///Methode permettant l'obtention du comportement courant du robot.
	ComportementAbstrait * getComportementCourant() { return comportementCourant_; };
	///Methode permettant de changer le comportement du robot lors de la rencontre d'un obstacle.
	void changerComportementsObstacles();
	///Methode permettant l'obtention du profil.
	Profil* obtenirProfil() { return profil_; };
	///Methode permettant l'assignation de l'affichage debugage du suivi de ligne.
	void setAffichageDebogageSuiviLigne(const bool& booleen) { flipFlopSuiviLigne_ = booleen; };
	///Methode permettant d'assigner l'etat actuelle du robot pour des fins d'affichage debugage a la console.
	virtual void setEtat(const ETATS& etat) { etatExecuter_ = etat; };
	///methode permettant l'assignation de l'affichage debugage des capteurs de distance.
	virtual void setAffichageDebogageCapteurDangerDroit(const bool& booleen) { flipFlopCapteurDangerDroit_ = booleen; };
	virtual void setAffichageDebogageCapteurDangerMilieu(const bool& booleen) { flipFlopCapteurDangerMilieu_ = booleen; };
	virtual void setAffichageDebogageCapteurDangerGauche(const bool& booleen) { flipFlopCapteurDangerGauche_ = booleen; };
	virtual void setAffichageDebogageCapteurSecuritaireDroit(const bool& booleen) { flipFlopCapteurSecuritaireDroit_ = booleen; };
	virtual void setAffichageDebogageCapteurSecuritaireMilieu(const bool& booleen) { flipFlopCapteurSecuritaireMilieu_ = booleen; };
	virtual void setAffichageDebogageCapteurSecuritaireGauche(const bool& booleen) { flipFlopCapteurSecuritaireGauche_ = booleen; };
	///Methode permettant la verification d'une detection ou non d'un obstacle.
	bool obstacleDetecte() {
		return estDetecteDangerDroit_ && estDetecteDangerMilieu_ && estDetecteDangerGauche_
			&& estDetecteSecuritaireDroit_ && estDetecteSecuritaireMilieu_ && estDetecteSecuritaireGauche_;};

	bool getSpotsActives(){ return spotsActives_; };
	bool getModeAutomatique(){ return modeAutomatique_; };
	///Methode permettant l'obtention de la vue première personne.
	vue::Vue* obtenirVuePremierePersonne()
	{
		return vuePremierePersonneRobot_;
	}

	bool sonTourner_ = false;
	bool sonMoteur_ = false;
	/// permet de jouer le son 
	void jouerSon(int i);
	/// permet de mettre en pause le son
	void pauseSon(int i, bool pause);
	/// permet de mettre a jour le son
	void mettreAjourSon();
	Son * son_;
	/// permet d'appliquer les sons des moteurs
	void appliquerSonMoteurs();
	/// permet d'obtenir la position du spot
	glm::dvec3 getPositionSpot_() { return positionSpot_; };
private:
	///Coefficient de fiction du robot.
	int coefficientFriction_ = COEFF_FRICTION;
	///Active le rebond ou non du robot.
	bool activerRebond_ = false;
	///Angle de rotation du robot.
	double angleRotation_{ 0.0 };
	///Angle de rotation initial du robot.
	double angleRotationInitial_{ 0.0 };
	///Angle de correction du robot.
	double angleCorrection_{ 0.0 };
	///increment de l'angle de rotation du robot.
	double incrAngleRotation_{ 0.0 };
	///Variation du rapport de vitesse du robot.
	double deltaRapportVitesse_{ 0.0 };
	///Rayon de rotation du robot.
	double rayonRotation_{ 0.0 };
	///Angle de reflexion du robot.
	double angleReflexion_{ 0.0 };
	///Force des moteurs du robot.
	double forceMoteurs_{ 0.0 };
	///Decompteur de deblocage du robot.
	int decompteurDeblocage_{ DECOMPT_DEBLOCAGE_MAX };
	///Dernier etat de deplacement du robot.
	EtatDeplacement dernierDeplacement_;
	///Bloque ou debloque le controle du robot.
	bool debloquerControle_{ true };
	///Compteur de temps du robot.
	int compteurTemps_{ 0 };
	///Coeffecient de correction du rayon du robot.
	double coefCorrecRayon_{ 1.0 };
	///Noeud representant la roue droite du robot.
	NoeudAbstrait* roueDroite_{ nullptr };
	///Noeud representant la roue gauche du robot.
	NoeudAbstrait* roueGauche_{ nullptr };

	

	/// Modélisation Suiveur de ligne
	glm::dvec3 senseurDeLigneExtremeGauche_;
	glm::dvec3 senseurDeLigneGauche_;
	glm::dvec3 senseurDeLigneCentral_;
	glm::dvec3 senseursDeLigneDroite_;
	glm::dvec3 senseurDeLigneExtremeDroite_;



	/// Détecteurs senseurs de ligne
	bool senseurDeLigneExtremeGaucheDetecte_{ false };
	bool senseurDeLigneGaucheDetecte_{ false };
	bool senseurDeLigneCentralDetecte_{ false };
	bool senseursDeLigneDroiteDetecte_{ false };
	bool senseurDeLigneExtremeDroiteDetecte_{ false };

	///Detection d'objet dans zone des capteurs
	bool estDetecteSecuritaireDroit_{ false };
	bool estDetecteSecuritaireMilieu_{ false };
	bool estDetecteSecuritaireGauche_{false};
	bool estDetecteDangerDroit_{ false };
	bool estDetecteDangerMilieu_{false};
	bool estDetecteDangerGauche_{false};
	//p2 et p1
	mutable glm::dvec2 p2CapteurSecuritaireDroit_; 
	mutable glm::dvec2 p2CapteurSecuritaireMilieu_; 
	mutable glm::dvec2 p2CapteurSecuritaireGauche_; 
	mutable glm::dvec2 p2CapteurDangerDroit_; 
	mutable glm::dvec2 p2CapteurDangerMilieu_; 
	mutable glm::dvec2 p2CapteurDangerGauche_; 
	mutable glm::dvec2 p1CapteurDangerDroit_; 
	mutable glm::dvec2 p1CapteurDangerMilieu_; 
	mutable glm::dvec2 p1CapteurDangerGauche_; 
	//p3 et p4
	mutable glm::dvec2 p3CapteurSecuritaireDroit_; 
	mutable glm::dvec2 p3CapteurSecuritaireMilieu_; 
	mutable glm::dvec2 p3CapteurSecuritaireGauche_; 
	mutable glm::dvec2 p3CapteurDangerDroit_; 
	mutable glm::dvec2 p3CapteurDangerMilieu_; 
	mutable glm::dvec2 p3CapteurDangerGauche_; 
	mutable glm::dvec2 p4CapteurDangerDroit_; 
	mutable glm::dvec2 p4CapteurDangerMilieu_; 
	mutable glm::dvec2 p4CapteurDangerGauche_; 
	///Comportement courant du robot.
	ComportementAbstrait * comportementCourant_{nullptr};
	///Profil du robot.
	Profil * profil_{ nullptr };
	///Profil de debugage du robot.
	Debug* debug_;

	///Temps de debut du robot.
	time_t tempsDebut_; //startTime
	///Temps de la derniere detection du robot.
	time_t DerniereDetection_;
	///Temps de la derniere intersection du robot avec une ligne.
	time_t derniereIntersection_;
	///Temps d'attente du robot avant de changer de comportement.
	time_t attenteAvantChanger_;
	///Booleen representant l'attente ou non du robot.
	bool attente_ = false;
	///Booleen representant si le robot doit suivre ou non la ligne.
	bool doitSuivre_;
	///Booleen representant la detection des capteurs lignes.
	bool DernierdetecteGauche_ = false;
	bool DernierdetecteDroite_ = false;
	///
	std::chrono::time_point < std::chrono::system_clock > TempsInitial_;
	std::chrono::duration<double> tempsPasse_;
	///Booleen representant si la lumiere ambiante est activee ou non.
	bool lumiereAmbianteActivee_;
	///Booleen representant si la lumiere directionnelle est activee.
	bool lumiereDirectionnelleActivee_;
	///Booleen representant si le spot est activer ou non.
	bool spotsActives_;
	///Variables booleenne utiliser pour des fins d'affichage debugage console.
	bool flipFlopSuiviLigne_{ true };
	bool flipFlopCapteurDangerDroit_{ true };
	bool flipFlopCapteurDangerMilieu_{ true };
	bool flipFlopCapteurDangerGauche_{ true };
	bool flipFlopCapteurSecuritaireDroit_{ true };
	bool flipFlopCapteurSecuritaireMilieu_{ true };
	bool flipFlopCapteurSecuritaireGauche_{ true };
	///Contient l'etat actuelle executer par le robot pour des fins d'affichage debugage console.
	ETATS etatExecuter_;
	
	vue::Vue* vuePremierePersonneRobot_{ nullptr }; // camera sensée faire

	// position de vise de la camera
	glm::dvec3 pointViseCamera_{ glm::dvec3(0.18, -15.5, -10.0) };
	glm::dvec3 positionCamera_{ glm::dvec3(0.18, -15.5, -10.0) };
	glm::dvec3 positionSpot_{ glm::dvec3(0.0, -4.0, 40.0) };
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
