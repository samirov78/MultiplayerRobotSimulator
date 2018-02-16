///////////////////////////////////////////////////////////////////////////////
/// @file Utilitaire.cpp
/// @author DGI
/// @date 2005-06-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Utilitaire.h"

#include <windows.h>
#include <fstream>
#include <limits>
#include <iostream>
#include <iomanip>

#include "scene.h"
#include "Modele3D.h"
#include "Noeud.h"

#include "glm\gtx\norm.hpp"

namespace utilitaire {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void afficherErreur(const std::string& message)
	///
	/// Cette fonction affiche une message d'erreur.
	///
	/// @param[in] message : La cha�ne d�crivant l'erreur.
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	void afficherErreur(const std::string& message)
	{
#ifdef WIN32
		MessageBoxA(0, message.c_str(), "Erreur", MB_OK | MB_ICONERROR);
#else
		std::cerr << message << std::endl;
#endif
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool EGAL_ZERO(double nombre)
	///
	/// Fonction pour savoir si un double est �gal � z�ro.
	///
	/// @param[in] nombre : Valeur � v�rifier.
	///
	/// @return true si nombre est �gal a 0, false autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool EGAL_ZERO(double nombre)
	{
		return (nombre < EPSILON) && (-nombre < EPSILON);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double RAD_TO_DEG(double angleRad)
	///
	/// Cette fonction convertit les angles de radians en degr�s.
	///
	/// @param[in] angleRad : L'angle en radians � convertir.
	///
	/// @return L'angle converti en degr�s
	///
	////////////////////////////////////////////////////////////////////////
	double RAD_TO_DEG(double angleRad)
	{
		return angleRad * 57.2957795130823208767981548141052;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double DEG_TO_RAD(double angleDeg)
	///
	/// Cette fonction convertit les angles de degr�s en radians.
	///
	/// @param[in] angleDeg : L'angle en degr�s � convertir.
	///
	/// @return L'angle converti en radians.
	///
	////////////////////////////////////////////////////////////////////////
	double DEG_TO_RAD(double angleDeg)
	{
		return angleDeg * 0.0174532925199432957692369076848861;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn float KMH_TO_MS( float kmh )
	///
	/// Fonction de conversion des km/h en m/s.
	///
	/// @param[in] kmh : Valeur en kilom�tres / heure.
	///
	/// @return float => vitesse en m�tres par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	float KMH_TO_MS(float kmh)
	{
		return (kmh * 1000.0f / 3600.0f);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn float MS_TO_KMH( float ms )
	///
	/// Fonction de conversion des m/s en km/h.
	///
	/// @param[in] ms : Valeur en m�tres / seconde.
	///
	/// @return float => vitesse en kilom�tres / heure.
	///
	////////////////////////////////////////////////////////////////////////
	float MS_TO_KMH(float ms)
	{
		return (ms * 3.6f);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn int SIGN( float nombre )
	///
	/// Fonction pour conna�tre le signe d'un nombre.
	///
	/// @param[in] nombre : Valeur dont on veut trouver le signe.
	///
	/// @return int => 1 si positif, -1 si n�gatif, 0 si = 0.
	///
	////////////////////////////////////////////////////////////////////////
	float SIGN(float nombre)
	{
		if (nombre == 0.0f) {
			return 0.0f;
		}
		else if (nombre > 0.0f) {
			return  1.0f;
		}
		else {
			return -1.0f;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool DANS_INTERVALLE( double valeur, double borneMin, double borneMax ) 
	///
	/// Cette fonction v�rifie si une valeur est dans un intervalle.
	///
	/// @param[in] valeur   : La valeur � v�rifier.
	/// @param[in] borneMin : La borne inf�rieure de l'intervalle.
	/// @param[in] borneMax : La borne sup�rieure de l'intervalle.
	///
	/// @return Vrai si la valeur est dans l'intervalle, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool DANS_INTERVALLE(double valeur, double borneMin, double borneMax)
	{
		return (valeur >= borneMin) && (valeur <= borneMax);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool DANS_LIMITESXY( double x, double xMin, double xMax, double y, double yMin, double yMax )
	///
	/// Cette fonction v�rifie si un point 2d est dans un carr�.
	///
	/// @param[in] x    : Coordonn�e x du point.
	/// @param[in] xMin : La borne inf�rieure en x.
	/// @param[in] xMax : La borne sup�rieure en x.
	/// @param[in] y    : Coordonn�e y du point.
	/// @param[in] yMin : La borne inf�rieure en y.
	/// @param[in] yMax : La borne sup�rieure en y.
	///
	/// @return Vrai si le point (x,y) est dans le carr�, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool DANS_LIMITESXY(double x, double xMin, double xMax,
		double y, double yMin, double yMax)
	{
		return (DANS_INTERVALLE(x, xMin, xMax) && DANS_INTERVALLE(y, yMin, yMax));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double CUtilitaire::ecrasement( double a, double b )
	///
	/// Cette fonction calcule le rapport d'�crasement pour un rectangle de
	/// longueur @a a et largeur @a b.
	///   - si a = b, le rapport est 1
	///   - le rapport est toujours positif et plus grand que 1.
	///
	/// @param[in] a : Valeur � rapprocher.
	/// @param[in] b : Point limite du rapprochement.
	///
	/// @return Le rapport @a r  de @a a /  @a b
	///
	////////////////////////////////////////////////////////////////////////
	double ecrasement(double a, double b)
	{
		double r{ a / b };
		// Le rapport doit �tre toujours positif.
		if (r < 1.0)
			r = 1.0 / r;

		return r;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool fichierExiste( const std::string &nomDuFichier )
	///
	/// Cette fonction v�rifie si un fichier d'un certain nom donn� existe.
	///
	/// @param [in] nomDuFichier : Le nom du fichier dont on veut v�rifier
	///                            l'existence.
	///
	/// @return Vrai si le fichier existe, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool fichierExiste(const std::string& nomDuFichier)
	{
		std::ifstream ficin;
		ficin.open(nomDuFichier.c_str());
		bool fail{ ficin.fail() };

		if (!fail)
			ficin.close();

		return !fail;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::mat4x4 ai_To_glm(aiMatrix4x4 const& m)
	///
	/// Cette fonction convertit une matrice 4x4 assimp vers une matrice
	/// 4x4 de glm
	///
	/// @param [in] m : La matrice assimp
	///
	/// @return la matrice glm
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4x4 ai_To_glm(aiMatrix4x4 const& m)
	{
		glm::mat4x4 mat;
		for (glm::length_t i{ 0 }; i < mat.length(); ++i)
		{
			for (glm::length_t j{ 0 }; j < mat.length(); ++j)
			{
				mat[i][j] = m[i][j];
			}
		}
		/// On passe d'un ordre par rang�e vers un ordre par colonne
		return glm::transpose(mat);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::vec3 ai_To_glm(aiColor3D const& c)
	///
	/// Cette fonction convertit une couleur 3D assimp vers un vecteur 3D
	/// de glm
	///
	/// @param [in] m : La couleur assimp
	///
	/// @return le vecteur glm
	///
	////////////////////////////////////////////////////////////////////////
	glm::vec3 ai_To_glm(aiColor3D const& c)
	{
		glm::vec3 couleur;
		for (glm::length_t i{ 0 }; i < couleur.length(); ++i)
		{
			couleur[i] = c[i];
		}
		return couleur;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void appliquerMatrice( const glm::dvec3& point, const double mat[])
	///
	/// Cette fonction multiplie le point par une matrice de transformation
	/// donn�e et retourne le r�sultat.
	///
	/// @param [in] point : Le point � transformer.
	/// @param [in] mat   : La matrice de transformation.
	///
	/// @return Le point transform�.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec3 appliquerMatrice(const glm::dvec3& point, const double mat [])
	{
		// Calculer la multiplication entre la matrice et le point.
		glm::dvec3 pointTransforme{
		mat[0] * point[0] + mat[4] * point[1] + mat[8] * point[2] + mat[12],
		mat[1] * point[0] + mat[5] * point[1] + mat[9] * point[2] + mat[13],
		mat[2] * point[0] + mat[6] * point[1] + mat[10] * point[2] + mat[14] };

		const double w{
			mat[3] * point[0] +
			mat[7] * point[1] +
			mat[11] * point[2] +
			mat[15] };

		// Retour des coordonn�es homog�nes vers la 3D.
		pointTransforme /= w;

		return pointTransforme;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn SphereEnglobante calculerSphereEnglobante(modele::Modele3D const& modele)
	///
	/// Cette fonction calcule la sph�re englobante d'un mod�le 3D en espace
	/// local.
	///
	/// @param [in] modele : le mod�le 3D
	///
	/// @return La sphereEnglobante.
	///
	////////////////////////////////////////////////////////////////////////
	SphereEnglobante calculerSphereEnglobante(modele::Modele3D const& modele)
	{
		auto dmin = std::numeric_limits<double>::min();
		auto dmax = std::numeric_limits<double>::max();

		glm::dvec3 xMin{ dmax, dmax, dmax },
			xMax{ dmin, dmin, dmin },
			yMin{ dmax, dmax, dmax },
			yMax{ dmin, dmin, dmin },
			zMin{ dmax, dmax, dmax },
			zMax{ dmin, dmin, dmin };

		obtenirPointsExtremes(modele.obtenirNoeudRacine(), xMin, xMax, yMin, yMax, zMin, zMax);

		// Le rayon de la sph�re englobante est le point le plus �loign� parmi les 6 points extr�mes possibles...
		double max{ 0 };
		double norme{ 0 };

		norme = glm::length2(xMin); if (norme > max) max = norme;
		norme = glm::length2(yMin); if (norme > max) max = norme;
		norme = glm::length2(zMin); if (norme > max) max = norme;
		norme = glm::length2(xMax); if (norme > max) max = norme;
		norme = glm::length2(yMax); if (norme > max) max = norme;
		norme = glm::length2(zMax); if (norme > max) max = norme;

		return SphereEnglobante{ sqrt(max) };
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn CylindreEnglobant calculerCylindreEnglobant(modele::Modele3D const& modele)
	///
	/// Cette fonction calcule le cylindre englobant d'u nmod�le 3D en espace
	/// local.
	///
	/// @param [in] modele : le mod�le 3D
	///
	/// @return Le cylindre englobant.
	///
	////////////////////////////////////////////////////////////////////////
	CylindreEnglobant calculerCylindreEnglobant(modele::Modele3D const& modele)
	{
		auto dmin = std::numeric_limits<double>::min();
		auto dmax = std::numeric_limits<double>::max();

		glm::dvec3 xMin{ dmax, dmax, dmax },
			xMax{ dmin, dmin, dmin },
			yMin{ dmax, dmax, dmax },
			yMax{ dmin, dmin, dmin },
			zMin{ dmax, dmax, dmax },
			zMax{ dmin, dmin, dmin };

		obtenirPointsExtremes(modele.obtenirNoeudRacine(), xMin, xMax, yMin, yMax, zMin, zMax);

		// Obtenir le point extr�me le plus �loign� parmi les axes xy. L'axe z servira
		// � �tablir le bas et le haut du cylindre.

		double max{ 0 };
		double norme{ 0 };
		norme = xMin[0] * xMin[0] + xMin[1] * xMin[1]; if (norme > max) max = norme;
		norme = yMin[0] * yMin[0] + yMin[1] * yMin[1]; if (norme > max) max = norme;
		norme = zMin[0] * zMin[0] + zMin[1] * zMin[1]; if (norme > max) max = norme;
		norme = xMax[0] * xMax[0] + xMax[1] * xMax[1]; if (norme > max) max = norme;
		norme = yMax[0] * yMax[0] + yMax[1] * yMax[1]; if (norme > max) max = norme;
		norme = zMax[0] * zMax[0] + zMax[1] * zMax[1]; if (norme > max) max = norme;

		// Nous avons trouv� le rayon...
		double rayon{ sqrt(max) };

		// Le bas et le dessus sont les extr�mums en z.
		double bas{ dmax }, haut{ dmin };
		if (xMin[2]<bas) bas = xMin[2]; if (xMin[2]>haut) haut = xMin[2];
		if (yMin[2]<bas) bas = yMin[2]; if (yMin[2]>haut) haut = yMin[2];
		if (zMin[2]<bas) bas = zMin[2]; if (zMin[2]>haut) haut = zMin[2];
		if (xMax[2]<bas) bas = xMax[2]; if (xMax[2]>haut) haut = xMax[2];
		if (yMax[2]<bas) bas = yMax[2]; if (yMax[2]>haut) haut = yMax[2];
		if (zMax[2]<bas) bas = zMax[2]; if (zMax[2]>haut) haut = zMax[2];

		return CylindreEnglobant{ rayon, bas, haut };
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn BoiteEnglobante calculerBoiteEnglobante(modele::Modele3D const& modele)
	///
	/// Cette fonction calcule la boite englobante d'un mod�le 3D en espace
	/// local.
	///
	/// @param [in] modele : le mod�le 3D
	///
	/// @return La boite englobante.
	///
	////////////////////////////////////////////////////////////////////////
	BoiteEnglobante calculerBoiteEnglobante(modele::Modele3D const& modele)
	{
		const modele::Noeud& noeud{ modele.obtenirNoeudRacine() };
		auto dmin = std::numeric_limits<double>::min();
		auto dmax = std::numeric_limits<double>::max();
		
		glm::dvec3 xMin{ dmax, dmax, dmax },
			xMax{ dmin, dmin, dmin },
			yMin{ dmax, dmax, dmax },
			yMax{ dmin, dmin, dmin },
			zMin{ dmax, dmax, dmax },
			zMax{ dmin, dmin, dmin };

		/// R�cup�rer les points extr�mes du mod�le 3D
		obtenirPointsExtremes(noeud, xMin, xMax, yMin, yMax, zMin, zMax);

		// Le coin min est simplement les coordonn�es minimales et le coin max est
		// simplement les coordonn�es maximales.
		glm::dvec3 coinMin{ xMin[0], yMin[1], zMin[2] };
		glm::dvec3 coinMax{ xMax[0], yMax[1], zMax[2] };

		return BoiteEnglobante{ coinMin, coinMax };
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void obtenirPointsExtremes(modele::Noeud const& noeud, glm::dvec3& xMin, glm::dvec3& xMax, glm::dvec3& yMin, glm::dvec3& yMax, glm::dvec3& zMin, glm::dvec3& zMax)
	///
	/// Cette fonction calcule les points extr�mes d'un noeud, r�cursivement.
	///
	/// @param [in] noeud : un noeud d'un mod�le 3D
	/// @param [in,out] xMin  : point contenant la valeur minimale de x
	/// @param [in,out] xMax  : point contenant la valeur maximale de x
	/// @param [in,out] yMin  : point contenant la valeur minimale de y
	/// @param [in,out] yMax  : point contenant la valeur maximale de y
	/// @param [in,out] zMin  : point contenant la valeur minimale de z
	/// @param [in,out] zMax  : point contenant la valeur maximale de z
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void obtenirPointsExtremes(modele::Noeud const& noeud,
		glm::dvec3& xMin, glm::dvec3& xMax,
		glm::dvec3& yMin, glm::dvec3& yMax,
		glm::dvec3& zMin, glm::dvec3& zMax)
	{
		// Pour chacun des 'meshes'...
		for (modele::Mesh const& mesh : noeud.obtenirMeshes())
		{
			// Pour chaque face...
			for (modele::Mesh::Face const& face : mesh.obtenirFaces())
			{
				// Pour chaque vertex...
				for (glm::length_t index{ 0 }; index < face.length(); ++index)
				{
					int indexVertex{ face[index] };

					// On v�rifie les coordonn�es...
					glm::dvec3 sommet{ mesh.obtenirSommets()[indexVertex] };

					if (sommet.x<xMin.x)
						xMin = sommet;
					else if (sommet.x>xMax.x)
						xMax = sommet;

					if (sommet.y<yMin.y)
						yMin = sommet;
					else if (sommet.y>yMax.y)
						yMax = sommet;

					if (sommet.z<zMin.z)
						zMin = sommet;
					else if (sommet.z>zMax.z)
						zMax = sommet;
				}
			}
		}

		// Calcul r�cursif des points extr�mes
		for (modele::Noeud const& noeud : noeud.obtenirEnfants())
		{
			obtenirPointsExtremes(noeud, xMin, xMax, yMin, yMax, zMin, zMax);
		}
	}


	glm::dvec3 vecteurUnitaire(glm::dvec3 point)
	{
		double norme = sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
		glm::dvec3 retour = point / norme;
		return retour;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void tournerPointAutourDuCentre(double centreX, double centreY, double angle, glm::dvec3 & point)
	///
	/// Cette fonction permet d'effectuer une rotation d'un point autour du centre.
	///
	/// @param[in]	centreX				: Position x du centre.
	///
	/// @param[in]	centreY				: Position y du centre.
	///
	/// @param[in]	angle				: Angle de rotation
	///
	/// @param[in, out]	point			: Nouveau point rotater.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void tournerPointAutourDuCentre(double centreX, double centreY, double angle, glm::dvec3 & point)
	{
		// effectuer une translation vers le centre
		point.x -= centreX;
		point.y -= centreY;

		// effectuer la rotation
		double nouveauX = point.x * cos(utilitaire::DEG_TO_RAD(angle)) - point.y * sin(utilitaire::DEG_TO_RAD(angle));
		double nouveauY = point.x * sin(utilitaire::DEG_TO_RAD(angle)) + point.y * cos(utilitaire::DEG_TO_RAD(angle));

		//effectuer une translation
		point.x = nouveauX + centreX;
		point.y = nouveauY + centreY;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool rectangleDansUneZone(glm::dvec3 pointDebut, glm::dvec3 pointFin, double largeur)
	///
	/// Cette fonction verifie si un rectangle est dans la une zone centree a (0, 0)
	///
	/// @param [in] pointDebut : le point de debut
	/// @param [in] pointFin : le point de fin
	/// @param [in] largeur  : la largeur du rectangle
	/// @param [in] largeurZone  : la largeur de la zone
	/// @param [in] longuerZone  : la longeur de la zone
	
	/// @return Vrai si la rectangle est dans la table faux sinon
	///
	////////////////////////////////////////////////////////////////////////
	bool rectangleDansUneZone(glm::dvec3 pointDebut, glm::dvec3 pointFin, double largeur,
		double longuerZone, double largeurZone)
	{
		if (pointDebut == pointFin)
			return true;
		else
		{
			glm::dvec3 vecteurDirecteur = utilitaire::vecteurUnitaire(pointFin - pointDebut);

			glm::dvec3 point1 = vecteurDirecteur;
			tournerPointAutourDuCentre(0, 0, 90, point1);
			point1 = point1 * (largeur / 2.0);
			glm::dvec3 point2 = -point1;

			glm::dvec3 point3 = vecteurDirecteur;
			tournerPointAutourDuCentre(0, 0, 90, point3);
			point3 = point3 * (largeur / 2.0);
			glm::dvec3 point4 = -point3;

			point1 = point1 + pointDebut;
			point2 = point2 + pointDebut;
			point3 = point3 + pointFin;
			point4 = point4 + pointFin;

			bool point1DansLaTable = utilitaire::DANS_LIMITESXY(point1.x, -longuerZone / 2,
				longuerZone / 2, point1.y, -largeurZone / 2, largeurZone/2);
			bool point2DansLaTable = utilitaire::DANS_LIMITESXY(point2.x, -longuerZone / 2, 
				longuerZone / 2, point2.y, -largeurZone / 2, largeurZone/2);
			bool point3DansLaTable = utilitaire::DANS_LIMITESXY(point3.x, -longuerZone / 2, 
				longuerZone / 2, point3.y, -largeurZone/2, largeurZone / 2);
			bool point4DansLaTable = utilitaire::DANS_LIMITESXY(point4.x, -longuerZone / 2, 
				longuerZone / 2, point4.y, -largeurZone/2, largeurZone / 2);

			return (point1DansLaTable && point2DansLaTable && point3DansLaTable && point4DansLaTable);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool cercleDansUneZone(glm::dvec3 pointDebut, glm::dvec3 pointFin, glm::dvec3 positionCentre,
	/// double rayon)
	///
	/// Cette fonction verifie si un cercle est dans une zone rectangulaire
	///
	/// @param [in] pointDebut : le point de debut de la zone
	/// @param [in] pointFin : le point de fin de la zone
	/// @param [in] positionCentre  : position du centre du cercle
	/// @param [in] rayon  : le rayon du cercle
	/// @return Vrai si le cercle est dans la zone faux sinon
	///
	////////////////////////////////////////////////////////////////////////
	bool cercleDansUneZone(double xMin, double xMax, double yMin, double yMax,
		double centreX, double centreY, double rayon)
	{
		if ( DANS_LIMITESXY(centreX, xMin + rayon, xMax - rayon, 
			centreY, yMin + rayon, yMax - rayon ) )
			return true;
		else
			return false;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool pointDansUnRectangle(glm::dvec3 position, glm::dvec3 coin1, glm::dvec3 coin2,
	/// glm::dvec3 coin3, glm::dvec3 coin4)
	///
	/// Cette fonction verifie si un point est dans un rectangle incline
	///
	/// @param [in] position : la position du point
	/// @param [in] coin1 : le premier coin du rectangle
	/// @param [in] coin2  : le deuxieme coin du rectangle
	/// @param [in] coin3  : le troisieme coin du rectangle
	/// @param [in] coin4  : le quatrieme coin du rectangle
	/// @return Vrai si le point est dans le rectangle faux sinon
	///
	////////////////////////////////////////////////////////////////////////
	bool pointDansUnRectangle(glm::dvec3 position, glm::dvec3 coin1, glm::dvec3 coin2, glm::dvec3 coin3, glm::dvec3 coin4)
	{
		glm::dvec3 vec12 = coin2 - coin1;
		glm::dvec3 vec1position = position - coin1;
		double scalaire12 = vec12.x * vec1position.x + vec12.y * vec1position.y;
		glm::dvec3 vec14 = coin4 - coin1;
		double scalaire14 = vec14.x * vec1position.x + vec14.y * vec1position.y;

		glm::dvec3 vec32 = coin2 - coin3;
		glm::dvec3 vec3position = position - coin3;
		double scalaire32 = vec32.x * vec3position.x + vec32.y * vec3position.y;
		glm::dvec3 vec34 = coin4 - coin3;
		double scalaire34 = vec34.x * vec3position.x + vec34.y * vec3position.y;
		bool dansLeRectangle = true;
		if (scalaire12 >= 0 && scalaire14 >= 0 && scalaire32 >= 0 && scalaire34 >= 0)
			dansLeRectangle = true;
		else
			dansLeRectangle = false;
		return dansLeRectangle;
	}

	std::string toString(double number, int precision)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(precision) << number;
		return ss.str();
	}

}; // Fin de l'espace de nom utilitaire.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
