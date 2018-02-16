///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionLigne.cs
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

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionLigne
    /// @brief Classe decrivant l'etat d'edition d'une ligne
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionLigne : EtatEdition
    {
        private int nbSegment_ = 0;
        private int xCentreLigne_ = 0;
        private int yCentreLigne_ = 0;
        private int xDebut_;
        private int yDebut_;
        private int xFin_;
        private int yFin_;
        private string id;
        private int compteurDeplacement = 0;
        
        private bool activerSuppression_ = false;

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
            if ( curseurValide_ )
            {
                compteurDeplacement = 0;
                if ( !Edition.enTrace_ )
                {
                    xDebut_ = x;
                    yDebut_ = y;
                    xFin_ = x;
                    yFin_ = y;
                    Edition.enTrace_ = true;
                    id = Guid.NewGuid().ToString();
                    string line;
                    lock (Program.NoyauLock)
                    {
                        line = Marshal.PtrToStringAnsi(FonctionsNatives.ajouterNoeudSimple
                            (NOM_LIGNE, xDebut_, yDebut_, Program.edition.OnLine, id));
                    }
                    if (Program.edition.OnLine)
                        Program.SDispatcher.EditionConnectionM.SpreadCreateNode(line, true);
                }
                else if ( k == Keys.Control )
                {
                    mettreAJourLigne(x, y);
                    string line;
                    lock (Program.NoyauLock)
                    {
                        line = Marshal.PtrToStringAnsi(FonctionsNatives.ajouterNoeudAvecScale
                            (NOM_SEGMENT, xDebut_, yDebut_, xFin_, yFin_, true, Program.edition.OnLine));
                    }
                    if (Program.edition.OnLine)
                        Program.SDispatcher.EditionConnectionM.SpreadModifyNode(line, false);
                    else
                        Program.edition.marquerModificationDansLaScene();
                    xDebut_ = xFin_;
                    yDebut_ = yFin_;
                }
                else
                {
                    mettreAJourLigne(x, y);
                    if (activerSuppression_)
                    {
                        lock (Program.NoyauLock)
                        {
                            FonctionsNatives.supprimerDernierNoeud();
                        }
                    }
                    string line;
                    lock (Program.NoyauLock)
                    {
                        line = Marshal.PtrToStringAnsi(FonctionsNatives.ajouterNoeudAvecScale
                            (NOM_SEGMENT, xDebut_, yDebut_, xFin_, yFin_, true, Program.edition.OnLine));
                    }
                    if (Program.edition.OnLine)
                        Program.SDispatcher.EditionConnectionM.SpreadModifyNode(line, false);
                    else
                        Program.edition.marquerModificationDansLaScene();
                    Edition.enTrace_ = false;
                    activerSuppression_ = false;
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void mettreAJourLigne(int x, int y)
        ///
        /// Methode permettant la mise a jour d'une ligne en fonction de la
        /// position de la souris
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void mettreAJourLigne(int x, int y)
        {
            nbSegment_++;
            xFin_ = x;
            yFin_ = y;
            xCentreLigne_ = (xCentreLigne_ * (nbSegment_ - 1) + (xDebut_ + xFin_) / 2) / nbSegment_;
            yCentreLigne_ = (yCentreLigne_ * (nbSegment_ - 1) + (yDebut_ + yFin_) / 2) / nbSegment_;
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
                    FonctionsNatives.supprimerDerniereLigne();
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
            xFin_ = x;
            yFin_ = y; 
            if  ( curseurValide_ )
            {
                compteurDeplacement++;
                if ( Edition.enTrace_ )
                {
                    if ( activerSuppression_  /*&& !Program.edition.OnLine*/)
                    {
                        lock (Program.NoyauLock)
                        {
                            FonctionsNatives.supprimerDernierNoeud();
                        }
                    }
                    string line;
                    lock (Program.NoyauLock)
                    {
                        line = Marshal.PtrToStringAnsi(FonctionsNatives.ajouterNoeudAvecScale
                            (NOM_SEGMENT, xDebut_, yDebut_, xFin_, yFin_, false, Program.edition.OnLine, id));
                    }
                    if (Program.edition.OnLine && compteurDeplacement > 2)
                    {
                        Program.SDispatcher.EditionConnectionM.SpreadModifyNode(line, true);
                        compteurDeplacement = 0;
                    }
                    activerSuppression_ = true;
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool verifierCurseur(int x, int y)
        ///
        /// Methode permettant la verification de la position du curseur pour
        /// l'edition d'une ligne
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Vrai lorsque le curseur est dans la bonne position pour editer
        /// une ligne, faux autrement.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool verifierCurseur(int x, int y)
        {
            lock (Program.NoyauLock)
            {
                if (!Edition.enTrace_)
                    curseurValide_ = FonctionsNatives.verifierPositionCurseur(x, y);
                else
                    curseurValide_ = FonctionsNatives.verifierCurseurFinLigne(xDebut_, yDebut_, xFin_, yFin_);
            }
            return curseurValide_;
        }
    }
}
