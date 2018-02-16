///////////////////////////////////////////////////////////////////////////////
/// @file SegmentDroite2D.h
/// @author INF2990 Eq.11
/// @date 2016-03-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "glm\glm.hpp"

namespace math
{
	class SegmentDroite2D
	{
	public:
		///Constructeur
		SegmentDroite2D(const glm::dvec2& point1, const glm::dvec2& point2) : point1Droite_(point1), point2Droite_(point2) {};
		///Destructeur
		~SegmentDroite2D() {};
		///Fonction permettant de determiner si deux segments s'intersecte.
		bool intersectionAvecSegment(const glm::dvec2& point1, const glm::dvec2& point2);
	private:
		///Premier point de la droite.
		const glm::dvec2 point1Droite_;
		///Deuxieme point de la droite.
		const glm::dvec2 point2Droite_;
	};
}