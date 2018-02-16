///////////////////////////////////////////////////////////////////////////////
/// @file NoeudComposite.h
/// @author DGI-INF2990
/// @date 2016-02-15
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__
#define __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__


#include "NoeudAbstrait.h"
#include "profil.h"
#include <vector>
#include "Debug.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudComposite
/// @brief Implantation d'un noeud du patron composite qui peut posséder
///        des enfants.
///
///        Cette classe implante les différentes fonctions relatives aux
///        enfants, comme l'ajout, le retrait, la recherche, etc.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudComposite : public NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudComposite(
		const std::string& type = std::string{ "" }
      );
   /// Destructeur.
   virtual ~NoeudComposite();

   // appliquer l'algorithme sur tous les noeuds 
   virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

   // Interface d'un noeud

   /// Calcule la profondeur de l'arbre sous le noeud courant.
   virtual unsigned int calculerProfondeur() const;

   /// Vide le noeud de ses enfants.
   virtual void vider();
   /// Efface le noeud passé en paramètre.
   virtual void effacer( const NoeudAbstrait* noeud );

   /// Cherche un noeud par le type (sur un noeud constant).
   virtual const NoeudAbstrait* chercher( const std::string& typeNoeud ) const;
   /// Cherche un noeud par le type.
   virtual NoeudAbstrait* chercher( const std::string& typeNoeud );
   /// Cherche un noeud enfant selon l'indice (sur un noeud constant).
   virtual const NoeudAbstrait* chercher( unsigned int indice ) const;
   /// Cherche un noeud enfant selon l'indice.
   virtual NoeudAbstrait* chercher( unsigned int indice );

   /// Ajoute un noeud enfant.
   virtual bool ajouter( NoeudAbstrait* enfant );
   /// Obtient le nombre d'enfants du noeud.
   virtual unsigned int obtenirNombreEnfants() const;

   // Changer la sélection du noeud: on prend la version de la classe de
   // base.
   // virtual void inverserSelection();
   /// Efface les enfants sélectionnés.
   virtual void effacerSelection();
   /// Efface les enfants avec IDS sélectionnés.
   virtual void effacerIDSelectionnes(char * id);
   /// Efface les enfants fantomes.
   virtual void effacerFantome();
   /// Sélectionne tous les enfants de même que le noeud.
   virtual void selectionnerTout();
   /// Désélectionne tous les enfants de même que le noeud.
   virtual void deselectionnerTout();
   ///virtual void deselectIfSameColor(NoeudAbstrait & noeud);
   /// Vérifier si le noeud ou un de ses enfants est sélectionné.
   virtual bool selectionExiste() const;

   /// Change le mode d'affichage des polygones.
   virtual void changerModePolygones( bool estForce );
   /// Assigne le mode d'affichage des polygones.
   virtual void assignerModePolygones( GLenum modePolygones );
   // Affiche le noeud: on prend la version de la classe de base.
   // virtual void afficher() const;
   /// Affiche le noeud de manière concrète.
   virtual void afficherConcret(const bool& attribuerCouleur) const;
   /// Anime le noeud.
   virtual void animer( float dt );
   ///Methode permettant le retour des enfants dans l'arbre de rendu.
   virtual std::vector<NoeudAbstrait*> * obtenirEnfants(){ return &enfants_; };

   /// verifier si la noeud est dans la table
   virtual bool estDansLaTableApresDeplacement(glm::dvec3 deplacement);
   /// verifier si le noeud est dans la table 
   virtual bool estDansLaTableApresScale(double scale);
   ///Methode permettant de verifier si un objet est toujours sur la table.
   bool estDansLaTable();
   bool dansLaTableSiSelectionne();
   bool objetsSelectionnesSurLaTable();
   ///Methode permettant d'initialiser les donnees d'un objet en traitement.
   void initialiserEnTraitement();
   ///Methode permettant d'actionner les moteurs du robot dans une certaine direction avec un certain rapport de vitesse pour les roues.
   virtual void actionnerMoteurs(const double& rapportVitesseGauche, const double& rapportVitesseDroit, const Direction& direction){};
   ///Methode permettant d'arreter les moteurs.
   virtual void stopperMoteurs(){};
   ///Getters des points des capteurs
   virtual glm::dvec2 obtenirP2CapteurSecuritaireDroit() { return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP2CapteurSecuritaireMilieu() { return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP2CapteurSecuritaireGauche() { return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP2CapteurDangerDroit() { return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP2CapteurDangerMilieu(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP2CapteurDangerGauche(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP1CapteurDangerDroit(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP1CapteurDangerMilieu(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP1CapteurDangerGauche(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP3CapteurSecuritaireDroit(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP3CapteurSecuritaireMilieu(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP3CapteurSecuritaireGauche(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP3CapteurDangerDroit(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP3CapteurDangerMilieu(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP3CapteurDangerGauche(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP4CapteurDangerDroit(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP4CapteurDangerMilieu(){ return glm::dvec2(0.0); };
   virtual glm::dvec2 obtenirP4CapteurDangerGauche(){ return glm::dvec2(0.0); };
   ///Setters des attributs de detection des capteurs.
   virtual void setDetectionSecuritaireDroit(const bool& detection) {};
   virtual void setDetectionSecuritaireMilieu(const bool& detection) {};
   virtual void setDetectionSecuritaireGauche(const bool& detection) {};
   virtual void setDetectionDangerDroit(const bool& detection) {};
   virtual void setDetectionDangerMilieu(const bool& detection) {};
   virtual void setDetectionDangerGauche(const bool& detection) {};
   ///Getters des attributs representant les etats d'activiter
   virtual bool obtenirEtatCapteurDroit() { return true; };
   virtual bool obtenirEtatCapteurMilieu() { return true; };
   virtual bool obtenirEtatCapteurGauche() { return true; };
   ///Methode permettant de verifier si une ligne est detecter ou non.
	virtual void ligneTouchee(glm::dvec3 point, bool& estTouche);
   ///Setters des longueur des zones securitaire et danger des differents capteurs.
   virtual void setLongueurDangerCapteurDroit(const double& longueur) {};
   virtual void setLongueurSecuritaireCapteurDroit(const double& longueur) {};
   virtual void setLongueurDangerCapteurMilieu(const double& longueur) {};
   virtual void setLongueurSecuritaireCapteurMilieu(const double& longueur) {};
   virtual void setLongueurDangerCapteurGauche(const double& longueur) {};
   virtual void setLongueurSecuritaireCapteurGauche(const double& longueur) {};
   ///Getters des etats de detection des zones securitaire et danger des differents capteurs.
   virtual bool getEtatCapteurSecuritaireDroit(){ return false; };
   virtual bool getEtatCapteurDangerDroit(){ return false; };
   virtual bool getEtatCapteurSecuritaireMilieu() { return false; }
   virtual bool getEtatCapteurDangerMilieu() { return false; };
   virtual bool getEtatCapteurSecuritaireGauche() { return false; }
   virtual bool getEtatCapteurDangerGauche() { return false; };
   ///Methode permettant le chargement d'un profil.
   virtual void chargerProfil(char* nomProfil){};
   ///Methode permettant le chargement d'un profil de debugage.
   virtual void chargerDebug(char* nomFichier){};
   ///Methode permettant l'obtention du profil de debugage.
   virtual Debug* obtenirDebug(){ return nullptr; };
   ///Methode permettant l'obtention du profil.
   virtual Profil* obtenirProfil() { return nullptr; };
   ///Methode permettant l'obtention de l'affichage debugage ou non.
   //virtual bool obtenirAffichageDebougage() { return false; };
   ///Methode permettant l'assignation de l'affichage debugage correspondant au suivi de ligne.
   virtual void setAffichageDebogageSuiviLigne(const bool& booleen) {};
   ///Methode permettant l'assignation de l'etat actuelle a un enum pour des fins de debugage a la console.
   virtual void setEtat(const ETATS& etat) {};
   ///methode permettant l'assignation de l'affichage debugage des capteurs de distance.
   virtual void setAffichageDebogageCapteurDangerDroit(const bool& booleen) {};
   virtual void setAffichageDebogageCapteurDangerMilieu(const bool& booleen) {};
   virtual void setAffichageDebogageCapteurDangerGauche(const bool& booleen) {};
   virtual void setAffichageDebogageCapteurSecuritaireDroit(const bool& booleen) {};
   virtual void setAffichageDebogageCapteurSecuritaireMilieu(const bool& booleen) {};
   virtual void setAffichageDebogageCapteurSecuritaireGauche(const bool& booleen) {};
   /// fonction qui permet d'attribuer la couleur de selection a chaque noeud
   virtual void attribuerCouleurSelection();
   virtual void setCustomSelectColor(int R, int G, int B);
   /// permet de modifier l'etat de l'attribut assigner visite
   virtual void assignerEstVisite(const bool& estVisite);

protected:
   /// Le choix du conteneur pour les enfants.
	using conteneur_enfants = std::vector<NoeudAbstrait*>;
   /// La liste des enfants.
   conteneur_enfants enfants_;


private:
   /// Constructeur copie déclaré privé mais non défini pour éviter le
   /// constructeur copie généré par le compilateur.
   NoeudComposite(const NoeudComposite&);

};




#endif // __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
