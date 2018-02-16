////////////////////////////////////////////////
/// @file   NoeudComposite.cpp
/// @author DGI-2990
/// @date   2007-01-25
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudComposite.h"

#include <cassert>
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudComposite::accepterVisiteur(VisiteurAbstrait& visiteur)
///
/// appliquer l'algorithme de visite sur le noeud courant
///
/// @param[in] type   VisiteurAbstrait        : un visiteur
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////

void NoeudComposite::accepterVisiteur(VisiteurAbstrait* visiteur){
	
	for (unsigned int i = 0; i < obtenirNombreEnfants(); i++)
	{
		enfants_[i]->accepterVisiteur(visiteur);
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudComposite::NoeudComposite(const std::string& type)
///
/// Ne fait qu'appeler la version de la classe de base.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudComposite::NoeudComposite(
	const std::string& type //= std::string{ "" }
	) :
	NoeudAbstrait{ type }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudComposite::~NoeudComposite()
///
/// Destructeur qui détruit tous les enfants du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudComposite::~NoeudComposite()
{
	vider();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudComposite::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 de plus que la profondeur de son
/// enfants le plus profond.
///
/// @return La profondeur de l'arbre sous ce noeud.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudComposite::calculerProfondeur() const
{
	unsigned int profondeurEnfantMax{ 0 };

	for (NoeudAbstrait const* enfant : enfants_)
	{
		const unsigned int profondeurEnfant{ enfant->calculerProfondeur() };
		if (profondeurEnfantMax < profondeurEnfant)
			profondeurEnfantMax = profondeurEnfant;
	}

	return profondeurEnfantMax + 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.  Elle effectue une
/// itération prudente sur les enfants afin d'être assez robuste pour
/// supporter la possibilité qu'un enfant en efface un autre dans son
/// destructeur, par exemple si deux objets ne peuvent pas exister l'un
/// sans l'autre.  Elle peut toutefois entrer en boucle infinie si un
/// enfant ajoute un nouveau noeud lorsqu'il se fait effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::vider()
{
	// L'itération doit être faite ainsi pour éviter les problèmes lorsque
	// le desctructeur d'un noeud modifie l'arbre, par exemple en retirant
	// d'autres noeuds.  Il pourrait y avoir une boucle infinie si la
	// desctruction d'un enfant entraînerait l'ajout d'un autre.
	while (!enfants_.empty()) {
		NoeudAbstrait* enfantAEffacer{ enfants_.front() };
		enfants_.erase(enfants_.begin());
		delete enfantAEffacer;
	}

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::effacer( const NoeudAbstrait* noeud )
///
/// Efface un noeud qui est un enfant ou qui est contenu dans un des
/// enfants.
///
/// @param[in] noeud : Le noeud à effacer.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::effacer(const NoeudAbstrait* noeud)
{
	for (conteneur_enfants::iterator it{ enfants_.begin() };
		it != enfants_.end();
		it++) {
		if (*it == noeud) {
			// On a trouvé le noeud à effacer
			NoeudAbstrait* noeudAEffacer{ (*it) };
			enfants_.erase(it);
			delete noeudAEffacer;
			return;
		}
		else {
			// On cherche dans les enfants.
			(*it)->effacer(noeud);
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudComposite::chercher( const std::string& typeNoeud ) const
///
/// Recherche un noeud d'un type donné parmi le noeud courant et ses
/// enfants.  Version constante de la fonction.
///
/// @param[in] typeNoeud : Le type du noeud cherché.
///
/// @return Noeud recherché ou 0 si le noeud n'est pas trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudComposite::chercher(
	const std::string& typeNoeud
	) const
{
	if (typeNoeud == type_) {
		return this;
	}
	else {
		for (NoeudAbstrait const* enfant : enfants_)
		{
			NoeudAbstrait const* noeud{ enfant->chercher(typeNoeud) };
			if (noeud != nullptr) {
				return noeud;
			}
		}
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudComposite::chercher( const std::string& typeNoeud )
///
/// Recherche un noeud d'un type donné parmi le noeud courant et ses
/// enfants.
///
/// @param[in] typeNoeud : Le type du noeud cherché.
///
/// @return Noeud recherché ou 0 si le noeud n'est pas trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudComposite::chercher(const std::string& typeNoeud)
{
	if (typeNoeud == type_) {
		return this;
	}
	else {
		for (NoeudAbstrait * enfant : enfants_)
		{
			NoeudAbstrait * noeud{ enfant->chercher(typeNoeud) };
			if (noeud != nullptr) {
				return noeud;
			}
		}
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudComposite::chercher( unsigned int indice ) const
///
/// Retourne le i-ème enfant, où i est l'indice passé à la fonction.
/// Version constante de la fonction.
///
/// @param[in] indice : L'indice de l'enfant cherché.
///
/// @return Noeud recherché ou 0 si le noeud n'est pas trouvé.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudComposite::chercher(unsigned int indice) const
{
	if ((indice >= 0) && (indice < enfants_.size())) {
		return enfants_[indice];
	}
	else {
		return nullptr;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudComposite::chercher( unsigned int indice )
///
/// Retourne le i-ème enfant, où i est l'indice passé à la fonction.
///
/// @param[in] indice : L'indice de l'enfant cherché.
///
/// @return Noeud recherché ou 0 si le noeud n'est pas trouvé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudComposite::chercher(unsigned int indice)
{
	if ((indice >= 0) && (indice < enfants_.size())) {
		return enfants_[indice];
	}
	else {
		return nullptr;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::ajouter( NoeudAbstrait* enfant )
///
/// Ajoute un noeud enfant au noeud courant.
///
/// @param[in] enfant: Noeud à ajouter.
///
/// @return Vrai si l'ajout a réussi, donc en tout temps pour cette classe.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::ajouter(NoeudAbstrait* enfant)
{
	enfant->assignerParent(this);
	enfants_.push_back(enfant);

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudComposite::obtenirNombreEnfants() const
///
/// Retourne le nombre d'enfants directement sous ce noeud.  Elle ne
/// donne pas le nombre total de descendants, mais bien le nombre de
/// ceux qui sont directement sous ce noeud.
///
/// @return Le nombre d'enfants directement sous ce noeud.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudComposite::obtenirNombreEnfants() const
{
	// La taille ne doit jamais être négative, sinon le cast plus bas
	// donnera un résultat erroné.
	assert(enfants_.size() >= 0);

	return static_cast<unsigned int> (enfants_.size());
}

void NoeudComposite::effacerIDSelectionnes(char * id)
{
	// On efface tous les noeuds sélectionnés descendants des enfants.
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->effacerIDSelectionnes(id);
	}

	// On efface les enfants sélectionnés.  On effectue ce traitement
	// dans une seconde boucle pour éviter de faire des assomptions
	// sur la robustesse des itérateurs lorsque le conteneur est
	// modifié pendant une itération.

	for (conteneur_enfants::iterator it{ enfants_.begin() };
		it != enfants_.end();
		) {
		if ((*it)->estSelectionne() && (*it)->obtenirType() != "fleche") {
			if ((*it)->ID == id)
			{
				NoeudAbstrait* enfant{ (*it) };
				enfants_.erase(it);
				delete enfant;

				// On ramène l'itération au début de la boucle, car le destructeur
				// de l'enfant pourrait éventuellement avoir retiré d'autres
				// enfants de l'arbre, ce qui briserait l'itération.  Pourrait
				// éventuellement être évité avec des itérateurs plus robustes.
				// Peut-être une liste chaînée?
				it = enfants_.begin();
			}
		}
		else {
			++it;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::effacerSelection()
///
/// Efface tous les noeuds sélectionnés situés sous ce noeud.  Elle
/// s'appelle donc récursivement sur tous les enfants, avant de retirer
/// les enfants sélectionnés.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::effacerSelection()
{
	// On efface tous les noeuds sélectionnés descendants des enfants.
	for (NoeudAbstrait * enfant : enfants_){
		enfant->effacerSelection();
	}

	// On efface les enfants sélectionnés.  On effectue ce traitement
	// dans une seconde boucle pour éviter de faire des assomptions
	// sur la robustesse des itérateurs lorsque le conteneur est
	// modifié pendant une itération.
	for (conteneur_enfants::iterator it{ enfants_.begin() };
		it != enfants_.end();
		) {
		if ((*it)->estSelectionne() && (*it)->obtenirType() != "fleche") {
			NoeudAbstrait* enfant{ (*it) };
			enfants_.erase(it);
			delete enfant;

			// On ramène l'itération au début de la boucle, car le destructeur
			// de l'enfant pourrait éventuellement avoir retiré d'autres
			// enfants de l'arbre, ce qui briserait l'itération.  Pourrait
			// éventuellement être évité avec des itérateurs plus robustes.
			// Peut-être une liste chaînée?
			it = enfants_.begin();
		}
		else {
			++it;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::effacerFantome()
///
/// Efface tous les noeuds fantomes situés sous ce noeud.  Elle
/// s'appelle donc récursivement sur tous les enfants, avant de retirer
/// les enfants fantomes.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::effacerFantome()
{
	// On efface tous les noeuds fantomes descendants des enfants.
	for (NoeudAbstrait * enfant : enfants_){
		enfant->effacerFantome();
	}

	// On efface les enfants fantomes.  On effectue ce traitement
	// dans une seconde boucle pour éviter de faire des assomptions
	// sur la robustesse des itérateurs lorsque le conteneur est
	// modifié pendant une itération.
	for (conteneur_enfants::iterator it{ enfants_.begin() };
		it != enfants_.end();
		) {
		if ((*it)->estFantome()) {
			NoeudAbstrait* enfant{ (*it) };
			enfants_.erase(it);
			delete enfant;

			// On ramène l'itération au début de la boucle, car le destructeur
			// de l'enfant pourrait éventuellement avoir retiré d'autres
			// enfants de l'arbre, ce qui briserait l'itération.  Pourrait
			// éventuellement être évité avec des itérateurs plus robustes.
			// Peut-être une liste chaînée?
			it = enfants_.begin();
		}
		else {
			++it;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::selectionnerTout()
///
/// Sélectionne tous les noeuds qui sont sélectionnés parmis les
/// les descendants de ce noeud, lui-même étant inclus.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::selectionnerTout()
{
	//NoeudAbstrait::selectionnerTout();
	assignerSelection(true);
	for (NoeudAbstrait * enfant : enfants_){
		enfant->selectionnerTout();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::deselectionnerTout()
///
/// Désélectionne tous les noeuds qui sont sélectionnés parmis les
/// les descendants de ce noeud, lui-même étant inclus.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::deselectionnerTout()
{
	
	selectionne_ = false;
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->deselectionnerTout();
	}
}

//void NoeudComposite::deselectIfSameColor(NoeudAbstrait & noeud)
//{
//	std::cout << "appel de deselectIfSameColor" << std::endl;
//	for (NoeudAbstrait * enfant : enfants_) {
//		if (enfant->couleurSelection_[0] == noeud.couleurSelection_[0] && enfant->couleurSelection_[1] == noeud.couleurSelection_[1]
//			&& enfant->couleurSelection_[2] == noeud.couleurSelection_[2])
//		{
//			enfant->deselectionnerTout();
//		}
//	}
//}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::selectionExiste() const
///
/// Vérifie si le noeud ou un de ses descendants est sélectionné en
/// s'appelant de manière récursive sur les enfants du noeud.
///
/// @return Vrai s'il existe un noeud sélectionné, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::selectionExiste() const
{
	bool reponse = false;
	if (selectionne_) {
		reponse = true;
	}

	for (NoeudAbstrait const* enfant : enfants_){
		if (enfant->selectionExiste())
			reponse = true;
	}

	return reponse;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::changerModePolygones( bool estForce )
///
/// Change le mode d'affichage des polygones pour ce noeud et ses
/// enfants.
///
/// @param[in] estForce : Si vrai, le mode est changé pour ce noeud et
///                       tous ses descendants.  Sinon, seuls les noeuds
///                       sélectionnés verront leur mode changer.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::changerModePolygones(bool estForce)
{
	NoeudAbstrait::changerModePolygones(estForce);
	const bool forceEnfant = ((estForce) || (estSelectionne()));

	// Applique le changement récursivement aux enfants.
	for (NoeudAbstrait * enfant : enfants_){
		enfant->changerModePolygones(forceEnfant);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud et
/// de ses enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::assignerModePolygones(GLenum modePolygones)
{
	// Appel à la version de la classe de base.
	NoeudAbstrait::assignerModePolygones(modePolygones);

	// Applique le changement récursivement aux enfants.
	for (NoeudAbstrait * enfant : enfants_){
		enfant->assignerModePolygones(modePolygones);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.  Elle est
/// appelée par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// Pour cette classe, elle affiche chacun des enfants du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::afficherConcret(const bool& attribuerCouleur) const
{
	NoeudAbstrait::afficherConcret(attribuerCouleur);

	for (NoeudAbstrait const* enfant : enfants_){
		enfant->afficher(attribuerCouleur);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::animer( float dt )
///
/// Anime tous les enfants de ce noeud.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::animer(float dt)
{
	try
	{
		for (NoeudAbstrait * enfant : enfants_) {
			enfant->animer(dt);
		}
	}
	catch (...)
	{
		;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::estDansLaTableApresDeplacement(glm::dvec3 deplacement)
///
/// Cette fonction permet de verifier si le noeud est sur la table apres
/// l'application d'un deplacement.
///
/// @param[in] deplacement : Coordonnees xyz de deplacement de l'objet
///
/// @return Vrai si l'objet le noeud est sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::estDansLaTableApresDeplacement(glm::dvec3 deplacement)
{
	bool reponse = true;;
	for (NoeudAbstrait * enfant : enfants_)
	{
		if (enfant->estDansLaTableApresDeplacement(deplacement) == false)
			reponse = false;
	}
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::estDansLaTableApresScale(double scale)
///
/// Cette fonction permet de verifier si le noeud est sur la table apres
/// l'application d'un redimensionnement.
///
/// @param[in] scale : Facteur de redimensionnement du noeud.
///
/// @return Vrai si l'objet le noeud est sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::estDansLaTableApresScale(double scale)
{
	bool reponse = true;
	for (NoeudAbstrait * enfant : enfants_)
	{
		if (enfant->estDansLaTableApresScale(scale) == false)
			reponse = false;
	}
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::estDansLaTable()
///
/// Cette fonction permet de verifier si le noeud est sur la table.
///
/// @return Vrai si l'objet le noeud est sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::estDansLaTable()
{
	bool reponse = true;
	for (NoeudAbstrait * enfant : enfants_)
	{
		if (!enfant->estDansLaTable())
			reponse = false;
	}
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::dansLaTableSiSelectionne()
///
/// Cette fonction permet de verifier si le noeud est selectionne et sur la table.
///
/// @return Vrai si le noeud est selectionne et sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::dansLaTableSiSelectionne()
{
	bool reponse = true;
	for (NoeudAbstrait * enfant : enfants_)
	{
		if (!enfant->dansLaTableSiSelectionne())
			reponse = false;
	}
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::objetsSelectionnesSurLaTable()
///
/// Cette fonction permet de verifier si les noeud selectionne sont sur la table.
///
/// @return Vrai si les objets sont sur la table, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::objetsSelectionnesSurLaTable()
{
	bool reponse = true;
	for (NoeudAbstrait * enfant : enfants_)
	{
		if (!enfant->dansLaTableSiSelectionne())
			reponse = false;
	}
	return reponse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::initialiserEnTraitement()
///
/// Cette fonction permet d'initialiser des donnees correspondant au noeud
/// en traitement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::initialiserEnTraitement()
{
	for (NoeudAbstrait * enfant : enfants_)
	{
		enfant->initialiserEnTraitement();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::ligneTouchee(glm::dvec3 point, bool& estTouche) 
///
/// Vérifie si le point touche le noeud présent, s'il est une ligne.
///
/// @param[in] point : Les coordonnées du point
/// @param[out] estTouche : Vrai si le point touche la ligne, faux sinon
///
/// @return aucune
///
////////////////////////////////////////////////////////////////////////

void NoeudComposite::ligneTouchee(glm::dvec3 point, bool& estTouche)
{
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->ligneTouchee(point, estTouche);
	}
}


void NoeudComposite::attribuerCouleurSelection()
{
	NoeudAbstrait::attribuerCouleurSelection();
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->attribuerCouleurSelection();
	}
}

void NoeudComposite::setCustomSelectColor(int R, int G, int B)
{
	NoeudAbstrait::setCustomSelectColor(R, G, B);
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->setCustomSelectColor(R, G, B);
	}
}

void NoeudComposite::assignerEstVisite(const bool& estVisite)
{
	NoeudAbstrait::assignerEstVisite(estVisite);
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->assignerEstVisite(estVisite);
	}
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
