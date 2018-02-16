//////////////////////////////////////////////////////////////////////////////
/// @file Utilitaire.h
/// @author Martin Bisson
/// @date 2007-03-11
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_UTILITAIRE_H__
#define __UTILITAIRE_UTILITAIRE_H__

#include "glm\glm.hpp"

#include <string>
#include <sstream>
#include <iterator>
#include <vector>


template <typename T> class aiMatrix4x4t;	/// D�claration avanc�e d'une classe
using aiMatrix4x4 = aiMatrix4x4t<float>;	//  template

struct aiColor3D;

namespace modele{
	class Modele3D;
	class Noeud;
}

namespace utilitaire {


   /// D�finition d'un type d'entier non sign�.
	using uint = unsigned int;

	/// Constante pour la diff�rence entre deux nombres r�els.
	static const double EPSILON{ 0.00000001 };
	/// Constante PI.
	static const double PI{ 3.1415926535897932384626433832795 };

	/// Le vecteur i (dirig� vers l'axe des X positifs et unitaire).
	static glm::dvec3 vi{ 1.0, 0.0, 0.0 };
	/// Le vecteur j (dirig� vers l'axe des Y positifs et unitaire).
	static glm::dvec3 vj{ 0.0, 1.0, 0.0 };
	/// Le vecteur k (dirig� vers l'axe des Z positifs et unitaire).
	static glm::dvec3 vk{ 0.0, 0.0, 1.0 };

   /// Fonction globale pour l'affichage d'erreur.
   void afficherErreur(const std::string& message);

   /// Pour convertir les angles de radians en degr�s.
   double RAD_TO_DEG( double AngleRad );
   /// Pour convertir les angles de degr�s en radians.
   double DEG_TO_RAD( double AngleDeg );

   /// Pour convertir les km/h en m/s.
   float KMH_TO_MS( float kmh );
   /// Pour convertir les m/s en km/h.
   float MS_TO_KMH( float ms );

   /// Fonction pour conna�tre le signe d'un nombre.
   float SIGN( float nombre );

   /// Fonction pour savoir si un double est �gal � z�ro.
   bool EGAL_ZERO(double Nombre);

   /// Pour savoir si un nombre est dans l'intervalle: [BorneMin, BorneMax].
   bool DANS_INTERVALLE( double Valeur, double BorneMin, double BorneMax );
   /// Fonction pour v�rifier si un Point 2d est dans un carr�.
   bool DANS_LIMITESXY( double x, double xMin, double xMax,
                        double y, double yMin, double yMax );

   /// calcule le vecteur unitaire a partir d'un point glm::dvec3
   glm::dvec3 vecteurUnitaire(glm::dvec3);
  
   /// Calcule le rapport d'�crasement
   double ecrasement( double a, double b);

   /// V�rification de l'existance d'un fichier
   bool fichierExiste( const std::string& nomDuFichier );

   /// Applique une matrice de transformation � un point.
   glm::dvec3 appliquerMatrice( const glm::dvec3& point, const double mat[] );

   /// Conversion d'une matrice Assimp vers glm
   glm::mat4x4 ai_To_glm(aiMatrix4x4 const& m);
   /// Conversion d'une couleur Assimp vers glm
   glm::vec3 ai_To_glm(aiColor3D const& c);

   /// Structure contenant les donn�es pour une sph�re englobante
   struct SphereEnglobante{
	   double rayon;
   };

   /// Structure contenant les donn�es pour un cylindre englobant
   struct CylindreEnglobant{
	   double rayon;
	   double bas;
	   double haut;
   };

   /// Structure contenant les donn�es pour une boite englobante
   struct BoiteEnglobante{
	   glm::dvec3 coinMin;
	   glm::dvec3 coinMax;
   };

   /// Structure contenant les donn�es pour un segment
   struct Segment{
	   glm::dvec2 point1;
	   glm::dvec2 point2;
   };

   /// Type de position de segment de la boite englobante du robot
   enum PositionSegment {
	   AVANT = 0, DROIT1, DROIT2, DROIT3, DROIT4, DROIT5, DROIT6, DROIT7, 
	   ARRIERE, GAUCHE7, GAUCHE6, GAUCHE5, GAUCHE4, GAUCHE3, GAUCHE2, GAUCHE1
   };

   /// Structure contenant les donn�es pour une boite englobante du robot
   struct BteEnglobanteRobot{
	   Segment segments[16];
   };

   /// Calcule la sph�re englobante
   SphereEnglobante calculerSphereEnglobante(modele::Modele3D const& modele);

   /// Calcule le cylindre englobant
   CylindreEnglobant calculerCylindreEnglobant(modele::Modele3D const& modele);

   /// Calcule la boite englobante
   BoiteEnglobante calculerBoiteEnglobante(modele::Modele3D const& modele);

   /// Permet de r�cup�rer les points extr�mes d'un noeud (r�cursivement)
   void obtenirPointsExtremes(modele::Noeud const& noeud, 
	   glm::dvec3& xMin, glm::dvec3& xMax, 
	   glm::dvec3& yMin, glm::dvec3& yMax, 
	   glm::dvec3& zMin, glm::dvec3& zMax);

   void tournerPointAutourDuCentre(double centreX, double centreY, double angle, glm::dvec3 & point);

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn T borneSuperieure(T const& valeur, T const& borne)
   ///
   /// Cette fonction s'assure que la valeur ne d�passe pas la borne.
   ///
   /// @param[in] valeur : La valeur de l'expression � borner.
   /// @param[in] borne  : La borne sup�rieure.
   ///
   /// @return La valeur born�e.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   T borneSuperieure(T const& valeur, T const& borne)
   {
	   return valeur > borne ? borne : valeur;
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn T borneInferieure(T const& valeur, T const& borne)
   ///
   /// Cette fonction s'assure que la valeur d�passe la borne.
   ///
   /// @param[in,out] valeur : La valeur de l'expression � borner.
   /// @param[in]     borne  : La borne inf�rieure.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   T borneInferieure(T const& valeur, T const& borne)
   {
	   return valeur < borne ? borne : valeur;
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn T borne(T const& valeur, T const& min, T const& max)
   ///
   /// Cette fonction s'assure que la valeur ne d�passe pas les bornes.
   ///
   /// @param[in] valeur	: La valeur de l'expression � borner.
   /// @param[in] min		: La borne inf�rieure.
   /// @param[in] max		: La borne sup�rieure.
   ///
   /// @return la valeur born�e.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   T borne(T const& valeur, T const& min, T const& max)
   {
	   return borneSuperieure(borneInferieure(valeur, min), max);
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn static std::string convertirEnChaine(const T& valeur)
   ///
   /// @brief Conversion d'un type g�n�rique vers une cha�ne de caract�res.
   ///
   /// Cette fonction convertit un type g�n�rique en une cha�ne de
   /// caract�res.  Comme elle se sert de l'op�rateur << appliqu� sur
   /// un ostringstream, elle devrait fonctionner pour toutes les classes
   /// qui d�finissent cet op�rateur pour les ostream&.
   ///
   /// @param[in] valeur    : Valeur template � convertir en cha�ne de
   ///                        caract�res.
   /// @param[in] modifieur : Fonction utilis�e pour la conversion de type
   ///                        particulier, par exemple std::hex ou std::oct
   ///                        pour les entiers.
   ///
   /// @return Cha�ne repr�sentant le type.
   ///
   ////////////////////////////////////////////////////////////////////////
   template<typename T> static std::string convertirEnChaine(
      const T& valeur,
      std::ios_base& (*modifieur)(std::ios_base&) = 0
      )
   {
      std::ostringstream oss;

      // Application du modifieur s'il est sp�cifi�.
      if (modifieur)
         oss << modifieur;

      oss << valeur;
      return oss.str();
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn static bool convertirEnType(const std::string& chaine, T& valeur, std::ios_base& (*modifieur)(std::ios_base&) = 0)
   ///
   /// @brief Conversion d'une cha�ne de caract�res vers un type g�n�rique.
   ///
   /// Cette fonction convertit une cha�ne de caract�res en un type g�n�rique.
   /// Comme elle se sert de l'op�rateur >> appliqu� sur un istringstream,
   /// elle devrait fonctionner pour toutes les classes qui d�finissent cet
   /// op�rateur pour les istream&.
   ///
   /// @param[in] chaine    : Cha�ne � convertir.
   /// @param[in] valeur    : Valeur template qui contiendra la valeur contenu
   ///                        dans la cha�ne.  Ne sera pas modifi�e si la
   ///                        cha�ne n'est pas valide.
   /// @param[in] modifieur : Fonction utilis�e pour la conversion de type
   ///                        particulier, par exemple std::hex ou std::oct
   ///                        pour les entiers.
   ///
   /// @return Vrai si la conversion a r�ussi.
   ///
   ////////////////////////////////////////////////////////////////////////
   template<typename T> static bool convertirEnType(
      const std::string& chaine,
      T& valeur,
      std::ios_base& (*modifieur)(std::ios_base&) = 0
      )
   {
	   std::istringstream iss{ chaine };

      // Application du modifieur s'il est sp�cifi�.
      if (modifieur)
         iss >> modifieur;

      // Lecture de la valeur
      T temp;
	  iss >> temp;

	  // Pour que la conversion soit un succ�s, toute la cha�ne doit avoir �t�
	  // convertie.  On ajoute donc le second test pour �viter qu'une cha�ne
	  // comme "123bidon" puisse �tre accept�e et que toute la cha�ne soit
	  // utilis�e pour que la conversion soit consid�r�e comme r�ussie.
	  const bool succes{ ((!iss.fail()) && (iss.peek() == EOF)) };

      if (succes)
         valeur = temp;

      return succes;
   }

   template<typename Out>
   static void split(const std::string &s, char delim, Out result) {
	   std::stringstream ss;
	   ss.str(s);
	   std::string item;
	   while (std::getline(ss, item, delim)) {
		   *(result++) = item;
	   }
   }

   static std::vector<std::string> split(const std::string &s, char delim) {
	   std::vector<std::string> elems;
	   split(s, delim, std::back_inserter(elems));
	   return elems;
   }

   /// Cette fonction verifie si un rectangle est dans la une zone centree a (0, 0)
   bool rectangleDansUneZone(glm::dvec3 pointDebut, glm::dvec3 pointFin, double largeur,
	   double longuerZone, double largeurZone);
   /// Cette fonction verifie si un cercle est dans une zone rectangulaire
   bool cercleDansUneZone(double xMin, double xMax, double yMin, double yMax,
	   double centreX, double centreY, double rayon);
   bool pointDansUnRectangle(glm::dvec3 position, glm::dvec3 coin1, glm::dvec3 coin2, glm::dvec3 coin3, glm::dvec3 coin4);
   std::vector<std::string> split(const std::string &s, char delim);
   std::string toString(double number, int precision = 2);

} // Fin du namespace utilitaire.


#endif // __UTILITAIRE_UTILITAIRE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
