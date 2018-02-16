///////////////////////////////////////////////////////////////////////////////
/// @file AideCollision.cpp
/// @brief Ce fichier contient l'implantation de l'espace de nom aidecollision.
///
/// Il contient les implantations de fonctions utiles pour le calcul des forces
/// caus�es par les collisions.
///
/// @author Martin Bisson
/// @date 2007-01-10
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AideCollision.h"
#include "glm\gtx\norm.hpp"
#include "glm\gtx\projection.hpp"

namespace aidecollision {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn DetailsCollision calculerCollisionSegment(
	///        const glm::dvec2& point1,
	///        const glm::dvec2& point2,
	///        const glm::dvec2& position,
	///        double          rayon,
	///        bool            collisionAvecPoints
	///        );
	///
	/// Cette fonction calcule l'intersection d'un cercle, identifi� par son
	/// centre et son rayon, avec un segment de droite, identifi� par les 
	/// coordonn�es de chacune de ses extr�mit�s.
	///
	/// Elle ne fait qu'appeler la version 3D de cette m�me fonction.
	///
	/// @param[in] point1              : Premi�re extr�mit� du segment de
	///                                  droite.
	/// @param[in] point2              : Seconde extr�mit� du segment de
	///                                  droite.
	/// @param[in] position            : Centre du cercle.
	/// @param[in] rayon               : Rayon du cercle.
	/// @param[in] collisionAvecPoints : Vrai si on veut les collisions avec
	///                                  les extr�mit�s.
	///
	/// @return Structure contenant de l'information sur la collision.
	///
	////////////////////////////////////////////////////////////////////////
	DetailsCollision calculerCollisionSegment(
		const glm::dvec2& point1,
		const glm::dvec2& point2,
		const glm::dvec2& position,
		double          rayon,
		bool            collisionAvecPoints //= true
		)
	{
		return calculerCollisionSegment(
			glm::dvec3{ point1, 0.0 },
			glm::dvec3{ point2, 0.0 },
			glm::dvec3{ position, 0.0 },
			rayon,
			collisionAvecPoints
			);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn DetailsCollision calculerCollisionSegment(
	///        const glm::dvec3& point1,
	///        const glm::dvec3& point2,
	///        const glm::dvec3& position,
	///        double          rayon,
	///        bool            collisionAvecPoints
	///        );
	///
	/// Cette fonction calcule l'intersection d'une sph�re, identifi�e par son
	/// centre et son rayon, avec un segment de droite, identifi� par les 
	/// coordonn�es de chacune de ses extr�mit�s.
	///
	/// @param[in] point1              : Premi�re extr�mit� du segment de
	///                                  droite.
	/// @param[in] point2              : Seconde extr�mit� du segment de
	///                                  droite.
	/// @param[in] position            : Centre de la sph�re.
	/// @param[in] rayon               : Rayon de la sph�re.
	/// @param[in] collisionAvecPoints : Vrai si on veut les collisions avec
	///                                  les extr�mit�s.
	///
	/// @return Structure contenant de l'information sur la collision.
	///
	////////////////////////////////////////////////////////////////////////
	DetailsCollision calculerCollisionSegment(
		const glm::dvec3& point1,
		const glm::dvec3& point2,
		const glm::dvec3& position,
		double          rayon,
		bool            collisionAvecPoints //= true
		)
	{
		// Valeur de retour.
		DetailsCollision detailsCollision;
		detailsCollision.type = COLLISION_AUCUNE;

		// On calcule la projection de la position de la sph�re sur le vecteur
		// du segment de droite.
		const glm::dvec3 segment{ point2 - point1 };
		const double ratio = glm::dot(position - point1, segment) /
			glm::length2(segment);

		if (collisionAvecPoints) {
			if (ratio < 0.0) {
				// On est du c�t� du premier point.
				const glm::dvec3 directionCollision{ position - point1 };
				const double distance = glm::length(directionCollision);
				if (distance < rayon) {
					detailsCollision.type = COLLISION_SEGMENT_PREMIERPOINT;
					detailsCollision.direction = directionCollision / distance;
					detailsCollision.enfoncement = rayon - distance;
				}
			}
			else if (ratio > 1.0) {
				// On est du c�t� du second point.
				const glm::dvec3 directionCollision{ position - point2 };
				const double distance = glm::length(directionCollision);
				if (distance < rayon) {
					detailsCollision.type = COLLISION_SEGMENT_DEUXIEMEPOINT;
					detailsCollision.direction = directionCollision / distance;
					detailsCollision.enfoncement = rayon - distance;
				}
			}
		}

		if (ratio >= 0.0 && ratio <= 1.0) {
			// On est sur le segment de droite.
			glm::dvec3 pointPerpendiculaire{ (1 - ratio) * point1 + ratio * point2 };
			const glm::dvec3 directionCollision{ position - pointPerpendiculaire };
			const double distance{ glm::length(directionCollision) };
			if (distance < rayon) {
				detailsCollision.type = COLLISION_SEGMENT;
				detailsCollision.direction = directionCollision / distance;
				detailsCollision.enfoncement = rayon - distance;
			}
		}

		return detailsCollision;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn DetailsCollision calculerCollisionCercle(
	///        const glm::dvec2& centreCercle,
	///        double          rayonCercle,
	///        const glm::dvec2& positionObjet,
	///        double          rayonObjet
	///        );
	///
	/// Cette fonction calcule l'intersection d'un cercle avec un autre
	/// cercle, chacun identifi� par son centre et son rayon.
	///
	/// Elle ne fait qu'appeler la version 3D de cette m�me fonction.
	///
	/// @param[in] centreCercle  : Centre du cercle avec lequel on teste la
	///                            collision.
	/// @param[in] rayonCercle   : Rayon du cercle avec lequel on teste la
	///                            collision.
	/// @param[in] positionObjet : Position de l'objet peut-�tre en collision.
	/// @param[in] rayonObjet    : Rayon de l'objet peut-�tre en collision.
	///
	/// @return Structure contenant de l'information sur la collision.
	///
	////////////////////////////////////////////////////////////////////////
	DetailsCollision calculerCollisionCercle(
		const glm::dvec2& centreCercle,
		double          rayonCercle,
		const glm::dvec2& positionObjet,
		double          rayonObjet
		)
	{
		return calculerCollisionSphere(
			glm::dvec3{ centreCercle, 0.0 },
			rayonCercle,
			glm::dvec3{ positionObjet, 0.0 },
			rayonObjet
			);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn DetailsCollision calculerCollisionArc(
	///        const glm::dvec2& centreCercle,
	///        const glm::dvec2& pointArc1,
	///        const glm::dvec2& pointArc2,
	///        const glm::dvec2& positionObjet,
	///        double          rayonObjet
	///        );
	///
	/// Cette fonction calcule l'intersection d'un cercle identifi� par
	/// son centre et son rayon, avec un arc de cercle identifi� par ses
	/// deux extr�mit�s et son centre.
	///
	/// @param[in] centreCercle  : Centre de l'arc avec lequel on teste
	///                            la collision.
	/// @param[in] pointArc1     : Premi�re extr�mit� de l'arc avec lequel on
	///                            teste la collision.
	/// @param[in] pointArc2     : Seconde extr�mit� de l'arc avec lequel on
	///                            teste la collision.
	/// @param[in] positionObjet : Position de l'objet peut-�tre en collision.
	/// @param[in] rayonObjet    : Rayon de l'objet peut-�tre en collision.
	///
	/// @return Structure contenant de l'information sur la collision.
	///
	////////////////////////////////////////////////////////////////////////
	DetailsCollision calculerCollisionArc(
		const glm::dvec2& centreCercle,
		const glm::dvec2& pointArc1,
		const glm::dvec2& pointArc2,
		const glm::dvec2& positionObjet,
		double          rayonObjet
		)
	{
		// Valeur de retour.
		DetailsCollision detailsCollision;
		detailsCollision.type = COLLISION_AUCUNE;

		// Rayon de l'arc de cercle.
		double rayonCercle{ glm::length((pointArc1 - centreCercle)) };

		detailsCollision.direction = glm::dvec3(positionObjet - centreCercle, 0.0);
		detailsCollision.enfoncement = rayonCercle + rayonObjet -
			glm::length(detailsCollision.direction);

		if (detailsCollision.enfoncement > 0) {
			glm::dvec3 direction1{ (pointArc1 - centreCercle), 0.0 };
			glm::dvec3 direction2{ (pointArc2 - centreCercle), 0.0 };

			// On v�rifie si la direction est situ�e � l'int�rieur de l'arc �
			// l'aide de produits vectoriels.
			double sensExtremites{ glm::cross(direction1, direction2)[2] };
			double sens1{ glm::cross(direction1, detailsCollision.direction)[2] };
			double sens2{ glm::cross(detailsCollision.direction, direction2)[2] };

			if (((sens1 > 0.0) == (sensExtremites > 0.0)) &&
				((sens1 > 0.0) == (sens2 > 0.0))) {
				detailsCollision.type = COLLISION_ARC;
			}
		}

		return detailsCollision;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn DetailsCollision calculerCollisionSphere( const glm::dvec3& centreSphere, double rayonSphere, const glm::dvec3& positionObjet, double rayonObjet );
	///
	/// Cette fonction calcule l'intersection d'une sph�re avec une autre
	/// sph�re, chacune identifi�e par son centre et son rayon.
	///
	/// @param[in] centreSphere  : Centre de la sph�re avec laquelle on teste la
	///                            collision.
	/// @param[in] rayonSphere   : Rayon de la sph�re avec laquelle on teste la
	///                            collision.
	/// @param[in] positionObjet : Position de l'objet peut-�tre en collision.
	/// @param[in] rayonObjet    : Rayon de l'objet peut-�tre en collision.
	///
	/// @return Structure contenant de l'information sur la collision.
	///
	////////////////////////////////////////////////////////////////////////
	DetailsCollision calculerCollisionSphere(
		const glm::dvec3& centreSphere,
		double          rayonSphere,
		const glm::dvec3& positionObjet,
		double          rayonObjet
		)
	{
		// Valeur de retour
		DetailsCollision detailsCollision;

		detailsCollision.direction = positionObjet - centreSphere;
		detailsCollision.enfoncement = rayonSphere + rayonObjet -
			glm::length(detailsCollision.direction);

		if (detailsCollision.enfoncement > 0)
			detailsCollision.type = COLLISION_SPHERE;
		else
			detailsCollision.type = COLLISION_AUCUNE;

		return detailsCollision;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec2 calculerForceRebondissement2D(
	///        const DetailsCollision& details,
	///        double constanteRebondissement
	///        );
	///
	/// Cette fonction calcule la force caus�e par une collision � partir
	/// de la loi des ressorts qui stipule que la force est proportionnelle
	/// � une constante caract�risant le ressort (dans ce cas l'objet sur
	/// lequel on rebondit) et � l'�tirement ou la compression du ressort
	/// (dans ce cas l'enfoncement).
	///
	///
	/// @param[in] details                 : D�tails de la collision.
	/// @param[in] constanteRebondissement : Constante de rebondissement de
	///                                      l'objet.
	///
	/// @return Force caus�e par la collision, en deux dimensions.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec2 calculerForceRebondissement2D(
		const DetailsCollision& details,
		double constanteRebondissement
		)
	{
		if (details.type == COLLISION_AUCUNE) {
			// Pas de collision, donc pas de force
			return glm::dvec2{ 0, 0 };
		}
		else {
			// Collision: application de la loi des ressorts
			return details.enfoncement * constanteRebondissement *
				glm::dvec2{ details.direction };
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec3 calculerForceRebondissement3D(
	///        const DetailsCollision& details,
	///        double constanteRebondissement
	///        );
	///
	/// Cette fonction calcule la force caus�e par une collision � partir
	/// de la loi des ressorts qui stipule que la force est proportionnelle
	/// � une constante caract�risant le ressort (dans ce cas l'objet sur
	/// lequel on rebondit) et � l'�tirement ou la compression du ressort
	/// (dans ce cas l'enfoncement).
	///
	/// @param[in] details                 : D�tails de la collision.
	/// @param[in] constanteRebondissement : Constante de rebondissement de
	///                                      l'objet.
	///
	/// @return Force caus�e par la collision, en trois dimensions.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec3 calculerForceRebondissement3D(
		const DetailsCollision& details,
		double constanteRebondissement
		)
	{
		if (details.type == COLLISION_AUCUNE) {
			// Pas de collision, donc pas de force.
			return glm::dvec3{ 0, 0, 0 };
		}
		else {
			// Collision: application de la loi des ressorts.
			return details.enfoncement * constanteRebondissement *
				details.direction;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec2 calculerForceAmortissement2D(
	///        const DetailsCollision& details,
	///        const glm::dvec2& vitesse,
	///        double constanteAmortissement
	///        );
	///
	/// Cette fonction calcule une force d'amortissement proportionnelle �
	/// la vitesse et dans sa direction, caus�e par une collision.
	///
	/// Elle ne fait qu'appeler la version 3D de cette m�me fonction.
	///
	/// @param[in] details                : D�tails de la collision.
	/// @param[in] vitesse                : Vitesse de l'objet en collision.
	/// @param[in] constanteAmortissement : Constante d'amortissement de
	///                                     l'objet.
	///
	/// @return Force caus�e par la collision, en deux dimensions.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec2 calculerForceAmortissement2D(
		const DetailsCollision& details,
		const glm::dvec2& vitesse,
		double constanteAmortissement
		)
	{
		return glm::dvec2{ calculerForceAmortissement3D(
			details, glm::dvec3{ vitesse, 0.0 }, constanteAmortissement
			) };
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec3 calculerForceAmortissement3D(
	///        const DetailsCollision& details,
	///        const glm::dvec3& vitesse,
	///        double constanteAmortissement
	///        );
	///
	/// Cette fonction calcule une force d'amortissement proportionnelle �
	/// la vitesse et dans sa direction, caus�e par une collision.
	///
	/// @param[in] details                : D�tails de la collision.
	/// @param[in] vitesse                : Vitesse de l'objet en collision.
	/// @param[in] constanteAmortissement : Constante d'amortissement de
	///                                     l'objet.
	///
	/// @return Force caus�e par la collision, en trois dimensions.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec3 calculerForceAmortissement3D(
		const DetailsCollision& details,
		const glm::dvec3& vitesse,
		double constanteAmortissement
		)
	{
		if (details.type == COLLISION_AUCUNE) {
			// Pas de collision, donc pas de force.
			return glm::dvec3{ 0, 0, 0 };
		}
		else {
			// Collision: application d'un amortissement.
			const glm::dvec3 vitesseCollision{ glm::proj(vitesse, details.direction) };
			return vitesseCollision * -constanteAmortissement;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec2 calculerCollisionSegment(
	///        const glm::dvec2&   point1,
	///        const glm::dvec2&   point2,
	///        const glm::dvec2&   position,
	///        double            rayon,
	///        bool              collisionAvecPoints,
	///        double            constanteRebondissement,
	///        double            constanteAmortissement,
	///        const glm::dvec2&   vitesse,
	///        DetailsCollision* retourDetails = 0
	///        );
	///
	/// Cette fonction calcule la force caus�e par la collision d'un cercle,
	/// identifi� par son centre et son rayon, avec un segment de droite,
	/// identifi� par les coordonn�es de chacune de ses extr�mit�s.  Elle
	/// tient compte d'une force de rebondissement ainsi qu'une force
	/// d'amortissement.
	///
	/// Elle ne fait qu'appeler la version 3D de cette m�me fonction.
	///
	/// @param[in]  point1                  : Premi�re extr�mit� du segment de
	///                                       droite.
	/// @param[in]  point2                  : Seconde extr�mit� du segment de
	///                                       droite.
	/// @param[in]  position                : Centre du cercle.
	/// @param[in]  rayon                   : Rayon du cercle.
	/// @param[in]  collisionAvecPoints     : Vrai si on veut les collisions
	///                                       avec les extr�mit�s.
	/// @param[in]  constanteRebondissement : Constante de rebondissement de
	///                                       l'objet.
	/// @param[in]  constanteAmortissement  : Constante d'amortissement de
	///                                       l'objet.
	/// @param[in]  vitesse                 : Vitesse de l'objet en collision.
	/// @param[out] retourDetails           : Pointeur pour retourner les
	///                                       d�tails de la collision.
	///
	/// @return Force caus�e par la collision, en deux dimensions.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec2 calculerCollisionSegment(
		const glm::dvec2&   point1,
		const glm::dvec2&   point2,
		const glm::dvec2&   position,
		double            rayon,
		bool              collisionAvecPoints,
		double            constanteRebondissement,
		double            constanteAmortissement,
		const glm::dvec2&   vitesse,
		DetailsCollision* retourDetails //= 0
		)
	{
		return glm::dvec2(calculerCollisionSegment(
			glm::dvec3{ point1, 0.0 }, glm::dvec3{ point2, 0.0 },
			glm::dvec3{ position, 0.0 }, rayon,
			collisionAvecPoints,
			constanteRebondissement,
			constanteAmortissement,
			glm::dvec3{ vitesse, 0.0 },
			retourDetails
			));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec3 calculerCollisionSegment(
	///        const glm::dvec3&   point1,
	///        const glm::dvec3&   point2,
	///        const glm::dvec3&   position,
	///        double            rayon,
	///        bool              collisionAvecPoints,
	///        double            constanteRebondissement,
	///        double            constanteAmortissement,
	///        const glm::dvec3&   vitesse,
	///        DetailsCollision* retourDetails = 0
	///        );
	///
	/// Cette fonction calcule la force caus�e par la collision d'un cercle,
	/// identifi� par son centre et son rayon, avec un segment de droite,
	/// identifi� par les coordonn�es de chacune de ses extr�mit�s.  Elle
	/// tient compte d'une force de rebondissement ainsi qu'une force
	/// d'amortissement.
	///
	/// @param[in]  point1                  : Premi�re extr�mit� du segment de
	///                                       droite.
	/// @param[in]  point2                  : Seconde extr�mit� du segment de
	///                                       droite.
	/// @param[in]  position                : Centre du cercle.
	/// @param[in]  rayon                   : Rayon du cercle.
	/// @param[in]  collisionAvecPoints     : Vrai si on veut les collisions
	///                                       avec les extr�mit�s.
	/// @param[in]  constanteRebondissement : Constante de rebondissement de
	///                                       l'objet.
	/// @param[in]  constanteAmortissement  : Constante d'amortissement de
	///                                       l'objet.
	/// @param[in]  vitesse                 : Vitesse de l'objet en collision.
	/// @param[out] retourDetails           : Pointeur pour retourner les
	///                                       d�tails de la collision.
	///
	/// @return Force caus�e par la collision, en trois dimensions.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec3 calculerCollisionSegment(
		const glm::dvec3&   point1,
		const glm::dvec3&   point2,
		const glm::dvec3&   position,
		double            rayon,
		bool              collisionAvecPoints,
		double            constanteRebondissement,
		double            constanteAmortissement,
		const glm::dvec3&   vitesse,
		DetailsCollision* retourDetails //= 0
		)
	{
		DetailsCollision details = calculerCollisionSegment(
			point1, point2,
			position, rayon,
			collisionAvecPoints
			);

		glm::dvec3 force{ calculerForceRebondissement3D(
			details, constanteRebondissement
			) };
		force += calculerForceAmortissement3D(
			details, vitesse, constanteAmortissement
			);

		if (retourDetails)
			*retourDetails = details;

		return force;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec2 calculerCollisionCercle(
	///        const glm::dvec2&   centreCercle,
	///        double            rayonCercle,
	///        const glm::dvec2&   positionObjet,
	///        double            rayonObjet,
	///        double            constanteRebondissement,
	///        double            constanteAmortissement,
	///        const glm::dvec2&   vitesse,
	///        DetailsCollision* retourDetails = 0
	///        );
	///
	/// Cette fonction calcule la force caus�e par la collision d'un
	/// cercle avec un autre cercle, chacun identifi� par son centre
	/// et son rayon.  Elle tient compte d'une force de rebondissement
	/// ainsi qu'une force d'amortissement.
	///
	/// Elle ne fait qu'appeler la version 3D de cette m�me fonction.
	///
	/// @param[in]  centreCercle            : Centre du cercle avec lequel on
	///                                       teste la collision.
	/// @param[in]  rayonCercle             : Rayon du cercle avec lequel on
	///                                       teste la collision.
	/// @param[in]  positionObjet           : Position de l'objet peut-�tre en
	///                                       collision.
	/// @param[in]  rayonObjet              : Rayon de l'objet peut-�tre en
	///                                       collision.
	/// @param[in]  constanteRebondissement : Constante de rebondissement de
	///                                       l'objet.
	/// @param[in]  constanteAmortissement  : Constante d'amortissement de
	///                                       l'objet.
	/// @param[in]  vitesse                 : Vitesse de l'objet en collision.
	/// @param[out] retourDetails           : Pointeur pour retourner les
	///                                       d�tails de la collision.
	///
	/// @return Force caus�e par la collision, en deux dimensions.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec2 calculerCollisionCercle(
		const glm::dvec2&   centreCercle,
		double            rayonCercle,
		const glm::dvec2&   positionObjet,
		double            rayonObjet,
		double            constanteRebondissement,
		double            constanteAmortissement,
		const glm::dvec2&   vitesse,
		DetailsCollision* retourDetails //= 0
		)
	{
		return glm::dvec2(calculerCollisionSphere(
			glm::dvec3{ centreCercle, 0.0 }, rayonCercle,
			glm::dvec3{ positionObjet, 0.0 }, rayonObjet,
			constanteRebondissement,
			constanteAmortissement,
			glm::dvec3{ vitesse, 0.0 },
			retourDetails
			));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec3 calculerCollisionSphere(
	///        const glm::dvec3&   centreSphere,
	///        double            rayonSphere,
	///        const glm::dvec3&   positionObjet,
	///        double            rayonObjet,
	///        double            constanteRebondissement,
	///        double            constanteAmortissement,
	///        const glm::dvec3&   vitesse,
	///        DetailsCollision* retourDetails = 0
	///        );
	///
	/// Cette fonction calcule la force caus�e par la collision d'une
	/// sph�re avec une autre sph�re, chacune identifi�e par son centre
	/// et son rayon.  Elle tient compte d'une force de rebondissement
	/// ainsi qu'une force d'amortissement.
	///
	/// @param[in]  centreSphere            : Centre de la sph�re avec laquelle
	///                                       on teste la collision.
	/// @param[in]  rayonSphere             : Rayon de la sph�re avec laquelle
	///                                       on teste la collision.
	/// @param[in]  positionObjet           : Position de l'objet peut-�tre en
	///                                       collision.
	/// @param[in]  rayonObjet              : Rayon de l'objet peut-�tre en
	///                                       collision.
	/// @param[in]  constanteRebondissement : Constante de rebondissement de
	///                                       l'objet.
	/// @param[in]  constanteAmortissement  : Constante d'amortissement de
	///                                       l'objet.
	/// @param[in]  vitesse                 : Vitesse de l'objet en collision.
	/// @param[out] retourDetails           : Pointeur pour retourner les
	///                                       d�tails de la collision.
	///
	/// @return Force caus�e par la collision, en trois dimensions.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec3 calculerCollisionSphere(
		const glm::dvec3&   centreSphere,
		double            rayonSphere,
		const glm::dvec3&   positionObjet,
		double            rayonObjet,
		double            constanteRebondissement,
		double            constanteAmortissement,
		const glm::dvec3&   vitesse,
		DetailsCollision* retourDetails //= 0
		)
	{
		DetailsCollision details = calculerCollisionSphere(
			centreSphere, rayonSphere,
			positionObjet, rayonObjet
			);

		glm::dvec3 force{ calculerForceRebondissement3D(
			details, constanteRebondissement
			) };
		force += calculerForceAmortissement3D(
			details, vitesse, constanteAmortissement
			);

		if (retourDetails)
			*retourDetails = details;

		return force;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double calculerCombinaisonRebondissement(
	///        double constante1, double constante2
	///        );
	///
	/// Cette fonction calcule la constante r�sultant de la combinaison de deux
	/// corps en collision poss�dant chacun leur constante de rebondissement.
	///
	/// Elle utilise le mod�le de ressort en s�rie qui se compriment l'un
	/// l'autre.
	///
	/// @param[in] constante1 : La constante du premier objet.
	/// @param[in] constante2 : La constante du second objet.
	///
	/// @return Constante r�sultante pour les deux objets.
	///
	////////////////////////////////////////////////////////////////////////
	double calculerCombinaisonRebondissement(
		double constante1, double constante2
		)
	{
		return constante1 * constante2 / (constante1 + constante2);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double calculerCombinaisonAmortissement(
	///        double constante1, double constante2
	///        );
	///
	/// Cette fonction calcule la constante r�sultant de la combinaison de deux
	/// corps en collision poss�dant chacun leur constante d'amortissement.
	///
	/// @param[in] constante1 : La constante du premier objet.
	/// @param[in] constante2 : La constante du second objet.
	///
	/// @return Constante r�sultante pour les deux objets.
	///
	////////////////////////////////////////////////////////////////////////
	double calculerCombinaisonAmortissement(
		double constante1, double constante2
		)
	{
		return constante1 + constante2;
	}


} // Fin de l'espace de nom aidecollision.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
