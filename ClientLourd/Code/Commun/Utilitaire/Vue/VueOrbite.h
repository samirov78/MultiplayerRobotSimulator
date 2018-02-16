//////////////////////////////////////////////////////////////////////////////
/// @file VueOrbite.h
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUEORBITE_H__
#define __UTILITAIRE_VUEORBITE_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionPerspective.h"

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class VueOrtho
	/// @brief Classe concrète de vue orthogonale.
	///
	/// Cette classe implante le comportement attendu d'une vue orthogonale.
	///
	/// @author Martin Bisson
	/// @date 2006-12-16
	////////////////////////////////////////////////////////////////////////
	class VueOrbite : public Vue
	{
	public:
		// Constructeur.
		VueOrbite(Camera const& camera, ProjectionPerspective const& projection, bool vuePremierePersonne);

		/// Obtention de la projection.
		virtual const ProjectionPerspective& obtenirProjection() const;
		/// Application de la projection.
		virtual void appliquerProjection() const;
		/// Application de la caméra.
		virtual void appliquerCamera() const;

		/// Modification de la clotûre.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax);

		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Zoom in élastique.
		virtual void zoomerInElastique(const glm::ivec2& pointMin,
			const glm::ivec2& pointMax);
		/// Zoom out élastique.
		virtual void zoomerOutElastique(const glm::ivec2& pointMin,
			const glm::ivec2& pointMax);

		/// Déplacement dans le plan XY par rapport à la vue.
		virtual void deplacerXY(double deplacementX, double deplacementY);
		/// Déplacement dans le plan XY par rapport à la vue.
		virtual void deplacerXY(const glm::ivec2& deplacement);
		/// Déplacement selon l'axe des Z par rapport à la vue.
		virtual void deplacerZ(double deplacement);
		/// Deplacement de la fenetre virtuelle avec la touche Haut.
		virtual void deplacerFenetreVirtuelleClavierHaut();
		/// Deplacement de la fenetre virtuelle avec la touche Bas.
		virtual void deplacerFenetreVirtuelleClavierBas();
		/// Deplacement de la fenetre virtuelle avec la touche Gauche.
		virtual void deplacerFenetreVirtuelleClavierGauche();
		/// Deplacement de la fenetre virtuelle avec la touche Droite.
		virtual void deplacerFenetreVirtuelleClavierDroite();
		///Deplacement de la vue avec la souris
		virtual void deplacerSouris(glm::dvec3 variationSouris, int x, int y);
		/// Rotation selon les axes des X et des Y par rapport à la vue.
		virtual void rotaterXY(double rotationX, double rotationY);
		/// Rotation selon les axes des X et des Y par rapport à la vue.
		virtual void rotaterXY(const glm::ivec2& rotation);
		/// Rotation selon l'axe des Z par rapport à la vue.
		virtual void rotaterZ(double rotation);

	private:
		/// Projection utilisée pour cette vue.
		ProjectionPerspective projection_;

		bool vuePremierePersonne_;
	};


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUEORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
