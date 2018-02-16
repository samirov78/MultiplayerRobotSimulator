///////////////////////////////////////////////////////////////////////////////
/// @file SegmentDroite2D.cpp
/// @author INF2990 Eq.11
/// @date 2016-03-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "SegmentDroite2D.h"
#include <iostream>

//Voir l'algorithme presenter ici : http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect/1968345#1968345
namespace math
{
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool SegmentDroite2D::intersectionAvecSegment(const glm::dvec2& point1, const glm::dvec2& point2)
	///
	/// Cette fonction permet de detecter si deux segments s'intersecte ou non.
	///
	/// @param[in]	point1				: Premier point d'un des segments.
	///
	/// @param[in]	point2				: Deuxieme point d'un des segments.
	///
	/// @return Vrai si les deux segments s'intersecte, faux sinon.
	///
	////////////////////////////////////////////////////////////////////////
	bool SegmentDroite2D::intersectionAvecSegment(const glm::dvec2& point1, const glm::dvec2& point2)
	{
		bool intersection = false;
		glm::dvec2 p, q;
		//vecteur directeur de la droite A
		p.x = point2.x - point1.x;
		p.y = point2.y - point1.y;
		//vecteur directeur de la droite B
		q.x = point2Droite_.x - point1Droite_.x;
		q.y = point2Droite_.y - point1Droite_.y;
		//	Forme parametrique d'une droite :
		//	Ax = point1.x + r * p.x
		//	Ay = point1.y + r * p.y
		//	Bx = point1Droite_.x + s * q.x
		//	By = point1Droite_.y + s * q.y

		//Recherchons r et s. Si r et s sont dans (0..1), alors il y a intersection.
		//Ax = Bx --> (r * p.x - s * q.x) = point1Droite_.x - point1.x
		//Ay = By --> (r * p.y - s * q.y) = point1Droite_.y - point1.y
		//sous forme matricielle :
		/*
		| p.x	-q.x |	| r |		| point1Droite_.x - point1.x |
		|			 |	|	|	=	|							 |
		| p.y	-q.y |	| s |		| point1Droite_.y - point1.y |
		*/

		//On utilise cramer pour determiner les valeurs respectives de r et s.

		//Idee de Cramer : x = |Dx| / |D|
		//				   y = |Dy| / |D|
		//				   Dans notre cas, x = r et y = s.


		double r = -1.0, s = -1.0;
		double determinantGlobal = (-q.x * p.y + p.x * q.y);
		if (determinantGlobal != 0)
		{
			//Resolution par Cramer.
			double determinantR = (-p.y * (point1.x - point1Droite_.x) + p.x * (point1.y - point1Droite_.y));
			double determinantS = (q.x * (point1.y - point1Droite_.y) - q.y * (point1.x - point1Droite_.x));
			r = determinantR / determinantGlobal;
			s = determinantS / determinantGlobal;
		}
		if (r >= 0 && r <= 1 && s >= 0 && s <= 1)
		{
			intersection = true;
		}
		return intersection;
	}
}

