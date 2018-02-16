///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionMur.cs
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
using System.Runtime.InteropServices;
using Commun;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionMur
    /// @brief Classe decrivant l'etat d'edition d'un mur.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionMur : EtatEdition
    {
        private int xDebut_ = 0;
        private int yDebut_ = 0;
        private string id;

        private int compteurDeplacement = 0;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterClic(int x, int y, Keys k)
        ///
        /// Methode permettant le lancement d'algorithmes lors d'un clic d'une
        /// touche quelconque.
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
        public override void interpreterClic(int x, int y, Keys k)
        {
            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return;

            if ( curseurValide_ )
            {
                compteurDeplacement = 0;
                if ( !Edition.enTrace_ )
                {
                    xDebut_ = x;
                    yDebut_ = y;
                    id = Guid.NewGuid().ToString();
                    string mur;
                    lock (Program.NoyauLock)
                    {
                        mur = Marshal.PtrToStringAnsi(FonctionsNatives.ajouterNoeudAvecScale(NOM_MUR, xDebut_, yDebut_, x, y, false, Program.OnLine, id));
                    }
                    if (Program.OnLine)
                        Program.SDispatcher.EditionConnectionM.SpreadCreateNode(mur, true);
                    Edition.enTrace_ = true;
                }
                else
                {
                    string mur;
                    lock (Program.NoyauLock)
                    {
                        FonctionsNatives.supprimerDernierNoeud();
                        mur = Marshal.PtrToStringAnsi(FonctionsNatives.ajouterNoeudAvecScale(NOM_MUR, xDebut_, yDebut_, x, y, true,Program.OnLine, id));
                    }
                    if (Program.OnLine)
                        Program.SDispatcher.EditionConnectionM.SpreadModifyNode(mur, false);
                    else
                        Program.edition.marquerModificationDansLaScene();
                    Edition.enTrace_ = false;
                }
            } 
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool interpreterEchap()
        ///
        /// Methode permettant le lancement d'algorithme lors de l'appui de la touche
        /// Echap.
        /// 
        /// @return True par defaut.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool interpreterEchap()
        {

            Program.edition.Cursor = Cursors.Default;
            if (Edition.enTrace_)
            {
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.supprimerDernierNoeud();
                    if (Program.OnLine)
                    {
                        Program.SDispatcher.EditionConnectionM.SpreadSuppDernierNoeud(id);
                    }
                }
                Edition.enTrace_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterDeplacement(int x, int y)
        ///
        /// Methode permettant le lancement d'algorithme lors du deplacement de
        /// la souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterDeplacement(int x, int y)
        {
            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return;

            if ( curseurValide_  && Edition.enTrace_)
            {
                compteurDeplacement++;
                string mur;
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.supprimerDernierNoeud();
                    mur = Marshal.PtrToStringAnsi(FonctionsNatives.ajouterNoeudAvecScale(
                        NOM_MUR, xDebut_, yDebut_, x, y, false, Program.OnLine, id));
                }
                if (Program.OnLine && compteurDeplacement > 2)
                {
                    Program.SDispatcher.EditionConnectionM.SpreadModifyNode(mur, true);
                    compteurDeplacement = 0;
                }
            }  
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool verifierCurseur(int x, int y)
        ///
        /// Methode permettant la verification de la position du curseur pour
        /// l'edition d'un mur
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Vrai lorsque le curseur est dans la bonne position pour editer
        /// un mur, faux autrement.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool verifierCurseur(int x, int y)
        {
            lock (Program.NoyauLock)
            {
                if (!Edition.enTrace_)
                    curseurValide_ = FonctionsNatives.verifierPositionCurseur(x, y);
                else
                    curseurValide_ = FonctionsNatives.verifierCurseurFinMur(xDebut_, yDebut_, x, y);
            }
            return curseurValide_;
        }
    }
}


