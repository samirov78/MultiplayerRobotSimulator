//////////////////////////////////////////////////////////////////////////////
/// @file Vue.h
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUE_H__
#define __UTILITAIRE_VUE_H__


#include "Camera.h"
#include <windows.h>

namespace math {
	class Plan3D;
}


namespace vue {


	class Projection;


	////////////////////////////////////////////////////////////////////////
	/// @class Vue
	/// @brief Classe pr�sentant l'interface commune � toutes les vues.
	///
	/// Cette classe d�finit l'interface que devront implanter chacune des
	/// vues, c'est-�-dire comme r�agir � certains �v�nements pour modifier
	/// la vue.  Chaque vue concr�te sera g�n�ralement compos�e d'une cam�ra
	/// (classe Camera) et d'une projection (classe Projection).
	///
	/// Elle offre �galement certaines fonctionnalit�s communes � toutes les
	/// vues, comme la possibilit� de trouver � quel point correspond, en
	/// coordonn�es virtuelles, un point donn� en coordonn�es de cl�ture.
	///
	/// @author Martin Bisson
	/// @date 2006-12-16
	////////////////////////////////////////////////////////////////////////
	class Vue
	{
	public:
		/// Constructeur � partir d'une cam�ra
		Vue(const Camera& camera);
		/// Destructeur virtuel vide.
		virtual ~Vue() {}

		/// Conversion de coordonn�es de cl�ture � coordonn�es virtuelles
		virtual bool convertirClotureAVirtuelle(int x, int y, glm::dvec3& point) const;
		/// Conversion de coordonn�es de cl�ture � coordonn�es virtuelles sur un plan donn�
		bool convertirClotureAVirtuelle(int x, int y, const math::Plan3D& plan, glm::dvec3& point) const;

		/// Obtient la cam�ra associ�e � cette vue.
		inline Camera& obtenirCamera();
		/// Obtient la cam�ra associ�e � cette vue (version constante).
		inline const Camera& obtenirCamera() const;


		// Obtention de la projection
		virtual const Projection& obtenirProjection() const = 0;
		/// Application de la projection
		virtual void appliquerProjection() const = 0;
		/// Application de la cam�ra
		virtual void appliquerCamera() const = 0;

		/// Modification de la clot�re
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax) = 0;

		/// Zoom in, c'est-�-dire un agrandissement.
		virtual void zoomerIn() = 0;
		/// Zoom out, c'est-�-dire un rapetissement.
		virtual void zoomerOut() = 0;
		/// Zoom in �lastique
		virtual void zoomerInElastique(const glm::ivec2& pointMin,
			const glm::ivec2& pointMax) = 0;
		/// Zoom out �lastique
		virtual void zoomerOutElastique(const glm::ivec2& pointMin,
			const glm::ivec2& pointMax) = 0;

		/// D�placement dans le plan XY par rapport � la vue
		virtual void deplacerXY(double deplacementX, double deplacementY) = 0;
		/// D�placement dans le plan XY par rapport � la vue
		virtual void deplacerXY(const glm::ivec2& deplacement) = 0;
		/// Deplacement de la fenetre virtuelle avec la touche haut.
		virtual void deplacerFenetreVirtuelleClavierHaut() = 0;
		/// Deplacement de la fenetre virtuelle avec la touche Bas.
		virtual void deplacerFenetreVirtuelleClavierBas() = 0;
		/// Deplacement de la fenetre virtuelle avec la touche Droite.
		virtual void deplacerFenetreVirtuelleClavierDroite() = 0;
		/// Deplacement de la fenetre virtuelle avec la touche Gauche.
		virtual void deplacerFenetreVirtuelleClavierGauche() = 0;
		///Deplacement de la vue avec la souris
		virtual void deplacerSouris(glm::dvec3 variationSouris, int x, int y) = 0;
		/// D�placement selon l'axe des Z par rapport � la vue
		virtual void deplacerZ(double deplacement) = 0;
		/// Rotation selon les axes des X et des Y par rapport � la vue
		virtual void rotaterXY(double rotationX, double rotationY) = 0;
		/// Rotation selon les axes des X et des Y par rapport � la vue
		virtual void rotaterXY(const glm::ivec2& rotation) = 0;
		/// Rotation selon l'axe des Z par rapport � la vue
		virtual void rotaterZ(double rotation) = 0;

		/// Animation de la vue en fonction du temps
		virtual void animer(double temps);

	protected:
		/// Cam�ra utilis�e pour cette vue
		Camera camera_;

	};


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline Camera& Vue::obtenirCamera()
	///
	/// Cette fonction retourne la cam�ra associ�e � cette vue.
	///
	/// @return La cam�ra associ�e � cet objet.
	///
	////////////////////////////////////////////////////////////////////////
	inline Camera& Vue::obtenirCamera()
	{
		return camera_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const Camera& Vue::obtenirCamera() const
	///
	/// Cette fonction retourne la cam�ra associ�e � cette vue (version
	/// constante).
	///
	/// @return La cam�ra associ�e � cet objet.
	///
	////////////////////////////////////////////////////////////////////////
	inline const Camera& Vue::obtenirCamera() const
	{
		return camera_;
	}


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
