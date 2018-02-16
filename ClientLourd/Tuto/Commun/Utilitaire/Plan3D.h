////////////////////////////////////////////////////////////////////////////////////
/// @file Plan3D.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#ifndef __UTILITAIRE_PLAN3D_H__
#define __UTILITAIRE_PLAN3D_H__


#include "glm\glm.hpp"

namespace math {
   
   
   ///////////////////////////////////////////////////////////////////////////
   /// @class Plan3D
   /// @brief D�finition de la classe qui cr�e un plan en 3 dimensions.
   ///
   /// Classe qui permet d'avoir un plan en 3D.\n
   /// Un plan est d�fini par \f$ Ax + By + Cz + D = 0 \f$ o� \f$ A, B \f$ et \f$ C  \f$ sont les
   /// composantes en  \f$ x, y \f$ et \f$ z  \f$ d'un vecteur normal au plan.
   ///
   /// @author DGI-2990
   /// @date 2005-09-27
   ///////////////////////////////////////////////////////////////////////////
   class Plan3D
   {
   public:
      /// Constructeur.
      Plan3D(const glm::dvec3& normale, const glm::dvec3& pointDuPlan);

      /// Lire la normale du plan.
      inline const glm::dvec3& lireNormale() const;

      /// Lire les 4 param�tres qui d�finissent un plan en 3D.
      void lireParam(double& a, double& b, double& c, double& d) const;


   private:
      /// La normale du plan.
      const glm::dvec3 normale_;

      /// Le d�calage du plan.
      const double   d_;

   };


   ///////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const glm::dvec3& Plan3D::lireNormale() const
   ///
   /// Cette fonction retourne le vecteur normal au plan.
   ///
   /// @return Le vecteur normal au plan.
   ///
   ///////////////////////////////////////////////////////////////////////////////
   inline const glm::dvec3& Plan3D::lireNormale() const
   {
      return normale_;
   }


} // fin de l'espace de nom math.


#endif // __UTILITAIRE_PLAN3D_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
