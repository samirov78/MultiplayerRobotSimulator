///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionDeplacementFenetre.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionDeplacementFenetre
    /// @brief Classe decrivant l'etat lors d'un deplacement de la fenetre
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionDeplacementFenetre : EtatEdition
    {
        private int compteurDeplacement_ = 0;
        //private bool 

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void initialiserDebut(int x, int y)
        ///
        /// Methode permettant l'initialisation de certaines donnees lors d'un
        /// clic de souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void initialiserDebut(int x, int y)
        {
            lock (Program.NoyauLock)
            {
                FonctionsNatives.sauverPositionSouris(x, y);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterGlissement( int x, int y )
        ///
        /// Methode permettant le lancement d'algorithme lors du deplacement de
        /// la souris avec un certain bouton enfonce.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterGlissement( int x, int y )
        {
            Program.edition.Cursor = Cursors.SizeAll;
            if (compteurDeplacement_ == 5)
            {
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.deplacerFenetreVirtuelleSouris(x, y);
                }
                compteurDeplacement_ = 0;
            }
            else
                compteurDeplacement_++;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterDepot(int x, int y, Keys k)
        ///
        /// Methode permettant le lancement d'algorithme lors du relachement d'un
        /// bouton de la souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @param[in] k : Represente la touche appuyer.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterDepot(int x, int y, Keys k)
        {
            lock (Program.NoyauLock)
            {
                FonctionsNatives.deplacerFenetreVirtuelleSouris(x, y);
            }
            Program.edition.Cursor = Cursors.Default;
        }
        
   }
}
